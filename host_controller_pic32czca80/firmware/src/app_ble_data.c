/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

//This file contains code for storing and managing BLE related device data

#include "definitions.h"
#include "app.h"
#include "app_ble_data.h"
#include "app_ble.h"

//#define TEST_DUMMY_DEVICE 1

APP_BLE_DEVICE * activeDevice = NULL;
OSAL_MUTEX_DECLARE(bleDataMutex);

APP_BLE_DEVICE multiLinkDemoDevices[APP_BLE_DEVICE_MAX] = 
{
    {.idx = 0, .valid = true, .active = true, .deviceAddress = "001167930759", .deviceName = "BLE_SENSOR_0320"},    
    {.idx = 1, .valid = true, .active = true, .deviceAddress = "001167930752", .deviceName = "BLE_SENSOR_0317"},
    {.idx = 2, .valid = true, .active = true, .deviceAddress = "001167930758", .deviceName = "BLE_SENSOR_0898"},
};

APP_RESULT APP_BLE_SetDeviceAddr(uint32_t index, char * deviceAddr)
{
    if (deviceAddr == NULL || 
        index >= APP_BLE_DEVICE_MAX)
    {
        return APP_ERR_INV;
    }
    
    strncpy(multiLinkDemoDevices[index].deviceAddress, deviceAddr, DEVICE_ADDR_SIZE);
    
    //Use the last 4 digits of Address for default deviceName
    memcpy((void *) &multiLinkDemoDevices[index].deviceName[11],
           (const void *) &deviceAddr[8], 
           4);
    
    return APP_SUCCESS; 
}

void APP_BLE_InitData(void)
{
    
    OSAL_MUTEX_Create(&bleDataMutex);
    
    APP_ResetData();

}

void APP_ResetData(void)
{
    uint32_t i;
    
    for (i = 0; i < APP_BLE_DEVICE_MAX; i++)
    {
        multiLinkDemoDevices[i].tempSensorValue = DEFAULT_DEVICE_TEMP_VALUE_C;

#ifdef TEST_DUMMY_DEVICE
        multiLinkDemoDevices[i].connected = true;
#endif        
    }
}

void APP_BLED_SetActiveDevice(APP_BLE_DEVICE * device)
{
    OSAL_MUTEX_Lock(&bleDataMutex, OSAL_WAIT_FOREVER);
    
    activeDevice = device;
    
//    if (device != NULL)
//    {
//        printf("ActiveDevice set %s : %s \r\n",
//                    device->deviceAddress,
//                    device->deviceName);
//    }
    
    OSAL_MUTEX_Unlock(&bleDataMutex);
}

void APP_BLED_SetDeviceColor(uint32_t index, uint32_t rgb888)
{
    if (index < APP_BLE_DEVICE_MAX)
    {
        OSAL_MUTEX_Lock(&bleDataMutex, OSAL_WAIT_FOREVER);

        if (multiLinkDemoDevices[index].active == true && 
            multiLinkDemoDevices[index].connected == true)
        {
            multiLinkDemoDevices[index].rgb888 = rgb888;
        }
        
        OSAL_MUTEX_Unlock(&bleDataMutex);
    }
}

APP_RESULT APP_BLED_GetDeviceColor(uint32_t index, uint32_t * rgb888)
{
    if (index < APP_BLE_DEVICE_MAX)
    {
        OSAL_MUTEX_Lock(&bleDataMutex, OSAL_WAIT_FOREVER);

        *rgb888 = multiLinkDemoDevices[index].rgb888;

        OSAL_MUTEX_Unlock(&bleDataMutex);
        
        return APP_SUCCESS;
    }
    
    return APP_ERR_NOTFOUND;
}

APP_BLE_DEVICE * APP_BLED_GetActiveDevice(void)
{
    return activeDevice;
}

APP_BLE_DEVICE * APP_BLED_GetMultiLinkDemoDevice(uint32_t index)
{
    if (index >= APP_BLE_DEVICE_MAX)
        return NULL;
    
    return &multiLinkDemoDevices[index];    
}

//get the device from last 2 bytes of address
APP_BLE_DEVICE * APP_BLED_GetDeviceByShortAddr(APP_BLE_DEVICE * list, uint32_t listSize, char * addr2Byte)
{
    uint32_t i = 0;
    
    for (i = 0; i < listSize; i++)
    {
        if (strncmp(&list[i].deviceAddress[8], addr2Byte, 4) == 0)
        {
            return &list[i];
        }
    }
    
    return NULL;
}

APP_BLE_NOTIF_TYPE APP_BLED_ParseNotification(char * notifStr,
                                      uint32_t size,
                                      char * outAddr2Byte,
                                      uint32_t * outValue)
{
    char * temp;
    
    if (notifStr == NULL || outValue == NULL || outAddr2Byte == NULL || size < MIN_NOTIF_PACKET_SIZE)
        return NOTIF_INVALID;
    
    //make sure it's a valid notification string
    if ((strncmp(&notifStr[0], "NOTI", 4) != 0) ||
        (strncmp(&notifStr[10], "8A", 2) != 0))
        return NOTIF_INVALID;
    
    //Notif is of format: NOTI,<control UUID handle>,<0x8A><1B size><2B BT addr end><payload>
    
    //get device address
    strncpy(outAddr2Byte, &notifStr[14], 4);
            
    //LED notif
    if (strncmp(&notifStr[18], "40", 2) == 0)
    {
        *outValue = (notifStr[21] == '0') ? 0 : 1;
        
        return NOTIF_LED;
    }
    //Temp sensor
    else if (strncmp(&notifStr[18], "41", 2) == 0)
    {
       *outValue = strtol(&notifStr[20], &temp, 16);
        
        return NOTIF_TEMP;
    }
    
    return NOTIF_INVALID;
}

APP_RESULT APP_BLED_GetDeviceTemp(APP_BLE_DEVICE * device, APP_BLE_DEVICE_TEMP_UNIT unit, uint32_t * outValue)
{
    if (outValue == NULL)
        return APP_ERR_INV;
    
    if(device == NULL)
    {
        return APP_ERR_NOTFOUND;
    }
    
    //get temp in celsius
    if (unit == CELS)
    {
        *outValue = device->tempSensorValue / 10;
        
        *outValue = (*outValue == 0) ? DEFAULT_DEVICE_TEMP_VALUE_C : *outValue;
        
        return APP_SUCCESS;
    }
    else if (unit == FAHR)
    {
        *outValue = (((device->tempSensorValue * 9) / 5) / 10) + 32;
        
        *outValue = (*outValue == 0) ? DEFAULT_DEVICE_TEMP_VALUE_F : *outValue;
        
        return APP_SUCCESS;
    }
    
    return APP_ERR_INV;
}
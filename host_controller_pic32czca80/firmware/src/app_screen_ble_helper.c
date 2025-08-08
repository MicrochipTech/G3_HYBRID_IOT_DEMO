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

#include "definitions.h"
#include "app_config.h"
#include "app_ble.h"
#include "app_ble_data.h"
#include "app_ui.h"
#include "app_screen_ble_helper.h"
#include "app_utils.h"

APP_BLE_DEVICE * Screen_GetActiveDevice(void)
{
    return APP_BLED_GetActiveDevice();
}

void Screen_SetActiveDevice(APP_BLE_DEVICE * device)
{
    APP_BLED_SetActiveDevice(device);
}

APP_RESULT ConnectGetDeviceByName(APP_BLE_DEVICE * deviceList,
                                        uint32_t deviceCount,
                                        char * deviceName,
                                        char * deviceAddress)
{
    uint32_t i;
    
    if (deviceName == NULL || deviceAddress == NULL)
      return APP_ERR_INV;  

    for (i = 0; i < deviceCount; i++)
    {
        if (deviceList[i].valid == true && 
            strcmp(deviceName, deviceList[i].deviceName) == 0)
        {
            strcpy(deviceAddress, deviceList[i].deviceAddress);
            return APP_SUCCESS;
        }
    }
    
    return APP_ERR_NOTFOUND;
}

APP_RESULT Control_SendBLELEDOnOffMsg(APP_BLE_MSG * bleMsg, bool on, APP_BLE_DEVICE_ID device)
{
    bleMsg->param.data[APP_BLE_MSG_DATA_DEVICE] = device;
    bleMsg->param.data[APP_BLE_MSG_DATA_OPCODE] = 0x8a;
    bleMsg->param.data[APP_BLE_MSG_DATA_SIZE] = 0x02;
    bleMsg->param.data[APP_BLE_MSG_DATA_COMMAND] = 0x10;
    bleMsg->param.data[4] = (on == true) ? 0x01 : 0x00;
    bleMsg->parmsize = 5;
    bleMsg->cmd = (device == APP_BLE_DEVICE_ALL) ? APP_BLE_CMD_ML_CONTROL_CTRL_SET : APP_BLE_CMD_CONTROL_CTRL_SET;
    
    return APP_BLE_Send_Msg(bleMsg);
}

APP_RESULT Control_SendBLELEDColorSetMsg(APP_BLE_MSG * bleMsg, APP_UI_LED_CFG * ledCfg, APP_BLE_DEVICE_ID device)
{
    bleMsg->param.data[APP_BLE_MSG_DATA_DEVICE] = device;
    
   //generate the HSV values
    bleMsg->param.data[APP_BLE_MSG_DATA_OPCODE] = 0x8a; //opcode
    bleMsg->param.data[APP_BLE_MSG_DATA_SIZE] = 0x04; //size
    bleMsg->param.data[APP_BLE_MSG_DATA_COMMAND] = 0x12; //command
    
    APP_DPRINTF("Send BLE color 0x%08x \r\n", ledCfg->color888);

    RGB2HSV(gfxColorChannelRed(ledCfg->color888, GFX_COLOR_MODE_RGB_888),
            gfxColorChannelGreen(ledCfg->color888, GFX_COLOR_MODE_RGB_888),
            gfxColorChannelBlue(ledCfg->color888, GFX_COLOR_MODE_RGB_888),
            &bleMsg->param.data[4],
            &bleMsg->param.data[5],
            &bleMsg->param.data[6]);

    bleMsg->param.data[6] = (ledCfg->brightness * 255) / 100;
    
    bleMsg->parmsize = 7;

    bleMsg->cmd = (device == APP_BLE_DEVICE_ALL) ? APP_BLE_CMD_ML_CONTROL_CTRL_SET : APP_BLE_CMD_CONTROL_CTRL_SET;

    return APP_BLE_Send_Msg(bleMsg);   
}
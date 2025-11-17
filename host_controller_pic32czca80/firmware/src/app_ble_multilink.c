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
#include "app_utils.h"
#include "app_ble.h"
#include "app_ble_data.h"
#include "app_ble_task.h"
#include "app_config.h"

#define APP_BLE_CALLBACK_COUNT 16
#define APP_BLE_CMD_READ_BUFF_BYTES 256
#define APP_BLE_LINE_BUFF_BYTES 256
#define APP_BLE_CHUNK_BUFF_BYTES 64
#define APP_BLE_MAX_TRIES 5

#define APP_BLE_SYSFS_TIMEOUT_MSECS 10000
#define APP_BLE_SYSFS_WAIT_MSECS 1000

#define APP_BLE_DEVICES_CONFIG_FILE "bleCfg.txt"
#define APP_BLE_DEVICES_CONFIG_ADDR_SIZE 53
#define APP_BLE_DEVICES_CONFIG_DEVATAG "DEVA:"
#define APP_BLE_DEVICES_CONFIG_DEVBTAG "DEVB:"
#define APP_BLE_DEVICES_CONFIG_DEVCTAG "DEVC:"

#define DEFAULT_CONTROL_EP_HANDLE "00A7\0"

#define APP_BLE_QUEUE_WR_EMPTY (-1)
#define APP_BLE_QUEUE_RD_EMPTY (-2)

#if ENABLE_BLE_TASK_DEBUG
#define BLE_TASK_DPRINTF(fmt, ...) SYS_DEBUG_PRINT(SYS_ERROR_INFO, fmt, ##__VA_ARGS__)
#else
#define BLE_TASK_DPRINTF(...) 
#endif

#define BLE_TASK_ERROR(fmt, ...) SYS_DEBUG_PRINT(SYS_ERROR_INFO, fmt, ##__VA_ARGS__)


APP_BLE_TASK_OBJ appBleTask;
static APP_BLE_MSG msg;

static uint32_t bytesRead = 0;
static uint32_t tries;

static uint8_t cmdBuffer[APP_BLE_CMD_READ_BUFF_BYTES];
static uint8_t lineBuffer[APP_BLE_LINE_BUFF_BYTES];
static uint8_t chunkBuffer[APP_BLE_CHUNK_BUFF_BYTES];

static APP_BLE_DEVICE * currentDevice;
static uint32_t currentDeviceIdx;

struct
{
    int wr;
    int rd;
    APP_BLE_MSG appBLEMsg[APP_BLE_QUEUE_COUNT];
} appBLEMsgQueue;

APP_RESULT APP_BLE_Send_Msg(APP_BLE_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR_INV;
       
    //full
    if ((appBLEMsgQueue.wr == APP_BLE_QUEUE_COUNT - 1 && appBLEMsgQueue.rd == 0) ||
        (appBLEMsgQueue.wr == appBLEMsgQueue.rd - 1))
    {
        return APP_ERR_NOMEM;
    }   
    
    //empty
    if (appBLEMsgQueue.wr == APP_BLE_QUEUE_WR_EMPTY)
    {
        appBLEMsgQueue.wr = 0;
        appBLEMsgQueue.rd = 0;
    }
    else
    {
         appBLEMsgQueue.wr = (appBLEMsgQueue.wr + 1) % APP_BLE_QUEUE_COUNT;
    }
            
    appBLEMsgQueue.appBLEMsg[appBLEMsgQueue.wr] = *msg;
    
    return APP_SUCCESS;
}

APP_RESULT APP_BLE_Read_Msg(APP_BLE_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR;
    
        //empty
    if (appBLEMsgQueue.wr == APP_BLE_QUEUE_WR_EMPTY)
    {
        return APP_ERR_EMPTY;
    }
    
    memcpy(msg, &appBLEMsgQueue.appBLEMsg[appBLEMsgQueue.rd], sizeof(APP_BLE_MSG));
    
    if (appBLEMsgQueue.rd == appBLEMsgQueue.wr)
    {
        appBLEMsgQueue.wr = APP_BLE_QUEUE_WR_EMPTY;
        appBLEMsgQueue.rd = APP_BLE_QUEUE_RD_EMPTY;
    }
    else 
    {
        appBLEMsgQueue.rd = (appBLEMsgQueue.rd + 1) % APP_BLE_QUEUE_COUNT;
    }
    
    return APP_SUCCESS;
}


static void APP_BLE_ClearBuffers(void)
{
    memset(cmdBuffer, 0, APP_BLE_CMD_READ_BUFF_BYTES);
    memset(lineBuffer, 0, APP_BLE_LINE_BUFF_BYTES);
    memset(chunkBuffer, 0, APP_BLE_CHUNK_BUFF_BYTES);
}

static void APP_BLE_Notify(APP_BLE_NOTIFY_EVENT event, void * data, uint32_t size)
{
    uint32_t i;
    
    //Call all state callback functions
    for (i = 0; i < APP_BLE_CALLBACK_COUNT; i++)
    {
        if (appBleTask.notifCallbacks[i].func != NULL)
        {
            appBleTask.notifCallbacks[i].func(event, data, size);
        }
    }
}

static void APP_BLE_ChangeState(APP_BLE_TASK_STATE state)
{
    appBleTask.taskState = state;
    APP_BLE_Notify(APP_BLE_STATE_CHANGE, (void *) state, sizeof(state));
}

static void APP_BLE_ReadFlushUart(uint32_t waitMS)
{
    uint32_t bytesRead;
    
    //Flush all data
    do 
    {
        bytesRead = BLE_UART_Read(cmdBuffer, APP_BLE_CMD_READ_BUFF_BYTES);
        if (bytesRead > 0)
        {
            BLE_TASK_DPRINTF("FLUSH : %s \r\n", cmdBuffer);
        }
    } while (bytesRead > 0);

}

void BLE_UART_Callback_Func(SERCOM_USART_EVENT event, uintptr_t context )
{
//    BaseType_t xHigherPriorityTaskWoken = false;
    
    if (event == SERCOM_USART_EVENT_READ_THRESHOLD_REACHED)
    {
        msg.cmd = APP_BLE_DATA_READY;
        APP_BLE_Send_Msg(&msg);
//        xQueueSendFromISR(appBleTask.msgQueue, (const void *) &msg, &xHigherPriorityTaskWoken);
    }
}

void APP_BLE_Tasks(void)
{
    APP_RESULT result;
    
    switch(appBleTask.taskState)
    {
        case APP_BLE_STATE_WAIT:
        {
            if (APP_IsTimerExpired() == true)
            {
                APP_BLE_ChangeState(appBleTask.nextState);
            }
            
            break;
        }
        case APP_BLE_STATE_INIT:
        {
            BLE_Intf_Init(true);
            
            APP_ResetData();
            
            APP_BLE_ChangeState(APP_BLE_STATE_MODULE_INIT);            
            break;
        }
        case APP_BLE_STATE_MODULE_INIT:
        {
            APP_BLE_ReadFlushUart(1000);
            
            APP_BLE_ChangeState(APP_BLE_STATE_SYSFS_MOUNT);
            
            tries = 0;
            
            break;
        }
        case APP_BLE_STATE_SYSFS_MOUNT:
        {
            //Wait for FS to be mounted
            if (APP_SYSFSMounted())
            {
                APP_BLE_ChangeState(APP_BLE_STATE_GET_DEV_ADDR);
            }
            else
            {
                APP_StartWaitTimer(2000);
                appBleTask.nextState = APP_BLE_STATE_SYSFS_MOUNT;
                appBleTask.taskState = APP_BLE_STATE_WAIT;
                    
                if (++tries > 1000)
                {
                    //TODO: Send error message
                    //Use default addresses
                    APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
                }
            }
            
            break;
        }
        case APP_BLE_STATE_GET_DEV_ADDR:
        {
            appBleTask.cfgFileHandle = SYS_FS_FileOpen(APP_SYS_FS_MOUNT_POINT"/"APP_BLE_DEVICES_CONFIG_FILE, 
                                                      (SYS_FS_FILE_OPEN_READ));
            if(appBleTask.cfgFileHandle != SYS_FS_HANDLE_INVALID)
            {
                size_t size = SYS_FS_FileRead(appBleTask.cfgFileHandle, chunkBuffer, APP_BLE_CHUNK_BUFF_BYTES);
                
                if (size >= APP_BLE_DEVICES_CONFIG_ADDR_SIZE)
                {
                    char * devAddr;
                    
                    //get Device A
                    devAddr = strstr((const char *) chunkBuffer, APP_BLE_DEVICES_CONFIG_DEVATAG);
                    if (devAddr)
                    {
                        APP_BLE_SetDeviceAddr(APP_BLE_DEVICE_A, 
                                              devAddr + strlen(APP_BLE_DEVICES_CONFIG_DEVATAG));
                    }
                    
                    //get Device B
                    devAddr = strstr((const char *) chunkBuffer, APP_BLE_DEVICES_CONFIG_DEVBTAG);
                    if (devAddr)
                    {
                        APP_BLE_SetDeviceAddr(APP_BLE_DEVICE_B,
                                              devAddr + strlen(APP_BLE_DEVICES_CONFIG_DEVBTAG));
                    }
                    
                    //get Device C
                    devAddr = strstr((const char *) chunkBuffer, APP_BLE_DEVICES_CONFIG_DEVCTAG);
                    if (devAddr)
                    {
                        APP_BLE_SetDeviceAddr(APP_BLE_DEVICE_C,
                                              devAddr + strlen(APP_BLE_DEVICES_CONFIG_DEVCTAG));
                    }
                }
                    
                SYS_FS_FileClose(appBleTask.cfgFileHandle);
            }
            
            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            
            break;
        }
        case APP_BLE_STATE_IDLE:
        {
            if (APP_BLE_Read_Msg(&msg) == APP_SUCCESS)
            {
                switch(msg.cmd)
                {
                    case APP_BLE_CMD_CONNECT_START:
                    {
                        if (msg.device != NULL)    
                        {
                            tries = 0;
                            currentDevice = (APP_BLE_DEVICE *) msg.device;
                            
                            BLE_TASK_DPRINTF("Starting connection \r\n");
                            APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_INIT);
                        }

                        break;
                    }
                    case APP_BLE_CMD_CONNECT_MULTI_START:
                    {
                        if (msg.device != NULL)    
                        {
                            tries = 0;
                            
                            currentDevice = (APP_BLE_DEVICE *) msg.device;
                            
                            BLE_TASK_DPRINTF("Starting connection \r\n");
                            APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_START);
                        }

                        break;
                    }
                    case APP_BLE_CMD_CONTROL_START:
                    {
                        currentDeviceIdx = 0;
                        tries = 0;
                        
                        APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_INIT);
                        
                        break;
                    }
                    case APP_BLE_CMD_CONTROL_CTRL_SET:
                    {
                        APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_SET);
                        
                        break;
                    }                         
                    case APP_BLE_CMD_ML_CONTROL_CTRL_SET:
                    {
                        APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_CONNECTED_ML_CTRL_SET);

                        break;
                    }                    
                    case APP_BLE_CMD_CONNECT_STOP:
                    {
                        break;
                    }
                    case APP_BLE_CMD_ABORT:
                    {
                        APP_BLE_ChangeState(APP_BLE_STATE_INIT);
                        
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            //read a byte to check for notifications
            else
            {
                char * str, *endStr;

                //let's read the pipe for notifications
                bytesRead = BLE_UART_Read(lineBuffer,
                                          APP_BLE_LINE_BUFF_BYTES - 1);
                lineBuffer[bytesRead] = '\0';

                if (bytesRead > 0)
                {
                    BLE_TASK_DPRINTF("IDLE READ %s \r\n", lineBuffer);
                    
                    //process any notifications
                    str = strstr((const char *)lineBuffer, "NOTI");
                    if (str != NULL)
                    {                
                        do
                        {
                            endStr = strstr(str, "%");
                            APP_BLE_Notify(APP_BLE_DEVICE_NOTIFY,
                                           (void *) str,
                                            endStr - str);
                            str = strstr((const char *)endStr, "NOTI");
                        } while (str != NULL);
                    }
                }
                
            }
            
            break;
        }
        case APP_BLE_STATE_PROCESS_NOTIF:
        {
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_INIT:
        {
            result = BLE_Module_Write_Data((uint8_t *) "$$$", 3);
            if (result == APP_SUCCESS)
            {
                BLE_TASK_DPRINTF("UART MODE CMD WRITE SUCCESS \r\n");

                //FIXME DELAY
                APP_DelayMS(APP_BLE_SYSFS_WAIT_MSECS);
                
                APP_BLE_ReadFlushUart(100);
                
                appBleTask.taskState = APP_BLE_STATE_ML_CONNECT_START;
            }
            else
            {
                BLE_TASK_ERROR("ERROR : UART MODE CMD WRITE FAILED \r\n");

                appBleTask.taskState = APP_BLE_STATE_ML_CONNECT_FAILED;
            }
            
            APP_BLE_ChangeState(appBleTask.taskState);
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_START:
        {
            //build the connect command based on device address
            if (currentDevice != NULL && 
                currentDevice->deviceAddress != NULL)
            {
                tries += 1;
                
                APP_BLE_ClearBuffers();
                
                sprintf((char*) cmdBuffer, "C,0,%s\r", currentDevice->deviceAddress);
                
                BLE_TASK_DPRINTF("(%lu) CONNECT CMD: %s \r\n", tries, cmdBuffer);

                APP_BLE_ReadFlushUart(500);
                result = BLE_Module_Write_Data(cmdBuffer, strlen((const char *)cmdBuffer));
                if (result == APP_SUCCESS)
                {
                    BLE_TASK_DPRINTF("CONNECT CMD WRITE SUCCESS \r\n");
                    
                    APP_StartWaitTimer(5000);
                    appBleTask.nextState = APP_BLE_STATE_ML_CONNECT_CONNECTING;
                    appBleTask.taskState = APP_BLE_STATE_WAIT;
                }
                else
                {
                    BLE_TASK_ERROR("ERROR : CONNECT CMD WRITE FAILED \r\n");
                    
                    appBleTask.taskState = APP_BLE_STATE_ML_CONNECT_FAILED;
                }
            }
            else
            {
                BLE_TASK_ERROR("ERROR : Invalid device \r\n");
                
                appBleTask.taskState = APP_BLE_STATE_ML_CONNECT_FAILED;
            }
            
            APP_BLE_ChangeState(appBleTask.taskState);
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_CONNECTING:
        {
            char * str, *endStr;
            
            //let's read wait an entire line of connect response
            bytesRead = BLE_UART_Read_Wait(lineBuffer,
                                      APP_BLE_LINE_BUFF_BYTES - 1,
                                      100);
            lineBuffer[bytesRead] = '\0';
            
            if (bytesRead > 0)
            {
                str = strstr((const char *)lineBuffer, "CONNECT");
                if (str != NULL)
                {
                    //Get connection handle
                    str = strstr((const char *)str, "PHY_UPDATED");
                    if (str != NULL)
                    {
                        strncpy(currentDevice->connHandleStr, &str[12], 4);
                        
                        //Get control endpoint handle from notification
                        str = strstr((const char *)str, "NOTI");
                        if (str != NULL)
                        {
                            strncpy(currentDevice->ctrlHandleStr, &str[5], 4);
                            
                            //process all notifications
                            do
                            {
                                endStr = strstr(str, "%");
                                APP_BLE_Notify(APP_BLE_DEVICE_NOTIFY,
                                               (void *) str,
                                                endStr - str);
                                str = strstr((const char *)endStr, "NOTI");
                            } while (str != NULL);
                            
                            APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_CONNECTED);
                        }
                        else
                        {
                            BLE_TASK_ERROR("NOTI not found: %s \r\n", lineBuffer);
                            BLE_TASK_ERROR("Using default handle : %s \r\n", DEFAULT_CONTROL_EP_HANDLE);
                            
                            strncpy(currentDevice->ctrlHandleStr, DEFAULT_CONTROL_EP_HANDLE, 5);
                            
                            APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_CONNECTED);
                        }
                        
                    }
                    else
                    {
                        BLE_TASK_DPRINTF("PHY_UPDATED not found: %s \r\n", lineBuffer);
                        
                        APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_DEVICE_FAILED);
                    }
                    
                    //Device is connected but response is invalid, disconnect
                    if (appBleTask.taskState == APP_BLE_STATE_ML_CONNECT_DEVICE_FAILED)
                    {
                        //Disconnect from device (in case was connected)
                        sprintf((char*) cmdBuffer, "k,1,%s\r", currentDevice->connHandleStr);
                        BLE_TASK_DPRINTF("DISCONNECT CMD: %s \r\n", cmdBuffer);
                        result = BLE_Module_Write_Data(cmdBuffer, strlen((const char *)cmdBuffer));
                        
                        APP_BLE_ReadFlushUart(100);                        
                    }
                }
                //Failed to get a response
                else 
                {
                    BLE_TASK_DPRINTF("CONNECT not found: %s \r\n", lineBuffer);
                    
                    //Cancel connect process if still active
                    sprintf((char*) cmdBuffer, "z\r");
                    BLE_TASK_DPRINTF("CANCEL CONNECT: %s \r\n", cmdBuffer);
                    result = BLE_Module_Write_Data(cmdBuffer, strlen((const char *)cmdBuffer));
                    
                    APP_BLE_ReadFlushUart(100);
                    
                    if (tries >= APP_BLE_MAX_TRIES)
                    {
                        APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_DEVICE_FAILED);
                    }
                    else
                    {
                        APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_START);
                    }
                }
            }
            else
            {
                BLE_TASK_DPRINTF("Response timeout \r\n");
                 
                //Cancel connect process if still active
                sprintf((char*) cmdBuffer, "z\r");
                BLE_TASK_DPRINTF("CANCEL CONNECT: %s \r\n", cmdBuffer);
                result = BLE_Module_Write_Data(cmdBuffer, strlen((const char *)cmdBuffer));
                    
                APP_BLE_ReadFlushUart(100);
                
                if (tries >= APP_BLE_MAX_TRIES)
                {
                    APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_DEVICE_FAILED);
                }
                else
                {
                    APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_START);
                }
            }
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_CONNECTED:
        {
            currentDevice->connected = true;
            
            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_INIT:
        {
            //Enable client mode on all connected handles
            if (currentDeviceIdx < APP_BLE_DEVICE_MAX )
            {
                APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(currentDeviceIdx);
                
                if ((device != NULL) &&
                    (device->connected == true) &&
                    (device->active == true))
                {
                    sprintf((char *) cmdBuffer, "CI,%s\r", device->connHandleStr);
                    BLE_TASK_DPRINTF("CI Write : %s \r\n", cmdBuffer);

                    //send command
                    result = BLE_Module_Write_Data(cmdBuffer, strlen((const char*) cmdBuffer));
                    //wait for response
                    appBleTask.taskState = APP_BLE_STATE_WAIT;
                    APP_StartWaitTimer(500);
                    appBleTask.nextState = APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_CHECK;
                }
            }     
            
            APP_BLE_ChangeState(appBleTask.taskState);
                
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_CHECK:
        {
            char * str;

            tries++;
            
            bytesRead = BLE_UART_Read_Wait(lineBuffer,
                                      APP_BLE_LINE_BUFF_BYTES - 1,
                                      100);
            if (bytesRead > 0)
            {
                lineBuffer[bytesRead] = '\0';
                str = strstr((const char *)lineBuffer, "AOK");

                if (str != NULL)
                {
                    BLE_TASK_DPRINTF("CI command Success : (%lu) tries\r\n", tries);
                }
                else
                {
                    BLE_TASK_ERROR("BLE ERR: Failed CI command \r\n");
                    
                    if (tries > APP_BLE_MAX_TRIES)
                    {
                        //max tries, how to handle?
                    }
                }
                
                currentDeviceIdx++;
                if (currentDeviceIdx >= APP_BLE_DEVICE_MAX )
                {
                    APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_READY);
                }
                else
                {
                    tries = 0;
                    APP_BLE_ChangeState(APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_INIT);
                }                
            }
            
            
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_READY:
        {
            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            
            break;
        }        
        case APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_SET:
        {
            APP_BLE_DEVICE * device;
            uint8_t index = msg.param.data[APP_BLE_MSG_DATA_DEVICE];
            
            if (index < APP_BLE_DEVICE_MAX)
            {
                device = APP_BLED_GetMultiLinkDemoDevice(index);
            
                if ((device != NULL) &&
                    (device->connected == true) &&
                    (device->active == true))
                {
                    uint32_t i = APP_BLE_MSG_DATA_OPCODE;
                    uint32_t length = 0;

                    length = sprintf((char *) cmdBuffer, "CHWM,%s,%s,", device->connHandleStr, device->ctrlHandleStr);
                    if (msg.param.data[i] > 0 && length + msg.parmsize < APP_BLE_CMD_READ_BUFF_BYTES - 2)
                    {
                        for (i = APP_BLE_MSG_DATA_OPCODE; i < msg.parmsize; i++)
                        {
                            length += sprintf((char*) &cmdBuffer[length], "%02x", msg.param.data[i]);
                        }

                        BLE_TASK_DPRINTF("Control Write : %s \r\n", cmdBuffer);

                        cmdBuffer[length] = '\r';
                        cmdBuffer[length + 1] = '\0';

                        result = BLE_Module_Write_Data(cmdBuffer, strlen((const char*) cmdBuffer));
                        if (result == APP_SUCCESS)
                        {
                            appBleTask.taskState = APP_BLE_STATE_CONNECT_CONNECTED_CTRL_SET_DONE;
                        }
                    }
                    else
                    {
                        BLE_TASK_ERROR("BLE ERR: Command Parameter is invalid or too long \r\n");
                    }          
                }
            }
            
            //send command to all ML connected devices
            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_CONNECTED_ML_CTRL_SET:
        {
            uint32_t i = 0;
            
            for (i = 0; i < APP_BLE_DEVICE_MAX; i++)
            {
                APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);
                 
                if ((device != NULL) &&
                    (device->connected == true) &&
                    (device->active == true))
                {
                    uint32_t i = APP_BLE_MSG_DATA_OPCODE;
                    uint32_t length = 0;
                    
                    length = sprintf((char *) cmdBuffer, "CHWM,%s,%s,", device->connHandleStr, device->ctrlHandleStr);
                    if (msg.param.data[i] > 0 && length + msg.parmsize < APP_BLE_CMD_READ_BUFF_BYTES - 2)
                    {

                        for (i = APP_BLE_MSG_DATA_OPCODE; i < msg.parmsize; i++)
                        {
                            length += sprintf((char*) &cmdBuffer[length], "%02x", msg.param.data[i]);
                        }

                        BLE_TASK_DPRINTF("Control Write : %s \r\n", cmdBuffer);

                        cmdBuffer[length] = '\r';
                        cmdBuffer[length + 1] = '\0';

                        result = BLE_Module_Write_Data(cmdBuffer, strlen((const char*) cmdBuffer));
                        if (result == APP_SUCCESS)
                        {
                            appBleTask.taskState = APP_BLE_STATE_CONNECT_CONNECTED_CTRL_SET_DONE;
                        }
                    }
                    else
                    {
                        BLE_TASK_ERROR("BLE ERR: Command Parameter is invalid or too long \r\n");
                    }
                }
            }
            //send command to all ML connected devices
            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            
            break;
        }
        case APP_BLE_STATE_CONNECT_CONNECTED_CTRL_SET_DONE:
        {
            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_FAILED:
        {
            //FIXME RESET???
//            xQueueReset(appBleTask.msgQueue);
            
            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            
            break;
        }
        case APP_BLE_STATE_ML_CONNECT_DEVICE_FAILED:
        {
            currentDevice->connected = false;

            BLE_TASK_ERROR("BLE ERR: Failed to connect =, %s \r\n", currentDevice->deviceAddress);

            APP_BLE_ChangeState(APP_BLE_STATE_IDLE);
            break;
        }
        default:
            break;
    }
}

void APP_BLE_Initialize(void)
{
    //initialize the msg queue
    appBLEMsgQueue.rd = APP_BLE_QUEUE_RD_EMPTY;
    appBLEMsgQueue.wr = APP_BLE_QUEUE_WR_EMPTY;
    memset(appBLEMsgQueue.appBLEMsg, 0, sizeof(APP_BLE_MSG) * APP_BLE_QUEUE_COUNT);
            
    memset(&msg, 0, sizeof(APP_BLE_MSG));
    memset(appBleTask.notifCallbacks, 0, sizeof(APP_BLE_NOTIF_CALLBACK) * APP_BLE_NOTIF_CALLBACK_COUNT);    
    
    APP_BLE_InitData();
    
    //FIXME INITIALIZE QUEUE
//    appBleTask.msgQueue = xQueueCreate(APP_BLE_QUEUE_LENGTH, sizeof(APP_BLE_MSG));
    appBleTask.taskState = APP_BLE_STATE_INIT;
}
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
#include "app_ble_task.h"
#include "app_screen_ble_helper.h"
#include "app_macros.h"

#define DEVICE_ACTIVE_IMAGE_ID 0
#define DEVICE_INACTIVE_IMAGE_ID 1

#define CONNECT_POSY_HIDE_BOTTOM 480
#define DEVICE_ICON_POSX_HIDE_LEFT -80
#define DEVICE_ICON_POSX_HIDE_RIGHT 800
#define DEVICE_ANIM_COEFF 3

#define READY_ICON_YSHOW_POS 260

#define MAX_STATUS_LABEL_LENGTH 12

typedef enum
{
    ML_CONNECT_INIT,
    ML_CONNECT_ANIM0,
    ML_CONNECT_ANIM1,
    ML_CONNECT_ANIM2,
    ML_CONNECT_ANIM3,
    ML_CONNECT_ANIM_DONE,
    ML_CONNECT_START_CONNECT,
    ML_CONNECT_CONNECTING,
    ML_CONNECT_DEVICE_CONNECTED,
    ML_CONNECT_DEVICE_INACTIVE,
    ML_CONNECT_DEVICE_FAILED,
    ML_CONNECT_FAILED,
    ML_CONNECT_CONNECTED_INIT,
    ML_CONNECT_CONNECTED_INIT_DONE,
    ML_CONNECT_CONNECTED_READY,
    ML_CONNECT_CONNECTED_EXIT,
    ML_CONNECT_MAX_STATES,
} ML_CONNECT_SCREEN_STATE;

typedef struct
{
    leImageSequenceWidget * deviceImage;  
    leLabelWidget * deviceLabel;
    leImageWidget * deviceStatusIcon;
    uint32_t xpos;
    uint32_t ypos;  
} ML_CONNECT_DEVICE;

#ifdef ENABLE_UI_DEBUG
static char * appScreenUIStates[ML_CONNECT_MAX_STATES] = 
{
    "ML_CONNECT_INIT",
    "ML_CONNECT_ANIM0",
    "ML_CONNECT_ANIM1",
    "ML_CONNECT_ANIM2",
    "ML_CONNECT_ANIM3",
    "ML_CONNECT_ANIM_DONE",
    "ML_CONNECT_START_CONNECT",
    "ML_CONNECT_CONNECTING",
    "ML_CONNECT_DEVICE_CONNECTED",
    "ML_CONNECT_DEVICE_INACTIVE",
    "ML_CONNECT_DEVICE_FAILED",
    "ML_CONNECT_FAILED",
    "ML_CONNECT_CONNECTED_INIT",
    "ML_CONNECT_CONNECTED_INIT_DONE",
    "ML_CONNECT_CONNECTED_READY",
    "ML_CONNECT_CONNECTED_EXIT",
};
#endif

static ML_CONNECT_SCREEN_STATE appScreenMLConnectState;
static ML_CONNECT_DEVICE devices[APP_BLE_DEVICE_MAX] = {0};
static APP_BLE_DEVICE_ID currentDevice = APP_BLE_DEVICE_A;
static uint32_t bleCallbackIdx;
static uint32_t connectedDevicesCount = 0;

static SYS_TIME_HANDLE mlConnectAnimTimer = SYS_TIME_HANDLE_INVALID;
static SYS_TIME_HANDLE mlConnectProgressTimer = SYS_TIME_HANDLE_INVALID;

static volatile uint32_t mlConnectProgressTickCount = 0;
static uint32_t mlConnectProgressTickPrev = 0;
static volatile uint32_t mlConnectAnimTickCount = 0;
static uint32_t mlConnectAnimTickPrev = 0;
static APP_UI_MSG uiMsg = {0};
static APP_BLE_MSG bleMsg = {0};

static leFixedString statusStr;
static leChar statusStrBuff[MAX_STATUS_LABEL_LENGTH] = {0};


static void MLConnect_UpdateStatusString(char * str);
static void MLConnectAnimTimer_Callback (uintptr_t context);
static void MLConnectProgressTimer_Callback (uintptr_t context);
static void MLConnect_InitDeviceTable(void);
static void MLConnectSetState(ML_CONNECT_SCREEN_STATE state);

void event_MultiLinkConnectScreen_HomeButton_OnPressed(leButtonWidget* btn)
{
    APP_UI_SendEvent(APP_EVENT_UI_HOME);
}

void MultiLinkConnectScreen_OnShow(void)
{
    MLConnectSetState(ML_CONNECT_INIT);
    
    MLConnect_InitDeviceTable();
    
    leFixedString_Constructor(&statusStr, statusStrBuff, MAX_STATUS_LABEL_LENGTH);
    statusStr.fn->setFont(&statusStr, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              stringID_ConnectingString,
                                                              0));
    
    APP_LE_SETX(devices[APP_BLE_DEVICE_A].deviceImage, DEVICE_ICON_POSX_HIDE_RIGHT);
    
    APP_LE_SETX(devices[APP_BLE_DEVICE_B].deviceImage, DEVICE_ICON_POSX_HIDE_RIGHT);
   
    APP_LE_SETX(devices[APP_BLE_DEVICE_C].deviceImage, DEVICE_ICON_POSX_HIDE_RIGHT);
    
    APP_LE_SETY(MultiLinkConnectScreen_ControlButton, CONNECT_POSY_HIDE_BOTTOM);    
    
    APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_A].deviceStatusIcon, LE_FALSE);
    APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_B].deviceStatusIcon, LE_FALSE);
    APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_C].deviceStatusIcon, LE_FALSE);
    
    APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_A].deviceLabel, LE_FALSE);
    APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_B].deviceLabel, LE_FALSE);
    APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_C].deviceLabel, LE_FALSE);
    
    APP_LE_SHOWIMAGE_IDX(devices[APP_BLE_DEVICE_A].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
    APP_LE_SHOWIMAGE_IDX(devices[APP_BLE_DEVICE_B].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
    APP_LE_SHOWIMAGE_IDX(devices[APP_BLE_DEVICE_C].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
    
    APP_LE_SETVISIBLE(MultiLinkConnectScreen_HomeButton, LE_FALSE);
    APP_LE_SETVISIBLE(MultiLinkConnectScreen_ProgressAnimSequence, LE_FALSE);
    APP_LE_SETVISIBLE(MultiLinkConnectScreen_ConnectionStatusLabel, LE_FALSE);
    
    bleCallbackIdx = APP_BLE_RegisterStateNotification(APP_UI_BLE_EventCallback);    

    
    mlConnectAnimTickCount = 0;
    mlConnectAnimTimer = SYS_TIME_CallbackRegisterMS(MLConnectAnimTimer_Callback,
                                                     1, ANIM_TIMER_TICK_PERIOD_MS,
                                                     SYS_TIME_PERIODIC);
    
    mlConnectProgressTimer =  SYS_TIME_CallbackRegisterMS(MLConnectProgressTimer_Callback,
                                                    1, PROGRESS_TIMER_TICK_PERIOD_MS,
                                                    SYS_TIME_PERIODIC);
            
    SYS_TIME_TimerStop(mlConnectAnimTimer);
    SYS_TIME_TimerStop(mlConnectProgressTimer);
}

void MultiLinkConnectScreen_OnHide(void)
{
    statusStr.fn->destructor(&statusStr);
    
    SYS_TIME_TimerDestroy(mlConnectAnimTimer);
    SYS_TIME_TimerDestroy(mlConnectProgressTimer);
    
    APP_BLE_UnregisterStateNotification(bleCallbackIdx);
}

void event_MultiLinkConnectScreen_ControlButton_OnPressed(leButtonWidget* btn)
{
    APP_UI_SendEvent(APP_EVENT_UI_START_CONTROL);
}

void MultiLinkConnectScreen_OnUpdate(void)
{
    switch(appScreenMLConnectState)
    {
        case ML_CONNECT_INIT:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            currentDevice = APP_BLE_DEVICE_A;
            connectedDevicesCount = 0;
            
            SYS_TIME_TimerStart(mlConnectAnimTimer);     
            
            MLConnectSetState(ML_CONNECT_ANIM0);
            
            break;
        }
        case ML_CONNECT_ANIM0:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;      
            
            if (mlConnectAnimTickCount != mlConnectAnimTickPrev)
            {
                int32_t xpos = APP_LE_GETX(devices[APP_BLE_DEVICE_A].deviceImage);
                int32_t deltaX = (xpos - devices[APP_BLE_DEVICE_A].xpos) / DEVICE_ANIM_COEFF;
                
            
                MLConnectSetState(ML_CONNECT_ANIM1);
                
                if (deltaX > 0)
                {
                    APP_LE_SETX(devices[APP_BLE_DEVICE_A].deviceImage, xpos - deltaX);
                    
                    MLConnectSetState(ML_CONNECT_ANIM0);
                }
                else
                {
                    APP_LE_SETX(devices[APP_BLE_DEVICE_A].deviceImage, devices[APP_BLE_DEVICE_A].xpos);
                }
                
                mlConnectAnimTickPrev = mlConnectAnimTickCount;
            }
            // Go to Sustainability Wall
            
            legato_showScreen(screenID_SWallControlScreen);
            
            break;
        }
        case ML_CONNECT_ANIM1:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;      
            
            if (mlConnectAnimTickCount != mlConnectAnimTickPrev)
            {
                int32_t xpos = APP_LE_GETX(devices[APP_BLE_DEVICE_B].deviceImage);
                int32_t deltaX = (xpos - devices[APP_BLE_DEVICE_B].xpos) / DEVICE_ANIM_COEFF;
                
            
                MLConnectSetState(ML_CONNECT_ANIM2);
                
                if (deltaX > 0)
                {
                    APP_LE_SETX(devices[APP_BLE_DEVICE_B].deviceImage, xpos - deltaX);
                    
                    MLConnectSetState(ML_CONNECT_ANIM1);
                }
                else
                {
                    APP_LE_SETX(devices[APP_BLE_DEVICE_B].deviceImage, devices[APP_BLE_DEVICE_B].xpos);
                }
                
                mlConnectAnimTickPrev = mlConnectAnimTickCount;
            }
            
            break;
        }
        case ML_CONNECT_ANIM2:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlConnectAnimTickCount != mlConnectAnimTickPrev)
            {
                int32_t xpos = APP_LE_GETX(devices[APP_BLE_DEVICE_C].deviceImage);
                int32_t deltaX = (xpos - devices[APP_BLE_DEVICE_C].xpos) / DEVICE_ANIM_COEFF;
                
                MLConnectSetState(ML_CONNECT_ANIM3);
                
                if (deltaX > 0)
                {
                    APP_LE_SETX(devices[APP_BLE_DEVICE_C].deviceImage, xpos - deltaX);
                    
                    MLConnectSetState(ML_CONNECT_ANIM2);
                }
                else
                {
                    APP_LE_SETX(devices[APP_BLE_DEVICE_C].deviceImage, devices[APP_BLE_DEVICE_C].xpos);
                }
                
                mlConnectAnimTickPrev = mlConnectAnimTickCount;
            }
            
            break;
        }
        case ML_CONNECT_ANIM3:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;

            APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_A].deviceLabel, LE_TRUE);
            APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_B].deviceLabel, LE_TRUE);
            APP_LE_SETVISIBLE(devices[APP_BLE_DEVICE_C].deviceLabel, LE_TRUE);

            APP_LE_SETVISIBLE(MultiLinkConnectScreen_HomeButton, LE_TRUE);
            
            MLConnectSetState(ML_CONNECT_ANIM_DONE);
            break;
        }
        case ML_CONNECT_ANIM_DONE:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            APP_LE_SHOWIMAGE_IDX(devices[APP_BLE_DEVICE_A].deviceImage, DEVICE_INACTIVE_IMAGE_ID);
            APP_LE_SHOWIMAGE_IDX(devices[APP_BLE_DEVICE_B].deviceImage, DEVICE_INACTIVE_IMAGE_ID);
            APP_LE_SHOWIMAGE_IDX(devices[APP_BLE_DEVICE_C].deviceImage, DEVICE_INACTIVE_IMAGE_ID);
            
            APP_LE_SETVISIBLE(MultiLinkConnectScreen_ProgressAnimSequence, LE_TRUE);
            APP_LE_SETVISIBLE(MultiLinkConnectScreen_ConnectionStatusLabel, LE_TRUE);

            SYS_TIME_TimerStop(mlConnectAnimTimer);
            
            mlConnectProgressTickCount = 0;
            SYS_TIME_TimerStart(mlConnectProgressTimer);                            
            
            MLConnectSetState(ML_CONNECT_START_CONNECT);
            
            currentDevice = APP_BLE_DEVICE_A;
                        
            break;
        }
        case ML_CONNECT_START_CONNECT:
        {
            APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(currentDevice);
                        
            if (device != NULL)
            {
                if (device->valid == true)
                {
                    bleMsg.device = device;
                    
                    APP_BLED_SetActiveDevice(device);

                    mlConnectProgressTickCount = 0;
                    SYS_TIME_TimerStart(mlConnectProgressTimer);

                    if (currentDevice >= APP_BLE_DEVICE_C)
                    {
                        bleMsg.cmd = APP_BLE_CMD_CONNECT_MULTI_START;
                    }
                    else
                    {
                        bleMsg.cmd = APP_BLE_CMD_CONNECT_START;
                    }

                    APP_BLE_Send_Msg(&bleMsg); 

                    MLConnectSetState(ML_CONNECT_CONNECTING);
                }
                else
                {
                    MLConnectSetState(ML_CONNECT_DEVICE_INACTIVE);
                }
            }
            else
            {
                MLConnectSetState(ML_CONNECT_FAILED);
            }
                            
            
            break;
        }
        case ML_CONNECT_CONNECTING:
        {
            //Check progress timer
            if (mlConnectProgressTickPrev != mlConnectProgressTickCount)
            {
                APP_UI_SendEvent(APP_EVENT_UI_PROGRESS_TIMER);
                
                mlConnectProgressTickPrev = mlConnectProgressTickCount;
            }
            
            if (APP_UI_ReadMsg(&uiMsg) == APP_SUCCESS)
            {
                switch(uiMsg.event)
                {
                    case APP_EVENT_UI_HOME:
                    {
                        bleMsg.cmd = APP_BLE_CMD_ABORT;
                        APP_BLE_Send_Msg(&bleMsg);
                        
                        mlConnectProgressTickCount = 0;
                        SYS_TIME_TimerStop(mlConnectAnimTimer);
                        SYS_TIME_TimerStop(mlConnectProgressTimer);

                        legato_showScreen(screenID_MainMenu);

                        break;
                    }
                    case APP_EVENT_UI_PROGRESS_TIMER:
                    {
                        APP_LE_SHOWIMAGE_NEXT(MultiLinkConnectScreen_ProgressAnimSequence);
                        APP_LE_SHOWIMAGE_NEXT(devices[currentDevice].deviceImage);
                        
                        //Connection Timeout
                        if (mlConnectProgressTickCount > MULTILINK_CONNECT_TIMEOUT_COUNTS)
                        {
                            //TBD: Handle connection timeout
                        }
                        
                        break;
                    }
                    case APP_EVENT_BLE_CONNECTING:
                    {
                        APP_LE_SETVISIBLE(MultiLinkConnectScreen_ConnectionStatusLabel, LE_TRUE);
                        MLConnect_UpdateStatusString("Connecting");
                        
                        break;
                    }
                    case APP_EVENT_BLE_CONNECTED:
                    {
                        
                        APP_LE_SETVISIBLE(devices[currentDevice].deviceStatusIcon, true);
                        APP_LE_SHOWIMAGE_IDX(devices[currentDevice].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
                        MLConnect_UpdateStatusString("Connected");
                        
                        connectedDevicesCount++;
                        
                        Screen_GetActiveDevice()->active = true;
                        Screen_GetActiveDevice()->connected = true;
                        
                        MLConnectSetState(ML_CONNECT_DEVICE_CONNECTED);
                        
                        break;
                    }
                    case APP_EVENT_BLE_DEVICE_NOTIFY:
                    {
                        APP_BLE_NOTIF_TYPE notifType;
                        char outAddr2Byte[4];
                        uint32_t outValue;
                        APP_BLE_DEVICE * device;

                        uiMsg.param.data[uiMsg.parmSize] = '\0';
                        
                        UI_DPRINTF("UI: Notif received %s \r\n", uiMsg.param.data);
                        
                        notifType = APP_BLED_ParseNotification((char *) uiMsg.param.data,
                                                               uiMsg.parmSize,
                                                               outAddr2Byte,
                                                               &outValue);
                        if (notifType != NOTIF_INVALID)
                        {
                            device = APP_BLED_GetDeviceByShortAddr(
                                                multiLinkDemoDevices,
                                                APP_BLE_DEVICE_MAX,
                                                outAddr2Byte);

                            if (device != NULL)
                            {
                                if (notifType == NOTIF_LED)
                                {
                                    device->led.onoff = (outValue == 0) ? 0 : 1;
                                }
                                else if (notifType == NOTIF_TEMP)
                                {
                                    device->tempSensorValue = outValue;
                                }
                            }
                        }
                        
                        break;
                    }
                    case APP_EVENT_BLE_DEVICE_CONNECT_FAILED:
                    {
                        APP_LE_SHOWIMAGE_IDX(devices[currentDevice].deviceImage, DEVICE_INACTIVE_IMAGE_ID);
                        MLConnect_UpdateStatusString("Failed");
                        
                        Screen_GetActiveDevice()->connected = false;
                        
                        MLConnectSetState(ML_CONNECT_DEVICE_FAILED);
                        
                        break;
                    }
                    
                    default:
                        break;
                }
            }

            break;
        }
        case ML_CONNECT_DEVICE_FAILED:
        case ML_CONNECT_DEVICE_INACTIVE: //no break;
        case ML_CONNECT_DEVICE_CONNECTED:
        {
            currentDevice++;
                        
            if (currentDevice >= APP_BLE_DEVICE_MAX)
            {
                if (connectedDevicesCount > 0)
                {
                    bleMsg.cmd = APP_BLE_CMD_CONTROL_START;
                    APP_BLE_Send_Msg(&bleMsg);
                    
                    MLConnect_UpdateStatusString("Preparing");
                    
                    MLConnectSetState(ML_CONNECT_CONNECTED_INIT);
                }
                else //No devices connected
                {
                    MLConnectSetState(ML_CONNECT_FAILED);
                }
            }
            else
            {
                MLConnectSetState(ML_CONNECT_START_CONNECT);
            }
            
            break;
        }
        case ML_CONNECT_FAILED:
        {
            //back to home
            bleMsg.cmd = APP_BLE_CMD_ABORT;
            APP_BLE_Send_Msg(&bleMsg);
            
            legato_showScreen(screenID_MainMenu);
            
            break;
        }
        case ML_CONNECT_CONNECTED_INIT:
        {
            //Check progress timer
            if (mlConnectProgressTickPrev != mlConnectProgressTickCount)
            {
                APP_UI_SendEvent(APP_EVENT_UI_PROGRESS_TIMER);
                
                mlConnectProgressTickPrev = mlConnectProgressTickCount;
            }
            
            if (APP_UI_ReadMsg(&uiMsg) == APP_SUCCESS)
            {
                switch(uiMsg.event)
                {
                    case APP_EVENT_UI_PROGRESS_TIMER:
                    {
                        APP_LE_SHOWIMAGE_NEXT(MultiLinkConnectScreen_ProgressAnimSequence);
                           
                        //Connection Timeout
                        if (mlConnectProgressTickCount > MULTILINK_CONNECT_TIMEOUT_COUNTS)
                        {
                            //TBD: Handle connection timeout
                        }
                        
                        break;
                    }                    
                    case APP_EVENT_BLE_CONTROL_READY:
                    {
                        APP_LE_SETVISIBLE(MultiLinkConnectScreen_ProgressAnimSequence, LE_FALSE);

                        MLConnect_UpdateStatusString("Ready");
                        
                        SYS_TIME_TimerStop(mlConnectProgressTimer);
                        
                        SYS_TIME_TimerStart(mlConnectAnimTimer);                     
                        MLConnectSetState(ML_CONNECT_CONNECTED_INIT_DONE);
                        
                        break;
                    }
                    default:
                        break;
                }
            }
            break;
        }
        case ML_CONNECT_CONNECTED_INIT_DONE:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlConnectAnimTickCount != mlConnectAnimTickPrev)
            {
                int32_t ypos = APP_LE_GETY(MultiLinkConnectScreen_ControlButton);
                int32_t deltaY = (ypos - READY_ICON_YSHOW_POS) / DEVICE_ANIM_COEFF;
                
                if (deltaY > 0)
                {
                    APP_LE_SETY(MultiLinkConnectScreen_ControlButton, ypos - deltaY);
                    
                }
                else
                {
                    SYS_TIME_TimerStop(mlConnectAnimTimer);
                    
                    MLConnectSetState(ML_CONNECT_CONNECTED_READY);
                    
                    APP_LE_SETY(MultiLinkConnectScreen_ControlButton, READY_ICON_YSHOW_POS);
                }
                
                mlConnectAnimTickPrev = mlConnectAnimTickCount;
            }

            break;
        }
        case ML_CONNECT_CONNECTED_READY:
        {
            if (APP_UI_ReadMsg(&uiMsg) == APP_SUCCESS)
            {
                switch(uiMsg.event)
                {
                    case APP_EVENT_UI_HOME:
                    {
                        bleMsg.cmd = APP_BLE_CMD_ABORT;
                        APP_BLE_Send_Msg(&bleMsg);
                        
                        mlConnectProgressTickCount = 0;

                        legato_showScreen(screenID_MainMenu);

                        break;
                    }
                    case APP_EVENT_BLE_DEVICE_NOTIFY:
                    {
                        APP_BLE_NOTIF_TYPE notifType;
                        char outAddr2Byte[4];
                        uint32_t outValue;
                        APP_BLE_DEVICE * device;
                        
                        uiMsg.param.data[uiMsg.parmSize] = '\0';
                        
                        notifType = APP_BLED_ParseNotification((char *) uiMsg.param.data,
                                                               uiMsg.parmSize,
                                                               outAddr2Byte,
                                                               &outValue);
                        if (notifType != NOTIF_INVALID)
                        {
                            device = APP_BLED_GetDeviceByShortAddr(
                                                multiLinkDemoDevices,
                                                APP_BLE_DEVICE_MAX,
                                                outAddr2Byte);

                            if (device != NULL)
                            {
                                if (notifType == NOTIF_LED)
                                {
                                    UI_DPRINTF("UI: LED Notif %lu \r\n", outValue);
                                    
                                    device->led.onoff = (outValue == 0) ? 0 : 1;
                                }
                                else if (notifType == NOTIF_TEMP)
                                {
                                    UI_DPRINTF("UI: TEMP Notif %lu \r\n", outValue);
                                    
                                    device->tempSensorValue = outValue;
                                }
                            }
                        }

                        break;
                    }
                    case APP_EVENT_UI_START_CONTROL:
                    {
                        SYS_TIME_TimerStart(mlConnectAnimTimer);
                        
                        MLConnectSetState(ML_CONNECT_CONNECTED_EXIT);
                        
                        break;
                    }
                    default:
                        break;
                }
            }            
            
            break;
        }
        case ML_CONNECT_CONNECTED_EXIT:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlConnectAnimTickCount != mlConnectAnimTickPrev)
            {
                int32_t ypos = APP_LE_GETY(MultiLinkConnectScreen_ControlButton);
                int32_t deltaY = (CONNECT_POSY_HIDE_BOTTOM - ypos) / DEVICE_ANIM_COEFF;
                
                if (deltaY > 0)
                {
                    APP_LE_SETY(MultiLinkConnectScreen_ControlButton, ypos + deltaY);
                    
                }
                else
                {
                    SYS_TIME_TimerStop(mlConnectAnimTimer);
                    
                    APP_LE_SETY(MultiLinkConnectScreen_ControlButton, CONNECT_POSY_HIDE_BOTTOM);
                    
                    legato_showScreen(screenID_LightControlScreen);
                }
                
                mlConnectAnimTickPrev = mlConnectAnimTickCount;
            }            
            
            break;
        }
        default:
        {
            break;
        }
    }
}

static void MLConnectSetState(ML_CONNECT_SCREEN_STATE state)
{
    appScreenMLConnectState = state;
    
#ifdef ENABLE_UI_DEBUG       
    if (state > ML_CONNECT_ANIM_DONE)
    {
        UI_DPRINTF("UI State is %s \r\n", appScreenUIStates[state]);
    }
#endif
}

static void MLConnectAnimTimer_Callback (uintptr_t context)
{
    mlConnectAnimTickCount++;
}

static void MLConnectProgressTimer_Callback (uintptr_t context)
{
    mlConnectProgressTickCount++;
}

static void MLConnect_InitDeviceTable(void)
{
    devices[APP_BLE_DEVICE_A] = (ML_CONNECT_DEVICE)
    {   .deviceImage = MultiLinkConnectScreen_ImageSequenceWidgetA, 
        .deviceLabel = MultiLinkConnectScreen_LabelWidgetA,
        .deviceStatusIcon = MultiLinkConnectScreen_CheckImageA,
    };
    
    devices[APP_BLE_DEVICE_A].xpos = APP_LE_GETX(devices[APP_BLE_DEVICE_A].deviceImage);
    devices[APP_BLE_DEVICE_A].ypos = APP_LE_GETY(devices[APP_BLE_DEVICE_A].deviceImage);

    devices[APP_BLE_DEVICE_B] = (ML_CONNECT_DEVICE)
    {   .deviceImage = MultiLinkConnectScreen_ImageSequenceWidgetB, 
        .deviceLabel = MultiLinkConnectScreen_LabelWidgetB,
        .deviceStatusIcon = MultiLinkConnectScreen_CheckImageB,
    };
    
    devices[APP_BLE_DEVICE_B].xpos = APP_LE_GETX(devices[APP_BLE_DEVICE_B].deviceImage);
    devices[APP_BLE_DEVICE_B].ypos = APP_LE_GETY(devices[APP_BLE_DEVICE_B].deviceImage);


    devices[APP_BLE_DEVICE_C] = (ML_CONNECT_DEVICE)
    {   .deviceImage = MultiLinkConnectScreen_ImageSequenceWidgetC, 
        .deviceLabel = MultiLinkConnectScreen_LabelWidgetC,
        .deviceStatusIcon = MultiLinkConnectScreen_CheckImageC,
    };
    
    devices[APP_BLE_DEVICE_C].xpos = APP_LE_GETX(devices[APP_BLE_DEVICE_C].deviceImage);
    devices[APP_BLE_DEVICE_C].ypos = APP_LE_GETY(devices[APP_BLE_DEVICE_C].deviceImage);    
}

static void MLConnect_UpdateStatusString(char * str)
{
    if (strlen(str) > MAX_STATUS_LABEL_LENGTH)
        return;
    
    statusStr.fn->setFromCStr(&statusStr, str);    
    APP_LE_SETLABELSTRING(MultiLinkConnectScreen_ConnectionStatusLabel, statusStr);
}
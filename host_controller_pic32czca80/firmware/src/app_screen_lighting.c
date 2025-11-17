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
#include "app_ui.h"
#include "app_macros.h"
#include "app_utils.h"
#include "gfx\legato\common\legato_utils.h"
#include "app_coordinator.h"

typedef struct
{
    leButtonWidget * button;
    leLabelWidget  * label;
    leImageWidget  * statusIcon;
    leButtonWidget * stateButton;
    bool             stateButtonScreen;
} SCREEN_LIGHTING_CONNECT_DEVICE;

typedef enum
{
    LIGHTING_LIGHTING_INDOOR_INDEX = 0,
    LIGHTING_LIGHTING_OUTDOOR_INDEX,
    LIGHTING_MAX_INDEX = LIGHTING_LIGHTING_OUTDOOR_INDEX
} APP_SCREEN_LIGHTING_DEVICE_INDEX;

typedef enum
{
    APP_SCREEN_LIGHTING_SM_INIT,
    APP_SCREEN_LIGHTING_SM_WAITING_MSG            
} APP_SCREEN_LIGHTING_SM;

APP_SCREEN_LIGHTING_SM appScreenLightingSM;

static SCREEN_LIGHTING_CONNECT_DEVICE devices_lighting[LIGHTING_MAX_INDEX + 1] = {0};

static uint32_t coordCallbackIdx, wifiCallbackIdx;

bool lightIndoorStatusScreen = false;
bool lightOutdoorStatusScreen = false;


void APP_SCREEN_LIGHTING_Prepare2Send_SetRgbMessage(uint8_t index)
{
    APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
    cmdData.data[0] = CMD_SET_LED_RGB_BLINK;;
    cmdData.data[1] = index;
    cmdData.data[2] = 0x80;   // COLOR : 0x2B: yellow, 0x55: green, 0xAA: blue, 0xFF: red, 0x80: cyan
    cmdData.data[3] = 0xFF;   // Saturation Value
    cmdData.data[4] = 0xFF;   // Saturation Value
    cmdData.data[5] = 0xf4;   // Blinking Frequency
    cmdData.data[6] = 0x01;   // Blinking Frequency - 500ms
    cmdData.data[7] = 0x10;   // Blinking Time
    cmdData.data[8] = 0x27;   // Blinking Time - 10s
    cmdData.length = 9;
    cmdData.answer = false;
    bool alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
    if (!alive)
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SLIGHT] : Coord Cmds Queue full\r\n");
    }
}

void APP_SCREEN_LIGHTING_Prepare2Send_SetLightMessage(uint8_t index, uint8_t on_off)
{
    APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
    cmdData.data[0] = CMD_SET_LIGHT;
    cmdData.data[1] = index;
    cmdData.data[2] = on_off; // 0: off, 1: on
    cmdData.length = 3;
    cmdData.answer = false;
    bool alive =  APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
    if (!alive)
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SLIGHT] : Coord Cmds Queue full\r\n");
    }
}

static void APP_SCREEN_LIGHTING_InitDeviceTable(void)
{
    devices_lighting[LIGHTING_LIGHTING_INDOOR_INDEX] = (SCREEN_LIGHTING_CONNECT_DEVICE)
    {   .button = LightControlScreen_LightingIndoorRefreshButtonWidget,
        .label = LightControlScreen_LightingIndoorStatusLabel,
        .statusIcon = LightControlScreen_LightingIndoorConnIcon,
        .stateButton = LightControlScreen_LightingIndoorOnOffButtonWidget,
        .stateButtonScreen = false
    };
    
    devices_lighting[LIGHTING_LIGHTING_OUTDOOR_INDEX] = (SCREEN_LIGHTING_CONNECT_DEVICE)
    {   .button = LightControlScreen_LightingOutdoorRefreshButtonWidget,
        .label = LightControlScreen_LightingOutdoorStatusLabel,
        .statusIcon = LightControlScreen_LightingOutdoorConnIcon,
        .stateButton = LightControlScreen_LightingOutdoorOnOffButtonWidget,
        .stateButtonScreen = false
    };
}

void APP_SCREEN_LIGHTING_OnShow(void)
{
    /* Show the current */
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT] : Screen onShow\r\n");
    APP_COORDINATOR_DEVICE_INFO device_info_lighting[APP_COORDINATOR_MAX_DEVICES];
    
    appScreenLightingSM = APP_SCREEN_LIGHTING_SM_INIT;
    
    // Coordinator Information
    APP_COORDINATOR_deviceDoSnapshot(&device_info_lighting);    
    APP_SCREEN_LIGHTING_InitDeviceTable();    
    for (uint8_t type = TYPE_LIGHTING_INDOOR; type <= TYPE_LIGHTING_OUTDOOR; type++)
    {       
        // Connection Icon
        uint8_t alive = APP_COORDINATOR_deviceGetAliveSnapshot(device_info_lighting, type);
        if (alive)
        {
            if (alive == APP_COORDINATOR_DEVICE_STATE_JOINED)
            {
                APP_LE_SETIMAGE(devices_lighting[type - TYPE_LIGHTING_INDOOR].statusIcon, ConnectIconYellow);
            }
            else
            {
                APP_LE_SETIMAGE(devices_lighting[type - TYPE_LIGHTING_INDOOR].statusIcon, ConnectIconGreen);
            }
        }
        else
        {
            APP_LE_SETIMAGE(devices_lighting[type - TYPE_LIGHTING_INDOOR].statusIcon, ConnectIconRed);
        }
        // State        
        bool state = APP_COORDINATOR_deviceGetStateSnapshot(device_info_lighting, type);
        devices_lighting[type - TYPE_LIGHTING_INDOOR].stateButtonScreen = state;
        APP_LE_SETPRESSED(devices_lighting[type - TYPE_LIGHTING_INDOOR].stateButton, !state);
    }
    
    // COORDINATOR - G3 Network
    if (APP_COORDINATOR_GetHeartbeatCount())
    {
        APP_LE_SETIMAGE(LightControlScreen_G3Widget, g3Green);
    }
    else
    {
        APP_LE_SETIMAGE(LightControlScreen_G3Widget, g3Red);
    }
    APP_LE_SETVISIBLE(LightControlScreen_G3Widget, LE_TRUE);
    coordCallbackIdx = APP_COORDINATOR_RegisterNotification(APP_UI_COORDINATOR_EventCallback);
    
    // WIFI/CLOUD PART
    uint32_t wifi_status;
    APP_WIFI_GetStatus(&wifi_status);
    
    if (wifi_status & APP_WIFI_AVAILABLE)
    {
        if ( wifi_status & APP_WIFI_CONNECTED)
        {
            APP_LE_SETIMAGE(LightControlScreen_WifiWidget, WifiGreen);
            if (wifi_status & APP_WIFI_MQTT_CONNECTED)
            {
                APP_LE_SETIMAGE(LightControlScreen_CloudWidget, CloudGreen);
            }
            else
            {
                APP_LE_SETIMAGE(LightControlScreen_CloudWidget, CloudRed);
            }
            APP_LE_SETVISIBLE(LightControlScreen_CloudWidget, LE_TRUE);
        }
        else
        {
            APP_LE_SETIMAGE(LightControlScreen_WifiWidget, WifiYellow);
            APP_LE_SETVISIBLE(LightControlScreen_CloudWidget, LE_FALSE);
        }
    }
    else
    {
        APP_LE_SETIMAGE(LightControlScreen_WifiWidget, WifiRed);
        APP_LE_SETVISIBLE(LightControlScreen_CloudWidget, LE_FALSE);
    }   
    APP_LE_SETVISIBLE(LightControlScreen_WifiWidget, LE_TRUE);
    wifiCallbackIdx = APP_WIFI_RegisterNotification(APP_UI_WIFI_EventCallback);
    
    // Alarm Status
    bool alarm = APP_COORDINATOR_GetAlarmStatus();
    if (alarm)
    {
        APP_LE_SETIMAGE(LightControlScreen_AlarmWidget, AlarmIcon50);
        APP_LE_SETVISIBLE(LightControlScreen_AlarmWidget, true);                            
    }
    else
    {
        APP_LE_SETVISIBLE(LightControlScreen_AlarmWidget, false);
    }
    
}

void APP_SCREEN_LIGHTING_screenHide(void)
{
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT] : Screen Hide\r\n");
    APP_COORDINATOR_UnregisterNotification(coordCallbackIdx);
    APP_WIFI_UnregisterNotification(wifiCallbackIdx);
}

void APP_SCREEN_LIGHTING_screenUpdate(void)
{
    uint8_t type;
    bool alive, state;
    APP_UI_MSG uiMsg;
    
    switch(appScreenLightingSM)
    {
        case APP_SCREEN_LIGHTING_SM_INIT:
            appScreenLightingSM = APP_SCREEN_LIGHTING_SM_WAITING_MSG;
            break;
        case APP_SCREEN_LIGHTING_SM_WAITING_MSG:
            // Waiting for Notifications
            if (APP_UI_ReadMsg(&uiMsg) == APP_SUCCESS)
            {
                switch(uiMsg.event)
                {
                    case APP_EVENT_COORD_RESET:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SLIGHT] : Coord Reset Message\r\n");
                        for (uint8_t i=0; i<=LIGHTING_MAX_INDEX; i++)
                            APP_LE_SETIMAGE(devices_lighting[i].statusIcon, ConnectIconRed);
                        APP_LE_SETIMAGE(LightControlScreen_G3Widget, g3Red);
                        APP_LE_SETVISIBLE(LightControlScreen_G3Widget, LE_TRUE);
                        break;
                    case APP_EVENT_COORD_HEARTBEAT:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SLIGHT] : Coord Heartbeat Message\r\n");
                        APP_LE_SETIMAGE(LightControlScreen_G3Widget, g3Green);
                        break;
                    case APP_EVENT_COORD_ALARM:
                        state = (bool) uiMsg.param.data[0];
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : Coord Alarm Message state=%s\r\n", state ? "true":"false");
                        if (state)
                        {
                            APP_LE_SETIMAGE(LightControlScreen_AlarmWidget, AlarmIcon50);
                            APP_LE_SETVISIBLE(LightControlScreen_AlarmWidget, true);
                        }
                        else
                        {
                            APP_LE_SETVISIBLE(LightControlScreen_AlarmWidget, false);
                        }
                        break;
                    case APP_EVENT_COORD_DEVICE_LEAVE:                        
                        type = (uint8_t) uiMsg.device;
                        if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_LIGHTING_OUTDOOR))
                        {
                            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : Coord Device 0x%02X Leave Message\r\n", type);
                            APP_LE_SETIMAGE(devices_lighting[type - TYPE_LIGHTING_INDOOR].statusIcon, ConnectIconRed);
                        }
                        break;    
                    case APP_EVENT_COORD_DEVICE_JOIN:                        
                        type = (uint8_t) uiMsg.device;
                        if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_LIGHTING_OUTDOOR))
                        {
                            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : Coord Device 0x%02X Join Message\r\n", type);
                            APP_LE_SETIMAGE(devices_lighting[type - TYPE_LIGHTING_INDOOR].statusIcon, ConnectIconYellow);
                        }
                        break;
                    case APP_EVENT_COORD_DEVICE_ALIVE:
                        type = uiMsg.device;
                        alive = (bool) uiMsg.param.data[0];
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : Coord Device 0x%02X Alive:%s Message\r\n", type, alive ? "true" : "false");
                        if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_LIGHTING_OUTDOOR))
                        {
                            if (alive)
                                APP_LE_SETIMAGE(devices_lighting[type - TYPE_LIGHTING_INDOOR].statusIcon, ConnectIconGreen);
                            else
                                APP_LE_SETIMAGE(devices_lighting[type - TYPE_LIGHTING_INDOOR].statusIcon, ConnectIconYellow);
                        }
                        break;                        
                    case APP_EVENT_COORD_DEVICE_STATE:                        
                        type = uiMsg.device;
                        state = (uint8_t) uiMsg.param.data[0];
                                                
                        if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_LIGHTING_OUTDOOR))
                        {
                            bool state_ui = devices_lighting[type - TYPE_LIGHTING_INDOOR].stateButtonScreen;
                            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : Coord Device 0x%02X State:%d (ui=%d) Message\r\n", type, state, state_ui);
                            if ( state_ui != state)
                            {
                                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : Update according with new state\r\n");                                
                                APP_LE_SETPRESSED(devices_lighting[type - TYPE_LIGHTING_INDOOR].stateButton, state_ui);
                            }
                        }
                        break;
                    case APP_EVENT_WIFI_AVAILABLE:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SLIGHT] : Wifi Available Message\r\n");
                        APP_LE_SETIMAGE(LightControlScreen_WifiWidget, WifiYellow);
                        APP_LE_SETVISIBLE(LightControlScreen_WifiWidget, LE_TRUE);
                        break;
                    case APP_EVENT_WIFI_CONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SLIGHT] : Wifi Connected Message\r\n");
                        APP_LE_SETIMAGE(LightControlScreen_WifiWidget, WifiGreen);
                        APP_LE_SETIMAGE(LightControlScreen_CloudWidget, CloudRed);
                        APP_LE_SETVISIBLE(LightControlScreen_CloudWidget, LE_TRUE);
                        break;
                    case APP_EVENT_WIFI_DISCONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SLIGHT] : Wifi Disconnected Message\r\n");
                        APP_LE_SETIMAGE(LightControlScreen_WifiWidget, WifiYellow);
                        APP_LE_SETVISIBLE(LightControlScreen_CloudWidget, LE_FALSE);
                        break;                        
                    case APP_EVENT_WIFI_MQTT_CONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SLIGHT] : MQTT connected over Wifi Message\r\n");
                        APP_LE_SETIMAGE(LightControlScreen_CloudWidget, CloudGreen);
                        APP_LE_SETVISIBLE(LightControlScreen_CloudWidget, LE_TRUE);
                        break;
                    case APP_EVENT_WIFI_MQTT_DISCONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SLIGHT] : MQTT disconnected over Wifi  Message\r\n");
                        APP_LE_SETIMAGE(LightControlScreen_CloudWidget, CloudRed);
                        break;                                                
                    default:
                        break;
                }
            }                    
            break;
        default:
            break;
    }
}

void event_LightControlScreen_LightingIndoorRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    
    uint8_t alive;
    uint8_t index;
        
    index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_INDOOR);
    APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_INDOOR, &alive); 
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT]: Lighting Indoor refresh - index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_LIGHTING_Prepare2Send_SetRgbMessage(index);
    }
}

void event_LightControlScreen_LightingOutdoorRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    
    uint8_t alive;
    uint8_t index;
    
    index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_OUTDOOR);
    APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_INDOOR, &alive);    
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT]: Lighting Outdoor refresh - index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_LIGHTING_Prepare2Send_SetRgbMessage(index);
    }    
}


void event_LightControlScreen_LightingIndoorOnOffButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;
    bool state;
    
    APP_COORDINATOR_deviceGetState(TYPE_LIGHTING_INDOOR, &state);
    devices_lighting[0 /* TYPE_LIGHTING_INDOOR */ ].stateButtonScreen = false;
    // Indoor Light off
    APP_LE_SETPRESSEDIMAGE(devices_lighting[0].button, IndoorLight);
    APP_LE_SETRELEASEDIMAGE(devices_lighting[0].button, IndoorLight);

    // state_ui is true on pressed
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : OnPressed, Device Type 0x%02X State:%d (ui=%d) Message\r\n", TYPE_LIGHTING_INDOOR, state, 0);
    if (state)
    {
        index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_INDOOR);
        APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_INDOOR, &alive); 
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT]: Lighting Indoor On/off pressed - index=0x%02X alive=%s\r\n", index, alive? "true":"false");
        if ((index != INDEX_UNKNOWN) && (alive))
        {        
            // Prepare command
            APP_SCREEN_LIGHTING_Prepare2Send_SetLightMessage(index, 0);
        }
    }
}

void event_LightControlScreen_LightingIndoorOnOffButtonWidget_OnReleased(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;
    bool state;
    
    APP_COORDINATOR_deviceGetState(TYPE_LIGHTING_INDOOR, &state);
    devices_lighting[0 /* TYPE_LIGHTING_INDOOR */ ].stateButtonScreen = true;
    // Light on
    APP_LE_SETPRESSEDIMAGE(devices_lighting[0].button, IndoorLightOn);
    APP_LE_SETRELEASEDIMAGE(devices_lighting[0].button, IndoorLightOn);
    // state_ui is true on pressed
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : OnReleased, Device Type 0x%02X State:%d (ui=%d) Message\r\n", TYPE_LIGHTING_INDOOR, state, 1);
    if (!state)
    {        
        index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_INDOOR);
        APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_INDOOR, &alive);    
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT]: Lighting Indoor On/Off released - index=0x%02X alive=%s\r\n", index, alive? "true":"false");
        if ((index != INDEX_UNKNOWN) && (alive))
        {
            // Prepare command
            APP_SCREEN_LIGHTING_Prepare2Send_SetLightMessage(index, 1);
        } 
    }
}

void event_LightControlScreen_LightingOutdoorOnOffButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;
    bool state;
    
    APP_COORDINATOR_deviceGetState(TYPE_LIGHTING_OUTDOOR, &state);
    devices_lighting[1 /* TYPE_LIGHTING_OUTDOOR */ ].stateButtonScreen = false;
    // Light off
    APP_LE_SETPRESSEDIMAGE(devices_lighting[1].button, OutdoorLight);
    APP_LE_SETRELEASEDIMAGE(devices_lighting[1].button, OutdoorLight);
    // state_ui is true on pressed
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : OnPressed, Device Type 0x%02X State:%d (ui=%d) Message\r\n", TYPE_LIGHTING_OUTDOOR, state, 0);
    if (state)
    {
        index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_OUTDOOR);
        APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_OUTDOOR, &alive); 
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT]: Outdoor Lighting On/off pressed - index=0x%02X alive=%s\r\n", index, alive? "true":"false");
        if ((index != INDEX_UNKNOWN) && (alive))
        {        
            // Prepare command
            APP_SCREEN_LIGHTING_Prepare2Send_SetLightMessage(index, 0);
        }
    }
}

void event_LightControlScreen_LightingOutdoorOnOffButtonWidget_OnReleased(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;
    bool state;
    
    APP_COORDINATOR_deviceGetState(TYPE_LIGHTING_OUTDOOR, &state);
    devices_lighting[1 /* TYPE_LIGHTING_OUTDOOR */ ].stateButtonScreen = true;
    // Light on
    APP_LE_SETPRESSEDIMAGE(devices_lighting[1].button, OutdoorLightOn);
    APP_LE_SETRELEASEDIMAGE(devices_lighting[1].button, OutdoorLightOn);
    // state_ui is true on pressed
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SLIGHT] : OnReleased, Device Type 0x%02X State:%d (ui=%d) Message\r\n", TYPE_LIGHTING_OUTDOOR, state, 1);
    if (!state)
    {        
        index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_OUTDOOR);
        APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_OUTDOOR, &alive);    
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_SLIGHT]: Outdoor Lighting On/Off released - index=0x%02X alive=%s\r\n", index, alive? "true":"false");
        if ((index != INDEX_UNKNOWN) && (alive))
        {
            // Prepare command
            APP_SCREEN_LIGHTING_Prepare2Send_SetLightMessage(index, 1);
        } 
    }
}

void event_LightControlScreen_NextLightingButtonWidget_OnPressed(leButtonWidget* btn)
{
    // Go to Sustainability Wall        
    legato_showScreen(screenID_SignalingControl);
}

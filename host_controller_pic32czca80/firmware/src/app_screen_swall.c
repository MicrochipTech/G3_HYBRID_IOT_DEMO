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
    leLabelWidget * label;
    leImageWidget * statusIcon;
} SCREEN_SWALL_CONNECT_DEVICE;

typedef enum
{
    SWALL_LIQUID_DETECTION_INDEX = 0,
    SWALL_SOLAR_INVERTER_INDEX,
    SWALL_BATTERY_CHARGER_INDEX,
    SWALL_ENERGY_STORAGE_INDEX,
    SWALL_HEAT_PUMP_INDEX,
    SWALL_EV_CHARGER_INDEX,
    SWALL_ELECTRICITY_METER_INDEX,
    SWALL_MAX_INDEX = SWALL_ELECTRICITY_METER_INDEX
} APP_SCREEN_SWALL_DEVICE_INDEX;

typedef enum
{
    APP_SCREEN_SWALL_SM_INIT,
    APP_SCREEN_SWALL_SM_WAITING_MSG            
} APP_SCREEN_SWALL_SM;

APP_SCREEN_SWALL_SM appScreenSwallSM;

static SCREEN_SWALL_CONNECT_DEVICE devices_swall[SWALL_MAX_INDEX + 1] = {0};

static uint32_t coordCallbackIdx, wifiCallbackIdx;

void APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(uint8_t index)
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
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL] : Coord Cmds Queue full\r\n");
    }
}

static void APP_SCREEN_SWALL_InitDeviceTable(void)
{
    devices_swall[SWALL_LIQUID_DETECTION_INDEX] = (SCREEN_SWALL_CONNECT_DEVICE)
    {   .button = SWallControlScreen_LiquidDetectionRefreshButtonWidget,
        .label = SWallControlScreen_LiquidDetectionStatusLabel,
        .statusIcon = SWallControlScreen_LiquidDetectionConnIcon
    };
    
    devices_swall[SWALL_SOLAR_INVERTER_INDEX] = (SCREEN_SWALL_CONNECT_DEVICE)
    {   .button = SWallControlScreen_SolarInverterRefreshButtonWidget,
        .label = SWallControlScreen_SolarInverterStatusLabel,
        .statusIcon = SWallControlScreen_SolarInverterConnIcon
    };
    
    devices_swall[SWALL_BATTERY_CHARGER_INDEX] = (SCREEN_SWALL_CONNECT_DEVICE)
    {   .button = SWallControlScreen_BatteryChargerRefreshButtonWidget,
        .label = SWallControlScreen_BatteryChargerStatusLabel,
        .statusIcon = SWallControlScreen_BatteryChargerConnIcon
    };
    
    devices_swall[SWALL_ENERGY_STORAGE_INDEX] = (SCREEN_SWALL_CONNECT_DEVICE)
    {   .button = SWallControlScreen_EnergyStorageRefreshButtonWidget,
        .label = SWallControlScreen_EnergyStorageStatusLabel,
        .statusIcon = SWallControlScreen_EnergyStorageConnIcon
    };
    
    devices_swall[SWALL_HEAT_PUMP_INDEX] = (SCREEN_SWALL_CONNECT_DEVICE)
    {   .button = SWallControlScreen_HeatPumpRefreshButtonWidget,
        .label = SWallControlScreen_HeatPumpStatusLabel,
        .statusIcon = SWallControlScreen_HeatPumpConnIcon
    };
    
    devices_swall[SWALL_EV_CHARGER_INDEX] = (SCREEN_SWALL_CONNECT_DEVICE)
    {   .button = SWallControlScreen_EVChargerRefreshButtonWidget,
        .label = SWallControlScreen_EVChargerStatusLabel,
        .statusIcon = SWallControlScreen_EVChargerConnIcon
    };
    
    devices_swall[SWALL_ELECTRICITY_METER_INDEX] = (SCREEN_SWALL_CONNECT_DEVICE)
    {   .button = SWallControlScreen_ElectricityMeterRefreshButtonWidget,
        .label = SWallControlScreen_ElectricityMeterStatusLabel,
        .statusIcon = SWallControlScreen_ElectricityMeterConnIcon
    };
}


void APP_SCREEN_SWALL_OnShow(void)
{
    uint8_t alive;
    APP_COORDINATOR_DEVICE_INFO device_info_swall[APP_COORDINATOR_MAX_DEVICES];
    
    // STATE MACHINE
    appScreenSwallSM = APP_SCREEN_SWALL_SM_INIT;
    
    // COORDINATOR PART
    APP_COORDINATOR_deviceDoSnapshot(&device_info_swall);
    APP_SCREEN_SWALL_InitDeviceTable();
    for (uint8_t type = TYPE_LIQUID_DETECTION; type <= TYPE_ELECTRICITY_METER; type++)
    {   
        alive = APP_COORDINATOR_deviceGetAliveSnapshot(device_info_swall, type);
        if (alive)
        {
            if (alive == APP_COORDINATOR_DEVICE_STATE_JOINED)
            {
                APP_LE_SETIMAGE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, ConnectIconYellow);
            }
            else
            {
                APP_LE_SETIMAGE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, ConnectIconGreen);
            }
        }
        else
        {
            APP_LE_SETIMAGE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, ConnectIconRed);
        }
        APP_LE_SETVISIBLE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, LE_TRUE);
    }
    
    // G3 Coordinator
    if (APP_COORDINATOR_GetHeartbeatCount())
    {
        APP_LE_SETIMAGE(SWallControlScreen_G3Widget, g3Green);
    }
    else
    {
        APP_LE_SETIMAGE(SWallControlScreen_G3Widget, g3Red);
    }
    APP_LE_SETVISIBLE(SWallControlScreen_G3Widget, LE_TRUE);
    coordCallbackIdx = APP_COORDINATOR_RegisterNotification(APP_UI_COORDINATOR_EventCallback); 
    
    // WIFI/CLOUD PART
    uint32_t wifi_status;
    APP_WIFI_GetStatus(&wifi_status);
    
    if (wifi_status & APP_WIFI_AVAILABLE)
    {
        APP_LE_SETIMAGE(SWallControlScreen_CloudWidget, CloudRed);
        if ( wifi_status & APP_WIFI_CONNECTED)
        {
            APP_LE_SETIMAGE(SWallControlScreen_WifiWidget, WifiGreen);
            if (wifi_status & APP_WIFI_MQTT_CONNECTED)
            {
                APP_LE_SETIMAGE(SWallControlScreen_CloudWidget, CloudGreen);
            }
        }
        else
        {
            APP_LE_SETIMAGE(SWallControlScreen_WifiWidget, WifiYellow);
        }
        APP_LE_SETVISIBLE(SWallControlScreen_CloudWidget, LE_TRUE);
    }
    else
    {
        APP_LE_SETIMAGE(SWallControlScreen_WifiWidget, WifiRed);
        APP_LE_SETVISIBLE(SWallControlScreen_CloudWidget, LE_FALSE);
    }   
    APP_LE_SETVISIBLE(SWallControlScreen_WifiWidget, LE_TRUE);
    
    wifiCallbackIdx = APP_WIFI_RegisterNotification(APP_UI_WIFI_EventCallback);
    
    // Alarm Status
    bool alarm = APP_COORDINATOR_GetAlarmStatus();
    if (alarm)
    {
        APP_LE_SETIMAGE(SWallControlScreen_AlarmWidget, AlarmIcon50);
        APP_LE_SETVISIBLE(SWallControlScreen_AlarmWidget, true);                            
    }
    else
    {
        APP_LE_SETVISIBLE(SWallControlScreen_AlarmWidget, false);
    }    
}

void APP_SCREEN_SWALL_screenHide(void)
{
    APP_COORDINATOR_UnregisterNotification(coordCallbackIdx);
    APP_WIFI_UnregisterNotification(wifiCallbackIdx);
}

void APP_SCREEN_SWALL_screenUpdate(void)
{
    uint8_t type;
    uint32_t counter;
    bool alive, state;
    APP_UI_MSG uiMsg;
    
    switch(appScreenSwallSM)
    {
        case APP_SCREEN_SWALL_SM_INIT:
            appScreenSwallSM = APP_SCREEN_SWALL_SM_WAITING_MSG;
            break;
        case APP_SCREEN_SWALL_SM_WAITING_MSG:
            // Waiting for Notifications
            if (APP_UI_ReadMsg(&uiMsg) == APP_SUCCESS)
            {
                switch(uiMsg.event)
                {
                    case APP_EVENT_COORD_RESET:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SWALL] : Coord Reset Message\r\n");
                        for (uint8_t i=0; i<=SWALL_MAX_INDEX; i++)
                            APP_LE_SETIMAGE(devices_swall[i].statusIcon, ConnectIconRed);
                        APP_LE_SETIMAGE(SWallControlScreen_G3Widget, g3Red);
                        break;
                    case APP_EVENT_COORD_HEARTBEAT:                        
                        memcpy(&counter, uiMsg.param.data, uiMsg.parmSize);
                        APP_LE_SETIMAGE(SWallControlScreen_G3Widget, g3Green);
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SWALL] : Coord Heartbeat %d Message\r\n", counter);
                        break;
                    case APP_EVENT_COORD_ALARM:
                        state = (bool) uiMsg.param.data[0];
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SWALL] : Coord Alarm Message state=%s\r\n", state ? "true":"false");
                        if (state)
                        {
                            APP_LE_SETIMAGE(SWallControlScreen_AlarmWidget, AlarmIcon50);
                            APP_LE_SETVISIBLE(SWallControlScreen_AlarmWidget, true);
                        }
                        else
                        {
                            APP_LE_SETVISIBLE(SWallControlScreen_AlarmWidget, false);
                        }
                        break;
                    case APP_EVENT_COORD_DEVICE_LEAVE:
                        type = (uint8_t) uiMsg.device;
                        if ((type >= TYPE_LIQUID_DETECTION) && (type <= TYPE_ELECTRICITY_METER))
                        {
                            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SWALL] : Coord Device 0x%02X Leave Message\r\n", type);
                            APP_LE_SETIMAGE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, ConnectIconRed);
                        }
                        break;
                    case APP_EVENT_COORD_DEVICE_JOIN:                        
                        type = (uint8_t) uiMsg.device;
                        if ((type >= TYPE_LIQUID_DETECTION) && (type <= TYPE_ELECTRICITY_METER))
                        {
                            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SWALL] : Coord Device 0x%02X Join Message\r\n", type);
                            APP_LE_SETIMAGE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, ConnectIconYellow);
                        }
                        break;
                    case APP_EVENT_COORD_DEVICE_ALIVE:
                        type = uiMsg.device;      
                        alive = (bool) uiMsg.param.data[0];
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SWALL] : Coord Device 0x%02X Alive:%s Message\r\n", type, alive ? "true" : "false");
                        if ((type >= TYPE_LIQUID_DETECTION) && (type <= TYPE_ELECTRICITY_METER))
                        {
                            if (alive)
                                APP_LE_SETIMAGE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, ConnectIconGreen);
                            else
                                APP_LE_SETIMAGE(devices_swall[type - TYPE_LIQUID_DETECTION].statusIcon, ConnectIconYellow);
                        }
                        break;                        
                    case APP_EVENT_COORD_DEVICE_STATE:                        
                        type = uiMsg.device;
                        state = (uint8_t) uiMsg.param.data[0];
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_SWALL] : Coord Device 0x%02X State:%s Message\r\n", type, state ? "true" : "false");
                        break;
                    case APP_EVENT_WIFI_AVAILABLE:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SWALL] : Wifi Available Message\r\n");
                        APP_LE_SETIMAGE(SWallControlScreen_WifiWidget, WifiYellow);
                        APP_LE_SETVISIBLE(SWallControlScreen_WifiWidget, LE_TRUE);
                    case APP_EVENT_WIFI_CONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SWALL] : Wifi Connected Message\r\n");
                        APP_LE_SETIMAGE(SWallControlScreen_WifiWidget, WifiGreen);
                        APP_LE_SETIMAGE(SWallControlScreen_CloudWidget, CloudRed);
                        APP_LE_SETVISIBLE(SWallControlScreen_CloudWidget, LE_TRUE);
                        break;
                    case APP_EVENT_WIFI_DISCONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SWALL] : Wifi Disconnected Message\r\n");
                        APP_LE_SETIMAGE(SWallControlScreen_WifiWidget, WifiYellow);
                        APP_LE_SETVISIBLE(SWallControlScreen_CloudWidget, LE_FALSE);
                        break;                        
                    case APP_EVENT_WIFI_MQTT_CONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SWALL] : MQTT connected over Wifi Message\r\n");
                        APP_LE_SETIMAGE(SWallControlScreen_CloudWidget, CloudGreen);
                        APP_LE_SETVISIBLE(SWallControlScreen_CloudWidget, LE_TRUE);
                        break;
                    case APP_EVENT_WIFI_MQTT_DISCONNECTED:
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_SWALL] : MQTT disconnected over Wifi  Message\r\n");
                        APP_LE_SETIMAGE(SWallControlScreen_CloudWidget, CloudRed);
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

void event_SWallControlScreen_BatteryChargerRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    
    uint8_t alive;
    uint8_t index;
    
    index = APP_COORDINATOR_deviceIndexByType(TYPE_BATTERY_CHARGER);
    APP_COORDINATOR_deviceGetAlive(TYPE_BATTERY_CHARGER, &alive);
    
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(index);
    }    
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL]: Battery Charger index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    }
}

void event_SWallControlScreen_EnergyStorageRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    
    uint8_t alive;
    uint8_t index;
    
    index = APP_COORDINATOR_deviceIndexByType(TYPE_ENERGY_STORAGE);
    APP_COORDINATOR_deviceGetAlive(TYPE_ENERGY_STORAGE, &alive);
    
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(index);
    }    
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL]: Energy Storage index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    }  
}

void event_SWallControlScreen_EVChargerRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    
    uint8_t alive;
    uint8_t index;
    
    index = APP_COORDINATOR_deviceIndexByType(TYPE_EV_CHARGER);
    APP_COORDINATOR_deviceGetAlive(TYPE_EV_CHARGER, &alive);
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(index);
    }    
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL]: EV Charger index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    }
}

void event_SWallControlScreen_SolarInverterRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;
    
    index = APP_COORDINATOR_deviceIndexByType(TYPE_SOLAR_INVERTER);
    APP_COORDINATOR_deviceGetAlive(TYPE_SOLAR_INVERTER, &alive);
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(index);
    }    
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL]: Solar Inverter index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    }
}

void event_SWallControlScreen_LiquidDetectionRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;
    
    index = APP_COORDINATOR_deviceIndexByType(TYPE_LIQUID_DETECTION);
    APP_COORDINATOR_deviceGetAlive(TYPE_LIQUID_DETECTION, &alive);
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(index);
    }    
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL]: Liquid Detector index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    }
}

void event_SWallControlScreen_HeatPumpRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;

    index = APP_COORDINATOR_deviceIndexByType(TYPE_HEAT_PUMP);
    APP_COORDINATOR_deviceGetAlive(TYPE_HEAT_PUMP, &alive);    
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(index);
    }    
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL]: Heat Pump index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    }
}

void event_SWallControlScreen_ElectricityMeterRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t alive;
    uint8_t index;
    
    index = APP_COORDINATOR_deviceIndexByType(TYPE_ELECTRICITY_METER);
    APP_COORDINATOR_deviceGetAlive(TYPE_ELECTRICITY_METER, &alive); 
    if ((index != INDEX_UNKNOWN) && (alive))
    {
        // Prepare command
        APP_SCREEN_SWALL_Prepare2Send_SetRgbMessage(index);
    }    
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_SWALL]: Electricity Meter index=0x%02X alive=%s\r\n", index, alive? "true":"false");
    }
}

void event_SWallControlScreen_NextSWButtonWidget_OnPressed(leButtonWidget* btn)
{
    // Go to Sustainability Wall        
    legato_showScreen(screenID_LightControlScreen);
}

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

void APP_SCREEN_SWALL_Prepare2Send_Message(uint8_t index)
{
    uint8_t buffer[9];
    uint8_t length = 9;
    
    buffer[0] = CMD_SET_LED_RGB_BLINK;;
    buffer[1] = index;
    buffer[2] = 0xAA;   // COLOR : 0x2B: yellow, 0x55: green, 0xAA: blue, 0xFF: red
    buffer[3] = 0xFF;   // Saturation Value
    buffer[4] = 0xFF;   // Saturation Value
    buffer[5] = 0x00;   // Blinking Frequency
    buffer[6] = 0x01;   // Blinking Frequency
    buffer[7] = 0x00;   // Blinking Time
    buffer[8] = 0x20;   // Blinking Time
    while (!APP_COORDINATOR_Prepare2Send_Message(index, buffer, length, false));    
}

void event_SWallControlScreen_BatteryChargerRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t index = APP_COORDINATOR_deviceGetIndex(TYPE_BATTERY_CHARGER);
    if (index != INDEX_UNKNOWN)
    {
        bool alive = APP_COORDINATOR_deviceGetAlive(TYPE_BATTERY_CHARGER);
        if (alive)
        {
            // Prepare command
            APP_SCREEN_SWALL_Prepare2Send_Message(index);
        }else{
            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_SCREEN_SWALL: Battery Charger not alive\r\n");
        }
    }
}

void event_SWallControlScreen_EnergyStorageRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t index = APP_COORDINATOR_deviceGetIndex(TYPE_ENERGY_STORAGE);
    if (index != INDEX_UNKNOWN)
    {
        bool alive = APP_COORDINATOR_deviceGetAlive(TYPE_ENERGY_STORAGE);
        if (alive)
        {
            // Prepare command
            APP_SCREEN_SWALL_Prepare2Send_Message(index);
        }
        else{
            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_SCREEN_SWALL: Energy Storage not alive\r\n");
        }
    }    
}

void event_SWallControlScreen_EVChargerRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t index = APP_COORDINATOR_deviceGetIndex(TYPE_EV_CHARGER);
    if (index != INDEX_UNKNOWN)
    {
        bool alive = APP_COORDINATOR_deviceGetAlive(TYPE_EV_CHARGER);
        if (alive)
        {
            // Prepare command
            APP_SCREEN_SWALL_Prepare2Send_Message(index);
        }
        else{
            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_SCREEN_SWALL: EV Charger not alive\r\n");
        }
    }    
}

void event_SWallControlScreen_SolarInverterRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t index = APP_COORDINATOR_deviceGetIndex(TYPE_SOLAR_INVERTER);
    if (index != INDEX_UNKNOWN)
    {
        bool alive = APP_COORDINATOR_deviceGetAlive(TYPE_SOLAR_INVERTER);
        if (alive)
        {
            // Prepare command
            APP_SCREEN_SWALL_Prepare2Send_Message(index);
        }
        else{
            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_SCREEN_SWALL: Solar Inverter not alive\r\n");
        }
    }    
}

void event_SWallControlScreen_LeakDetectorRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t index = APP_COORDINATOR_deviceGetIndex(TYPE_LEAK_DETECTOR);
    if (index != INDEX_UNKNOWN)
    {
        bool alive = APP_COORDINATOR_deviceGetAlive(TYPE_LEAK_DETECTOR);
        if (alive)
        {
            // Prepare command
            APP_SCREEN_SWALL_Prepare2Send_Message(index);
        }
        else
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_SCREEN_SWALL: Leak Detector not alive\r\n");
        }
    }    
}

void event_SWallControlScreen_HeatPumpRefreshButtonWidget_OnPressed(leButtonWidget* btn)
{
    uint8_t index = APP_COORDINATOR_deviceGetIndex(TYPE_HEAT_PUMP);
    if (index != INDEX_UNKNOWN)
    {
        bool alive = APP_COORDINATOR_deviceGetAlive(TYPE_HEAT_PUMP);
        if (alive)
        {
            // Prepare command
            APP_SCREEN_SWALL_Prepare2Send_Message(index);
        }
        else{
            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_SCREEN_SWALL: Heat Pump not alive\r\n");
        }
    }    
}


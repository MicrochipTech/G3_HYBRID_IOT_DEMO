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
#include "app_utils.h"
#include "gfx\legato\common\legato_utils.h"

#define DEVICE_ACTIVE_IMAGE_ID 0
#define DEVICE_INACTIVE_IMAGE_ID 1

#define CONTROL_DELAY_MS 80
#define CONTROL_POSY_HIDE_BOTTOM 480
#define SLIDER_X_SHOWPOS 728
#define CONTROL_ANIM_COEFF 3
#define CONTROL_PANEL_ANIM_COEFF 6
#define MAX_TEMP_STR_LENGTH 6

#define GRAPH_TIMER_TICK_PERIOD_MS   30000

#define COLOR_PICKER_YPOS 180

#define MIN_BRIGHTNESS_PCT 5

#define NUM_TEMP_GRAPH_ENTRIES 10

#define INFO_PANEL_MIN_HEIGHT 2
#define INFO_PANEL_HEIGHT 340

#define INFOGRAPH_ANIM_DELAY_SLOW_MS 400
#define INFOGRAPH_ANIM_DELAY_MS 100
#define INFOGRAPH_ANIM_DELAY_FAST_MS 50

typedef enum
{
    ML_CONTROL_INIT,
    ML_CONTROL_ANIM0,
    ML_CONTROL_ANIM1,
    ML_CONTROL_ANIM2,
    ML_CONTROL_INIT_DONE,
    ML_CONTROL_PROCESSING,
    ML_CONTROL_HIDE_INFO,
    ML_CONTROL_HIDE_INFOGRAPH,
    ML_CONTROL_SHOW_GRAPH,
    ML_CONTROL_SHOW_BLE,
    ML_CONTROL_SHOW_WIFI,
    ML_CONTROL_SHOW_INFOGRAPH,
    ML_CONTROL_DISCONNECT,
    ML_CONTROL_EXIT,
    ML_CONTROL_MAX_STATES,
} ML_CONTROL_SCREEN_STATE;

typedef enum
{
    ML_CTRL_DATA_GRAPH,
    ML_CTRL_DATA_BLE,
    ML_CTRL_DATA_WIFI,
    ML_CTRL_INFOGRAPHIC,
    ML_CTRL_DATA_NONE
} ML_CONTROL_DATAPANEL_STATE;

typedef struct
{
    leButtonWidget * button;
    leImageSequenceWidget * deviceImage;  
    leLabelWidget * tempLabel;
    leWidget * colorPanel;
    leFixedString tempStr;
    leChar tempStrBuff[MAX_TEMP_STR_LENGTH];
    leLabelWidget * lineGraphLabel;
    leScheme ColorSelectScheme;
    leLabelWidget * bleInfoLabel;
    leImageWidget * bleInfoConnected;
    leFixedString bleAddrString;
    leChar bleAddrStringBuff[DEVICE_ADDR_SIZE + 1];    
} ML_CONTROL_DEVICE;

typedef struct
{
    leWidget ** widget;
    uint32_t delayMS;
} ML_INFOGRAPH_ANIM_OBJ;

#ifdef ENABLE_UI_DEBUG
static char * appScreenUIStates[ML_CONTROL_MAX_STATES] = 
{
    "ML_CONTROL_INIT",
    "ML_CONTROL_ANIM0",
    "ML_CONTROL_ANIM1",
    "ML_CONTROL_ANIM2",
    "ML_CONTROL_INIT_DONE",
    "ML_CONTROL_PROCESSING",
    "ML_CONTROL_DISCONNECT",
    "ML_CONTROL_EXIT",
};
#endif

static const struct leScheme * lineGraphDeviceScheme[APP_BLE_DEVICE_MAX] = 
{
    &RedScheme,
    &GreenScheme,
    &BlueScheme,
};

#if 1
static ML_INFOGRAPH_ANIM_OBJ infoGraphShowAnimObjs[] = 
{
    {&ControlScreen_SmartConSecLogoBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_MfgBlock, INFOGRAPH_ANIM_DELAY_SLOW_MS},
    {&ControlScreen_BldgBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_EnergyBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_EnvBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_AgriBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_LogiBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_HomeAutoBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_SmartCityBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_SmartBlock, INFOGRAPH_ANIM_DELAY_SLOW_MS},
    {&ControlScreen_ConnectedBlock, INFOGRAPH_ANIM_DELAY_SLOW_MS},
    {&ControlScreen_SecureBlock, INFOGRAPH_ANIM_DELAY_SLOW_MS},
};

static ML_INFOGRAPH_ANIM_OBJ infoGraphHideAnimObjs[] = 
{
    {&ControlScreen_MfgBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_BldgBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_EnergyBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_EnvBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_AgriBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_LogiBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_HomeAutoBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_SmartCityBlock, INFOGRAPH_ANIM_DELAY_FAST_MS},
    {&ControlScreen_SmartBlock, 0},
    {&ControlScreen_ConnectedBlock, 0},
    {&ControlScreen_SecureBlock, 0},
    {&ControlScreen_SmartConSecLogoBlock, INFOGRAPH_ANIM_DELAY_MS},    
};
#endif
static ML_CONTROL_SCREEN_STATE appScreenMLControlState;
static SYS_TIME_HANDLE mlControlAnimTimer = SYS_TIME_HANDLE_INVALID;
static SYS_TIME_HANDLE mlControlGraphTimer = SYS_TIME_HANDLE_INVALID;

static volatile uint32_t mlControlAnimTickCount = 0;
static uint32_t mlControlAnimTickPrev = 0;
static APP_UI_MSG uiMsg = {0};
static APP_BLE_MSG bleMsg = {0};
static uint32_t bleCallbackIdx;
static uint32_t httpCallbackIdx;
static APP_UI_LED_CFG ledCfg = {0};
static ML_CONTROL_DATAPANEL_STATE dataPanelState = ML_CTRL_DATA_GRAPH;
static uint32_t infoGraphAnimIdx = 0;

static leFixedString numWifiConnStr;
static leChar numWifiConnStrBuff[4];

leScheme ColorWheelSelectScheme;

static ML_CONTROL_DEVICE devices[APP_BLE_DEVICE_MAX] = {0};

static uint32_t deviceTempRunValue[APP_BLE_DEVICE_MAX][NUM_TEMP_GRAPH_ENTRIES] = {0};

static void HideInfoWidgets(void);
static void ShowDeviceInfoWidgets(void);
static void ShowBluetoothInfoWidgets(void);
static void ShowWifiInfoWidgets(void);

static void MLControlAnimTimer_Callback (uintptr_t context);
static void MLControlGraphTimer_Callback (uintptr_t context);

static void MLControlSetState(ML_CONTROL_SCREEN_STATE state);
static void MultiLink_InitDeviceControlTable(void);
static void MultiLink_DestroyDeviceControlTable(void);
static APP_RESULT MLControlSendEventParm(APP_UI_EVENTS event, uint32_t num);
static leBool ColorSelector_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);
static leBool Slider_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);
static void SetBrightnessValue(uint32_t pct);
static void SetSliderPosition(uint32_t pct);
static void MultiLink_UpdateDeviceColor(gfxColor color888);
static void UpdateDeviceColorPanel(APP_BLE_DEVICE_ID id, gfxColor color888);

static leWidgetEventFilter ColorSelector_eventFilter =
{
    ColorSelector_filterEvent,
    NULL
};

static leWidgetEventFilter BrightnessSlider_eventFilter =
{
    Slider_filterEvent,
    NULL
};

static leColor rgb888_rgb565(leColor color)
{
    uint32_t red, green, blue;
    
    red = (color & 0xF80000) >> 8;
    green = (color & 0xFC00) >> 5;
    blue = (color & 0xF8) >> 3;
    
    return red | green | blue;
}

void event_ControlScreen_DisconnectButton_OnPressed(leButtonWidget* btn)
{
    APP_UI_SendEvent(APP_EVENT_UI_START_DISCONNECT);
}

void event_ControlScreen_DeviceAButton_OnPressed(leButtonWidget* btn)
{
    MLControlSendEventParm(APP_EVENT_UI_SELECT_DEVICE, APP_BLE_DEVICE_A);
}

void event_ControlScreen_DeviceBButton_OnPressed(leButtonWidget* btn)
{
    MLControlSendEventParm(APP_EVENT_UI_SELECT_DEVICE, APP_BLE_DEVICE_B);
}

void event_ControlScreen_DeviceCButton_OnPressed(leButtonWidget* btn)
{
    MLControlSendEventParm(APP_EVENT_UI_SELECT_DEVICE, APP_BLE_DEVICE_C);
}

void event_ControlScreen_AllDevicesButton_OnPressed(leButtonWidget* btn)
{
    APP_UI_SendEvent(APP_EVENT_UI_DEACTIVATE_ALL_DEVICES);
    APP_LE_SETSCHEME(btn, &TextInactiveScheme);
    
}

void event_ControlScreen_AllDevicesButton_OnReleased(leButtonWidget* btn)
{
    APP_UI_SendEvent(APP_EVENT_UI_ACTIVATE_ALL_DEVICES);
}


void event_ControlScreen_DeviceInfoButton_OnPressed(leButtonWidget* btn)
{
    APP_LE_SETRELEASEDIMAGE(ControlScreen_DeviceInfoButton, graphtab60);
    APP_LE_SETRELEASEDIMAGE(ControlScreen_WiFiInfoButton, WifiTab60);
    APP_LE_SETRELEASEDIMAGE(ControlScreen_BLEInfoButton, bleTab60);
    
    switch(dataPanelState)
    {
        case ML_CTRL_DATA_GRAPH:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFOGRAPHIC);
            break;
        }
        case ML_CTRL_INFOGRAPHIC:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFOGRAPHIC);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFO_GRAPH);
            APP_LE_SETRELEASEDIMAGE(ControlScreen_DeviceInfoButton, GraphTabA60);
            
            break;
        }
        default:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFO_GRAPH);
            APP_LE_SETRELEASEDIMAGE(ControlScreen_DeviceInfoButton, GraphTabA60);
            break;
        }
    }
}

void event_ControlScreen_BLEInfoButton_OnPressed(leButtonWidget* btn)
{
    APP_LE_SETRELEASEDIMAGE(ControlScreen_DeviceInfoButton, graphtab60);
    APP_LE_SETRELEASEDIMAGE(ControlScreen_WiFiInfoButton, WifiTab60);
    APP_LE_SETRELEASEDIMAGE(ControlScreen_BLEInfoButton, bleTab60);
    
    switch(dataPanelState)
    {
        case ML_CTRL_DATA_BLE:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFOGRAPHIC);
            break;
        }
        case ML_CTRL_INFOGRAPHIC:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFOGRAPHIC);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFO_BLE);
            APP_LE_SETRELEASEDIMAGE(ControlScreen_BLEInfoButton, bleTabA60);
            
            break;
        }
        default:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFO_BLE);
            APP_LE_SETRELEASEDIMAGE(ControlScreen_BLEInfoButton, bleTabA60);
            break;
        }
    }
}

void event_ControlScreen_WiFiInfoButton_OnPressed(leButtonWidget* btn)
{
    APP_LE_SETRELEASEDIMAGE(ControlScreen_DeviceInfoButton, graphtab60);
    APP_LE_SETRELEASEDIMAGE(ControlScreen_WiFiInfoButton, WifiTab60);
    APP_LE_SETRELEASEDIMAGE(ControlScreen_BLEInfoButton, bleTab60);
    
    switch(dataPanelState)
    {
        case ML_CTRL_DATA_WIFI:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFOGRAPHIC);
            break;
        }
        case ML_CTRL_INFOGRAPHIC:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFOGRAPHIC);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFO_WIFI);
            APP_LE_SETRELEASEDIMAGE(ControlScreen_WiFiInfoButton, WifiTabA60);
            
            break;
        }
        default:
        {
            APP_UI_SendEvent(APP_EVENT_UI_HIDE_INFO);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFO_WIFI);
            APP_LE_SETRELEASEDIMAGE(ControlScreen_WiFiInfoButton, WifiTabA60);
            break;
        }
    }
}


void ControlScreen_OnShow(void)
{
    uint32_t i = 0;
    uint32_t temp;
    APP_BLE_DEVICE * device;
    char tempCharBuff[MAX_TEMP_STR_LENGTH] = {0};
    
    MLControlSetState(ML_CONTROL_INIT);
    
    MultiLink_InitDeviceControlTable();
    
    APP_LE_SETEVENTFILTER(ControlScreen_ColorPickerImage, ColorSelector_eventFilter);
    APP_LE_SETEVENTFILTER(ControlScreen_SliderControlPanel, BrightnessSlider_eventFilter);
    
    APP_LE_SETY(ControlScreen_ColorPickerImage, CONTROL_POSY_HIDE_BOTTOM);
    APP_LE_SETX(ControlScreen_SliderImageWidget, 800);

    APP_LE_SETVISIBLE(ControlScreen_ScrollKnobImageWidget, LE_FALSE);
    APP_LE_SETVISIBLE(ControlScreen_AllDevicesButton, LE_FALSE);
    
    APP_LE_SETVISIBLE(ControlScreen_DeviceInfoButton, LE_FALSE);
    APP_LE_SETVISIBLE(ControlScreen_BLEInfoButton, LE_FALSE);
    APP_LE_SETVISIBLE(ControlScreen_WiFiInfoButton, LE_FALSE);
    
    ledCfg.brightness = DEFAULT_LED_BRIGHTNESS_PCT;
    ledCfg.color888 = DEFAULT_LED_COLOR_RGB;
    
    mlControlAnimTickCount = 0;
    mlControlAnimTimer = SYS_TIME_CallbackRegisterMS(MLControlAnimTimer_Callback,
                                                     1, ANIM_TIMER_TICK_PERIOD_MS,
                                                     SYS_TIME_PERIODIC); 
    
    mlControlGraphTimer = SYS_TIME_CallbackRegisterMS(MLControlGraphTimer_Callback,
                                                     1, GRAPH_TIMER_TICK_PERIOD_MS,
                                                     SYS_TIME_PERIODIC);
    
    bleCallbackIdx = APP_BLE_RegisterStateNotification(APP_UI_BLE_EventCallback);
    
    httpCallbackIdx = APP_HTTP_RegisterStateNotification(APP_UI_HTTP_EventCallback);

    //Configure device UI based on status
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        device = APP_BLED_GetMultiLinkDemoDevice(i);
        
        if (device->connected)
        {
            APP_LE_SETVISIBLE(devices[i].button, LE_TRUE);
            APP_LE_SHOWIMAGE_IDX(devices[i].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
            
            if (APP_BLED_GetDeviceTemp(device, CELS, &temp) == APP_SUCCESS)
            {
                snprintf(tempCharBuff, sizeof(tempCharBuff), "%lu°C", temp);
                
                //updateDeviceTempRunValue(device->idx, temp);
            }
            else
            {
                snprintf(tempCharBuff, sizeof(tempCharBuff), "--°");
                
            }
            
            APP_LE_SETVISIBLE(devices[i].tempLabel, LE_TRUE);
            APP_LE_SETVISIBLE(devices[i].colorPanel, LE_TRUE);
            devices[i].tempStr.fn->setFromCStr(&devices[i].tempStr, tempCharBuff);  
            devices[i].tempLabel->fn->setString(devices[i].tempLabel, (leString*)&devices[i].tempStr);
        }
        else
        {
            APP_LE_SETVISIBLE(devices[i].tempLabel, LE_FALSE);
            APP_LE_SETVISIBLE(devices[i].colorPanel, LE_FALSE);
            APP_LE_SETVISIBLE(devices[i].button, LE_FALSE);
            APP_LE_SHOWIMAGE_IDX(devices[i].deviceImage, DEVICE_INACTIVE_IMAGE_ID);
        }
    }
    
    
    leFixedString_Constructor(&numWifiConnStr, numWifiConnStrBuff, 4);
    numWifiConnStr.fn->setFont(&numWifiConnStr, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              stringID_ZeroValueStr,
                                                              0));
    snprintf(tempCharBuff, sizeof(tempCharBuff), "%lu", APP_WIFI_GetConnectedCount());
    numWifiConnStr.fn->setFromCStr(&numWifiConnStr, tempCharBuff);
    APP_LE_SETLABELSTRING(ControlScreen_NetConnInfo, numWifiConnStr);
    
    HideInfoWidgets();
    
    APP_LE_SETVISIBLE(ControlScreen_AnimImageWidget, LE_FALSE);
    
    APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, INFO_PANEL_MIN_HEIGHT);

    APP_LE_SETVISIBLE(ControlScreen_DisconnectButton, LE_FALSE);    
    
}

void ControlScreen_OnHide(void)
{
    MultiLink_DestroyDeviceControlTable();
    
    SYS_TIME_TimerDestroy(mlControlAnimTimer);
    APP_BLE_UnregisterStateNotification(bleCallbackIdx);    
    APP_HTTP_UnregisterStateNotification(httpCallbackIdx);
}

void ControlScreen_OnUpdate(void)
{
    switch(appScreenMLControlState)
    {
        case ML_CONTROL_INIT:
        {
            MLControlSetState(ML_CONTROL_ANIM0);
            SYS_TIME_TimerStart(mlControlAnimTimer);

            break;
        }
        case ML_CONTROL_ANIM0:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlControlAnimTickCount != mlControlAnimTickPrev)
            {
                int32_t ypos = APP_LE_GETY(ControlScreen_ColorPickerImage);
                int32_t deltaY = (ypos - COLOR_PICKER_YPOS) / CONTROL_ANIM_COEFF;
                
                if (deltaY > 0)
                {
                    APP_LE_SETY(ControlScreen_ColorPickerImage, ypos - deltaY);
                }
                else
                {
                    appScreenMLControlState = ML_CONTROL_ANIM1;
                    
                    APP_LE_SETY(ControlScreen_ColorPickerImage, COLOR_PICKER_YPOS);
                }
                
                mlControlAnimTickPrev = mlControlAnimTickCount;
            }            

            break;
        }
        case ML_CONTROL_ANIM1:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlControlAnimTickCount != mlControlAnimTickPrev)
            {
                int32_t xpos = APP_LE_GETX(ControlScreen_SliderImageWidget);
                int32_t deltaX = (xpos - SLIDER_X_SHOWPOS) / CONTROL_ANIM_COEFF;
                
                if (deltaX > 0)
                {
                    APP_LE_SETX(ControlScreen_SliderImageWidget, xpos - deltaX);
                }
                else
                {
                    SYS_TIME_TimerStop(mlControlAnimTimer);
                    
                    appScreenMLControlState = ML_CONTROL_ANIM2;
                    
                    APP_LE_SETX(ControlScreen_SliderImageWidget, SLIDER_X_SHOWPOS);
                }
                
                mlControlAnimTickPrev = mlControlAnimTickCount;
            }            

            break;
        }
        case ML_CONTROL_ANIM2:
        {
            APP_LE_SETVISIBLE(ControlScreen_ScrollKnobImageWidget, LE_TRUE);
            APP_LE_SETVISIBLE(ControlScreen_AllDevicesButton, LE_TRUE);
            
            APP_LE_SETVISIBLE(ControlScreen_DeviceInfoButton, LE_TRUE);
            APP_LE_SETVISIBLE(ControlScreen_BLEInfoButton, LE_TRUE);
            APP_LE_SETVISIBLE(ControlScreen_WiFiInfoButton, LE_TRUE);
            
#ifdef ENABLE_DISCONNECT_BUTTON    
            APP_LE_SETVISIBLE(LightControlScreen_DisconnectButton, LE_TRUE);
#endif            

            MLControlSetState(ML_CONTROL_INIT_DONE);

            break;
        }
        case ML_CONTROL_INIT_DONE:
        {
            Control_SendBLELEDOnOffMsg(&bleMsg, true, true);
            
            MLControlSetState(ML_CONTROL_PROCESSING);
            
            APP_UI_SendEvent(APP_EVENT_UI_ACTIVATE_ALL_DEVICES);
            APP_UI_SendEvent(APP_EVENT_UI_SHOW_INFOGRAPHIC);
            
            break;
        }
        case ML_CONTROL_HIDE_INFO:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, INFO_PANEL_MIN_HEIGHT);
            MLControlSetState(ML_CONTROL_PROCESSING);
            
//            if (mlControlAnimTickCount != mlControlAnimTickPrev)
//            {
//                int32_t height = APP_LE_GETHEIGHT(LightControlScreen_DeviceDataPanelA);
//                int32_t deltaHeight = height / CONTROL_PANEL_ANIM_COEFF;
//                
//                if (deltaHeight > 0)
//                {
//                    APP_LE_SETHEIGHT(LightControlScreen_DeviceDataPanelA, height - deltaHeight);
//                }
//                else
//                {
//                    APP_LE_SETHEIGHT(LightControlScreen_DeviceDataPanelA, INFO_PANEL_MIN_HEIGHT);
//                    
//                    SYS_TIME_TimerStop(mlControlAnimTimer);
//                    
//                    dataPanelState = ML_CTRL_DATA_NONE;
//                    
//                    MLControlSetState(ML_CONTROL_PROCESSING);                    
//                }
//                
//                mlControlAnimTickPrev = mlControlAnimTickCount;
//            }
            
            break;
        }
        case ML_CONTROL_SHOW_GRAPH:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlControlAnimTickCount != mlControlAnimTickPrev)
            {
                int32_t height = APP_LE_GETHEIGHT(ControlScreen_DeviceDataPanelA);
                int32_t deltaHeight = (INFO_PANEL_HEIGHT - height) / CONTROL_PANEL_ANIM_COEFF;
                
                APP_LE_SETSCHEME(ControlScreen_DeviceDataPanelA, &GraphScheme);
                
                if (deltaHeight > 0)
                {
                    APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, height + deltaHeight);
                }
                else
                {
                    APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, INFO_PANEL_HEIGHT);
                    
                    ShowDeviceInfoWidgets();
                    
                    SYS_TIME_TimerStop(mlControlAnimTimer);
                    
                    dataPanelState = ML_CTRL_DATA_GRAPH;
                    
                    MLControlSetState(ML_CONTROL_PROCESSING);                    
                }
                
                mlControlAnimTickPrev = mlControlAnimTickCount;
            }            
            
            break;
        }
        case ML_CONTROL_SHOW_INFOGRAPH:
        {
            if (infoGraphAnimIdx < sizeof(infoGraphShowAnimObjs)/sizeof(ML_INFOGRAPH_ANIM_OBJ))
            {
                //clear the blocking panels
                leWidget * widget = *infoGraphShowAnimObjs[infoGraphAnimIdx].widget;
                
                APP_LE_SETVISIBLE(widget, LE_FALSE);
                //FIXME DELAY
//                vTaskDelay(infoGraphShowAnimObjs[infoGraphAnimIdx].delayMS / portTICK_PERIOD_MS);
                
                infoGraphAnimIdx++;
            }
            else
            {
                dataPanelState = ML_CTRL_INFOGRAPHIC;
                
                MLControlSetState(ML_CONTROL_PROCESSING);  
            }
            
            break;
        }
        case ML_CONTROL_HIDE_INFOGRAPH:
        {
            if (infoGraphAnimIdx < sizeof(infoGraphHideAnimObjs)/sizeof(ML_INFOGRAPH_ANIM_OBJ))
            {
                leWidget * widget = *infoGraphHideAnimObjs[infoGraphAnimIdx].widget;
                
                //Show the blocking panels
                APP_LE_SETVISIBLE(widget, LE_TRUE);
                //FIXME DELAY
//                vTaskDelay(infoGraphHideAnimObjs[infoGraphAnimIdx].delayMS / portTICK_PERIOD_MS);
                
                infoGraphAnimIdx++;
            }
            else
            {
                //Hide the inforgraphic
                APP_LE_SETVISIBLE(ControlScreen_AnimImageWidget, LE_FALSE);
                
                dataPanelState = ML_CTRL_DATA_NONE;
                
                MLControlSetState(ML_CONTROL_PROCESSING);  
            }
            
            break;
        }        
        case ML_CONTROL_SHOW_BLE:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlControlAnimTickCount != mlControlAnimTickPrev)
            {
                int32_t height = APP_LE_GETHEIGHT(ControlScreen_DeviceDataPanelA);
                int32_t deltaHeight = (INFO_PANEL_HEIGHT - height) / CONTROL_PANEL_ANIM_COEFF;
                
                APP_LE_SETSCHEME(ControlScreen_DeviceDataPanelA, &BLEPanelScheme);
                
                if (deltaHeight > 0)
                {
                    APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, height + deltaHeight);
                }
                else
                {
                    APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, INFO_PANEL_HEIGHT);
                    
                    ShowBluetoothInfoWidgets();
                    
                    SYS_TIME_TimerStop(mlControlAnimTimer);
                    
                    dataPanelState = ML_CTRL_DATA_BLE;
                    
                    MLControlSetState(ML_CONTROL_PROCESSING);                    
                }
                
                mlControlAnimTickPrev = mlControlAnimTickCount;
            }
            
            break;
        }
        case ML_CONTROL_SHOW_WIFI:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mlControlAnimTickCount != mlControlAnimTickPrev)
            {
                int32_t height = APP_LE_GETHEIGHT(ControlScreen_DeviceDataPanelA);
                int32_t deltaHeight = (INFO_PANEL_HEIGHT - height) / CONTROL_PANEL_ANIM_COEFF;
                
                APP_LE_SETSCHEME(ControlScreen_DeviceDataPanelA, &WifiPanelScheme);
                
                if (deltaHeight > 0)
                {
                    APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, height + deltaHeight);
                }
                else
                {
                    APP_LE_SETHEIGHT(ControlScreen_DeviceDataPanelA, INFO_PANEL_HEIGHT);
                    
                    ShowWifiInfoWidgets();
                    
                    SYS_TIME_TimerStop(mlControlAnimTimer);
                    
                    dataPanelState = ML_CTRL_DATA_WIFI;
                    
                    MLControlSetState(ML_CONTROL_PROCESSING);                    
                }
                
                mlControlAnimTickPrev = mlControlAnimTickCount;
            }

            break;
        }
        case ML_CONTROL_PROCESSING:
        {
            if (APP_UI_ReadMsg(&uiMsg) == APP_SUCCESS)
            {
                switch(uiMsg.event)
                {
                    case APP_EVENT_UI_HIDE_INFO:
                    {
                        SYS_TIME_TimerStart(mlControlAnimTimer);
                        
                        HideInfoWidgets();                        
                        
                        MLControlSetState(ML_CONTROL_HIDE_INFO);
                        
                        break;
                    }
                    case APP_EVENT_UI_HIDE_INFOGRAPHIC:
                    {
                        infoGraphAnimIdx = 0;
                        
                        MLControlSetState(ML_CONTROL_HIDE_INFOGRAPH);

                        break;
                    }
                    case APP_EVENT_UI_SHOW_INFOGRAPHIC:
                    {
                        APP_LE_SETVISIBLE(ControlScreen_AnimImageWidget, LE_TRUE);
                        
                        infoGraphAnimIdx = 0;
                        
                        MLControlSetState(ML_CONTROL_SHOW_INFOGRAPH);
                        
                        break;
                    }
                    case APP_EVENT_UI_SHOW_INFO_GRAPH:
                    {
                        SYS_TIME_TimerStart(mlControlAnimTimer);
                        
                        MLControlSetState(ML_CONTROL_SHOW_GRAPH);

                        break;
                    }
                    case APP_EVENT_UI_SHOW_INFO_WIFI:
                    {
                        SYS_TIME_TimerStart(mlControlAnimTimer);
                        
                        MLControlSetState(ML_CONTROL_SHOW_WIFI);
                        
                        break;
                    }
                    case APP_EVENT_UI_SHOW_INFO_BLE:
                    {
                        SYS_TIME_TimerStart(mlControlAnimTimer);
                        
                        MLControlSetState(ML_CONTROL_SHOW_BLE);
                        
                        break;
                    }
                    case APP_EVENT_UI_ML_LED_COLOR_SELECTED:
                    {
                        if (uiMsg.param.num != ledCfg.color888)
                        {
                            ledCfg.color888 = uiMsg.param.num;

                            MultiLink_UpdateDeviceColor(ledCfg.color888);

                            Control_SendBLELEDColorSetMsg(&bleMsg, &ledCfg, APP_BLE_DEVICE_ALL);
                        }
                        break;
                    }
                    case APP_EVENT_UI_LED_UPDATE:
                    {
                        Control_SendBLELEDColorSetMsg(&bleMsg, &ledCfg, APP_BLE_DEVICE_ALL);
                        
//                        vTaskDelay(CONTROL_DELAY_MS / portTICK_PERIOD_MS);
                        
                        break;
                    }
                    case APP_EVENT_UI_LED_BRIGHTNESS_SET:
                    {
                        uint32_t i;
                        
                        //Activate all devices based on status
                        for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
                        {
                            APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);

                            if (device != NULL && 
                                device->connected == true &&
                                device->active == true)
                            {             
                                APP_UI_LED_CFG cfg;
                                
                                cfg = ledCfg;
                                
                                APP_BLED_GetDeviceColor(i, &cfg.color888);
                                
                                Control_SendBLELEDColorSetMsg(&bleMsg, &cfg, i);
                            }
                        }
                        
                        break;
                    }
                    case APP_EVENT_UI_START_DISCONNECT:
                    {
                        MLControlSetState(ML_CONTROL_DISCONNECT);
                        
                        break;
                    }
                    case APP_EVENT_UI_SELECT_DEVICE:
                    {
                        APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(uiMsg.param.num);
                                
                        if(device != NULL && device->connected == true)
                        {
                            Screen_SetActiveDevice(device);
                            bleMsg.device = device;
                            
                            if (device->active == true)
                            {
                                APP_LE_SHOWIMAGE_IDX(devices[uiMsg.param.num].deviceImage, DEVICE_INACTIVE_IMAGE_ID);
                                APP_LE_SETSCHEME(devices[uiMsg.param.num].tempLabel, &TextInactiveScheme);

                                device->active = false;
                            }
                            else
                            {
                                APP_LE_SHOWIMAGE_IDX(devices[uiMsg.param.num].deviceImage, DEVICE_ACTIVE_IMAGE_ID);
                                APP_LE_SETSCHEME(devices[uiMsg.param.num].tempLabel, &TextScheme);
                                
                                bleMsg.device = device;
                                Control_SendBLELEDOnOffMsg(&bleMsg, true, false);                                
                                
                                device->active = true;
                            }
                        }
                        
                        break;
                    }
                    case APP_EVENT_UI_ACTIVATE_ALL_DEVICES:
                    {
                        uint32_t i;
                        //Activate all devices based on status
                        for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
                        {
                            APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);

                            if (device != NULL && device->connected == true)
                            {
                                APP_LE_SETSCHEME(devices[i].tempLabel, &TextScheme);
                                APP_LE_SHOWIMAGE_IDX(devices[i].deviceImage, DEVICE_ACTIVE_IMAGE_ID);

                                Screen_SetActiveDevice(device);
                                bleMsg.device = device;
                                
                                Control_SendBLELEDOnOffMsg(&bleMsg, true, false);
                                
                                device->active = true;
                            }
                        }  
                        
                        APP_LE_SETSCHEME(ControlScreen_AllDevicesButton, &TextScheme); 
                        
                        break;
                    }
                    case APP_EVENT_UI_DEACTIVATE_ALL_DEVICES:
                    {
                        uint32_t i;
                        
                        for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
                        {
                            APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);

                            if (device != NULL && device->connected == true)
                            {
                                APP_LE_SETSCHEME(devices[i].tempLabel, &TextInactiveScheme);
                                APP_LE_SHOWIMAGE_IDX(devices[i].deviceImage, DEVICE_INACTIVE_IMAGE_ID);

                                Screen_SetActiveDevice(device);
                                bleMsg.device = device;
                                
                                Control_SendBLELEDOnOffMsg(&bleMsg, false, false);
                                
                                device->active = false;
                            }
                        }
                        
                        APP_LE_SETSCHEME(ControlScreen_AllDevicesButton, &TextInactiveScheme); 

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
                                    uint32_t temp;
                                    char tempCharBuff[MAX_TEMP_STR_LENGTH] = {0};
    
                                    UI_DPRINTF("UI: TEMP Notif %lu \r\n", outValue);
                                    
                                    device->tempSensorValue = outValue;
                                    
                                    if (APP_BLED_GetDeviceTemp(device, CELS, &temp) == APP_SUCCESS)
                                    {
                                        snprintf(tempCharBuff, sizeof(tempCharBuff), "%lu°C", temp);
                                        
                                        //send event to update graph widget
                                        MLControlSendEventParm(APP_EVENT_UI_GRAPH_UPDATE, 0);
                                    }
                                    else
                                    {
                                        snprintf(tempCharBuff, sizeof(tempCharBuff), "--°C");

                                    }

                                    devices[device->idx].tempStr.fn->setFromCStr(&devices[device->idx].tempStr, tempCharBuff);  
                                    devices[device->idx].tempLabel->fn->setString(devices[device->idx].tempLabel, (leString*)&devices[device->idx].tempStr);                                    

                                }
                            }
                        }

                        break;
                    }
                    case APP_EVENT_UI_GRAPH_UPDATE:
                    {
                        uint32_t i;
                        
                        for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
                        {
                            APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);

                            if (device != NULL && device->connected == true)
                            {
                                uint32_t temp;
                                
                                if (APP_BLED_GetDeviceTemp(device, CELS, &temp) == APP_SUCCESS)
                                {
                                    //updateDeviceTempRunValue(device->idx, temp);
                                }
                            }
                        }
                        
                        break;
                    }
                    case APP_EVENT_HTTP_CONNECTED:
                    case APP_EVENT_HTTP_DISCONNECTED:
                    {
                        char tempCharBuff[MAX_TEMP_STR_LENGTH] = {0};
                        
                        snprintf(tempCharBuff, sizeof(tempCharBuff), "%lu", APP_WIFI_GetConnectedCount());
                        numWifiConnStr.fn->setFromCStr(&numWifiConnStr, tempCharBuff);
                        APP_LE_SETLABELSTRING(ControlScreen_NetConnInfo, numWifiConnStr);
                        break;
                    }
                    case APP_EVENT_HTTP_DEVICE_CONTROL:
                    {
                        if (uiMsg.device < APP_BLE_DEVICE_MAX)
                        {
                            UpdateDeviceColorPanel(uiMsg.device, uiMsg.param.num);
                        }

                        break;
                    }
                    default:
                        break;
                }
            }

            break;
        }
        case ML_CONTROL_DISCONNECT:
        {
            bleMsg.cmd = APP_BLE_CMD_ABORT;
            APP_BLE_Send_Msg(&bleMsg);
                        
            MLControlSetState(ML_CONTROL_EXIT);
            
            break;
        }
        case ML_CONTROL_EXIT:
        {
            legato_showScreen(screenID_MainMenu);
            
            break;
        }
        default:
            break;
    }
}

static void MLControlAnimTimer_Callback (uintptr_t context)
{
    mlControlAnimTickCount++;
}

static void MLControlGraphTimer_Callback (uintptr_t context)
{
    MLControlSendEventParm(APP_EVENT_UI_GRAPH_UPDATE, 0);
}

static void MLControlSetState(ML_CONTROL_SCREEN_STATE state)
{
    appScreenMLControlState = state;
    
#ifdef ENABLE_UI_DEBUG       
    UI_DPRINTF("UI State is %s \r\n", appScreenUIStates[state]);
#endif    
    
}

static APP_RESULT MLControlSendEventParm(APP_UI_EVENTS event, uint32_t num)
{
    uiMsg.event = event;
    uiMsg.param.num = num;

    return APP_UI_SendMsg(&uiMsg);
}

static void MultiLink_InitDeviceControlTable(void)
{
    uint32_t i;
    
    devices[APP_BLE_DEVICE_A] = (ML_CONTROL_DEVICE)
    {   
        .button = ControlScreen_DeviceAButton,
        .deviceImage = ControlScreen_ImageSequenceWidgetA, 
        .tempLabel = ControlScreen_TempLabelA,
        .colorPanel = ControlScreen_SelectedColorPanelA,
        .lineGraphLabel = ControlScreen_LineGraphLabelA,
        .bleInfoLabel = ControlScreen_BLEDeviceAName,                
        .bleInfoConnected = ControlScreen_BLEDeviceAOK,
    };
    
    devices[APP_BLE_DEVICE_B] = (ML_CONTROL_DEVICE)
    {   
        .button = ControlScreen_DeviceBButton,
        .deviceImage = ControlScreen_ImageSequenceWidgetB, 
        .tempLabel = ControlScreen_TempLabelB,
        .colorPanel = ControlScreen_SelectedColorPanelB,
        .lineGraphLabel = ControlScreen_LineGraphLabelB,
        .bleInfoLabel = ControlScreen_BLEDeviceBName,
        .bleInfoConnected = ControlScreen_BLEDeviceBOK,
    };
    
    devices[APP_BLE_DEVICE_C] = (ML_CONTROL_DEVICE)
    {   
        .button = ControlScreen_DeviceCButton,
        .deviceImage = ControlScreen_ImageSequenceWidgetC, 
        .tempLabel = ControlScreen_TempLabelC,
        .colorPanel = ControlScreen_SelectedColorPanelC,
        .lineGraphLabel = ControlScreen_LineGraphLabelC,
        .bleInfoLabel = ControlScreen_BLEDeviceCName,              
        .bleInfoConnected = ControlScreen_BLEDeviceCOK,
    };
    
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        memset(devices[i].tempStrBuff, 0, sizeof(leChar) * MAX_TEMP_STR_LENGTH);
        leFixedString_Constructor(&devices[i].tempStr, devices[i].tempStrBuff, MAX_TEMP_STR_LENGTH);
        devices[i].tempStr.fn->setFont(&devices[i].tempStr,
                                       leStringTable_GetStringFont(leGetState()->stringTable,
                                       stringID_DefaultTemp,
                                       0));
        
        
        memset(devices[i].bleAddrStringBuff, 0, sizeof(leChar) * (DEVICE_ADDR_SIZE + 1));
        leFixedString_Constructor(&devices[i].bleAddrString, devices[i].bleAddrStringBuff, DEVICE_ADDR_SIZE + 1);
        devices[i].bleAddrString.fn->setFont(&devices[i].bleAddrString,
                                       leStringTable_GetStringFont(leGetState()->stringTable,
                                       stringID_BLEDeviceInfo,
                                       0));
    }
}

static void MultiLink_DestroyDeviceControlTable(void)
{
    uint32_t i;
    
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        devices[i].tempStr.fn->destructor(&devices[i].tempStr);
    }
}

static void UpdateDeviceColorPanel(APP_BLE_DEVICE_ID id, gfxColor color888)
{
    if (id < APP_BLE_DEVICE_MAX)
    {
        APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(id);

        if(device != NULL && 
           device->connected == true && 
           device->active == true)
        {
            devices[id].ColorSelectScheme.tables[LE_COLOR_MODE_RGB_565].colors.base = rgb888_rgb565(color888);
            devices[id].ColorSelectScheme.tables[LE_COLOR_MODE_RGB_888].colors.base = color888;
            
            ControlScreen_BarGraphWidget_0->fn->setDataInSeries(ControlScreen_BarGraphWidget_0, 
                                                                         0, id, 
                                                                         leColorChannelRed(color888, LE_COLOR_MODE_RGB_888));
            ControlScreen_BarGraphWidget_0->fn->setDataInSeries(ControlScreen_BarGraphWidget_0, 
                                                                         1, id, 
                                                                         leColorChannelGreen(color888, LE_COLOR_MODE_RGB_888));
            ControlScreen_BarGraphWidget_0->fn->setDataInSeries(ControlScreen_BarGraphWidget_0, 
                                                                         2, id, 
                                                                         leColorChannelBlue(color888, LE_COLOR_MODE_RGB_888));        
            
            APP_LE_INVALIDATE(ControlScreen_BarGraphWidget_0);

            APP_LE_SETSCHEME(devices[id].colorPanel, (const leScheme *) &devices[id].ColorSelectScheme);
            devices[id].colorPanel->fn->invalidate(devices[id].colorPanel);
        }
    }
}

static void MultiLink_UpdateDeviceColor(gfxColor color888)
{
    uint32_t i = 0;
    
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);

        if(device != NULL && device->connected == true)
        {
            UpdateDeviceColorPanel(i, color888);

            APP_BLED_SetDeviceColor(i, color888);
        }
    }
}

static leBool ColorSelector_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{
    leBool retval = LE_FALSE;    
    lePoint pnt;
    gfxColor color888;
    
    pnt.x = ((leWidgetEvent_TouchDown *) evt)->x;
    pnt.y = ((leWidgetEvent_TouchDown *) evt)->y;      
    
    switch(evt->id)
    {
        case LE_EVENT_TOUCH_MOVE:         
        case LE_EVENT_TOUCH_DOWN:
        {
            evt->accepted = LE_TRUE;
            evt->owner = target;
            
            leUtils_PointScreenToLocalSpace(target, &pnt);
            
            color888 = gfxPixelBufferGet((const gfxPixelBuffer*) 
                                          &ColorPickerBlueBack200_888.buffer,
                                          pnt.x,
                                          pnt.y);            
            
            ColorWheelSelectScheme.tables[LE_COLOR_MODE_RGB_565].colors.base = rgb888_rgb565(color888);
            ColorWheelSelectScheme.tables[LE_COLOR_MODE_RGB_888].colors.base = color888;
            
            APP_LE_SETSCHEME(ControlScreen_ColorWheelSelectColor, (const leScheme *) &ColorWheelSelectScheme);
            APP_LE_INVALIDATE(ControlScreen_ColorWheelSelectColor);
            
            uiMsg.event = APP_EVENT_UI_ML_LED_COLOR_SELECTED;
            uiMsg.param.num = color888;

            APP_UI_SendMsg(&uiMsg);

            retval = LE_TRUE;
            
            break;
        }   
        case LE_EVENT_TOUCH_UP:            
        {
            
            leUtils_PointScreenToLocalSpace(target, &pnt);
            
            color888 = gfxPixelBufferGet((const gfxPixelBuffer*) 
                                          &ColorPickerBlueBack200_888.buffer,
                                          pnt.x,
                                          pnt.y);
            
            uiMsg.event = APP_EVENT_UI_ML_LED_COLOR_SELECTED;
            uiMsg.param.num = color888;

            APP_UI_SendMsg(&uiMsg);
            
            evt->accepted = LE_TRUE;
                    
            retval = LE_TRUE;

            break;        
        }
        default:
            break;
    }
    
   return retval;
}

static leBool Slider_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{
    leBool retval = LE_FALSE;    
    lePoint pnt;
    static uint32_t brightness;
    
    pnt.x = ((leWidgetEvent_TouchDown *) evt)->x;
    pnt.y = ((leWidgetEvent_TouchDown *) evt)->y;
    
    if (leRectContainsPoint(&target->rect, &pnt) == true)
    {
        switch(evt->id)
        {
            case LE_EVENT_TOUCH_MOVE:         
            case LE_EVENT_TOUCH_DOWN:
            {
                evt->accepted = LE_TRUE;
                evt->owner = target;

                retval = LE_TRUE;
                
                //Update brightness and send event
                brightness = ((target->rect.height - (pnt.y - target->rect.y)) * 100) / target->rect.height;
                
                SetSliderPosition(brightness);
                
                SetBrightnessValue(brightness); 

                break;
            }   
            case LE_EVENT_TOUCH_UP:            
            {
                evt->accepted = LE_TRUE;

                retval = LE_TRUE;
                
                SetBrightnessValue(brightness);                

                break;        
            }
            default:
                break;
        }
    }
    
   return retval;
}

static void SetBrightnessValue(uint32_t pct)
{
    if (ledCfg.brightness != pct &&
        pct >= MIN_BRIGHTNESS_PCT)
    {
        ledCfg.brightness = pct;

        APP_UI_SendEvent(APP_EVENT_UI_LED_BRIGHTNESS_SET);
    }
}

static void SetSliderPosition(uint32_t pct)
{
    uint32_t SliderKnobPosY = 
            ControlScreen_SliderControlPanel->fn->getY(ControlScreen_SliderControlPanel) - 
            ControlScreen_ScrollKnobImageWidget->fn->getHeight(ControlScreen_ScrollKnobImageWidget)/2;
    
    SliderKnobPosY = ControlScreen_SliderControlPanel->fn->getY(ControlScreen_SliderControlPanel) +
                     ((ControlScreen_SliderControlPanel->fn->getHeight(ControlScreen_SliderControlPanel) * ( 100 - pct)) / 100) - 
                     ControlScreen_ScrollKnobImageWidget->fn->getHeight(ControlScreen_ScrollKnobImageWidget) / 2;
    
    ControlScreen_ScrollKnobImageWidget->fn->setY(ControlScreen_ScrollKnobImageWidget, SliderKnobPosY);
}

static void HideInfoWidgets(void)
{
    uint32_t i;
    
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        APP_LE_SETVISIBLE(devices[i].lineGraphLabel, LE_FALSE);
        
        //BLE Info device widgets
        APP_LE_SETVISIBLE(devices[i].bleInfoConnected, LE_FALSE);
        APP_LE_SETVISIBLE(devices[i].bleInfoLabel, LE_FALSE);
    }
    
    APP_LE_SETVISIBLE(ControlScreen_DeviceInfoLabel, LE_FALSE);
    
    //Graph info widgets
    APP_LE_SETVISIBLE(ControlScreen_ColorGraphLabel, LE_FALSE);
    APP_LE_SETVISIBLE(ControlScreen_LineGraphWidget_0, LE_FALSE);
    APP_LE_SETVISIBLE(ControlScreen_BarGraphWidget_0, LE_FALSE);
    APP_LE_SETVISIBLE(ControlScreen_TempSensorGraphLabel, LE_FALSE);
    
    //Wifi Info Widgets
    APP_LE_SETVISIBLE(ControlScreen_NetInfoPanel, LE_FALSE);
}

static void ShowDeviceInfoWidgets(void)
{
    uint32_t i;
    APP_BLE_DEVICE * device;
    
    //Configure device UI based on status
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        device = APP_BLED_GetMultiLinkDemoDevice(i);
        
        if (device->connected)
        {
            APP_LE_SETVISIBLE(devices[i].lineGraphLabel, LE_TRUE);
        }
        else
        {
            APP_LE_SETVISIBLE(devices[i].lineGraphLabel, LE_FALSE);
        }
    }
    
    APP_LE_SETVISIBLE(ControlScreen_ColorGraphLabel, LE_TRUE);
    APP_LE_SETVISIBLE(ControlScreen_DeviceInfoLabel, LE_TRUE);
    APP_LE_SETVISIBLE(ControlScreen_LineGraphWidget_0, LE_TRUE);
    APP_LE_SETVISIBLE(ControlScreen_BarGraphWidget_0, LE_TRUE);
    APP_LE_SETVISIBLE(ControlScreen_TempSensorGraphLabel, LE_TRUE);
    
    APP_LE_SETLABELSTRING(ControlScreen_DeviceInfoLabel, string_DeviceInfo);
    
    //UpdateTempLineGraph();
}

static void ShowBluetoothInfoWidgets(void)
{
    uint32_t i;
    APP_BLE_DEVICE * device;
    
    //Configure device UI based on status
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        device = APP_BLED_GetMultiLinkDemoDevice(i);
        
        if (device != NULL)
        {
            APP_LE_SETVISIBLE(devices[i].bleInfoLabel, device->active ? LE_TRUE : LE_FALSE);
            APP_LE_SETVISIBLE(devices[i].bleInfoConnected, device->connected ? LE_TRUE : LE_FALSE);
            APP_LE_SETLABELDYNSTRING(devices[device->idx].bleInfoLabel, devices[device->idx].bleAddrString, device->deviceAddress);
        }
    }
    
    APP_LE_SETVISIBLE(ControlScreen_DeviceInfoLabel, LE_TRUE);
    APP_LE_SETLABELSTRING(ControlScreen_DeviceInfoLabel, string_BLEDeviceInfo);
}

static void ShowWifiInfoWidgets(void)
{
    uint16_t leases = 0;
    uint16_t inUse = 0;
//    TCPIP_DHCPS_RES retval;
//    static TCPIP_NET_HANDLE netHdl;
    
    APP_LE_SETLABELSTRING(ControlScreen_DeviceInfoLabel, string_WiFiDeviceInfo);
    APP_LE_SETVISIBLE(ControlScreen_NetInfoPanel, LE_TRUE);
    

    
//    netHdl = TCPIP_STACK_NetHandleGet("WINC");
             
//    retval = TCPIP_DHCPS_LeaseEntriesGet(netHdl, &leases, &inUse);
        
//    APP_DPRINTF("\r\n (%d) retval, (%d) In Use\r\n", retval, inUse);
}


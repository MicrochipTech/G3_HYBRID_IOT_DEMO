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

#define RESTART_ICON_YSHOW_POS 240

#define DEVICE_ICON_POSX_HIDE_LEFT -110
#define DEVICE_ICON_POSX_HIDE_RIGHT 800
#define DEVICE_ICON_POSY_HIDE_BOTTOM 480

#define LIGHT_CONTROL_TIMER_PERIOD_MS   200

#define GAME_ANIM_COEFF 3

#define GAME_NUM_COLORS 6

#define MIN_BRIGHTNESS_PCT 5

typedef enum
{
    ML_GAME_INIT,
    ML_GAME_ANIM0,
    ML_GAME_INIT_DONE,
    ML_GAME_PROCESSING,
    ML_GAME_EXIT_ANIM1,
    ML_GAME_EXIT_ANIM2,            
    ML_GAME_EXIT,
    ML_GAME_MAX_STATES,
} ML_GAME_SCREEN_STATE;

typedef struct
{
    leButtonWidget * button;
    leImageWidget * check;
    leLabelWidget * instruction;
    int32_t xpos;
    int32_t ypos;
    
    bool deviceActive;
    APP_UI_LED_CFG ledCfg;
    
} ML_GAME_DEVICE;

#ifdef ENABLE_UI_DEBUG
static char * appScreenUIStates[ML_GAME_MAX_STATES] = 
{
    "ML_GAME_INIT",
    "ML_GAME_ANIM0",
    "ML_GAME_INIT_DONE",
    "ML_GAME_PROCESSING",
    "ML_GAME_DISCONNECT",
    "ML_GAME_EXIT",
};
#endif

static uint32_t colors888[GAME_NUM_COLORS] = 
{
    0x000000ff, //blue
    0x0000ff00, //green
    0x00ff0000, //red
    0x00A020F0, //purple
    0x00FFFF00, //yellow
    0x00FFA500, //orange
};

static APP_UI_LED_CFG ledCfg = {0};

static ML_GAME_SCREEN_STATE appScreenMLGameState;
static SYS_TIME_HANDLE mlGameAnimTimer = SYS_TIME_HANDLE_INVALID;
static SYS_TIME_HANDLE mlGameLightTimer = SYS_TIME_HANDLE_INVALID;

static volatile uint32_t mlGameAnimTickCount = 0;
static uint32_t mlGameAnimTickPrev = 0;

static uint32_t bleCallbackIdx;

extern QueueHandle_t uiMsgQueue;
static APP_UI_MSG uiMsg = {0};
static APP_BLE_MSG bleMsg = {0};



static ML_GAME_DEVICE devices[APP_BLE_DEVICE_MAX] = {0};
static APP_BLE_DEVICE_ID currentDevice = APP_BLE_DEVICE_A;

static void MLGameAnimTimer_Callback (uintptr_t context);
static void MLGameLightTimer_Callback (uintptr_t context);
static void MLGameSetState(ML_GAME_SCREEN_STATE state);

static void MultiLink_InitDeviceGameTable(void);

static void SetBrightnessValue(uint32_t pct);
static void SetSliderPosition(uint32_t pct);

static leBool Slider_filterEvent(leWidget* target, leWidgetEvent* evt, void* data);

static leWidgetEventFilter BrightnessSlider_eventFilter =
{
    Slider_filterEvent,
    NULL
};

static APP_RESULT MLGameSendEventParm(APP_UI_EVENTS event, uint32_t num)
{
    uiMsg.event = event;
    uiMsg.param.num = num;

    return APP_UI_SendMsg(&uiMsg);
}

void event_MultiLinkGameScreen_DeviceAButton_OnPressed(leButtonWidget* btn)
{
    MLGameSendEventParm(APP_EVENT_UI_SELECT_DEVICE, APP_BLE_DEVICE_A);
}

void event_MultiLinkGameScreen_DeviceBButton_OnPressed(leButtonWidget* btn)
{
    MLGameSendEventParm(APP_EVENT_UI_SELECT_DEVICE, APP_BLE_DEVICE_B);
}

void event_MultiLinkGameScreen_DeviceCButton_OnPressed(leButtonWidget* btn)
{
    MLGameSendEventParm(APP_EVENT_UI_SELECT_DEVICE, APP_BLE_DEVICE_C);
}

void event_MultiLinkGameScreen_RestartGameButton_OnPressed(leButtonWidget* btn)
{
    APP_UI_SendEvent(APP_EVENT_UI_ACTIVATE_ALL_DEVICES);
}

void event_MultiLinkGameScreen_ControlButton_OnPressed(leButtonWidget* btn)
{
    APP_UI_SendEvent(APP_EVENT_UI_START_CONTROL);
}

static void MultiLink_InitDeviceGameTable(void)
{
    uint32_t i;
    
    devices[APP_BLE_DEVICE_A] = (ML_GAME_DEVICE)
    {   
        .button = MultiLinkGameScreen_DeviceAButton,
        .check = MultiLinkGameScreen_DeviceACheck,
        .instruction = MultiLinkGameScreen_StopLabelA,
    };
    
    devices[APP_BLE_DEVICE_B] = (ML_GAME_DEVICE)
    {   
        .button = MultiLinkGameScreen_DeviceBButton,
        .check = MultiLinkGameScreen_DeviceBCheck,
        .instruction = MultiLinkGameScreen_StopLabelB,
    };
    
    devices[APP_BLE_DEVICE_C] = (ML_GAME_DEVICE)
    {   
        .button = MultiLinkGameScreen_DeviceCButton,
        .check = MultiLinkGameScreen_DeviceCCheck,
        .instruction = MultiLinkGameScreen_StopLabelC,                
    };
    
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        devices[i].xpos = APP_LE_GETX(devices[i].button);
        devices[i].ypos = APP_LE_GETY(devices[i].button);
    }
}

void MultiLinkGameScreen_OnShow(void)
{
    APP_BLE_DEVICE * device;
    uint32_t i;
    
    MultiLink_InitDeviceGameTable();
    
    appScreenMLGameState = ML_GAME_INIT;
    
    mlGameAnimTickCount = 0;
    mlGameAnimTimer = SYS_TIME_CallbackRegisterMS(MLGameAnimTimer_Callback,
                                                     1, ANIM_TIMER_TICK_PERIOD_MS,
                                                     SYS_TIME_PERIODIC); 
    
    mlGameLightTimer = SYS_TIME_CallbackRegisterMS(MLGameLightTimer_Callback,
                                                     1, LIGHT_CONTROL_TIMER_PERIOD_MS,
                                                     SYS_TIME_PERIODIC); 

    bleCallbackIdx = APP_BLE_RegisterStateNotification(APP_UI_BLE_EventCallback);    
    
    APP_LE_SETY(MultiLinkGameScreen_RestartGameButton, 320);
    APP_LE_SETVISIBLE(MultiLinkGameScreen_ControlButton, LE_FALSE);
    APP_LE_SETVISIBLE(MultiLinkGameScreen_RestartLabel, LE_FALSE);
    APP_LE_SETVISIBLE(MultiLinkGameScreen_GameTitle, LE_FALSE);
    
    APP_LE_SETEVENTFILTER(MultiLinkGameScreen_SliderControlPanel, BrightnessSlider_eventFilter);
    
    for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
    {
        device = APP_BLED_GetMultiLinkDemoDevice(i);
        
        if (device != NULL && device->connected)
        {
            APP_LE_SETVISIBLE(devices[i].button, LE_TRUE);
        }
        else
        {
            APP_LE_SETVISIBLE(devices[i].button, LE_FALSE);
        }
        
        devices[i].ledCfg.brightness = 50;
        devices[i].ledCfg.color888 = 0x000000ff;
        devices[i].deviceActive = true;

        device->active = true;

        APP_LE_SETVISIBLE(devices[i].check, LE_FALSE);
        APP_LE_SETVISIBLE(devices[i].instruction, LE_FALSE);
    }
}

void MultiLinkGameScreen_OnHide(void)
{
    SYS_TIME_TimerDestroy(mlGameAnimTimer);
    SYS_TIME_TimerDestroy(mlGameLightTimer);
    APP_BLE_UnregisterStateNotification(bleCallbackIdx);      
}

void MultiLinkGameScreen_OnUpdate(void)
{
    switch(appScreenMLGameState)
    {
        case ML_GAME_INIT:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            currentDevice = APP_BLE_DEVICE_A;
            
            SYS_TIME_TimerStart(mlGameAnimTimer);     
            
            MLGameSetState(ML_GAME_ANIM0);
            
            break;
        }
        case ML_GAME_ANIM0:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;

            if (mlGameAnimTickCount != mlGameAnimTickPrev)
            {
                int32_t ypos = APP_LE_GETY(MultiLinkGameScreen_RestartGameButton);
                int32_t deltaY = (ypos - RESTART_ICON_YSHOW_POS) / GAME_ANIM_COEFF;
                
                if (deltaY > 0)
                {
                    APP_LE_SETY(MultiLinkGameScreen_RestartGameButton, ypos - deltaY);
                }
                else
                {
                    MLGameSetState(ML_GAME_INIT_DONE);
                    
                    APP_LE_SETY(MultiLinkGameScreen_RestartGameButton, RESTART_ICON_YSHOW_POS);
                }
                
                mlGameAnimTickPrev = mlGameAnimTickCount;
            }
            

            break;
        }
        
        case ML_GAME_INIT_DONE:
        {
            APP_LE_SETVISIBLE(MultiLinkGameScreen_ControlButton, LE_TRUE);
            APP_LE_SETVISIBLE(MultiLinkGameScreen_RestartLabel, LE_TRUE);
            APP_LE_SETVISIBLE(MultiLinkGameScreen_GameTitle, LE_TRUE);
            
            
            SYS_TIME_TimerStop(mlGameAnimTimer); 
            SYS_TIME_TimerStart(mlGameLightTimer); 
            
            Control_SendBLELEDOnOffMsg(&bleMsg, true, true);
            
            APP_UI_SendEvent(APP_EVENT_UI_ACTIVATE_ALL_DEVICES);
            
            MLGameSetState(ML_GAME_PROCESSING);
            
            break;
        }
        case ML_GAME_PROCESSING:
        {
            if (xQueueReceive(uiMsgQueue, &uiMsg, 0) == pdTRUE)
            {
                switch(uiMsg.event)
                {
                    case APP_EVENT_UI_LED_BRIGHTNESS_SET:
                    {
                        APP_BLE_DEVICE_ID i;
                        
                        for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
                        {
                            APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);

                            if (device != NULL && 
                                device->connected == true)
                            {
                                devices[i].ledCfg.brightness = uiMsg.param.num;
                                
                                bleMsg.device = device;
                                
                                Control_SendBLELEDColorSetMsg(&bleMsg, &devices[i].ledCfg, i);
                            }
                        }
                        
                        break;
                    }
                    case APP_EVENT_UI_LED_UPDATE:
                    {
                        uint32_t i;
                        
                        static uint32_t colorID = 0;
                        
                        ledCfg.color888 = colors888[colorID];

                        for (i = APP_BLE_DEVICE_A; i < APP_BLE_DEVICE_MAX; i++)
                        {
                            APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(i);

                            if (device != NULL && 
                                device->connected == true &&
                                devices[i].deviceActive == true)
                            {
                                devices[i].ledCfg.color888 = colors888[colorID];
                                
                                bleMsg.device = device;
                                
                                Control_SendBLELEDColorSetMsg(&bleMsg, &devices[i].ledCfg, i);
                            }
                        }
                        
                        colorID = (colorID < GAME_NUM_COLORS - 1) ? colorID + 1 : 0;
                        
                        break;
                    }
                    case APP_EVENT_UI_SELECT_DEVICE:
                    {
                        APP_BLE_DEVICE * device = APP_BLED_GetMultiLinkDemoDevice(uiMsg.param.num);
                                
                        if (device != NULL &&
                            device->connected == true &&
                            devices[uiMsg.param.num].deviceActive == true)
                        {
                            Screen_SetActiveDevice(device);
                            
                            devices[uiMsg.param.num].deviceActive = false;
                            
                            APP_LE_SETVISIBLE(devices[uiMsg.param.num].check, LE_TRUE);
                            APP_LE_SETVISIBLE(devices[uiMsg.param.num].instruction, LE_FALSE);
                            
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

                            if (device != NULL && 
                                device->connected == true)
                            {
                                APP_LE_SETVISIBLE(devices[i].check, LE_FALSE);
                                APP_LE_SETVISIBLE(devices[i].instruction, LE_TRUE);

                                devices[i].deviceActive = true;
                            }
                        }  
                        
                        break;
                    }
                    case APP_EVENT_UI_START_CONTROL:
                    {
                        APP_LE_SETVISIBLE(MultiLinkGameScreen_ScrollKnobImageWidget, LE_FALSE);
                        APP_LE_SETVISIBLE(MultiLinkGameScreen_RestartLabel, LE_FALSE);
                        APP_LE_SETVISIBLE(MultiLinkGameScreen_GameTitle, LE_FALSE);
                        
                        SYS_TIME_TimerStart(mlGameAnimTimer); 
                        
                        MLGameSetState(ML_GAME_EXIT_ANIM1);
                        
                        break;
                    }
                    default:
                        break;
                }
            }            
            break;
        }
        case ML_GAME_EXIT_ANIM1:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;

            if (mlGameAnimTickCount != mlGameAnimTickPrev)
            {
                int32_t pos = APP_LE_GETX(MultiLinkGameScreen_SliderImageWidget);
                int32_t delta = (DEVICE_ICON_POSX_HIDE_RIGHT - pos) / GAME_ANIM_COEFF;
                
                if (delta > 0)
                {
                    APP_LE_SETX(MultiLinkGameScreen_SliderImageWidget, pos + delta);
                }
                else
                {
                    MLGameSetState(ML_GAME_EXIT_ANIM2);
                    
                    APP_LE_SETX(MultiLinkGameScreen_SliderImageWidget, DEVICE_ICON_POSX_HIDE_RIGHT);
                }
            }
            
            
            
            break;
        }
        case ML_GAME_EXIT_ANIM2:
        {
            
            if(leRenderer_IsIdle() != LE_TRUE)
                break;

            if (mlGameAnimTickCount != mlGameAnimTickPrev)
            {
                int32_t pos = APP_LE_GETY(MultiLinkGameScreen_RestartGameButton);
                int32_t delta = (DEVICE_ICON_POSY_HIDE_BOTTOM - pos) / GAME_ANIM_COEFF;
                
                if (delta > 0)
                {
                    APP_LE_SETY(MultiLinkGameScreen_RestartGameButton, pos + delta);
                }
                else
                {
                    MLGameSetState(ML_GAME_EXIT);

                    APP_LE_SETY(MultiLinkGameScreen_RestartGameButton, DEVICE_ICON_POSY_HIDE_BOTTOM);
                }
                
                mlGameAnimTickPrev = mlGameAnimTickCount;
            }
            
            break;
        }        
        case ML_GAME_EXIT:
        {
            SYS_TIME_TimerStop(mlGameAnimTimer); 
            
            legato_showScreen(screenID_MultiLinkControlScreen);
            
            break;
        }
        default:
            break;
    }
}

static void MLGameSetState(ML_GAME_SCREEN_STATE state)
{
    appScreenMLGameState = state;
    
#ifdef ENABLE_UI_DEBUG       
    if (state > ML_GAME_INIT_DONE)
    {
        UI_DPRINTF("UI State is %s \r\n", appScreenUIStates[state]);
    }
#endif
}

static void MLGameAnimTimer_Callback (uintptr_t context)
{
    mlGameAnimTickCount++;
}

static void MLGameLightTimer_Callback (uintptr_t context)
{
    APP_UI_SendEvent(APP_EVENT_UI_LED_UPDATE);
}

static void SetBrightnessValue(uint32_t pct)
{
    uiMsg.param.num = pct;
    
    uiMsg.event = APP_EVENT_UI_LED_BRIGHTNESS_SET;
    
    APP_UI_SendMsg(&uiMsg);
}

static void SetSliderPosition(uint32_t pct)
{
    uint32_t SliderKnobPosY = 
            MultiLinkGameScreen_SliderControlPanel->fn->getY(MultiLinkGameScreen_SliderControlPanel) - 
            MultiLinkGameScreen_ScrollKnobImageWidget->fn->getHeight(MultiLinkGameScreen_ScrollKnobImageWidget)/2;
    
    SliderKnobPosY = MultiLinkGameScreen_SliderControlPanel->fn->getY(MultiLinkGameScreen_SliderControlPanel) +
                     ((MultiLinkGameScreen_SliderControlPanel->fn->getHeight(MultiLinkGameScreen_SliderControlPanel) * ( 100 - pct)) / 100) - 
                     MultiLinkGameScreen_ScrollKnobImageWidget->fn->getHeight(MultiLinkGameScreen_ScrollKnobImageWidget) / 2;
    
    MultiLinkGameScreen_ScrollKnobImageWidget->fn->setY(MultiLinkGameScreen_ScrollKnobImageWidget, SliderKnobPosY);
}

static leBool Slider_filterEvent(leWidget* target, leWidgetEvent* evt, void* data)
{
    leBool retval = LE_FALSE;    
    lePoint pnt;
    uint32_t brightness;
    
    pnt.x = ((leWidgetEvent_TouchDown *) evt)->x;
    pnt.y = ((leWidgetEvent_TouchDown *) evt)->y;
    
//    leUtils_PointScreenToLocalSpace(MultiLinkControlScreen_SliderControlPanel, &pnt);
    
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
                
                if (brightness >= MIN_BRIGHTNESS_PCT)
                    SetBrightnessValue(brightness);

                break;
            }   
            case LE_EVENT_TOUCH_UP:            
            {
                evt->accepted = LE_TRUE;

                retval = LE_TRUE;

                break;        
            }
            default:
                break;
        }
    }
    
   return retval;
}
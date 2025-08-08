/* 
 * File:   app_ui.h
 * Author: C18797
 *
 * Created on July 20, 2022, 9:30 PM
 */

#ifndef APP_UI_H
#define	APP_UI_H

#ifdef	__cplusplus
extern "C" {
#endif

#define UI_QUEUE_DATA_SIZE 64
#define APP_UI_QUEUE_COUNT 64
#define UI_QUEUE_SEND_TIMEOUT_TICKS 1000
    
#define NO_ACK_UI 1
#define NOTIF_DELAY_MS 1000    
#define APP_SCAN_TIME_SECS 30    

//#define ENABLE_CONFIG_MENU 1    
    
#define ANIM_TIMER_TICK_PERIOD_MS   10
    
#define MULTILINK_CONNECT_TIMEOUT_MSEC 30000
#define PROGRESS_TIMER_TICK_PERIOD_MS   1000
    
#define MULTILINK_CONNECT_TIMEOUT_COUNTS (MULTILINK_CONNECT_TIMEOUT_MSEC/PROGRESS_TIMER_TICK_PERIOD_MS)
    
#define DEFAULT_TEMP_LABEL_VALUE 400
    
#define DEFAULT_UI_REDPANEL_MODE 1
    
#define ABORT_ON_BLE_FAIL 1
    
#define DEFAULT_LED_COLOR_RGB 0x000000ff //blue
#define DEFAULT_LED_BRIGHTNESS_PCT 50
    
#define APP_UI_QUEUE_WR_EMPTY (-1)
#define APP_UI_QUEUE_RD_EMPTY (-1)
        
    
#if ENABLE_UI_DEBUG
//#define UI_DPRINTF(...) printf(__VA_ARGS__)
#define UI_DPRINTF(fmt, ...) SYS_DEBUG_PRINT(SYS_ERROR_INFO, fmt, ##__VA_ARGS__)
#else
#define UI_DPRINTF(...) 
#endif
    
    typedef enum
    {
        APP_EVENT_UI_NONE = 0,
        APP_EVENT_UI_HOME,
        APP_EVENT_UI_START_SCAN,
        APP_EVENT_UI_PROGRESS_TIMER,
        APP_EVENT_UI_SEC_TIMER,
        APP_EVENT_UI_STOP_SCAN,
        APP_EVENT_UI_CONFIG,

        APP_EVENT_UI_START_CONNECT,
        APP_EVENT_UI_START_CONNECT_A,
        APP_EVENT_UI_START_CONNECT_B,
        APP_EVENT_UI_STOP_CONNECT,
        APP_EVENT_UI_CONNECT_OK,
        APP_EVENT_UI_START_DISCONNECT,
        APP_EVENT_UI_DISCONNECT_OK,
        APP_EVENT_UI_DEVICE_CONNECT_TIMEOUT,
                
        APP_EVENT_UI_START_CONTROL,
        APP_EVENT_UI_SELECT_DEVICE,
        APP_EVENT_UI_ACTIVATE_ALL_DEVICES, 
        APP_EVENT_UI_DEACTIVATE_ALL_DEVICES,
        
        APP_EVENT_UI_LED_COLOR_SELECTED,
        APP_EVENT_UI_ML_LED_COLOR_SELECTED,
        APP_EVENT_UI_LED_UPDATE,
        APP_EVENT_UI_LED_BRIGHTNESS_SET, 
        APP_EVENT_UI_LED_OFF,
        APP_EVENT_UI_LED_ON,
        APP_EVENT_UI_GRAPH_UPDATE,
        
        APP_EVENT_UI_HIDE_INFO,
        APP_EVENT_UI_SHOW_INFO_GRAPH,
        APP_EVENT_UI_SHOW_INFO_WIFI,
        APP_EVENT_UI_SHOW_INFO_BLE,
        APP_EVENT_UI_SHOW_INFOGRAPHIC,
        APP_EVENT_UI_HIDE_INFOGRAPHIC,
                
        APP_EVENT_UI_FAILED_OK,
                
        APP_EVENT_BLE_SCANNING,
        APP_EVENT_BLE_SCANNING_UPDATE,
        APP_EVENT_BLE_SCAN_COMPLETE,

        APP_EVENT_BLE_CONNECTING,
        APP_EVENT_BLE_SYNCING,        
        APP_EVENT_BLE_CONNECTED,
        APP_EVENT_BLE_CONTROL_READY,
        APP_EVENT_BLE_DEVICE_CONNECT_FAILED,
        APP_EVENT_BLE_DEVICE_CFG_FAILED,
                
        APP_EVENT_BLE_DISCONNECTING,
        APP_EVENT_BLE_DISCONNECTED,
        APP_EVENT_BLE_FAILED,
        APP_EVENT_BLE_RESET,
        APP_EVENT_BLE_DATA_READY,
                
        APP_EVENT_BLE_DEVICE_NOTIFY,
                
        APP_EVENT_HTTP_CONNECTED,
        APP_EVENT_HTTP_DISCONNECTED,
        APP_EVENT_HTTP_DEVICE_CONTROL,
    } APP_UI_EVENTS;
    
    typedef struct
    {
        uint32_t color888;
        uint32_t brightness;
        bool on;
    } APP_UI_LED_CFG;
    
    typedef struct
    {
        APP_UI_EVENTS event;
        uint32_t device;
        uint32_t parmSize;
        union
        {
            uint32_t num;
            void * dataPtr;
            uint8_t data[UI_QUEUE_DATA_SIZE];
        } param;
    } APP_UI_MSG;
    
void APP_UI_Initialize(void);
void APP_UI_BLE_EventCallback(uint32_t event, void * data, uint32_t size);
void APP_UI_HTTP_EventCallback(uint32_t event, void * data, uint32_t size);

APP_RESULT APP_UI_SendMsg(APP_UI_MSG * msg);
APP_RESULT APP_UI_SendMsgFromISR(APP_UI_MSG * msg);
APP_RESULT APP_UI_SendEvent(APP_UI_EVENTS event);
APP_RESULT APP_UI_ReadMsg(APP_UI_MSG * msg);

bool APP_UI_RedPanelModeIsEnabled(void);
void APP_UI_RedPanelModeEnable(bool enable);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_UI_H */


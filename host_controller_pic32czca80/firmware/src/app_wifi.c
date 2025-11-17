/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_wifi.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "definitions.h"
#include "app_ui.h"
#include "app_wifi.h"
#include "wdrv_winc.h"
#include "time.h"
#include "stdio.h"
#include "system/wifi/sys_wincs_wifi_service.h"
#include "system/sys_wincs_system_service.h"
#include "system/mqtt/sys_wincs_mqtt_service.h"
#include "system/wifiprov/sys_wincs_provision_service.h"
#include "app_coordinator.h"

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_WIFI_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_WIFI_DATA app_wifiData;
static uint32_t connectedCount = 0;
static uint32_t coordCallbackIdx;
static uint32_t wifiCallbackIdx;

static bool isAppWifiStatusMutexCreated = false;
static OSAL_MUTEX_DECLARE(appWifiStatusMutex);

// MQTT configuration settings for connecting to Broker
SYS_WINCS_MQTT_CFG_t    g_mqttCfg = {
    .url                    = SYS_WINCS_MQTT_CLOUD_URL,
    .username               = SYS_WINCS_MQTT_CLOUD_USER_NAME,
    .clientId               = SYS_WINCS_MQTT_CLIENT_ID,
    .password               = SYS_WINCS_MQTT_PASSWORD,
    .port                   = SYS_WINCS_MQTT_CLOUD_PORT,
    .tlsIdx                 = SYS_WINCS_MQTT_TLS_ENABLE,
    .protoVer               = SYS_WINCS_MQTT_PROTO_VERSION,
    .keepAliveTime          = SYS_WINCS_MQTT_KEEP_ALIVE_TIME,
    .cleanSession           = SYS_WINCS_MQTT_CLEAN_SESSION,
    .sessionExpiryInterval  = SYS_WINCS_MQTT_KEEP_ALIVE_TIME,
};

// MQTT frame settings for subscribing to a topic
SYS_WINCS_MQTT_FRAME_t  g_mqttSubsframe = {
    .qos                    = SYS_WINCS_MQTT_SUB_TOPIC_0_QOS,
    .topic                  = SYS_WINCS_MQTT_SUB_TOPIC_0,
    .protoVer               = SYS_WINCS_MQTT_PROTO_VERSION
};

#if 0
struct
{
    int32_t wr;
    int32_t rd;
    APP_WIFI_MSG appWifiMsg[APP_WIFI_QUEUE_COUNT];
} appWifiMsgQueue;

APP_RESULT APP_WIFI_SendEvent(APP_WIFI_EVENTS event)
{
    wifiMsg.event = event;
       
    return APP_WIFI_SendMsg(&wifiMsg);
}

APP_RESULT APP_WIFI_SendMsg(APP_WIFI_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR;
    
    //full
    if ((appWifiMsgQueue.wr == APP_WIFI_QUEUE_COUNT - 1 && appWifiMsgQueue.rd == 0) ||
        (appWifiMsgQueue.wr == appWifiMsgQueue.rd - 1))
    {
        return APP_ERR_NOMEM;
    }    
    
    //empty
    if (appWifiMsgQueue.wr == APP_WIFI_QUEUE_WR_EMPTY)
    {
        appWifiMsgQueue.wr = 0;
        appWifiMsgQueue.rd = 0;
    }
    else
    {
         appWifiMsgQueue.wr = (appWifiMsgQueue.wr + 1) % APP_WIFI_QUEUE_COUNT;
    }
            
    appWifiMsgQueue.appWifiMsg[appWifiMsgQueue.wr] = *msg;
    
    return APP_SUCCESS;
}

APP_RESULT APP_WIFI_ReadMsg(APP_WIFI_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR;
    
        //empty
    if (appWifiMsgQueue.wr == APP_WIFI_QUEUE_WR_EMPTY)
    {
        return APP_ERR_EMPTY;
    }
    
    memcpy(msg, &appWifiMsgQueue.appWifiMsg[appWifiMsgQueue.rd], sizeof(APP_WIFI_MSG));
    
    if (appWifiMsgQueue.rd == appWifiMsgQueue.wr)
    {
        appWifiMsgQueue.wr = APP_WIFI_QUEUE_WR_EMPTY;
        appWifiMsgQueue.rd = APP_WIFI_QUEUE_RD_EMPTY;
    }
    else 
    {
        appWifiMsgQueue.rd = (appWifiMsgQueue.rd + 1) % APP_WIFI_QUEUE_COUNT;
    }
    
    return APP_SUCCESS;
}
#endif

bool APP_WIFI_GetWifiParamsFromFile(char *wifi_ssid, char *wifi_pass, uint8_t *wifi_sec)
{
    char content[100];
    bool ok = false;
    
    app_wifiData.cfgFileHandle = SYS_FS_FileOpen(APP_WIFI_CONFIG_FILE, (SYS_FS_FILE_OPEN_READ));
    if (app_wifiData.cfgFileHandle != SYS_FS_HANDLE_INVALID)
    {
        SYS_FS_RESULT result = SYS_FS_FileStringGet(app_wifiData.cfgFileHandle, content, 100);
        if (result == SYS_FS_RES_SUCCESS)
        {
            char *ssid, *pass, *sec;                       
            uint8_t security;

            //get Device A
            ssid = strstr((const char *) content, APP_WIFI_CONFIG_SSID);
            if (ssid)
            {
                memset(wifi_ssid,'\0',32);
                pass = strstr((const char *) content, APP_WIFI_CONFIG_PASS);
                if (pass)
                {                                
                    strncpy(wifi_ssid, ssid + strlen(APP_WIFI_CONFIG_SSID), pass - (ssid + strlen(APP_WIFI_CONFIG_SSID)));
                    memset(wifi_pass,'\0',32);
                    sec = strstr((const char *) content, APP_WIFI_CONFIG_SEC);
                    if (sec)
                    {
                        strncpy(wifi_pass, pass + strlen(APP_WIFI_CONFIG_PASS), sec - (pass + strlen(APP_WIFI_CONFIG_PASS)));
                        *wifi_sec = *(sec + strlen(APP_WIFI_CONFIG_SEC)) - '0';
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] - WIFI params from SDcard - ssid:\"%s\" pass:\"%s\" sec=%d\r\n", wifi_ssid, wifi_pass,*wifi_sec );
                        ok = true;
                    }
                }
            }
        }
        SYS_FS_FileClose(app_wifiData.cfgFileHandle);
    }
    return ok;
}

bool APP_WIFI_SetWifiParamsToFile(char *wifi_ssid, char *wifi_pass, uint8_t wifi_sec)
{
    char content[100];
    uint16_t size;
    bool ok = false;

    if(APP_SYSFSReady())
    {
        app_wifiData.cfgFileHandle = SYS_FS_FileOpen(APP_WIFI_CONFIG_FILE, (SYS_FS_FILE_OPEN_WRITE));
        if (app_wifiData.cfgFileHandle != SYS_FS_HANDLE_INVALID)
        {
            snprintf(content, 100, "ssid=%s,key=%s,sec=%u",wifi_ssid, wifi_pass, (int)wifi_sec);
            size = strlen(content) + 1;
            if(SYS_FS_FileWrite(app_wifiData.cfgFileHandle, (const void *)content, size) != -1)
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] - %s written with \"%s\"\r\n", APP_WIFI_CONFIG_FILE, content);
                ok = true;
            }
            SYS_FS_FileClose(app_wifiData.cfgFileHandle);
        }
    }
    return ok;
}

/*******************************************************************************
  Function:
    void APP_WIFI_Initialize ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

bool APP_WIFI_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_wifiData.state = APP_WIFI_STATE_WINCS_PRINT;

    app_wifiData.status = APP_WIFI_OFF;
    app_wifiData.ssid = SYS_WINCS_WIFI_STA_SSID;
    app_wifiData.password = SYS_WINCS_WIFI_STA_PWD;
    app_wifiData.cloudConnected = false;
    app_wifiData.connectionRetires = 0;
    app_wifiData.alarmStatusPublished = false;
    app_wifiData.lightIndoorStatusPublished = false;
    app_wifiData.lightOutdoorStatusPublished = false;
    app_wifiData.coordHeartbeatCounter = 0;
    app_wifiData.heartbeatsPublished = 0;
    app_wifiData.mqttMessCntWifi = 0;
    
    /* Mutex creation to notify status */
    if (isAppWifiStatusMutexCreated == false)
    {
        if(OSAL_MUTEX_Create(&(appWifiStatusMutex)) != OSAL_RESULT_SUCCESS)
        {
            return false;
        }
        else
        {
            isAppWifiStatusMutexCreated = true;
        }
    }
    
#if 0    
    // Handle Events 
    app_wifiData.wr = APP_WIFI_QUEUE_WR_EMPTY;
    app_wifiData.rd = APP_WIFI_QUEUE_RD_EMPTY;
    memset(app_wifiData.appWifiMsg, 0, sizeof(APP_WIFI_MSG) * APP_WIFI_QUEUE_COUNT);
#endif    
    return true;
}

void APP_SYS_TIME_CallbackSetFlag(uintptr_t context)
{
    if (context != 0)
    {
        /* Context holds the flag's address */
        *((bool *) context) = true;
    }
}

int32_t APP_WIFI_RegisterNotification(void (*func)(uint32_t, void *, uint32_t))
{
    uint32_t i;
    
    if (func == NULL)
        return -APP_ERR_INV;
    
    for (i = 0; i < APP_WIFI_NOTIF_CALLBACK_COUNT; i++)
    {
        if (app_wifiData.notifCallbacks[i].func == NULL)
        {
           app_wifiData.notifCallbacks[i].func = func;
           SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Register Notification %d\r\n", i);
           return i;
        }
    }
   
    return -APP_ERR_NOMEM;
}

APP_RESULT APP_WIFI_UnregisterNotification(uint32_t idx)
{
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Unregister Notification %d\r\n", idx);
    if (idx < APP_WIFI_NOTIF_CALLBACK_COUNT)
    {
        app_wifiData.notifCallbacks[idx].func = NULL;
        
        return APP_SUCCESS;
    }
    
    return APP_ERR_EMPTY;
}

static void APP_WIFI_Notify(APP_WIFI_NOTIFY_EVENT event, void * data, uint32_t size)
{
    uint32_t i;
    
    //Call all state callback functions
    for (i = 0; i < APP_WIFI_NOTIF_CALLBACK_COUNT; i++)
    {
        if (app_wifiData.notifCallbacks[i].func != NULL)
        {
            app_wifiData.notifCallbacks[i].func(event, data, size);
        }
    }
}

void APP_WIFI_EventCallback(uint32_t event, void * data, uint32_t size)
{
    if(OSAL_MUTEX_Lock(&appWifiStatusMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        return;
    }
    
    switch(event)
    {
        case APP_WIFI_AVAILABLE_NOTIFY:
        {
            app_wifiData.status |= APP_WIFI_AVAILABLE;
            break;
        }
        case APP_WIFI_CONNECTED_NOTIFY:
        {
            app_wifiData.status |= APP_WIFI_CONNECTED;
            break;
        }
        case APP_WIFI_DISCONNECTED_NOTIFY:
        {
            app_wifiData.status &= ~APP_WIFI_CONNECTED;
            app_wifiData.status &= ~APP_WIFI_MQTT_CONNECTED;
            break;
        }
        case APP_WIFI_SNTP_UP_NOTIFY:
        {
            app_wifiData.status |= APP_WIFI_SNTP_UP;
            break;
        }
        case APP_WIFI_MQTT_CONNECTED_NOTIFY:
        {
            app_wifiData.status |= APP_WIFI_MQTT_CONNECTED;
            app_wifiData.cloudConnected = true;
            break;
        }
        case APP_WIFI_MQTT_DISCONNECTED_NOTIFY:
        {
            app_wifiData.status &= ~APP_WIFI_MQTT_CONNECTED;
            app_wifiData.cloudConnected = false;
            break;
        }
        default:
        {
            break;
        }
    }
    /* Release mutex */
    (void) OSAL_MUTEX_Unlock(&appWifiStatusMutex);
    return;
}

bool APP_WIFI_GetStatus(uint32_t *status)
{
    if(OSAL_MUTEX_Lock(&appWifiStatusMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        return false;
    }
    
    *status = app_wifiData.status;
    
    /* Release mutex */
    (void) OSAL_MUTEX_Unlock(&appWifiStatusMutex);
    
    return true;
}

uint32_t APP_WIFI_GetConnectedCount(void)
{
    return connectedCount;
}

void APP_WIFI_PublishData(char *msg)
{
    SYS_WINCS_MQTT_FRAME_t mqtt_pub;

    if(app_wifiData.cloudConnected)
    {
        mqtt_pub.qos      = SYS_WINCS_MQTT_PUB_MSG_QOS_TYPE;
        mqtt_pub.topic    = SYS_WINCS_MQTT_PUB_TOPIC_NAME;
        mqtt_pub.message  = msg;
        mqtt_pub.protoVer = SYS_WINCS_MQTT_PROTO_VERSION;
        SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_PUBLISH, (void *)&mqtt_pub);
    }
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_WIFI] : MQTT connection not ready to publish data\r\n");
    }
}

static void APP_WIFI_PublishDataInit(void)
{
    char message[50];
    
    sprintf(message, "{\"alarm\": %d}", appData.alarmStatus);
    APP_WIFI_PublishData(message);
    sprintf(message, "{\"light_indoor\": %d}", appData.lightIndoorStatus);
    APP_WIFI_PublishData(message);
    sprintf(message, "{\"light_outdoor\": %d}", appData.lightOutdoorStatus);
    APP_WIFI_PublishData(message);
    sprintf(message, "{\"coordHeartbeatCounter\": %d}", app_wifiData.coordHeartbeatCounter);
    APP_WIFI_PublishData(message);
    sprintf(message, "{\"mqttMessCntWifi\": %d}", app_wifiData.mqttMessCntWifi);
    APP_WIFI_PublishData(message);
    
}

static void APP_Parse_Rx_Message(SYS_WINCS_MQTT_FRAME_t *mqttRxFrame)
{
    char *parts[10];
    int count = 0;

    char *str_copy = strdup(mqttRxFrame->topic);
    if (!str_copy)
    {
        return;
    }

    char *token = strtok(str_copy, "/");
    while(token != NULL)
    {
        parts[count++] = token;
        token = strtok(NULL, "/");
    }

    if(strcmp(parts[count - 2], "switch-light") == 0)
    {
        // toggle indoor light
        if(strstr(mqttRxFrame->message, "\"light_indoor\":\"toggle\"") != NULL)
        {
            uint8_t alive;
            uint8_t index;

            index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_INDOOR);
            APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_INDOOR, &alive);
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                if(app_wifiData.lightIndoorStatus)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_indoor off\r\n");
                    app_wifiData.lightIndoorStatus = false;
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_indoor on\r\n");
                    app_wifiData.lightIndoorStatus = true;
                }

                // inform coordinator
                APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
                cmdData.data[0] = CMD_SET_LIGHT;
                cmdData.data[1] = index;
                cmdData.data[2] = app_wifiData.lightIndoorStatus;
                cmdData.length = 3;
                cmdData.answer = false;
                alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
				if (!alive)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_WIFI] : Coord Cmds Queue full\r\n");
                }
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : device type 0x%02X not present\r\n", TYPE_LIGHTING_INDOOR);
            }
        }
        // toggle outdoor light
        else if (strstr(mqttRxFrame->message, "\"light_outdoor\":\"toggle\"") != NULL)
        {
            uint8_t alive;
            uint8_t index;

            index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_OUTDOOR);
            APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_OUTDOOR, &alive);
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                if(app_wifiData.lightOutdoorStatus)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_outdoor off\r\n");
                    app_wifiData.lightOutdoorStatus = false;
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_outdoor on\r\n");
                    app_wifiData.lightOutdoorStatus = true;
                }

                // inform coordinator
                APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
                cmdData.data[0] = CMD_SET_LIGHT;
                cmdData.data[1] = index;
                cmdData.data[2] = app_wifiData.lightOutdoorStatus;
                cmdData.length = 3;
                cmdData.answer = false;
                alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
				if (!alive)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_WIFI] : Coord Cmds Queue full\r\n");
                }
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : device type 0x%02X not present\r\n", TYPE_LIGHTING_OUTDOOR);
            }
        }
    }
    else if(strcmp(parts[count - 2], "set-rgb") == 0)
    {
        const char *device_str = strstr(mqttRxFrame->message, "\"device\":\"0x");
        const char *color_str = strstr(mqttRxFrame->message, "\"color\":\"0x");

        uint8_t device = 0;
        uint8_t color = 0;

        if(device_str && color_str)
        {
            unsigned int temp_device, temp_color;

            sscanf(device_str, "\"device\":\"0x%x\"", &temp_device);
            sscanf(color_str, "\"color\":\"0x%x\"", &temp_color);

            device = (uint8_t)temp_device;
            color = (uint8_t)temp_color;

            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : Device: 0x%02X, Color: 0x%02X\n", device, color);
            // inform coordinator
            uint8_t alive;
            uint8_t index;

            index = APP_COORDINATOR_deviceIndexByType(device);
            APP_COORDINATOR_deviceGetAlive(device, &alive);
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
                cmdData.data[0] = CMD_SET_LED_RGB_BLINK;
                cmdData.data[1] = index;
                cmdData.data[2] = color;  // COLOR : 0x2B: yellow, 0x55: green, 0xAA: blue, 0xFF: red
                cmdData.data[3] = 0xFF;   // Saturation Value
                cmdData.data[4] = 0xFF;   // Saturation Value
                cmdData.data[5] = 0xf4;   // Blinking Frequency
                cmdData.data[6] = 0x01;   // Blinking Frequency - 500ms
                cmdData.data[7] = 0x10;   // Blinking Time
                cmdData.data[8] = 0x27;   // Blinking Time - 10s
                cmdData.length = 9;
                cmdData.answer = false;
                alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
				if (!alive)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_WIFI] : Coord Cmds Queue full\r\n");
                }
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : device type 0x%02X not present\r\n", device);
            }
        }
    }

    free(str_copy);
}

// *****************************************************************************
// Application MQTT Callback Handler
//
// Summary:
//    Handles MQTT events.
//
// Description:
//    This function handles various MQTT events and performs appropriate actions.
//
// Parameters:
//    event - The type of MQTT event
//    mqttHandle - The MQTT handle associated with the event
//
// Returns:
//    SYS_WINCS_RESULT_t - The result of the callback handling
//
// Remarks:
//    None.
// *****************************************************************************

SYS_WINCS_RESULT_t APP_MQTT_Callback
(
    SYS_WINCS_MQTT_EVENT_t event,
    SYS_WINCS_MQTT_HANDLE_t mqttHandle
)
{
    switch(event)
    {
        case SYS_WINCS_MQTT_CONNECTED:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, TERM_GREEN"\r\n[APP_WIFI] : MQTT : Connected to broker\r\n"TERM_RESET);
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Subscribing to %s\r\n",SYS_WINCS_MQTT_SUB_TOPIC_0);
                    
            //  Subscribe to topic
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_SUBS_TOPIC, (SYS_WINCS_MQTT_HANDLE_t)&g_mqttSubsframe);
            break;
        }

        case SYS_WINCS_MQTT_SUBCRIBE_ACK:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, TERM_GREEN"[APP_WIFI] : MQTT Subscription has been acknowledged. \r\n"TERM_RESET);            
            // Notify apps
            APP_WIFI_Notify(APP_WIFI_MQTT_CONNECTED_NOTIFY, NULL, 0);
            APP_WIFI_PublishDataInit();
            break;
        }

        case SYS_WINCS_MQTT_SUBCRIBE_MSG:
        {
            char mqttMessCntWifiString[50];
            SYS_WINCS_MQTT_FRAME_t *mqttRxFrame = (SYS_WINCS_MQTT_FRAME_t *)mqttHandle;
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, TERM_YELLOW"[APP_WIFI] : MQTT RX: From Topic : %s ; Msg -> %s\r\n"TERM_RESET,
                    mqttRxFrame->topic, mqttRxFrame->message);
            app_wifiData.mqttMessCntWifi++;
            sprintf(mqttMessCntWifiString, "{\"mqttMessCntWifi\": %d}", app_wifiData.mqttMessCntWifi);
            APP_WIFI_PublishData(mqttMessCntWifiString);
            APP_Parse_Rx_Message(mqttRxFrame);
            break;
        }

        case SYS_WINCS_MQTT_UNSUBSCRIBED:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : MQTT- A topic has been un-subscribed. \r\n");
            break;
        }

        case SYS_WINCS_MQTT_PUBLISH_ACK:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : MQTT- Publish has been sent. \r\n");
            break;
        }

        case SYS_WINCS_MQTT_DISCONNECTED:
        {            
            SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_WIFI] : MQTT- Disconnected\r\n");

            if(app_wifiData.status & APP_WIFI_CONNECTED)
            {
                SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_WIFI] : MQTT- Reconnecting...\r\n");
                APP_WIFI_Notify(APP_WIFI_MQTT_DISCONNECTED_NOTIFY, NULL, 0);
                // Set the callback function for MQTT events
                SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_SET_CALLBACK, APP_MQTT_Callback);
                // Configure the MQTT service with the provided configuration
                SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONFIG, (SYS_WINCS_MQTT_HANDLE_t)&g_mqttCfg);
                // Connect to the MQTT broker using the specified configuration
                SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONNECT, &g_mqttCfg);
            }
            break;
        }

        case SYS_WINCS_MQTT_ERROR:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_WIFI] : MQTT - ERROR\r\n");
            break;
        }

        default:
        break;
    }
    return SYS_WINCS_PASS;
}

void APP_WIFI_COORDINATOR_EventCallback(uint32_t event, void * data, uint32_t size)
{
    uint8_t type;
    bool state;
    uint8_t alive;
    
    if (event == APP_COORDINATOR_RESET_NOTIFY)
    {
        // Do something???
        app_wifiData.coordHeartbeatCounter = 0;
    }    
    else if (event == APP_COORDINATOR_HEARTBEAT_NOTIFY)
    {
        app_wifiData.coordHeartbeatCounter++;
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Heartbeat counter change to %d\r\n", app_wifiData.coordHeartbeatCounter);
    }
    else if (event == APP_COORDINATOR_ALARM_NOTIFY)
    {
        state = *((uint8_t *)data);
        app_wifiData.alarmStatus = state; 
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Alarm state change to %d\r\n", state);
    }
    else if (event == APP_COORDINATOR_DEVICE_OUT_NOTIFY)
    {
        // Nothing by now
        type = *((uint8_t *)data++);
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Device type 0x%02X leave\r\n", type);
    }
    else if (event == APP_COORDINATOR_DEVICE_JOINED_NOTIFY)
    {
        // Nothing by now
        type = *((uint8_t *)data++);
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Device type 0x%02X joined\r\n", type);
    }
    else if (event == APP_COORDINATOR_DEVICE_ALIVE_NOTIFY)
    {
        type = *((uint8_t *)data++);
        alive = *((uint8_t *)data);
        if (type == TYPE_LIGHTING_INDOOR) 
        {
            //app_wifiData.lightIndoorAlive = alive;
        }else if (type == TYPE_LIGHTING_OUTDOOR)
        {
            //app_wifiData.lightOutdoorAlive = alive;
        }                 
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Device type 0x%02X alive change to %d\r\n", type, alive);
    }
    else if (event == APP_COORDINATOR_DEVICE_STATE_NOTIFY)
    {
        type = *((uint8_t *)data++);
        state = *((uint8_t *)data);
        if (type == TYPE_LIGHTING_INDOOR) 
        {
            app_wifiData.lightIndoorStatus = state;
        }else if (type == TYPE_LIGHTING_OUTDOOR)
        {
            app_wifiData.lightOutdoorStatus = state;
        }        
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Device type 0x%02X state change to %d\r\n", type, state);
    }
}

// *****************************************************************************
// Application Wi-Fi Callback Handler
//
// Summary:
//    Handles Wi-Fi events.
//
// Description:
//    This function handles various Wi-Fi events and performs appropriate actions.
//
// Parameters:
//    event - The type of Wi-Fi event
//    wifiHandle - Handle to the Wi-Fi event data
//
// Returns:
//    None.
//
// Remarks:
//    None.
// *****************************************************************************
void SYS_WINCS_WIFI_CallbackHandler
(
    SYS_WINCS_WIFI_EVENT_t event,         // The type of Wi-Fi event
    SYS_WINCS_WIFI_HANDLE_t wifiHandle    // Handle to the Wi-Fi event data
)
{

    switch(event)
    {
        /* Set regulatory domain Acknowledgment */
        case SYS_WINCS_WIFI_REG_DOMAIN_SET_ACK:
        {
            // The driver generates this event callback twice, hence the if condition 
            // to ignore one more callback. This will be resolved in the next release.
            static bool domainFlag = false;
            if( domainFlag == false)
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Set Reg Domain -> SUCCESS\r\n");
                app_wifiData.state = APP_WIFI_STATE_WINCS_GET_WIFI_PARAMS;
                domainFlag = true;
            }

            break;
        }

        /* SNTP UP event code*/
        case SYS_WINCS_WIFI_SNTP_UP:
        {            
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : SNTP UP \r\n");
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Connecting to the Cloud\r\n");
            APP_WIFI_Notify(APP_WIFI_SNTP_UP_NOTIFY, NULL, 0);

            // Set the callback function for MQTT events
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_SET_CALLBACK, APP_MQTT_Callback);

            // Configure the MQTT service with the provided configuration
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONFIG, (SYS_WINCS_MQTT_HANDLE_t)&g_mqttCfg);

            // Connect to the MQTT broker using the specified configuration
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONNECT, &g_mqttCfg);
            break;
        }
        break;

        /* Wi-Fi connected event code*/
        case SYS_WINCS_WIFI_CONNECTED:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, TERM_GREEN"[APP_WIFI] : Wi-Fi Connected\r\n"TERM_RESET);
            connectedCount += 1;
            app_wifiData.connectionRetires = 0;
            // Notify apps
            APP_WIFI_Notify(APP_WIFI_CONNECTED_NOTIFY, NULL, 0);
            if(app_wifiData.status & APP_WIFI_SNTP_UP)
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Connecting to the Cloud\r\n");
                // Set the callback function for MQTT events
                SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_SET_CALLBACK, APP_MQTT_Callback);
                // Configure the MQTT service with the provided configuration
                SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONFIG, (SYS_WINCS_MQTT_HANDLE_t)&g_mqttCfg);
                // Connect to the MQTT broker using the specified configuration
                SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONNECT, &g_mqttCfg);
            }
            break;
        }

        /* Wi-Fi disconnected event code*/
        case SYS_WINCS_WIFI_DISCONNECTED:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_ERROR, TERM_RED"[APP_WIFI] : Wi-Fi Disconnected\r\n"TERM_RESET);
            char sntp_url[] =  SYS_WINCS_WIFI_SNTP_ADDRESS;
            if (SYS_WINCS_FAIL == SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_SET_SNTP, sntp_url))
            {
                app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                break;
            }
            SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_STA_CONNECT, NULL);
            connectedCount -= 1;
            // Notify apps
            APP_WIFI_Notify(APP_WIFI_DISCONNECTED_NOTIFY, NULL, 0);
            app_wifiData.connectionRetires++;
            break;
        }

        /* Wi-Fi connection failed event code*/
        case SYS_WINCS_WIFI_CONNECT_FAILED:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_WARNING, TERM_RED"[APP_WIFI] : Wi-Fi connection failed\r\n"TERM_RESET);
            app_wifiData.connectionRetires++;
            if(app_wifiData.connectionRetires < APP_WIFI_MAX_CON_RETRIES)
            {
                SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_STA_CONNECT, NULL);
                SYS_DEBUG_PRINT(SYS_ERROR_WARNING, TERM_RED"[APP_WIFI] : Reconnecting...\r\n"TERM_RESET);
            }
            app_wifiData.cloudConnected = false;
            break;
        }

        /* Wi-Fi DHCP complete event code*/
        case SYS_WINCS_WIFI_DHCP_IPV4_COMPLETE:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : DHCP IPv4 : %s\r\n", (uint8_t *)wifiHandle);
            SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_GET_TIME, NULL);
            break;
        }

        case SYS_WINCS_WIFI_DHCP_IPV6_LOCAL_COMPLETE:
        {
            //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : DHCP IPv6 Local : %s\r\n", (uint8_t *)wifiHandle);
            break;
        }

        case SYS_WINCS_WIFI_DHCP_IPV6_GLOBAL_COMPLETE:
        {
            //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : DHCP IPv6 Global: %s\r\n", (uint8_t *)wifiHandle);

            // Retrieve the current time from the Wi-Fi service
            //SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_GET_TIME, NULL);
            break;
        }

        default:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_WIFI] : WiFi Callback unhandeled event: %d\r\n", event);
            break;
        }
    }
}

void APP_WIFIPROV_CallbackHandler(SYS_WINCS_PROV_EVENT_t event, SYS_WINCS_PROV_HANDLE_t provHandle)
{
    switch(event)
    {
        case SYS_WINCS_PROV_COMPLETE:
        {
            SYS_WINCS_WIFI_PARAM_t *prov = (SYS_WINCS_WIFI_PARAM_t *)provHandle;

            SYS_WINCS_PROV_SrvCtrl(SYS_WINCS_PROV_DISABLE, NULL);
            app_wifiData.ssid = strdup(prov->ssid);
            app_wifiData.password = strdup(prov->passphrase);
            app_wifiData.state = APP_WIFI_STATE_WINCS_SET_WIFI_PARAMS;
            APP_WIFI_SetWifiParamsToFile(app_wifiData.ssid, app_wifiData.password, SYS_WINCS_WIFI_STA_SECURITY);
            break;
        }
        case SYS_WINCS_PROV_FAILURE:
        {
            SYS_WINCS_PROV_SrvCtrl(SYS_WINCS_PROV_DISABLE, NULL);
            app_wifiData.state = APP_WIFI_STATE_WINCS_START_PROVISIONING;
            SYS_DEBUG_PRINT(SYS_ERROR_WARNING, TERM_RED"[APP_WIFI] : Wi-Fi provisioning failed\r\n"TERM_RESET);
            break;
        }
    }
}

/******************************************************************************
  Function:
    void APP_WIFI_Tasks ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

void APP_WIFI_Tasks ( void )
{
    static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;

    /* Check the application's current state. */
    switch(app_wifiData.state)
    {
        // State to print Message 
        case APP_WIFI_STATE_WINCS_PRINT:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, " --- WINCS02 MQTT client demo ---\r\n");
            // Register to coordinator notifications
            coordCallbackIdx = APP_COORDINATOR_RegisterNotification(APP_WIFI_COORDINATOR_EventCallback); 
            wifiCallbackIdx = APP_WIFI_RegisterNotification(APP_WIFI_EventCallback);
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Coordinator Notification index = %d\r\n", coordCallbackIdx);
            app_wifiData.state = APP_WIFI_STATE_WINCS_INIT;
            break;
        }

        /* Application's initial state. */
        case APP_WIFI_STATE_WINCS_INIT:
        {   
            SYS_STATUS status;
            // Get the driver status
            SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_GET_DRV_STATUS, &status);

            // If the driver is ready, move to the next state
            if (SYS_STATUS_READY == status)
            {
                SYS_TIME_DelayMS(2000, &timer);
                app_wifiData.state = APP_WIFI_STATE_WINCS_OPEN_DRIVER;
            }

            break;
        }

        case APP_WIFI_STATE_WINCS_OPEN_DRIVER:
        {
            DRV_HANDLE wdrvHandle = DRV_HANDLE_INVALID;
            
            if(SYS_TIME_DelayIsComplete(timer) == false)
            {
                break;
            }
            // Open the Wi-Fi driver
            if (SYS_WINCS_FAIL == SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_OPEN_DRIVER, &wdrvHandle))
            {
                app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                break;
            }

            // Get the driver handle
            SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_GET_DRV_HANDLE, &wdrvHandle);
            app_wifiData.state = APP_WIFI_STATE_WINCS_DEVICE_INFO;
            break;
        }

        case APP_WIFI_STATE_WINCS_DEVICE_INFO:
        {
            APP_DRIVER_VERSION_INFO drvVersion;
            APP_FIRMWARE_VERSION_INFO fwVersion;
            APP_DEVICE_INFO devInfo;
            SYS_WINCS_RESULT_t status = SYS_WINCS_BUSY;

            // Get the firmware version
            status = SYS_WINCS_SYSTEM_SrvCtrl(SYS_WINCS_SYSTEM_SW_REV, &fwVersion);

            if(status == SYS_WINCS_PASS)
            {
                // Get the device information
                status = SYS_WINCS_SYSTEM_SrvCtrl(SYS_WINCS_SYSTEM_DEV_INFO, &devInfo);
            }

            if(status == SYS_WINCS_PASS)
            {
                // Get the driver version
                status = SYS_WINCS_SYSTEM_SrvCtrl(SYS_WINCS_SYSTEM_DRIVER_VER, &drvVersion);
            }

            if(status == SYS_WINCS_PASS)
            {
                char buff[30];
                // Print device information
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "WINC: Device ID = %08x\r\n", devInfo.id);
                for (int i = 0; i < devInfo.numImages; i++)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "%d: Seq No = %08x, Version = %08x, Source Address = %08x\r\n", 
                            i, devInfo.image[i].seqNum, devInfo.image[i].version, devInfo.image[i].srcAddr);
                }

                // Print firmware version
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, TERM_CYAN "Firmware Version: %d.%d.%d ", fwVersion.version.major,
                        fwVersion.version.minor, fwVersion.version.patch);
                strftime(buff, sizeof(buff), "%X %b %d %Y", localtime((time_t*)&fwVersion.build.timeUTC));
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, " [%s]\r\n", buff);

                // Print driver version
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "Driver Version: %d.%d.%d\r\n"TERM_RESET, drvVersion.version.major, 
                        drvVersion.version.minor, drvVersion.version.patch);

                // Notify apps
                APP_WIFI_Notify(APP_WIFI_AVAILABLE_NOTIFY, NULL, 0);

                // Next State
                app_wifiData.state = APP_WIFI_STATE_WINCS_SET_REG_DOMAIN;
            }
            break;
        }

        case APP_WIFI_STATE_WINCS_SET_REG_DOMAIN:
        {
            // Set the callback handler for Wi-Fi events
            SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_SET_CALLBACK, SYS_WINCS_WIFI_CallbackHandler);

            SYS_DEBUG_PRINT(SYS_ERROR_INFO, TERM_YELLOW"[APP_WIFI] : Setting REG domain to " TERM_UL "%s\r\n"TERM_RESET ,SYS_WINCS_WIFI_COUNTRYCODE);

            app_wifiData.state = APP_WIFI_STATE_WINCS_SERVICE_TASKS;
            // Set the regulatory domain
            if (SYS_WINCS_FAIL == SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_SET_REG_DOMAIN, SYS_WINCS_WIFI_COUNTRYCODE))
            {
                app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                break;
            }
            break;
        }
        
        case APP_WIFI_STATE_WINCS_GET_WIFI_PARAMS:
        {
            char wifi_ssid_str[32];
            char wifi_pass_str[32];
            uint8_t wifi_security;

            //If FS mounted get information from SDcard
            if(APP_WIFI_GetWifiParamsFromFile(wifi_ssid_str, wifi_pass_str, &wifi_security))
            {
                // Update Structure
                app_wifiData.ssid = strdup(wifi_ssid_str);
                app_wifiData.password = strdup(wifi_pass_str);
                //app_wifiData.security = wifi_security;
            }
            app_wifiData.state = APP_WIFI_STATE_WINCS_SET_WIFI_PARAMS;
            break;
           // Get WIFI params from uSD
            
        }

        case APP_WIFI_STATE_WINCS_SET_WIFI_PARAMS:
        {
            char sntp_url[] =  SYS_WINCS_WIFI_SNTP_ADDRESS;
            if (SYS_WINCS_FAIL == SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_SET_SNTP, sntp_url))
            {
                app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                break;
            }

            // Configuration parameters for Wi-Fi station mode
            SYS_WINCS_WIFI_PARAM_t wifi_sta_cfg = {
                .mode        = SYS_WINCS_WIFI_DEVMODE,         // Set Wi-Fi mode to Station (STA)
                .ssid        = app_wifiData.ssid,              // Set the SSID (network name) for the Wi-Fi connection
                .passphrase  = app_wifiData.password,          // Set the passphrase (password) for the Wi-Fi connection
                .security    = SYS_WINCS_WIFI_STA_SECURITY,    // Set the security type (e.g., WPA2) for the Wi-Fi connection
                .autoConnect = SYS_WINCS_WIFI_STA_AUTOCONNECT, // Enable or disable auto-connect to the Wi-Fi network
                .channel     = WDRV_WINC_CID_ANY
            };

            // Set the Wi-Fi parameters
            if (SYS_WINCS_FAIL == SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_SET_PARAMS, &wifi_sta_cfg))
            {
                app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                break;
            }
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "\r\n[APP_WIFI] : Wi-Fi Connecting to : %s\r\n", app_wifiData.ssid);
            app_wifiData.state = APP_WIFI_STATE_WINCS_SERVICE_TASKS;
            break;
        }

        case APP_WIFI_STATE_WINCS_SERVICE_TASKS:
        {
            char message[50];

            if(app_wifiData.alarmStatus != app_wifiData.alarmStatusPublished)
            {   // publish alarm status
                sprintf(message, "{\"alarm\": %d}", app_wifiData.alarmStatus);
                APP_WIFI_PublishData(message);
                app_wifiData.alarmStatusPublished = app_wifiData.alarmStatus;
            }

            if(app_wifiData.lightIndoorStatus != app_wifiData.lightIndoorStatusPublished)
            {   // publish light_indoor status
                sprintf(message, "{\"light_indoor\": %d}", app_wifiData.lightIndoorStatus);
                APP_WIFI_PublishData(message);
                app_wifiData.lightIndoorStatusPublished = app_wifiData.lightIndoorStatus;
            }

            if(app_wifiData.lightOutdoorStatus != app_wifiData.lightOutdoorStatusPublished)
            {   // publish light_indoor status
                sprintf(message, "{\"light_outdoor\": %d}", app_wifiData.lightOutdoorStatus);
                APP_WIFI_PublishData(message);
                app_wifiData.lightOutdoorStatusPublished = app_wifiData.lightOutdoorStatus;
            }

            if(app_wifiData.coordHeartbeatCounter != app_wifiData.heartbeatsPublished)
            {   // publish Coordinator heartbeat counter
                sprintf(message, "{\"coordHeartbeatCounter\": %d}", app_wifiData.coordHeartbeatCounter);
                APP_WIFI_PublishData(message);
                app_wifiData.heartbeatsPublished = app_wifiData.coordHeartbeatCounter;
            }

            if(app_wifiData.connectionRetires >= APP_WIFI_MAX_CON_RETRIES)
            {   // skip WINCS service tasks after APP_WIFI_MAX_CON_RETRIES and start provisioning
                app_wifiData.connectionRetires++;
                SYS_DEBUG_PRINT(SYS_ERROR_WARNING, TERM_YELLOW"[APP_WIFI] : WiFi connection not possible\r\n"TERM_RESET);
                app_wifiData.state = APP_WIFI_STATE_WINCS_START_PROVISIONING;
            }
            break;
        }

        case APP_WIFI_STATE_WINCS_START_PROVISIONING:
        {
            WDRV_WINC_DCPT *const pDcpt = (WDRV_WINC_DCPT *const)sysObj.drvWifiWinc;

            if (pDcpt->pCtrl->connectedState == WDRV_WINC_CONN_STATE_DISCONNECTED)
            {
                SYS_WINCS_PROV_SrvCtrl(SYS_WINCS_PROV_SET_CALLBACK, APP_WIFIPROV_CallbackHandler);
                if(SYS_WINCS_PASS != SYS_WINCS_PROV_SrvCtrl(SYS_WINCS_PROV_ENABLE, NULL))
                {
                    app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                    break;
                }
                app_wifiData.connectionRetires = 0;
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : WiFi provisioning started\r\n");
                app_wifiData.state = APP_WIFI_STATE_WINCS_DO_NOTHING;
            }
            break;
        }

        case APP_WIFI_STATE_WINCS_ERROR:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_ERROR, TERM_RED"[APP_WIFI] : ERROR in Application\r\n"TERM_RESET);
            app_wifiData.state = APP_WIFI_STATE_WINCS_SERVICE_TASKS;
            break;
        }

        case APP_WIFI_STATE_WINCS_DO_NOTHING:
        {
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */

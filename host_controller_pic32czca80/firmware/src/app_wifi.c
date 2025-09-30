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

/*******************************************************************************
  Function:
    void APP_WIFI_Initialize ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

void APP_WIFI_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_wifiData.state = APP_WIFI_STATE_WINCS_PRINT;
    app_wifiData.mqttMessCntWifi = 0;
    app_wifiData.mqttMessCntLtem = 0;
}

void APP_SYS_TIME_CallbackSetFlag(uintptr_t context)
{
    if (context != 0)
    {
        /* Context holds the flag's address */
        *((bool *) context) = true;
    }
}

void APP_WIFI_PublishData(char *msg)
{
    SYS_WINCS_MQTT_FRAME_t mqtt_pub;
    mqtt_pub.qos      = SYS_WINCS_MQTT_PUB_MSG_QOS_TYPE;
    mqtt_pub.topic    = SYS_WINCS_MQTT_PUB_TOPIC_NAME;
    mqtt_pub.message  = msg;
    mqtt_pub.protoVer = SYS_WINCS_MQTT_PROTO_VERSION;
    SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_PUBLISH, (void *)&mqtt_pub);
}

static void APP_WIFI_PublishDataInit(void)
{
    APP_WIFI_PublishData("{\"alarm\": 0}");
    APP_WIFI_PublishData("{\"light_indoor\": 0}");
    APP_WIFI_PublishData("{\"light_outdoor\": 0}");
    APP_WIFI_PublishData("{\"mqttMessCntWifi\": 0}");
    APP_WIFI_PublishData("{\"mqttMessCntLtem\": 0}");
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
            if(app_wifiData.lightIndoorStatus)
            {
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_indoor off\r\n");
                app_wifiData.lightIndoorStatus = false;
                APP_WIFI_PublishData("{\"light_indoor\": 0}");

            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_indoor on\r\n");
                app_wifiData.lightIndoorStatus = true;
                APP_WIFI_PublishData("{\"light_indoor\": 1}");
            }

            // inform coordinator
            if(APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_INDOOR))
            {
                uint8_t index;
                uint8_t buffer[3];
                uint8_t length = 3;

                index = APP_COORDINATOR_deviceGetIndex(TYPE_LIGHTING_INDOOR);
                buffer[0] = CMD_SET_LIGHT;;
                buffer[1] = index;
                buffer[2] = app_wifiData.lightIndoorStatus;
                while(!APP_COORDINATOR_Prepare2Send_Message(index, buffer, length, false));
            }
        }
        // toggle outdoor light
        else if (strstr(mqttRxFrame->message, "\"light_outdoor\":\"toggle\"") != NULL)
        {
            if(app_wifiData.lightOutdoorStatus)
            {
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_outdoor off\r\n");
                app_wifiData.lightOutdoorStatus = false;
                APP_WIFI_PublishData("{\"light_outdoor\": 0}");

            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_WIFI] : light_outdoor on\r\n");
                app_wifiData.lightOutdoorStatus = true;
                APP_WIFI_PublishData("{\"light_outdoor\": 1}");
            }

            // inform coordinator
            if(APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_OUTDOOR))
            {
                uint8_t index;
                uint8_t buffer[3];
                uint8_t length = 3;

                index = APP_COORDINATOR_deviceGetIndex(TYPE_LIGHTING_OUTDOOR);
                buffer[0] = CMD_SET_LIGHT;;
                buffer[1] = index;
                buffer[2] = app_wifiData.lightOutdoorStatus;
                while(!APP_COORDINATOR_Prepare2Send_Message(index, buffer, length, false));
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
            if(APP_COORDINATOR_deviceGetAlive(device))
            {
                uint8_t index;
                uint8_t buffer[9];
                uint8_t length = 9;

                index = APP_COORDINATOR_deviceGetIndex(device);
                buffer[0] = CMD_SET_LED_RGB_BLINK;;
                buffer[1] = index;
                buffer[2] = color;  // COLOR : 0x2B: yellow, 0x55: green, 0xAA: blue, 0xFF: red
                buffer[3] = 0xFF;   // Saturation Value
                buffer[4] = 0xFF;   // Saturation Value
                buffer[5] = 0xf4;   // Blinking Frequency
                buffer[6] = 0x01;   // Blinking Frequency - 500ms
                buffer[7] = 0x10;   // Blinking Time
                buffer[8] = 0x27;   // Blinking Time - 10s
                while(!APP_COORDINATOR_Prepare2Send_Message(index, buffer, length, false));
            }
        }
    }


    free(str_copy);
}


uint32_t APP_WIFI_GetConnectedCount(void)
{
    return connectedCount;
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

            //Subscribe to topic 
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_SUBS_TOPIC, (SYS_WINCS_MQTT_HANDLE_t)&g_mqttSubsframe);
            break;
        }

        case SYS_WINCS_MQTT_SUBCRIBE_ACK:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, TERM_GREEN"[APP_WIFI] : MQTT Subscription has been acknowledged. \r\n"TERM_RESET);
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
            SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_WIFI] :MQTT-  Reconnecting...\r\n");
            // Set the callback function for MQTT events
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_SET_CALLBACK, APP_MQTT_Callback);
            // Configure the MQTT service with the provided configuration
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONFIG, (SYS_WINCS_MQTT_HANDLE_t)&g_mqttCfg);
            // Connect to the MQTT broker using the specified configuration
            SYS_WINCS_MQTT_SrvCtrl(SYS_WINCS_MQTT_CONNECT, &g_mqttCfg);
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
                app_wifiData.state = APP_WIFI_STATE_WINCS_SET_WIFI_PARAMS;
                domainFlag = true;
            }

            break;
        }

        /* SNTP UP event code*/
        case SYS_WINCS_WIFI_SNTP_UP:
        {            
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : SNTP UP \r\n"); 
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_WIFI] : Connecting to the Cloud\r\n");

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
            break;
        }

        /* Wi-Fi disconnected event code*/
        case SYS_WINCS_WIFI_DISCONNECTED:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_ERROR, TERM_RED"[APP_WIFI] : Wi-Fi Disconnected\nReconnecting... \r\n"TERM_RESET);
            char sntp_url[] =  SYS_WINCS_WIFI_SNTP_ADDRESS;
            if (SYS_WINCS_FAIL == SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_SET_SNTP, sntp_url))
            {
                app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                break;
            }
            SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_STA_CONNECT, NULL);
            connectedCount -= 1;
            break;
        }

        /* Wi-Fi connection failed event code*/
        case SYS_WINCS_WIFI_CONNECT_FAILED:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_WARNING, TERM_RED"[APP_WIFI] : Wi-Fi connection failed\nReconnecting... \r\n"TERM_RESET);
            SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_STA_CONNECT, NULL);
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

/******************************************************************************
  Function:
    void APP_WIFI_Tasks ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

void APP_WIFI_Tasks ( void )
{
    static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;
    static SYS_TIME_HANDLE alarmTimer = SYS_TIME_HANDLE_INVALID;

    /* Check the application's current state. */
    switch(app_wifiData.state)
    {
        // State to print Message 
        case APP_WIFI_STATE_WINCS_PRINT:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, " --- WINCS02 MQTT client demo ---\r\n");
            
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
                .ssid        = SYS_WINCS_WIFI_STA_SSID,        // Set the SSID (network name) for the Wi-Fi connection
                .passphrase  = SYS_WINCS_WIFI_STA_PWD,         // Set the passphrase (password) for the Wi-Fi connection
                .security    = SYS_WINCS_WIFI_STA_SECURITY,    // Set the security type (e.g., WPA2) for the Wi-Fi connection
                .autoConnect = SYS_WINCS_WIFI_STA_AUTOCONNECT  // Enable or disable auto-connect to the Wi-Fi network
            };

            // Set the Wi-Fi parameters
            if (SYS_WINCS_FAIL == SYS_WINCS_WIFI_SrvCtrl(SYS_WINCS_WIFI_SET_PARAMS, &wifi_sta_cfg))
            {
                app_wifiData.state = APP_WIFI_STATE_WINCS_ERROR;
                break;
            }
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "\r\n[APP_WIFI] : Wi-Fi Connecting to : %s\r\n", SYS_WINCS_WIFI_STA_SSID);
            app_wifiData.state = APP_WIFI_STATE_WINCS_SERVICE_TASKS;
            break;
        }

        case APP_WIFI_STATE_WINCS_SERVICE_TASKS:
        {
            if(app_wifiData.alarmExpired == true)
            {
                //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "Alarm off\r\n");
                //USER_LED1_Set();
                app_wifiData.alarmExpired = false;
                alarmTimer = SYS_TIME_HANDLE_INVALID;
                app_wifiData.alarmStatus = false;
                APP_WIFI_PublishData("{\"alarm\": 0}");
                break;
            }
            
            if((app_wifiData.alarmStatus != false) && (alarmTimer == SYS_TIME_HANDLE_INVALID))
            {
                //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "Alarm on\r\n");
                //USER_LED1_Clear();
                APP_WIFI_PublishData("{\"alarm\": 1}");
                app_wifiData.alarmExpired = false;
                alarmTimer = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &app_wifiData.alarmExpired, 30000, SYS_TIME_SINGLE);
                (void)alarmTimer; // prevent compiler warning - set but not used
            }
            break;
        }

        case APP_WIFI_STATE_WINCS_ERROR:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_ERROR, TERM_RED"[APP_WIFI] : ERROR in Application "TERM_RESET);
            app_wifiData.state = APP_WIFI_STATE_WINCS_SERVICE_TASKS;
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */

/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "app_lte.h"

#include <string.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

APP_LTE_DATA_T app_lteData;
static uint32_t coordCallbackIdx;
static uint32_t lteCallbackIdx;

static bool isAppLteStatusMutexCreated = false;
static OSAL_MUTEX_DECLARE(appLteStatusMutex);

typedef struct
{
    const char*     cmdStr;         // string identifying the command
    const char*     cmdExpResp;     // expected response string
    uint32_t        timeout;        // response timeout
    const char*     cmdDescr;       // simple command description

} APP_LTE_COMMANDS; // command descriptor

static const APP_LTE_COMMANDS app_lte_command_sequence[]=
{// command                                                     exp. response               timeout(ms) description
    {"",                                                        "+SYSSTART",                5000,       "Module powered up and ready"},
    {"AT\r",                                                    "OK",                       2000,       "communication check"},
    {"AT+IFC=0,0\r",                                            "OK",                       2000,       "disable hardware flow control"},
    {"AT+CFUN=1\r",                                             "OK",                       2000,       "set full phone functionality"},
    {"AT+CEREG=1\r",                                            "OK",                       2000,       "Enable network registration unsolicited result code"},
    {"AT+CEREG?\r",                                             "+CEREG: 1,5",              15000,      "network registered"},
    {"AT+CMEE=2\r",                                             "OK",                       2000,       "Report Mobile Termination with result code and verbose values"},
    {"AT+CSQ\r",                                                "OK",                       2000,       "check Signal Quality"},
    {"AT+SQNSMQTTCFG=0,\"mchp_enlit_demo_dev02\"\r",            "OK",                       2000,       "MQTT client configuration"},
    {"AT+SQNSMQTTCONNECT=0,"LTEIOT10_MQTT_CLOUD_URL",1883\r",   "+SQNSMQTTONCONNECT:0,0",   15000,      "MQTT server connection"},
    {"AT+SQNSMQTTSUBSCRIBE=0,"LTEIOT10_MQTT_SUB_TOPIC"\r", \
                                      "+SQNSMQTTONSUBSCRIBE:0,"LTEIOT10_MQTT_SUB_TOPIC",0", 5000,       "Subscribe to topic"},
    {"AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,12\r",   ">",                        2000,       "Publish topic"},
    {"{\"alarm\": 0}\r",                                        "OK",                       2000,       "Initialize alarm"},
    {"AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,19\r",   ">",                        2000,       "Publish topic"},
    {"{\"light_indoor\": 0}\r",                                 "OK",                       2000,       "Initialize light_indoor"},
    {"AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,20\r",   ">",                        2000,       "Publish topic"},
    {"{\"light_outdoor\": 0}\r",                                "OK",                       2000,       "Initialize light_outdoor"},
    {"AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,25\r",   ">",                        2000,       "Publish topic"},
    {"{\"mqttRecMessCntLtem\": 0}\r",                           "OK",                       2000,       "Initialize mqttRecMessCntLtem"},
};

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */
volatile bool response_received;

static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;
static char mqttMessageString[50];
static char atCmdPubTopicString[80];

static void _APP_LTE_UartReadCallback(uintptr_t context);

void lteiot10_reset_device(void)
{
    // MikroBUS_RST
    WINC_LTE_RESETN_Clear();
    APP_DelayMS(100);
    WINC_LTE_RESETN_Set();
    APP_DelayMS(1000);
 }

static void _APP_LTE_StartResponseRcv(void)
{
    // Start New Response Reception
    response_received = false;
    memset(app_lteData.rx_buf, 0, sizeof(app_lteData.rx_buf));
    app_lteData.rx_buf_index = 0;
    SERCOM4_USART_Read(&app_lteData.rx_byte, 1);
 }

size_t read_response(char *p_response)
{
    size_t len = 0;

    if(response_received)
    {
        len = strlen((char *)app_lteData.rx_buf);
        memcpy(p_response, app_lteData.rx_buf, len);
#ifdef APP_LTE_DEBUG_LOGS
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : rd response: %s\r\n", p_response);
#endif
        _APP_LTE_StartResponseRcv();
    }
    return len;
}

bool read_response_and_compare(const char *p_exp_response)
{
    if(response_received)
    {
        if(strstr((char *)app_lteData.rx_buf, p_exp_response) != NULL)
        {   // rx_buf contains expected string
#ifdef APP_LTE_DEBUG_LOGS
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : rdcmp pass: %s\r\n", (char *)app_lteData.rx_buf);
#endif
            _APP_LTE_StartResponseRcv();
            return true;
        }
        else
        {
#ifdef APP_LTE_DEBUG_LOGS
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : rdcmp fail: %s\r\n", (char *)app_lteData.rx_buf);
#endif
        }
        _APP_LTE_StartResponseRcv();
    }
    return false;
}
bool send_cmd(const char *p_cmd)
{
    SERCOM4_USART_Write((uint8_t *)p_cmd, strlen(p_cmd));
#ifdef APP_LTE_DEBUG_LOGS
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : send: %s\n", p_cmd);
#endif
    return true;
}

void _APP_LTE_UartReadCallback(uintptr_t context)
{
    app_lteData.rx_buf[app_lteData.rx_buf_index] = app_lteData.rx_byte;
    if (app_lteData.rx_buf_index > 0) {
        if(   (app_lteData.rx_buf[app_lteData.rx_buf_index - 1] == '\r')
           && (app_lteData.rx_buf[app_lteData.rx_buf_index] == '\n'))
        {   // response complete
            uint8_t msg_len = app_lteData.rx_buf_index - 1;
            if(msg_len > 0)
            {
                app_lteData.rx_buf[app_lteData.rx_buf_index - 1] = 0; // remove \r
                app_lteData.rx_buf[app_lteData.rx_buf_index] = 0;   // remove \n
                response_received = true;
            }
            else
            {   // empty response '\r\n' --> Start New Response Reception
                _APP_LTE_StartResponseRcv();
            }
            return;
        }
        else if(   (app_lteData.rx_buf[app_lteData.rx_buf_index - 1] == '>')
                && (app_lteData.rx_buf[app_lteData.rx_buf_index] == ' '))
        {   // prompt received
            response_received = true;
        }
    }
    app_lteData.rx_buf_index++;
#ifdef APP_LTE_DEBUG_LOGS
    //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : read callback: %c\r\n", app_lteData.rx_buf[app_lteData.rx_buf_index - 1]);
#endif
    SERCOM4_USART_Read(&app_lteData.rx_byte, 1);
}

void APP_LTE_COORDINATOR_EventCallback(uint32_t event, void * data, uint32_t size)
{
    uint8_t type;
    uint8_t alive;
    bool state;
    
    if (event == APP_COORDINATOR_RESET_NOTIFY)
    {
        // Do something???
        //app_lteData.coordHeartbeatCounter = 0;
    }    
    else if (event == APP_COORDINATOR_HEARTBEAT_NOTIFY)
    {
        //app_lteData.coordHeartbeatCounter++;
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_LTE] : Heartbeat counter change\r\n");
    }
    else if (event == APP_COORDINATOR_ALARM_NOTIFY)
    {
        state = *((uint8_t *)data);
        app_lteData.alarmStatus = state;
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : Alarm state change to %d\r\n", state);
    }
    else if (event == APP_COORDINATOR_DEVICE_JOINED_NOTIFY)
    {
        // Nothing by now
        type = *((uint8_t *)data++);
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : Device type 0x%02X joined\r\n", type);
    }
    else if (event == APP_COORDINATOR_DEVICE_ALIVE_NOTIFY)
    {
        type = *((uint8_t *)data++);
        alive = *((uint8_t *)data);
        if (type == TYPE_LIGHTING_INDOOR) 
        {
            //app_lteData.lightIndoorAlive = alive;
        }else if (type == TYPE_LIGHTING_OUTDOOR)
        {
            //app_lteData.lightOutdoorAlive = alive;
        }
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : Device type 0x%02X alive change to %d\r\n", type, alive);
    }
    else if (event == APP_COORDINATOR_DEVICE_STATE_NOTIFY)
    {
        type = *((uint8_t *)data++);
        state = *((uint8_t *)data);
        if (type == TYPE_LIGHTING_INDOOR) 
        {
            app_lteData.lightIndoorStatus = state;
        }else if (type == TYPE_LIGHTING_OUTDOOR)
        {
            app_lteData.lightOutdoorStatus = state;
        }    
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : Device type 0x%02X state change to %d\r\n", type, state);
    }
}

int32_t APP_LTE_RegisterNotification(void (*func)(uint32_t, void *, uint32_t))
{
    uint32_t i;
    
    if (func == NULL)
        return -APP_ERR_INV;
    
    for (i = 0; i < APP_LTE_NOTIF_CALLBACK_COUNT; i++)
    {
        if (app_lteData.notifCallbacks[i].func == NULL)
        {
           app_lteData.notifCallbacks[i].func = func;
           
           return i;
        }
    }
   
    return -APP_ERR_NOMEM;
}

APP_RESULT APP_LTE_UnregisterNotification(uint32_t idx)
{
    if (idx < APP_LTE_NOTIF_CALLBACK_COUNT)
    {
        app_lteData.notifCallbacks[idx].func = NULL;
        
        return APP_SUCCESS;
    }
    
    return APP_ERR_EMPTY;
}

static void APP_LTE_Notify(APP_LTE_NOTIFY_EVENT event, void * data, uint32_t size)
{
    uint32_t i;
    
    //Call all state callback functions
    for (i = 0; i < APP_LTE_NOTIF_CALLBACK_COUNT; i++)
    {
        if (app_lteData.notifCallbacks[i].func != NULL)
        {
            app_lteData.notifCallbacks[i].func(event, data, size);
        }
    }
}

bool APP_LTE_EventCallback(uint32_t event, void * data, uint32_t size)
{
    if(OSAL_MUTEX_Lock(&appLteStatusMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        return false;
    }
    
    switch(event)
    {
        case APP_LTE_AVAILABLE_NOTIFY:
        {
            app_lteData.status |= APP_LTE_AVAILABLE;
            break;
        }
        case APP_LTE_CONNECTED_NOTIFY:
        {
            app_lteData.status |= APP_LTE_CONNECTED;
            break;
        }
        case APP_LTE_DISCONNECTED_NOTIFY:
        {
            app_lteData.status &= ~APP_LTE_CONNECTED;
            app_lteData.status &= ~APP_LTE_MQTT_CONNECTED;
            break;
        }
        case APP_LTE_MQTT_CONNECTED_NOTIFY:
        {
            app_lteData.status |= APP_LTE_MQTT_CONNECTED;
            app_lteData.cloudConnected = true;
            break;
        }
        case APP_LTE_MQTT_DISCONNECTED_NOTIFY:
        {
            app_lteData.status &= ~APP_LTE_MQTT_CONNECTED;
            app_lteData.cloudConnected = false;
            break;
        }
        default:
        {
            break;
        }
    }
    /* Release mutex */
    (void) OSAL_MUTEX_Unlock(&appLteStatusMutex);
    return true;
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
bool APP_LTE_Initialize(void)
{
    SERCOM4_USART_ReadCallbackRegister(_APP_LTE_UartReadCallback, (uintptr_t)NULL);

    _APP_LTE_StartResponseRcv();

    app_lteData.state = APP_LTE_STATE_INIT;

    //WDRV_WINC_SSN_Clear(); // RTS not connected
    // WKP always '1'
    LTE_WAKEUP_Set();

    //lteiot10_reset_device(); // reset line shared with WINC module - resetted within wdrv_winc.c

    app_lteData.status = APP_LTE_OFF;
    app_lteData.cloudConnected = false;
    app_lteData.connectionRetires = 0;
    app_lteData.mqttMessCntLtem = 0;
    app_lteData.mqttRecMessCntLtem = 0;
    app_lteData.mqttRecMessCntLtemReported = 0;
    app_lteData.alarmStatusPublished = false;
    app_lteData.lightIndoorStatusPublished = false;
    app_lteData.lightOutdoorStatusPublished = false;
    app_lteData.messageRecOngoing = false;
    app_lteData.messagePubOngoing = false;
    
    /* Mutex creation to notify status */
    if (isAppLteStatusMutexCreated == false)
    {
        if(OSAL_MUTEX_Create(&(appLteStatusMutex)) != OSAL_RESULT_SUCCESS)
        {
            return false;
        }
        else
        {
            isAppLteStatusMutexCreated = true;
        }
    }    

    // start timer for timeout detection
    SYS_TIME_DelayMS(5000, &timer);
    
    return true;
}

static void APP_Parse_Rx_Message(char *mqttRxTopic, char *mqttRxMessage)
{
    char *parts[10];
    int count = 0;

    char *str_copy = strdup(mqttRxTopic);
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
        if(strstr(mqttRxMessage, "\"light_indoor\":\"toggle\"") != NULL)
        {
            uint8_t alive;
            uint8_t index;

            index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_INDOOR);
            APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_INDOOR, &alive);
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                if(app_lteData.lightIndoorStatus)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_LTE] : light_indoor off\r\n");
                    app_lteData.lightIndoorStatus = false;
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_LTE] : light_indoor on\r\n");
                    app_lteData.lightIndoorStatus = true;
                }

                // inform coordinator
                APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
                cmdData.data[0] = CMD_SET_LIGHT;
                cmdData.data[1] = index;
                cmdData.data[2] = app_lteData.lightIndoorStatus;
                cmdData.length = 3;
                cmdData.answer = false;
                APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : device type 0x%02X not present\r\n", TYPE_LIGHTING_INDOOR);
            }
        }
        // toggle outdoor light
        else if (strstr(mqttRxMessage, "\"light_outdoor\":\"toggle\"") != NULL)
        {
            uint8_t alive;
            uint8_t index;

            index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_OUTDOOR);
            APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_OUTDOOR, &alive);
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                if(app_lteData.lightOutdoorStatus)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_LTE] : light_outdoor off\r\n");
                    app_lteData.lightOutdoorStatus = false;
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_LTE] : light_outdoor on\r\n");
                    app_lteData.lightOutdoorStatus = true;
                }

                // inform coordinator
                APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
                cmdData.data[0] = CMD_SET_LIGHT;
                cmdData.data[1] = index;
                cmdData.data[2] = app_lteData.lightOutdoorStatus;
                cmdData.length = 3;
                cmdData.answer = false;
                APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : device type 0x%02X not present\r\n", TYPE_LIGHTING_OUTDOOR);
            }
        }
    }
    else if(strcmp(parts[count - 2], "set-rgb") == 0)
    {
        const char *device_str = strstr(mqttRxMessage, "\"device\":\"0x");
        const char *color_str = strstr(mqttRxMessage, "\"color\":\"0x");

        uint8_t device = 0;
        uint8_t color = 0;

        if(device_str && color_str)
        {
            unsigned int temp_device, temp_color;

            sscanf(device_str, "\"device\":\"0x%x\"", &temp_device);
            sscanf(color_str, "\"color\":\"0x%x\"", &temp_color);

            device = (uint8_t)temp_device;
            color = (uint8_t)temp_color;

            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_LTE] : Device: 0x%02X, Color: 0x%02X\n", device, color);
            // inform coordinator
            uint8_t alive;
            uint8_t index;

            index = APP_COORDINATOR_deviceIndexByType(TYPE_LIGHTING_OUTDOOR);
            APP_COORDINATOR_deviceGetAlive(TYPE_LIGHTING_OUTDOOR, &alive);
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
                APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : device type 0x%02X not present\r\n", device);
            }
        }
    }

    free(str_copy);
}

void APP_LTE_Tasks(void)
{
    static uint8_t seq_index = 0;

    /* Check the application's current state. */
    switch(app_lteData.state)
    {
        case APP_LTE_STATE_INIT:
            // Register to Coordinator Notifications
            coordCallbackIdx = APP_COORDINATOR_RegisterNotification(APP_LTE_COORDINATOR_EventCallback);
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : Coordinator Notification index = %d\r\n", coordCallbackIdx);
            lteCallbackIdx = APP_LTE_RegisterNotification(APP_LTE_EventCallback);
            app_lteData.state = APP_LTE_STATE_INITIALIZE;
            break;
            
        case APP_LTE_STATE_INITIALIZE:
        {        
            if(app_lte_command_sequence[seq_index].cmdStr == "AT+CEREG?\r") // wait for network registration
            {   // special handling because multiple responses are allowed
                char response[400] = {0};
                size_t len;

                len = read_response(response);
                if(len != 0)
                {
                    if(   (strcmp((char *)response, "+CEREG: 5") == 0) // Registered, roaming
                       || (strcmp((char *)response, "+CEREG: 1") == 0) // Registered, home network
                       || (strcmp((char *)response, "+CEREG: 1,5") == 0) // Registered, roaming
                       || (strcmp((char *)response, "+CEREG: 1,1") == 0)) // Registered, home network
                    {
                        seq_index++;

                        if(app_lte_command_sequence[seq_index].cmdStr != "")
                        {   // send next command
                            send_cmd(app_lte_command_sequence[seq_index].cmdStr);
                        }

                        // start timeout
                        if(timer != SYS_TIME_HANDLE_INVALID)
                        {
                            SYS_TIME_TimerDestroy(timer);
                        }
                        SYS_TIME_DelayMS(app_lte_command_sequence[seq_index].timeout, &timer);
                    }
                }
            }
            else if(read_response_and_compare(app_lte_command_sequence[seq_index].cmdExpResp))
            {
                seq_index++;
                if(seq_index >= (sizeof(app_lte_command_sequence)/sizeof(APP_LTE_COMMANDS)))
                {   // end of command list reached
                    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_LTE] : Initialization sequence completed\r\n");
                    app_lteData.state = APP_LTE_STATE_RUNNING;
                    if(timer != SYS_TIME_HANDLE_INVALID)
                    {
                        SYS_TIME_TimerDestroy(timer);
                    }
                    SYS_TIME_DelayMS(2000, &timer);
                    break;
                }

                if(app_lte_command_sequence[seq_index].cmdStr != "")
                {   // send next command
                    send_cmd(app_lte_command_sequence[seq_index].cmdStr);
                }

                // start timeout
                if(timer != SYS_TIME_HANDLE_INVALID)
                {
                    SYS_TIME_TimerDestroy(timer);
                }
                SYS_TIME_DelayMS(app_lte_command_sequence[seq_index].timeout, &timer);
            }

            if(   (timer != SYS_TIME_HANDLE_INVALID)
               && (SYS_TIME_DelayIsComplete(timer) == true))
            {   // timeout reached
                SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_LTE] : %s - timeout at seq state %d\r\n", app_lte_command_sequence[seq_index].cmdDescr, seq_index);
                app_lteData.state = APP_LTE_STATE_TIMEOUT;
                SYS_TIME_TimerDestroy(timer);
                SYS_TIME_DelayMS(20000, &timer);
            }
            break;
        }

        case APP_LTE_STATE_TIMEOUT:
        {
            if(seq_index > 0)
            {
                if(app_lteData.connectionRetires >= APP_LTE_MAX_CON_RETRIES)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_LTE] : %s - error\r\n", app_lte_command_sequence[seq_index].cmdDescr);
                    app_lteData.state = APP_LTE_STATE_NOT_CONNECTED;
                }
                else if(SYS_TIME_DelayIsComplete(timer) == true)
                {   // retry communication check if +SYSSTART has been received
                    seq_index = 1;
                    send_cmd(app_lte_command_sequence[seq_index].cmdStr);
                    SYS_TIME_TimerDestroy(timer);
                    SYS_TIME_DelayMS(app_lte_command_sequence[seq_index].timeout, &timer);
                    app_lteData.state = APP_LTE_STATE_INITIALIZE;
                    app_lteData.connectionRetires++;
                }
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_LTE] : module not connected\r\n");
                app_lteData.state = APP_LTE_STATE_NOT_CONNECTED;
            }
            break;
        }

        case APP_LTE_STATE_RUNNING:
        {
            char response[400] = {0};
            size_t len;
            static char topic[100];
            
            len = read_response(response);
            if(len != 0)
            {
                if(strstr((char *)response, "ERROR") != NULL)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_LTE] : %s\r\n", response);
                    app_lteData.messageRecOngoing = false;
                    app_lteData.messagePubOngoing = false;
                }
                else if(strstr((char *)response, ">") != NULL)
                {   // publish topic message after prompt
                    send_cmd(mqttMessageString);
                }
                else if(strstr((char *)response, "OK") != NULL)
                {
                    app_lteData.messageRecOngoing = false;
                    app_lteData.messagePubOngoing = false;
                }
                else if(strstr((char *)response, "+SQNSMQTTONMESSAGE:") != NULL)
                {   // message notification
                    const char* start = strchr(response, '"');
                    start++;  // first "
                    const char* end = strchr(start, '"');
                    size_t len = end - start;
                    strncpy(topic, start, len);
                    topic[len] = '\0'; // mark end of string

                    if(strstr((char *)topic, "json/error") == NULL)
                    {   // ask for message of topic
                        char atCmdRecMessageString[100];
                        sprintf(atCmdRecMessageString, "AT+SQNSMQTTRCVMESSAGE=0,\"%s\"\r", topic);
                        send_cmd(atCmdRecMessageString);
                        app_lteData.messageRecOngoing = true;
                        app_lteData.mqttRecMessCntLtem++;
                    }
                }
                else if(   (app_lteData.messageRecOngoing)
                        && (strstr((char *)response, "\"payload\":") != NULL))
                {
                    APP_Parse_Rx_Message(topic, response);
                }
                else if(strstr((char *)response, "+CEREG:") != NULL)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_WARNING, "[APP_LTE] : network status change: %s\r\n", response);
                }
            }
            else if(   (SYS_TIME_DelayIsComplete(timer) == true)
                    && (app_lteData.messageRecOngoing == false)
                    && (app_lteData.messagePubOngoing == false))
            {
                // increase and publish LTE module counter
                app_lteData.mqttMessCntLtem++;
                sprintf(mqttMessageString, "{\"mqttMessCntLtem\":%d}\r", app_lteData.mqttMessCntLtem);
                sprintf(atCmdPubTopicString, "AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,%d\r", strlen((char *)mqttMessageString) - 1);
                app_lteData.messagePubOngoing = true;
                send_cmd(atCmdPubTopicString);

                if(timer != SYS_TIME_HANDLE_INVALID)
                {
                    SYS_TIME_TimerDestroy(timer);
                }
                // resend after delay
                SYS_TIME_DelayMS(60000, &timer);
            }
            else if(   (app_lteData.alarmStatus != app_lteData.alarmStatusPublished)
                    && (app_lteData.messageRecOngoing == false)
                    && (app_lteData.messagePubOngoing == false))
            {
                // publish alarm status
                app_lteData.alarmStatusPublished = app_lteData.alarmStatus;
                sprintf(mqttMessageString, "{\"alarm\":%d}\r", app_lteData.alarmStatus);
                sprintf(atCmdPubTopicString, "AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,%d\r", strlen((char *)mqttMessageString) - 1);
                app_lteData.messagePubOngoing = true;
                send_cmd(atCmdPubTopicString);
            }
            else if(   (app_lteData.lightIndoorStatus != app_lteData.lightIndoorStatusPublished)
                    && (app_lteData.messageRecOngoing == false)
                    && (app_lteData.messagePubOngoing == false))
            {
                // publish light_indoor status
                app_lteData.lightIndoorStatusPublished = app_lteData.lightIndoorStatus;
                sprintf(mqttMessageString, "{\"light_indoor\":%d}\r", app_lteData.lightIndoorStatus);
                sprintf(atCmdPubTopicString, "AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,%d\r", strlen((char *)mqttMessageString) - 1);
                app_lteData.messagePubOngoing = true;
                send_cmd(atCmdPubTopicString);
            }
            else if(   (app_lteData.lightOutdoorStatus != app_lteData.lightOutdoorStatusPublished)
                    && (app_lteData.messageRecOngoing == false)
                    && (app_lteData.messagePubOngoing == false))
            {
                // publish light_outdoor status
                app_lteData.lightOutdoorStatusPublished = app_lteData.lightOutdoorStatus;
                sprintf(mqttMessageString, "{\"light_outdoor\":%d}\r", app_lteData.lightOutdoorStatus);
                sprintf(atCmdPubTopicString, "AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,%d\r", strlen((char *)mqttMessageString) - 1);
                app_lteData.messagePubOngoing = true;
                send_cmd(atCmdPubTopicString);
            }
            else if(   (app_lteData.mqttRecMessCntLtem != app_lteData.mqttRecMessCntLtemReported)
                    && (app_lteData.messageRecOngoing == false)
                    && (app_lteData.messagePubOngoing == false))
            {
                // publish received message counter
                app_lteData.mqttRecMessCntLtemReported = app_lteData.mqttRecMessCntLtem;
                sprintf(mqttMessageString, "{\"mqttRecMessCntLtem\":%d}\r", app_lteData.mqttRecMessCntLtem);
                sprintf(atCmdPubTopicString, "AT+SQNSMQTTPUBLISH=0,"LTEIOT10_MQTT_PUB_TOPIC",0,%d\r", strlen((char *)mqttMessageString) - 1);
                app_lteData.messagePubOngoing = true;
                send_cmd(atCmdPubTopicString);
            }
            break;
        }

        case APP_LTE_STATE_NOT_CONNECTED:
        {   // do nothing
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            break;
        }
    }
}

/* *****************************************************************************
 End of File
 */

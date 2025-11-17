/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_interface.c

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
#include "app_interface.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_INTERFACE_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

#define CMD_EMERGENCY_SUPPORT

APP_INTERFACE_DATA app_interfaceData;
static char appPwd[APP_INTERFACE_PWD_SIZE] = APP_INTERFACE_DEFAULT_PWD;

APP_COORDINATOR_DEVICE_INFO CACHE_ALIGN device_info_interface[APP_COORDINATOR_MAX_DEVICES];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/

static void _commandSETLIGHT (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandSETPANELINFO (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandSETRGB (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandSETRGBBLINK (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandPINGTYPE (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
#ifdef CMD_EMERGENCY_SUPPORT    
static void _commandEMERGENCY (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
#endif
static void _commandPOWER (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandSETWIFI (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandGETWIFI (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandREGDEV (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandDBGLVL (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandCRST (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandHELP(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);

static const SYS_CMD_DESCRIPTOR appCmdTbl[]=
{
    {"SET_LIGHT", _commandSETLIGHT, ": SET_LIGHT <XXXX(dest)> [0|1] (0:off, 1:on)"},
    {"SET_PANEL_INFO", _commandSETPANELINFO, ": SET_PANEL_INFO <X(dest)> [0|1] (0:Logo, 1:Alarm)"},
    {"SET_RGB", _commandSETRGB, ": SET_RGB <X(dest)> <X(H)> <X(S)> <X(V)>"},
    {"SET_RGBB", _commandSETRGBBLINK, ": SET_RGBB <X(dest)> <X(H)> <X(S)> <X(V)> <X(freq)> <X(time)>"},
#ifdef CMD_EMERGENCY_SUPPORT    
    {"EMERGENCY", _commandEMERGENCY, ": EMERGENCY [0|1] (0:Off, 1:On)"},
#endif    
    {"POWER", _commandPOWER, ": POWER [0|1] (0:Off, 1:On)"},
    {"SET_WIFI", _commandSETWIFI, ": SET_WIFI <X(SSID)> <X(PASS)> <X(SECURITY MODE 0-3)>"},
    {"GET_WIFI", _commandGETWIFI, ": GET_WIFI>"},
    {"PING", _commandPINGTYPE, ": CPING <X(dest)>"},
    {"REGDEV", _commandREGDEV, ": REGDEV - Show Registered Devices"},
    {"DBGLVL", _commandDBGLVL, ": DBGLVL [0-4] - Modify Debug Level"},
    {"RST", _commandCRST, ": CRST - Coordinator Reset"},
//    {"CPOWER", _commandCPOWEROFF, ": CPOWER [0-1] - Power off(0)/on(1)"},
    {"HELP",_commandHELP, ": Help on commands"}
};

/*******************************************************************************
  Function:
    Timer in milliseconds for creating and waiting the delay.
 */

static bool APP_INTERFACE_TaskDelay(uint32_t ms, SYS_TIME_HANDLE* handle)
{
    // Check if there is the timer has been created and running
    if (*handle == SYS_TIME_HANDLE_INVALID)
    {
        // Create timer
        if (SYS_TIME_DelayMS(ms, handle) != SYS_TIME_SUCCESS)
        {
            return false;
        }
    }
    else
    {
        // Check timer
        if (SYS_TIME_DelayIsComplete(*handle) == true)
        {
            *handle = SYS_TIME_HANDLE_INVALID;
            return true;
        }
    }

    return false;
}

/*******************************************************************************
  Function:
    Software Reset
 */

bool _preprocessorCallback ( const SYS_CMD_DESCRIPTOR* pCmdTbl,
        SYS_CMD_DEVICE_NODE* pCmdIO, char* cmdBuff, size_t bufSize, void* hParam)
{
    return false;
}

static inline void _removePrompt(void)
{
    SYS_CMD_MESSAGE("\b");
}

static void _commandPINGTYPE(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    uint8_t type, index;    
    bool alive;
    
        if (argc == 2)
        {
            type = atoi(argv[1]);                
        if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_PANEL_LED))
        {                
            index = APP_COORDINATOR_deviceIndexByType(type);
            APP_COORDINATOR_deviceGetAlive(type, &alive);         
            if ((index != INDEX_UNKNOWN) && (alive))
            {  
                APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
                cmdData.data[0] = CMD_GET_DEVICE_INFO;
                cmdData.data[1] = index;
                cmdData.length = 2;
                cmdData.answer = false;
                alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
                if (!alive)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_INTERFACE] : Coord Cmds Queue full\r\n");
                }
            }else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_INTERFACE: Device Type 0x%02X index=%d alive=%s\r\n", type, index, alive?"true":"false");
            }
        }
        else
        {
            SYS_CMD_MESSAGE("Invalid type\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE("Incorrect param number\r\n");
    }
}

static void _commandSETRGB(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{

    APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
    uint8_t type, index;
    bool alive;
    
        if (argc == 5)
        {            
            type = atoi(argv[1]);
        if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_PANEL_LED))
        {                
            index = APP_COORDINATOR_deviceIndexByType(type);
            APP_COORDINATOR_deviceGetAlive(type, &alive);
            if ((index != INDEX_UNKNOWN) && (alive))
            {  
                app_interfaceData.deviceCmdFlag = true;                 
                cmdData.data[0] = CMD_SET_LED_RGB;
                cmdData.data[1] = index;
                uint16_t convertResult = APP_RES_SUCCESS;
                convertResult |= COMMON_U8AsciiToHex(argv[2], &cmdData.data[2]); // H
                convertResult |= COMMON_U8AsciiToHex(argv[3], &cmdData.data[3]); // S
                convertResult |= COMMON_U8AsciiToHex(argv[4], &cmdData.data[4]); // V
                if(convertResult == APP_RES_SUCCESS)
                {   // only send when parameter were given correctly
                    cmdData.length = 5;
                    cmdData.answer = false; 
                    alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
                    if (!alive)
                    {
                        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_INTERFACE] : Coord Cmds Queue full\r\n");
                    }
                }
                else 
                {                    
                    SYS_CMD_PRINT("invalid characters: %s %s %s %s\r\n", argv[1], argv[2], argv[3], argv[4]);
                    app_interfaceData.deviceCmdFlag = false;
                }  
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_INTERFACE: Device Type 0x%02X index=%d alive=%s\r\n", type, index, alive?"true":"false");
            }    
        }
        else
        {
            SYS_CMD_MESSAGE("Invalid type\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: SET_RGB <XXXX(type)> <XX(H)> <XX(S)> <XX(V)> ***\r\n");
    }

}

static void _commandSETRGBBLINK(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
    uint8_t type, index;
    bool alive;
    
        if (argc == 7)
        {
            type = atoi(argv[1]);               
        if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_PANEL_LED))
        {                
            index = APP_COORDINATOR_deviceIndexByType(type);
            APP_COORDINATOR_deviceGetAlive(type, &alive);
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                // Prepare command
                app_interfaceData.deviceCmdFlag = true;
                memset(cmdData.data, 0, CMD_DATA_SIZE);
                cmdData.data[0] = CMD_SET_LED_RGB_BLINK;
                cmdData.data[1] = index;
                uint16_t convertResult = APP_RES_SUCCESS;
                convertResult |= COMMON_U8AsciiToHex(argv[2], &cmdData.data[2]); // H
                convertResult |= COMMON_U8AsciiToHex(argv[3], &cmdData.data[3]); // S
                convertResult |= COMMON_U8AsciiToHex(argv[4], &cmdData.data[4]); // V
                convertResult |= COMMON_U16AsciiToHex(argv[5], (uint16_t *) &cmdData.data[5]); // Blinking frequency
                convertResult |= COMMON_U16AsciiToHex(argv[6], (uint16_t *) &cmdData.data[7]); // Blinking time
                if(convertResult == APP_RES_SUCCESS)
                {   // only send when parameter were given correctly
                    cmdData.length = 9;
                    cmdData.answer = false; 
                    alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
                    if (!alive)
                    {
                        SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_INTERFACE] : Coord Cmds Queue full\r\n");
                    }
                }
                else
                {
                    app_interfaceData.deviceCmdFlag = false;
                    SYS_CMD_MESSAGE("invalid characters\r\n");
                }   
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_INTERFACE: Device Type 0x%02X index=%d alive=%s\r\n", type, index, alive?"true":"false");
            }  
        }
        else
        {
            SYS_CMD_MESSAGE("Invalid type\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: SET_RGB_BLINK <XXXX(type)> <XX(H)> <XX(S)> <XX(V)> <XXXX(freq)> <XXXX(time)> ***\r\n");
    }      
}

static void _commandSETLIGHT(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
    uint8_t type, index;
    bool alive;

        if (argc == 3)
        {
            type = atoi(argv[1]);
        if ((type == TYPE_LIGHTING_INDOOR) || (type == TYPE_LIGHTING_OUTDOOR))
        {
            index = APP_COORDINATOR_deviceIndexByType(type);
            APP_COORDINATOR_deviceGetAlive(type, &alive);    
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                app_interfaceData.deviceCmdFlag = true;
                cmdData.data[0] = CMD_SET_LIGHT;
                cmdData.data[1] = index;
                if (atoi(argv[2]) == 0)
                {
                    cmdData.data[2] = 0x00; // off
                }
                else
                {
                    cmdData.data[2]= 0x01; // on
                }
                cmdData.length = 3;
                cmdData.answer = false; 
                alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData); 
                if (!alive)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_INTERFACE] : Coord Cmds Queue full\r\n");
                }
                else
                {
                    //Notify if change in the state 
                }
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_INTERFACE: Device Type 0x%02X index=%d alive=%s\r\n", type, index, alive?"true":"false");
            } 
        }
        else
        {
            SYS_CMD_MESSAGE("Invalid type\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: SET_LIGHT <XXXX(type)> [0|1] (0:off, 1:on) ***\r\n");
    } 
}

static void _commandSETPANELINFO(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
    uint8_t type, index;
    bool alive;

    if (argc == 3)
    {
        type = atoi(argv[1]);                        
        type = TYPE_PANEL_LED;
        if (type == TYPE_PANEL_LED)
        {
            index = APP_COORDINATOR_deviceIndexByType(type);
            APP_COORDINATOR_deviceGetAlive(type, &alive);    
            if ((index != INDEX_UNKNOWN) && (alive))
            {
                app_interfaceData.deviceCmdFlag = true;
                cmdData.data[0] = CMD_SET_PANEL_LED;
                cmdData.data[1] = index;
                if(atoi(argv[2]) == 0)
                {
                    cmdData.data[2] = 0x00; // Microchip Logo
                }
                else
                {
                    cmdData.data[2] = 0x01; // ALARM
                }
                cmdData.length = 3;
                cmdData.answer = false; 
                alive = APP_COORDINATOR_PushCoordCmdsQueue(&cmdData);
                if (!alive)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_INTERFACE] : Coord Cmds Queue full\r\n");
                }
                else
                {
                    //Notify if change in the state
                }
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_INTERFACE: Device Type 0x%02X index=%d alive=%s\r\n", type, index, alive?"true":"false");
            }
        }
        else
        {
            SYS_CMD_MESSAGE("Invalid type\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: SET_PANEL_INFO <XXXX(type)> [0|1] (0:LOGO, 1:ALARM) ***\r\n");
    } 
}

#ifdef CMD_EMERGENCY_SUPPORT    
static void _commandEMERGENCY(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    APP_COORDINATOR_CMDS_QUEUE_DATA cmdData;
    uint8_t onoff;
    uint32_t time_keep_alarm_ms;
    
    if (argc == 3)
    {
        onoff = (uint8_t) atoi(argv[1]);    
        if (onoff)
        {
            time_keep_alarm_ms = (uint8_t) atoi(argv[2]);
            if (time_keep_alarm_ms > 30)
                time_keep_alarm_ms = 30;  //Maximum 30 seconds
            
            time_keep_alarm_ms *= 1000;
            APP_COORDINATOR_handleEmergency(time_keep_alarm_ms);
            SYS_CMD_MESSAGE("Emergency On\r\n");
        }            
        else
        {
            APP_COORDINATOR_handleEmergency(0);
            SYS_CMD_MESSAGE("Emergency Off\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: EMERGENCY [0|1] <XXX TIME> (0:off, 1:on) ***\r\n");
    } 
}
#endif

static void _commandPOWER(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    uint8_t onoff;
    
    if (argc == 2)
    {
        onoff = atoi(argv[1]);
        if (onoff)
        {
            USB_HOST_PWR_Clear();
            SYS_CMD_MESSAGE("Coordinator Power On\r\n");
        }            
        else
        {
            USB_HOST_PWR_Set();
            SYS_CMD_MESSAGE("Coordinator Power Off\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: POWER [0|1] (0:off, 1:on) ***\r\n");
    } 
}

static void _commandSETWIFI(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    uint8_t sec;
    uint16_t size;
    char content[100];
    
    if (argc == 4)
    {
        sec = (uint8_t) atoi(argv[3]);
        if (sec > 3)
        {
            SYS_CMD_MESSAGE(" *** USAGE: SET_WIFI SSID_STR PASS_STR <0-3> ***\r\n");
        }
        else
        {
            if (APP_WIFI_SetWifiParamsToFile(argv[1], argv[2], sec))
            {
                SYS_CMD_PRINT("%s successfully written\r\n", APP_WIFI_CONFIG_FILE);
            }
            else
            {
                SYS_CMD_PRINT("Error writting %s\r\n", APP_WIFI_CONFIG_FILE);        
            }
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: SET_WIFI SSID_STR PASS_STR <0-3> ***\r\n");
    } 
}

static void _commandGETWIFI(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    char wifi_ssid_str[32];
    char wifi_pass_str[32];
    uint8_t wifi_sec;
    
    if (argc == 1)
    {
        if (APP_WIFI_GetWifiParamsFromFile(wifi_ssid_str, wifi_pass_str, &wifi_sec))
        {
            SYS_CMD_PRINT("WIFI params SSID=%s PASS=%s SEC=%u\r\n", wifi_ssid_str, wifi_pass_str, wifi_sec);
        }
        else
        {
            SYS_CMD_PRINT("Error getting WIFI params from %s\r\n", APP_WIFI_CONFIG_FILE);        
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE(" *** USAGE: SET_WIFI SSID_STR PASS_STR <0-3> ***\r\n");
    } 
}

static void _commandHELP(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    if (argc == 2)
    {
        SYS_CMD_DESCRIPTOR *pCmd;
        uint8_t idx;
        size_t len;

        // Show help for a single command
        pCmd = (SYS_CMD_DESCRIPTOR *)appCmdTbl;
        for (idx = 0; idx < app_interfaceData.numCommands; idx++, pCmd++)
        {
            len = strlen(argv[1]);

            if (strncmp(pCmd->cmdStr, argv[1], len) == 0)
            {
                SYS_CMD_PRINT("%s\t%s\r\n", pCmd->cmdStr, pCmd->cmdDescr);
                break;
            }
        }

        if (idx == app_interfaceData.numCommands)
        {
            SYS_CMD_MESSAGE("Command is not found.\r\n");
        }
    }
    else
    {
        app_interfaceData.state = APP_INTERFACE_STATE_PRINT_HELP;
        app_interfaceData.cmdNumToShowHelp = app_interfaceData.numCommands;
        app_interfaceData.pCmdDescToShowHelp = (SYS_CMD_DESCRIPTOR *)appCmdTbl;

        // Remove Prompt symbol
        _removePrompt();
    }
}

static void _commandCRST(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    if (argc == 2)
    {
        // Check password from parameters
        if (strncmp(argv[1], appPwd, APP_INTERFACE_PWD_SIZE) == 0)
        {
            // Correct password, Reset System
            SYS_CMD_MESSAGE("Reset Command is Ok !\r\n");
            // Go to state to reset system
            app_interfaceData.state = APP_INTERFACE_STATE_SW_RESET;
        }
        else
        {
            // Invalid password
            SYS_CMD_MESSAGE("Invalid password\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE("Incorrect param number\r\n");
    }
}

static void _commandREGDEV(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    if (argc == 1)
    {
        uint16_t numdevices = APP_COORDINATOR_MAX_DEVICES;
        if (numdevices)
        {
            APP_COORDINATOR_deviceDoSnapshot(&device_info_interface);
            
            app_interfaceData.state = APP_INTERFACE_STATE_PRINT_REG_DEVICES;
            app_interfaceData.cmdNumToShowHelp = numdevices;
            // Remove Prompt symbol
            _removePrompt();
            SYS_CMD_MESSAGE("Index Type Alive State\r\n");
            SYS_CMD_MESSAGE("----- ---- ----- -----\r\n");
        }
        else
        {
            SYS_CMD_MESSAGE("No registered devices\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE("Incorrect param number\r\n");
    }
}

static void _commandDBGLVL(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    if (argc == 2)
    {
        SYS_ERROR_LEVEL level;
        level = atoi(argv[1]);               
        if ((level >= 0) && (level <= 4))
        {
            SYS_DEBUG_ErrorLevelSet(level);
            SYS_CMD_PRINT("Debug Level switched to %d\r\n",level);
        }
        else
        {
            // Invalid password
            SYS_CMD_MESSAGE("Invalid password\r\n");
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE("Incorrect param number\r\n");
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_INTERFACE_Initialize ( void )

  Remarks:
    See prototype in app_interface.h.
 */

void APP_INTERFACE_Initialize ( void )
{
    
    /* Place the App state machine in its initial state. */
    app_interfaceData.state = APP_INTERFACE_STATE_INIT;
    app_interfaceData.deviceCmdFlag = false;
    app_interfaceData.numCommands = sizeof(appCmdTbl)/sizeof(SYS_CMD_DESCRIPTOR);

    /* Init timers */
    app_interfaceData.timer = SYS_TIME_HANDLE_INVALID;
    app_interfaceData.alarmTimer = SYS_TIME_HANDLE_INVALID;
    app_interfaceData.alarmCounter = false;

    if (!SYS_CMD_ADDGRP(appCmdTbl, app_interfaceData.numCommands, "HELP", ": Hybrid IoT Host Controller console commands"))
    {
        SYS_CONSOLE_Print(SYS_CONSOLE_INDEX_0, "Failed to create APP Console Commands\r\n");
        app_interfaceData.numCommands = 0;
    }
    else
    {
        SYS_CMD_CallbackRegister(appCmdTbl, _preprocessorCallback, 0);
    }
}


/******************************************************************************
  Function:
    void APP_INTERFACE_Tasks ( void )

  Remarks:
    See prototype in app_interface.h.
 */

void APP_INTERFACE_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_interfaceData.state )
    {
        /* Application's initial state. */
        case APP_INTERFACE_STATE_IDLE:
        case APP_INTERFACE_STATE_WAIT_DATA:
        {
            break;
        }

        case APP_INTERFACE_STATE_PROMPT:
        {
            SYS_CMD_MESSAGE(">");
            app_interfaceData.state = APP_INTERFACE_STATE_IDLE;
            break;
        }
        
        /* Application's initial state. */
        case APP_INTERFACE_STATE_INIT:
        {
            if (SYS_CMD_READY_TO_READ())
            {
                // Set default console storage data just in case it cannot be read later
                app_interfaceData.state = APP_INTERFACE_STATE_WAIT_DATA;
            }
            break;
        }
        case APP_INTERFACE_STATE_PRINT_HELP:
        {
            uint8_t idx;
            uint8_t idxMax = 2;

            _removePrompt();
            if (app_interfaceData.cmdNumToShowHelp > 0)
            {
                if (app_interfaceData.cmdNumToShowHelp < 5)
                {
                    idxMax = app_interfaceData.cmdNumToShowHelp;
                }

                for (idx = 0; idx < idxMax; idx++, app_interfaceData.pCmdDescToShowHelp++)
                {
                    SYS_CMD_PRINT("%s\t%s\r\n", app_interfaceData.pCmdDescToShowHelp->cmdStr,
                            app_interfaceData.pCmdDescToShowHelp->cmdDescr);
                    app_interfaceData.cmdNumToShowHelp--;
                }
            }
            else
            {
                // All commands have been represented
                app_interfaceData.state = APP_INTERFACE_STATE_PROMPT;
                break;
            }

            app_interfaceData.nextState = app_interfaceData.state;
            app_interfaceData.state = APP_INTERFACE_STATE_DELAY;
            app_interfaceData.delayMs = APP_INTERFACE_TASK_DFLT_DELAY_MS_BETWEEN_STATES;
            break;
        }
        
        case APP_INTERFACE_STATE_PRINT_REG_DEVICES:
        {
            uint8_t idx;
            uint8_t idxMax = 2;
            
            _removePrompt();            
            if (app_interfaceData.cmdNumToShowHelp > 0)
            {
                if (app_interfaceData.cmdNumToShowHelp < 3)
                {
                    idxMax = app_interfaceData.cmdNumToShowHelp;
                }

                for (idx = 1; idx <= idxMax; idx++)
                {
                    if (device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].index != INDEX_UNKNOWN)
                    {                      
                        SYS_CMD_PRINT("0x%02X-0x%02X-%s-%d\r\n", device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].index , device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].type, device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].alive? "true" : "false", device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].state);
                    }                    
                }
                app_interfaceData.cmdNumToShowHelp-=idxMax;
            }
            else
            {
                // All commands have been represented
                app_interfaceData.state = APP_INTERFACE_STATE_PROMPT;
                break;
            }

            app_interfaceData.nextState = app_interfaceData.state;
            app_interfaceData.state = APP_INTERFACE_STATE_DELAY;
            app_interfaceData.delayMs = APP_INTERFACE_TASK_DFLT_DELAY_MS_BETWEEN_STATES;
            break;
        }
        
        case APP_INTERFACE_STATE_SW_RESET:
        {
            /* Wait time to show message through the Console */
            app_interfaceData.nextState = app_interfaceData.state;
            app_interfaceData.state = APP_INTERFACE_STATE_DELAY;
            app_interfaceData.delayMs = 100;
            break;
        }

        case APP_INTERFACE_STATE_DELAY:
        {
            // Wait delay time
            if (APP_INTERFACE_TaskDelay(app_interfaceData.delayMs, &app_interfaceData.timer))
            {
                // Check low power state
                if (app_interfaceData.nextState == APP_INTERFACE_STATE_SW_RESET)
                {
                    // Perform Reset
                    SYS_CONSOLE_Print(SYS_CONSOLE_INDEX_0, "Performing Reset\r\n");
                    //APP_INTERFACE_Reset();
                }
                else
                {
                    // Set next app state
                    app_interfaceData.state = app_interfaceData.nextState;
                }
            }
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

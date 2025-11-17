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
#include "app_cycles.h"
#include "app_interface.h"
#include "common\common.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
extern APP_CYCLES_DATA app_cyclesData;
extern uint8_t app_cyclesPayload[16];

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
static void _commandREGDEV (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandDBGLVL (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandRST (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandGetPIB (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandSetPIB (SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _commandHELP(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);

static const SYS_CMD_DESCRIPTOR appCmdTbl[]=
{
    {"SET_LIGHT", _commandSETLIGHT, ": SET_LIGHT <XXXX(dest)> [0|1] (0:off, 1:on)"},
    {"SET_PANEL_INFO", _commandSETPANELINFO, ": SET_PANEL_INFO <X(dest)> [0|1] (0:Logo, 1:Alarm)"},
    {"SET_RGB", _commandSETRGB, ": SET_RGB <X(dest)> <X(H)> <X(S)> <X(V)>"},
    {"SET_RGBB", _commandSETRGBBLINK, ": SET_RGBB <X(dest)> <X(H)> <X(S)> <X(V)> <X(freq)> <X(time)>"},
    {"PING", _commandPINGTYPE, ": Ping Device Type Index <X(dest)>"},
    {"REGDEV", _commandREGDEV, ": Registered Devices"},
    {"DBGLVL", _commandDBGLVL, ": Debug Level (0-4)"},
    {"RST", _commandRST, ": Reset"},
    {"GET_PIB", _commandGetPIB, ": GET_PIB <LVL(0-3)> <PIB(hex)> <INDEX>"},
    {"SET_PIB", _commandSetPIB, ": SET_PIB <LVL(0-3)> <PIB(hex)> <INDEX> <LEN> <VALUE>"},
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

static bool APP_INTERFACE_Reset()
{
    CFG_REGS->CFG_SYSKEY = 0x00000000U;
    CFG_REGS->CFG_SYSKEY = 0xAA996655U;
    CFG_REGS->CFG_SYSKEY = 0x556699AAU;    
    // 2. Set the SWRST bit (RSWRST[0]) = 1.
    RCON_REGS->RCON_RSWRST |= RCON_RSWRST_SWRST_SWRST;
    // 3. Read the RSWRST register;
    uint8_t rswrst = RCON_REGS->RCON_RSWRST;
    // Setting the SWRST bit (RSWRST[0]) will arm the software Reset. 
    // The subsequent read of the RSWRST register triggers the software Reset, 
    // which must occur on the next clock cycle following the read operation. 
    // To ensure no other user code is executed before the Reset event occurs, 
    // it is recommended that four NOP instructions or a while(1) statement 
    // be placed after the READ instruction.    
    while ( true );
}

bool _preprocessorCallback ( const SYS_CMD_DESCRIPTOR* pCmdTbl,
        SYS_CMD_DEVICE_NODE* pCmdIO, char* cmdBuff, size_t bufSize, void* hParam)
{
    char *pBuff = cmdBuff;
    char cmdChar;
    size_t idx;

    for(idx = 0; idx < bufSize; idx++, pBuff++)
    {
        cmdChar = *pBuff;
        if ((cmdChar >= 'a') && (cmdChar <= 'z'))
        {
            // Convert upper case
            *pBuff -= 32;
        }
        else if ((cmdChar == '\t') || (cmdChar == ',') || (cmdChar == ';') || (cmdChar == '[') ||
                (cmdChar == ']') || (cmdChar == '(') || (cmdChar == ')'))
        {
            // Replace command separator
            *pBuff = ' ';
        }
    }

    return false;
}

static inline void _removePrompt(void)
{
    SYS_CMD_MESSAGE("\b");
}

static void _commandPINGTYPE(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    
    APP_COORDINATOR_CMDS_QUEUE_DATA deviceCmd;
    
    if (app_interfaceData.deviceCmdFlag)
    {
        SYS_CMD_MESSAGE("Another Ping is already running\r\n");
    }
    else
    {
        if (argc == 2)
        {
            uint8_t index, type;
            index = atoi(argv[1]);               
            type = APP_COORDINATOR_deviceTypeByIndex(index);
            
            if ((type >= TYPE_LIGHTING_INDOOR) && (type <= TYPE_PANEL_LED))
            {                
                APP_COORDINATOR_deviceDoSnapshot(&device_info_interface);            
                uint16_t joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_interface, type);

                if (joined)
                {
                    //app_interfaceData.deviceCmdFlag = true;

                    //app_interfaceData.state = APP_INTERFACE_STATE_PING_DEVICE;
                    deviceCmd.index = index;
                    deviceCmd.data[0] = CMD_GET_DEVICE_INFO;
                    deviceCmd.length = 1;
                    deviceCmd.answer = true;      
                    APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                }
                else
                {
                    // Invalid password
                    SYS_CMD_MESSAGE("Device not joined\r\n");
                }
            }
            else
            {
                // Invalid password
                SYS_CMD_MESSAGE("Invalid type\r\n");
            }
        }
        else
        {
            // Incorrect parameter number
            SYS_CMD_MESSAGE("Incorrect param number\r\n");
        }
    }
}

static void _commandSETRGB(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{

    APP_COORDINATOR_CMDS_QUEUE_DATA deviceCmd;
    
    if (app_interfaceData.deviceCmdFlag)
    {
        SYS_CMD_MESSAGE("Another Ping is already running\r\n");
    }
    else
    {    
        if (argc == 5)
        {
            uint8_t index, type;
            uint16_t convertResult;

            index = atoi(argv[1]);
            
            if ((index >= 0) && (index < APP_COORDINATOR_MAX_DEVICES))
            {
                type = APP_COORDINATOR_deviceTypeByIndex(index);
            
                APP_COORDINATOR_deviceDoSnapshot(&device_info_interface);            
                uint16_t joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_interface, type);

                if (joined)
                {
                    //app_interfaceData.deviceCmdFlag = true;

                    //app_interfaceData.state = APP_INTERFACE_STATE_PING_DEVICE;
                    deviceCmd.index = index;
                    deviceCmd.data[0] = CMD_SET_LED_RGB;
                    convertResult |= COMMON_U8AsciiToHex(argv[2], &deviceCmd.data[1]); // H
                    convertResult |= COMMON_U8AsciiToHex(argv[3], &deviceCmd.data[2]); // S
                    convertResult |= COMMON_U8AsciiToHex(argv[4], &deviceCmd.data[3]); // V
                    if(convertResult == APP_RES_SUCCESS)
                    {   // only send when parameter were given correctly
                        deviceCmd.length = 4;
                        deviceCmd.answer = false; 
                        APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                    }
                    else
                    {
                        app_interfaceData.deviceCmdFlag = false;
                        SYS_CMD_MESSAGE("invalid characters\r\n");
                    }  
                }
                else
                {
                    // Invalid password
                    SYS_CMD_MESSAGE("Device not joined\r\n");
                }
            }
            else
            {
                // Invalid password
                SYS_CMD_MESSAGE("Invalid index\r\n");
            }
        }
        else
        {
            // Incorrect parameter number
            SYS_CMD_MESSAGE(" *** USAGE: SET_RGB <XXXX(dest)> <XX(H)> <XX(S)> <XX(V)> ***\r\n");
        }
    }
}

static void _commandSETRGBBLINK(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    APP_COORDINATOR_CMDS_QUEUE_DATA deviceCmd;
    
    if (app_interfaceData.deviceCmdFlag)
    {
        SYS_CMD_MESSAGE("Another Ping is already running\r\n");
    }
    else
    {    
        if (argc == 7)
        {
            uint8_t index, type;
            uint8_t eui64[8];
            uint16_t convertResult;
            
            index = atoi(argv[1]);    
            if ((index >= 0) && (index < APP_COORDINATOR_MAX_DEVICES))
            {
                type = APP_COORDINATOR_deviceTypeByIndex(index);

                APP_COORDINATOR_deviceDoSnapshot(&device_info_interface);            
                uint16_t joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_interface, type);

                if (joined)
                {
                    //app_interfaceData.deviceCmdFlag = true;

                    //app_interfaceData.state = APP_INTERFACE_STATE_PING_DEVICE;
                    deviceCmd.index = index;
                    deviceCmd.data[0] = CMD_SET_LED_RGB_BLINK;
                    convertResult |= COMMON_U8AsciiToHex(argv[2], &deviceCmd.data[1]); // H
                    convertResult |= COMMON_U8AsciiToHex(argv[3], &deviceCmd.data[2]); // S
                    convertResult |= COMMON_U8AsciiToHex(argv[4], &deviceCmd.data[3]); // V
                    convertResult |= COMMON_U16AsciiToHex(argv[5], (uint16_t *) &deviceCmd.data[4]); // Blinking frequency
                    convertResult |= COMMON_U16AsciiToHex(argv[6], (uint16_t *) &deviceCmd.data[6]); // Blinking time
                    if(convertResult == APP_RES_SUCCESS)
                    {   // only send when parameter were given correctly
                        deviceCmd.length = 8;
                        deviceCmd.answer = false; 
                        APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                    }
                    else
                    {
                        app_interfaceData.deviceCmdFlag = false;
                        SYS_CMD_MESSAGE("invalid characters\r\n");
                    }   
                }
                else
                {
                    // Invalid password
                    SYS_CMD_MESSAGE("Device not joined\r\n");
                }
            }
            else
            {
                // Invalid password
                SYS_CMD_MESSAGE("Invalid index\r\n");
            }
        }
        else
        {
            // Incorrect parameter number
            SYS_CMD_MESSAGE(" *** USAGE: SET_RGB_BLINK <XXXX(dest)> <XX(H)> <XX(S)> <XX(V)> <XXXX(freq)> <XXXX(time)> ***\r\n");
        }
    }
}

static void _commandSETLIGHT(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    uint16_t convertResult;
    APP_COORDINATOR_CMDS_QUEUE_DATA deviceCmd;

    if (app_interfaceData.deviceCmdFlag)
    {
        SYS_CMD_MESSAGE("Another Ping is already running\r\n");
    }
    else
    {    
        if (argc == 3)
        {
            uint8_t index, type;
            bool onoff;
            
            index = atoi(argv[1]);  
            onoff = (atoi(argv[2]) == 0)? false: true;
            type = APP_COORDINATOR_deviceTypeByIndex(index);
            if ((type == TYPE_LIGHTING_INDOOR) || (type == TYPE_LIGHTING_OUTDOOR))
            {
                APP_COORDINATOR_deviceDoSnapshot(&device_info_interface);            
                uint16_t joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_interface, type);
                if (joined)
                {
                    deviceCmd.index = index;
                    deviceCmd.data[0] = CMD_SET_LIGHT;
                    if (onoff == false)
                    {
                        deviceCmd.data[1] = 0x00; // off
                    }
                    else
                    {
                        deviceCmd.data[1] = 0x01; // on
                    }
                    deviceCmd.length = 2;
                    deviceCmd.answer = false; 
                    APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                    APP_COORDINATOR_deviceSetStateByType(type, onoff);
                }
                else
                {
                    // Invalid password
                    SYS_CMD_PRINT("Device Type 0x%02X not joined\r\n", type);
                }
            }
            else
            {
                // Invalid password
                SYS_CMD_PRINT("Invalid index %d\r\n", index);
            }
        }
        else
        {
            // Incorrect parameter number
            SYS_CMD_MESSAGE(" *** USAGE: SET_LIGHT <XXXX(dest)> [0|1] (0:off, 1:on) ***\r\n");
        }
    }
}

static void _commandSETPANELINFO(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    uint16_t convertResult;
    APP_COORDINATOR_CMDS_QUEUE_DATA deviceCmd;

    if (app_interfaceData.deviceCmdFlag)
    {
        SYS_CMD_MESSAGE("Another Ping is already running\r\n");
    }
    else
    {           
        if (argc == 3)
        {
            uint8_t index, type;
            bool onoff;
            
            index = atoi(argv[1]); 
            index = (TYPE_PANEL_LED - TYPE_LIGHTING_INDOOR);
            onoff = (atoi(argv[2]) == 0)? false: true;
            type = APP_COORDINATOR_deviceTypeByIndex(index);
            type = TYPE_PANEL_LED;
            if (type == TYPE_PANEL_LED)
            {
                APP_COORDINATOR_deviceDoSnapshot(&device_info_interface);            
                uint16_t joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_interface, type);
                
                if (joined)
                {
                    //app_interfaceData.deviceCmdFlag = true;

                    //app_interfaceData.state = APP_INTERFACE_STATE_PING_DEVICE;
                    deviceCmd.index = index;
                    deviceCmd.data[0] = CMD_SET_PANEL_LED;
                    if (onoff == false)
                    {
                        deviceCmd.data[1] = 0x00; // Microchip Logo
                    }
                    else
                    {
                        deviceCmd.data[1] = 0x01; // ALARM
                    }
                    deviceCmd.length = 2;
                    deviceCmd.answer = false; 
                    APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                    //APP_COORDINATOR_deviceSetStateByType(type, onoff);
                }
                else
                {
                    // Invalid password
                    SYS_CMD_PRINT("Device Type 0x%02X not joined\r\n", type);
                }
            }
            else
            {
                // Invalid password
                SYS_CMD_PRINT("Invalid index %d\r\n", index);
            }
        }
        else
        {
            // Incorrect parameter number
            SYS_CMD_MESSAGE(" *** USAGE: SET_PANEL_INFO <XXXX(dest)> [0|1] (0:LOGO, 1:ALARM) ***\r\n");
        }
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

static void _commandRST(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
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
        uint16_t numdevices = APP_EAP_SERVER_GetNumDevicesJoined();
        
        if (numdevices)
        {
            APP_COORDINATOR_deviceDoSnapshot(&device_info_interface);
            
            app_interfaceData.state = APP_INTERFACE_STATE_PRINT_REG_DEVICES;
            app_interfaceData.cmdNumToShowHelp = APP_COORDINATOR_MAX_DEVICES;
            // Remove Prompt symbol
            _removePrompt();
            SYS_CMD_MESSAGE("Index   SA    Type  Alive State\r\n");
            SYS_CMD_MESSAGE("----- ------ ------ ----- -----\r\n");
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

static void _commandGetPIB(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    if (argc == 4)
    {
        // Check password from parameters
        uint32_t level = atoi(argv[1]);               
        if ((level >= 0) && (level <= 3))
        {            
            SYS_CMD_PRINT("Getting PIB of %d level\r\n",level);
        }
        else
        {
            // Invalid password
            SYS_CMD_MESSAGE("Invalid level, 0:PHY 1:MAC 2:ADP 3:LBP\r\n");
        }
        
        uint32_t pib;
        uint16_t convertResult=COMMON_U32AsciiToHex(argv[2], &pib);
        
        ADP_GET_CFM_PARAMS getConfirm;
        
        if (convertResult == APP_RES_SUCCESS)
        {
            uint16_t index = (uint16_t) atoi(argv[3]);            
            SYS_CMD_PRINT("Getting PIB 0x%08X - level %d - index %d\r\n", pib, level, index);
            
            switch (level)
            {
                case 0: // PHY
                    ADP_MacGetRequestSync(MAC_WRP_PIB_MANUF_PHY_PARAM, pib, &getConfirm);
                    if (getConfirm.status == G3_SUCCESS)
                    {                                        
                        SYS_CMD_MESSAGE("Value: 0x");
                        for (int i=0; i<getConfirm.attributeLength; i++)
                            SYS_CMD_PRINT("%02X", getConfirm.attributeValue[i]);
                        SYS_CMD_MESSAGE("\r\n");
                    }
                    break;
                case 1:
                    ADP_MacGetRequestSync(pib, index, &getConfirm);
                    if (getConfirm.status == G3_SUCCESS)
                    {                                        
                        SYS_CMD_MESSAGE("Value: 0x");
                        for (int i=0; i<getConfirm.attributeLength; i++)
                            SYS_CMD_PRINT("%02X", getConfirm.attributeValue[i]);
                        SYS_CMD_MESSAGE("\r\n");
                    }
                    break;
                case 2:                                        
                    ADP_GetRequestSync(pib, index, &getConfirm);
                    if (getConfirm.status == G3_SUCCESS)
                    {                                        
                        SYS_CMD_MESSAGE("Value: 0x");
                        for (int i=0; i<getConfirm.attributeLength; i++)
                            SYS_CMD_PRINT("%02X", getConfirm.attributeValue[i]);
                        SYS_CMD_MESSAGE("\r\n");
                    }
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE("Incorrect param number -> GET_PIB <LVL(0-3)> <PIB(hex)> <INDEX>\r\n");
    }
}

static void _commandSetPIB(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    uint32_t level;
    uint32_t pib;
    uint16_t index;
    uint16_t length;
    uint8_t values[64];
    uint16_t convertResult;
    ADP_SET_CFM_PARAMS setConfirm;

    if (argc == 6)
    {
        level = atoi(argv[1]);               
        if ((level >= 0) && (level <= 3))
        {            
            SYS_CMD_PRINT("Setting PIB of %d level\r\n",level);
        }
        else
        {
            // Invalid password
            SYS_CMD_MESSAGE("Invalid level, 0:PHY 1:MAC 2:ADP 3:LBP\r\n");
        }        
        convertResult = COMMON_U32AsciiToHex(argv[2], &pib);
        
        if (convertResult == APP_RES_SUCCESS)
        {
            index = (uint16_t) atoi(argv[3]);            
            length = atoi(argv[4]);                      
            SYS_CMD_PRINT("Setting PIB 0x%08X - level %d - index %d - len %d\r\n", pib, level, index, length);
            convertResult = COMMON_StringToHex(argv[5], values, length);
            if (convertResult == APP_RES_SUCCESS)
            {
                switch (level)
                {
                    case 0: // PHY
                        ADP_MacSetRequestSync(MAC_WRP_PIB_MANUF_PHY_PARAM, pib, length, values, &setConfirm);
                        if (setConfirm.status == G3_SUCCESS)
                        {                                        
                            SYS_CMD_MESSAGE("OK\r\n");
                        }
                        break;
                    case 1:
                        ADP_MacSetRequestSync(pib, index, length, values, &setConfirm);
                        if (setConfirm.status == G3_SUCCESS)
                        {                                        
                            SYS_CMD_MESSAGE("OK\r\n");
                        }
                        break;
                    case 2:                                        
                        ADP_SetRequestSync(pib, index, length, values, &setConfirm);
                        if (setConfirm.status == G3_SUCCESS)
                        {                                        
                            SYS_CMD_MESSAGE("OK\r\n");
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        // Incorrect parameter number
        SYS_CMD_MESSAGE("Incorrect param number -> SET_PIB <LVL(0-3)> <PIB(hex)> <INDEX> <LEN> <VALUE>\r\n");
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
    /* Allow RTS pin */
    RTS_Clear();
    
    /* Place the App state machine in its initial state. */
    app_interfaceData.state = APP_INTERFACE_STATE_INIT;
    app_interfaceData.deviceCmdFlag = false;
    app_interfaceData.numCommands = sizeof(appCmdTbl)/sizeof(SYS_CMD_DESCRIPTOR);

    /* Init timer */
    app_interfaceData.timer = SYS_TIME_HANDLE_INVALID;

    if (!SYS_CMD_ADDGRP(appCmdTbl, app_interfaceData.numCommands, "HELP", ": Hybrid IoT Coordinator console commands"))
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
                    SYS_CMD_PRINT("0x%02X  0x%04X 0x%04X 0x%04X %d\r\n",app_interfaceData.cmdNumToShowHelp - idx, device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].sa, device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].type, (device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].alive << 1) + device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].joined , device_info_interface[app_interfaceData.cmdNumToShowHelp - idx].state);
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
                    APP_INTERFACE_Reset();
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

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
#include <string.h>

#include "app_interface.h"
#include "app.h"
#include "app_cycles.h"
#include "common/common.h"
//#include "app_p2p_phy/app_phy_cmd_processor/inc/app_phy_cmd_processor.h"
//#include "app_gateway/ble/ble.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */
/**
 * @brief Command Callback Function
 * This function will be called before the command is processed.  
 * 
 * @param pCmdTbl pointer to a command group that has been added with SYS_CMD_ADDGRP
 * @param pCmdIO pointer to a SYS_CMD_DEVICE_NODE identifying the command channel that has been added with SYS_CMDIO_ADD
 * @param cmdBuff the buffer containing the current command to be processed. This buffer can be examined or modified as needed.
 * @param bufSize the size of the cmdBuff, including the termination '\0' character.
 * @param hParam a user parameter that's passed to the SYS_CMD_CallbackRegister() to be used in the callback.
 * @return true if the command has been completely processed by the external handler. The internal SYS_CM handler will then ignore the command.
 * @return false the string in the cmdBuff needs to be parsed ad processed as usually.
 */
static bool _INTERFACE_CommandCallback(
        const SYS_CMD_DESCRIPTOR* pCmdTbl,
        SYS_CMD_DEVICE_NODE* pCmdIO,
        char* cmdBuff,
        size_t bufSize,
        void* hParam) {
    // TODO: Add Implementation
    return false;
}

static void _INTERFACE_ExitCommandMode(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    APP_Msg_T msg;
//    msg.msgId = APP_MSG_CMD_INTERFACE_EXIT_COMMAND_MODE;
//    OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
}

static void _INTERFACE_QueryFirmwareVersion(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    uint8_t strVersion[128];
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    memset(strVersion, 0, sizeof(strVersion));
    sprintf((char*)strVersion, "+V:%s" LINE_TERM, APP_VERSION);
    (*pCmdIO->pCmdApi->msg)(cmdIoParam, strVersion);
}
// <editor-fold defaultstate="collapsed" desc="NOT Implemented at the moment">
#if false /* NOT Implemented at the moment */
static void _INTERFACE_FactoryReset(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    /*
     * Factory Reset (SF<1,2>)
     * Format: SF,<1,2>
     * This command resets the configurations into the default factory settings.
     * - Parameter is set to 1 - This command does not delete the private service and characteristics.
     * - Parameter is set to 2 - Resets all the configurations into factory default including clearing the private service table.
     */
    if (argc == 2) {
        
        if ( ( atoi(argv[1]) == 1) || ( atoi(argv[1]) == 2) ) {
            APP_Msg_T msg;
            msg.msgId = APP_MSG_CMD_INTERFACE_FACTORY_RESET;
            OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
            return;
        }
    }
    SYS_CMD_PRINT("Err\r\n");   // Syntax error or invalid parameter
}
#endif
// </editor-fold>

static void _INTERFACE_Shutdown(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    APP_Msg_T msg;
    SYS_CONSOLE_PRINT("OK\r\n");
    while(SERCOM1_USART_TransmitComplete() == false) {}
//    msg.msgId = APP_MSG_CMD_INTERFACE_SHUTDOWN;
//    OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
}

static void _INTERFACE_Reboot(void)
{
    // Debug Command - Reset MCU BLE Application via Software Reset (SWR)
    // This device does not provide a specific RESET instruction; however, 
    // a hardware Reset can be performed in software (software Reset) by 
    // executing a software Reset command sequence. The software Reset acts 
    // like a MCLR Reset. The software Reset sequence requires the system 
    // unlock sequence to be executed before the SWRST bit (RSWRST[0]) can 
    // be written.
    // A software Reset is performed as follows:
    // 1. Write the system unlock sequence
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

static void _INTERFACE_Reset(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    /*
     * This command forces a complete device reboot (similar to a reboot or power
     * cycle. It has a mandatory parameter of 1. 
     */
    if (argc == 1) {
        _INTERFACE_Reboot();
        return;
    }
    SYS_CONSOLE_PRINT(" *** USAGE: RESET ***\r\n");
}

static void _INTERFACE_Add2BleSensorList(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    if (argc == 2) {
        APP_Msg_T msg;
        memset(msg.msgData, 0, sizeof(msg.msgData));
        uint8_t *p_data = msg.msgData;
        char* pTkn;
        char str[20];
        char *addr[6] = {0};
        uint8_t nAddr = 0;

        (void) strncpy(str, argv[1], 20);
        pTkn = strtok(str, ":");
        while(pTkn != NULL)
        {
            if(nAddr < (uint8_t)6)
            {
                addr[nAddr] = pTkn;
            }
            nAddr++;
            pTkn = strtok(NULL, ":");
        }
        for(int8_t i = 5; i >= 0; i--)
        {
            COMMON_U8AsciiToHex(addr[i], p_data++);
        }
//        msg.msgId = APP_MSG_CMD_ADD_2_BLE_SENSOR_LIST;
//        OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
        return;
    } else {
        SYS_CONSOLE_PRINT(" *** USAGE: (AT+AS=\"<hex8>:<hex8>:<hex8>:<hex8>:<hex8>:<hex8>\") ***\r\n");
    }
}

static void _INTERFACE_ClearBleSensorList(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    APP_Msg_T msg;
//    msg.msgId = APP_MSG_CMD_CLEAR_BLE_SENSOR_LIST;
//    OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
}

static void _INTERFACE_ReadBleSensorList(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    APP_Msg_T msg;
//    msg.msgId = APP_MSG_CMD_READ_BLE_SENSOR_LIST;
//    OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
}
 
static void _INTERFACE_StartBleScanning(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    /*
     * Start BLE Scanning (F[,<hex16>,<hex16>]
     * Format: F[,<hex16>,<hex16>]
     * Use command F to automatically switch the device into central GAP role
     * and start BLE scanning.
     * If no parameter is provided, command f starts the process of scanning with
     * a default scan interval of 375 ms and a scan window of 250 ms. The command F
     * receives to optional parameters that determine the scan interval and the scan 
     * window The input parameters are 16-bit hex format. Each parameter (scan interval
     * and scan window) has a unit of 0.625 ms. The scan interval and the scan window
     * values can range from 2.5 ms to 40.959s.
     * Note: The scan interval must be larger than or equal to the scan window. 
     * Use the X command to stop an active scan.
     */
    if ( (argc >= 1) && (argc <=3) ) {
        
//        APP_Msg_T msg;
//        msg.msgId = APP_MSG_CMD_INTERFACE_START_BLE_SCANNING;
//        START_BLE_SCN_PARAMS_T *p_param = (START_BLE_SCN_PARAMS_T *)msg.msgData;
//        p_param->scan_interval = SCAN_INTERVAL_DEFAULT;
//        p_param->scan_window = SCAN_WINDOW_DEFAULT;
//        if (argc == 2) {
//            // p_param->scan_interval = atoi(argv[1]);
//            COMMON_U16AsciiToHex(argv[1],&p_param->scan_interval);
//        }
//        if (argc == 3) {
//            // p_param->scan_interval = atoi(argv[1]);
//            COMMON_U16AsciiToHex(argv[1],&p_param->scan_interval);
//            // p_param->scan_window = atoi(argv[2]);
//            COMMON_U16AsciiToHex(argv[2],&p_param->scan_window);
//        }
//        OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
        return;
    }
    SYS_CONSOLE_PRINT(" *** USAGE: AT+F[=\"<hex16>\",\"<hex16>\"] ***\r\n");
}

static void _INTERFACE_StartExtendedBleScanning(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    /*
     * Start Extended BLE Scanning (FE,<hex16>...)
     * Format: FE,<hex16>,<hex16>,<hex8>,<hex8>[,<Device Name Filter Data>,<Service Filter Data>,<Manufacturer Specific Filter Data>]
     * Command FE performs extended Bluetooth Low Energy scanning to be used on the advertising
     * physical channels. The command receives seven input parameters.
     * The parameters supported by FE commands are:
     *  - 16-bit hex value of scan interval
     *  - 16- bit hex value of scan window
     *  - 8-bit value of scanning PHYS
     *  - 8-bit value of filter option
     * Note: Based on the filter option selection, the user must pass an additional parameter value.
     * These parameters are described in the following list:
     *  - Scan interval <hex16> ? Time interval from when the controller started its last scan until it begins
     *    the subsequent scan on the primary advertising physical channel. The unit is 0.625 ms, and the
     *    range is from 2.5 ms to 40.959s.
     *  - Scan window <hex16> ? Duration of the scan on the primary advertising physical channel. The
     *    unit is 0.625 ms, and the range is from 2.5 ms to 40.959s.
     */
    if (argc >= 5) {
//        APP_Msg_T msg;
//        msg.msgId = APP_MSG_CMD_INTERFACE_START_EXTENDED_BLE_SCANNING;
//        START_EXT_BLE_SCN_PARAMS_T *p_params = (START_EXT_BLE_SCN_PARAMS_T *) msg.msgData;
//        
//        const START_EXT_BLE_SCN_PARAMS_T initial_ext_ble_scn_params ={
//            .scan_interval = SCAN_INTERVAL_DEFAULT,
//            .scan_window = SCAN_WINDOW_DEFAULT,
//            .scanning_phys = 0,
//            .filter_option = 0,
//            .name_filter = {
//                .nameLen = 0,
//                .targetName = {0}
//            },
//            .service_data_filter = {
//                .uuidLen = 0,
//                .uuidData = {0},
//                .svcDataLen = 0,
//                .svcData = {0}
//            },
//            .msd_filter = {
//                .companyId = {0},
//                .msdLen = 0,
//                .msd = {0}
//            }
//        };
//        memcpy(p_params, &initial_ext_ble_scn_params, sizeof(initial_ext_ble_scn_params));
//        // p_params->scan_interval = atoi(argv[1]);
//        COMMON_U16AsciiToHex(argv[1],&p_params->scan_interval);
//        // p_params->scan_window = atoi(argv[2]);
//        COMMON_U16AsciiToHex(argv[2],&p_params->scan_window);
//        // p_params->scanning_phys = atoi(argv[3]);
//        COMMON_U8AsciiToHex(argv[3],&p_params->scanning_phys);
//        // p_params->filter_option = atoi(argv[4]);
//        COMMON_U8AsciiToHex(argv[4],&p_params->filter_option);
//        if (argc == 6) {
//            uint8_t *p_data = (uint8_t *)argv[5];
//            if (p_params->filter_option & (1<<0)) {
//                /* Enable device name filter
//                 * Device name filter data - A string representing the device name 
//                 * content, where the first byte indicates the length of the device
//                 * name. The maximum length allowed is 16 bytes
//                 */
//                COMMON_U8AsciiToHex(p_data, &p_params->name_filter.nameLen);
//                p_data += 2;
//                for (int i=0; i< p_params->name_filter.nameLen; i++) {
//                    COMMON_U8AsciiToHex(p_data, &p_params->name_filter.targetName[i]);
//                    p_data += 2;
//                }
//                
//                // memcpy(&p_params->name_filter, p_data, strlen(p_data));
//            }
//            else if (p_params->filter_option & (1<<1)) {
//                /* Enable service data filter
//                 * Service filter data - The service filter data consists of four elements
//                 *  - UUID length (1 byte)
//                 *  - UUID data (16 bytes)
//                 *  - Service data length (1 byte)
//                 *  - Service data (16 bytes)
//                 */
//                uint8_t index = 0;
//                // p_params->service_filter_data.uuid_length = p_data[index++];
//                COMMON_U8AsciiToHex(p_data, &p_params->service_data_filter.uuidLen);
//                p_data += 2;
//
//                for (int i=0; i < p_params->service_data_filter.uuidLen; i++) {
//                    // p_params->service_filter_data.uuid_data[i] = p_data[index++];
//                    COMMON_U8AsciiToHex(p_data, &p_params->service_data_filter.uuidData[i]);
//                    p_data += 2;
//                }
//
//                // p_params->service_filter_data.service_data_length = p_data[index++];
//                COMMON_U8AsciiToHex(p_data, &p_params->service_data_filter.svcDataLen);
//                p_data += 2;
//                
//                for (int i=0; i < p_params->service_data_filter.svcDataLen; i++) {
//                    // p_params->service_filter_data.service_data[i] = p_data[index++];
//                    COMMON_U8AsciiToHex(p_data, &p_params->service_data_filter.svcData[i]);
//                    p_data += 2;
//                }
//            }
//            else if (p_params->filter_option & (1<<2)) {
//                /* Enable manufacturer specific data filter
//                 * Manufacturer specific filter data - The Manufacturer filter data consists
//                 * of three elements
//                 *  - company id(2 bytes) 
//                 *  - manufacturer data length (1 byte)
//                 *  - manufacturer data (16 bytes)
//                 */
//                uint8_t index = 0;
//                // p_params->manufacturer_specific_filter_data.company_id[0] = p_data[index++];
//                // p_params->manufacturer_specific_filter_data.company_id[1] = p_data[index++];
//                COMMON_StringToHex(p_data, p_params->msd_filter.companyId, 2);
//                p_data += 4;
//                // p_params->manufacturer_specific_filter_data.manufacturer_data_length = p_data[index++];
//                COMMON_U8AsciiToHex(p_data, &p_params->msd_filter.msdLen);
//                p_data += 2;
//                for ( int i=0; i< p_params->msd_filter.msdLen; i++) {
//                    // p_params->manufacturer_specific_filter_data.manufacturer_data[i] = p_data[index++];
//                    COMMON_U8AsciiToHex(p_data, &p_params->msd_filter.msd[i]);
//                    p_data += 2;
//                }
//            }
//        }
//        OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
        return;
    }
    SYS_CONSOLE_PRINT(" *** USAGE: AT+FE=\"<hex16>\",\"<hex16>\",\"<hex8>\",\"<hex8>\"[,\"<Device Name Filter Data>\",\"<Service Filter Data>\",\"<Manufacturer Specific Filter Data>\"] ***\r\n");
}

static void _INTERFACE_StopBleScanning(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    APP_Msg_T msg;
//    msg.msgId = APP_MSG_CMD_INTERFACE_STOP_BLE_SCANNING;
//    OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
}

// <editor-fold defaultstate="collapsed" desc="NOT Implemented at the moment">
#if false /* NOT Implemented at the moment */
static void _INTERFACE_LowPowerControl(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv) {
    APP_Msg_T msg;
    msg.msgId = APP_MSG_CMD_INTERFACE_LOW_POWER_CONTROL;
    OSAL_QUEUE_Send(&appData.appQueue, &msg, 0);
    SYS_CMD_PRINT("Low Power Control -> TODO: Add Implementation\r\n");
    // TODO: Add Implementation
}
#endif
// </editor-fold>

static void _INTERFACE_GetDeviceList(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv)
{
    uint16_t shortAddress;
    uint8_t eui64[8];

    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "List of connected devices\r\n");
    if(app_cyclesData.numDevicesJoined)
    {
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "index\t\tshortAddr\tdevType\ttimeout\r\n");
        for(uint16_t i = 0; i < app_cyclesData.numDevicesJoined; i++)
        {
            shortAddress = APP_EAP_SERVER_GetDeviceAddress(i, eui64);
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "0x%04X\t\t0x%04X\t\t0x%02X\t0x%02X\r\n", i, shortAddress, app_cyclesData.deviceType[i], app_cyclesData.deviceTimeout[i]);
        }
    }
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "--- empty ---\r\n");
    }
}

static void _INTERFACE_GetCycleState(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv)
{
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "app_cyclesData.state: 0x%02X\r\n", app_cyclesData.state);
}

static void _INTERFACE_GetDeviceInfo(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv)
{
    uint16_t convertResult;
    
    if (argc == 2)
    {
        convertResult = COMMON_U16AsciiToHex(argv[1], &app_cyclesData.deviceIndex); // destination
        
        if(convertResult == APP_RES_SUCCESS)
        {   // only send when parameter were given correctly
            //app_cyclesData.state = APP_CYCLES_STATE_READ_DEV_TYPE; // GET_DEVICE_INFO
            app_cyclesData.readDevTypeRequest = true;
        }
        else
        {
            SYS_CONSOLE_PRINT("Invalid characters\r\n", app_cyclesData.deviceIndex);
        }
    }
    else
    {
        SYS_CONSOLE_PRINT(" *** USAGE: GET_DEVICE_INFO <XXXX(dest)> ***\r\n");
    }
}

static void _INTERFACE_SetRgbLed(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv)
{
    uint16_t convertResult;
    
    if (argc == 5)
    {
        convertResult = COMMON_U16AsciiToHex(argv[1], &app_cyclesData.deviceIndex); // destination
        app_cyclesData.txData[0] = 0xF6; // SET_RGB_LED
        convertResult |= COMMON_U8AsciiToHex(argv[2], &app_cyclesData.txData[1]);  // H value
        convertResult |= COMMON_U8AsciiToHex(argv[3], &app_cyclesData.txData[2]);  // S value
        convertResult |= COMMON_U8AsciiToHex(argv[4], &app_cyclesData.txData[3]);  // V value
        
        if(convertResult == APP_RES_SUCCESS)
        {   // only send when parameter were given correctly
            app_cyclesData.txLength = 4;
        }
        else
        {
            SYS_CONSOLE_PRINT("invalid characters\r\n", app_cyclesData.deviceIndex);
        }
    }
    else
    {
        SYS_CONSOLE_PRINT(" *** USAGE: SET_RGB <XXXX(dest)> <XX(H)> <XX(S)> <XX(V)> ***\r\n");
    }
}

static void _INTERFACE_SetRgbLedBlink(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv)
{
    uint16_t convertResult;
    
    if (argc == 7)
    {
        convertResult = COMMON_U16AsciiToHex(argv[1], &app_cyclesData.deviceIndex); // destination
        app_cyclesData.txData[0] = 0xF8; // SET_RGB_LED_BLINK
        convertResult |= COMMON_U8AsciiToHex(argv[2], &app_cyclesData.txData[1]);  // H value
        convertResult |= COMMON_U8AsciiToHex(argv[3], &app_cyclesData.txData[2]);  // S value
        convertResult |= COMMON_U8AsciiToHex(argv[4], &app_cyclesData.txData[3]);  // V value
        convertResult |= COMMON_U16AsciiToHex(argv[5], (uint16_t *)&app_cyclesData.txData[4]);  // blinking frequency
        convertResult |= COMMON_U16AsciiToHex(argv[6], (uint16_t *)&app_cyclesData.txData[6]);  // blinking time
        
        if(convertResult == APP_RES_SUCCESS)
        {   // only send when parameter were given correctly
            app_cyclesData.txLength = 8;
        }
        else
        {
            SYS_CONSOLE_PRINT("invalid characters\r\n", app_cyclesData.deviceIndex);
        }
    }
    else
    {
        SYS_CONSOLE_PRINT(" *** USAGE: SET_RGB_BLINK <XXXX(dest)> <XX(H)> <XX(S)> <XX(V)> <XXXX(freq)> <XXXX(time)> ***\r\n");
    }
}

static void _INTERFACE_SetLight(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char **argv)
{
    uint16_t convertResult;
    
    if (argc == 3)
    {
        convertResult = COMMON_U16AsciiToHex(argv[1], &app_cyclesData.deviceIndex); // destination
        app_cyclesData.txData[0] = 0xFE; // SET_LIGHT
        if(atoi(argv[2]) == 0)
        {
            app_cyclesData.txData[1] = 0x00; // off
        }
        else
        {
            app_cyclesData.txData[1] = 0x01; // on
        }
        if(convertResult == APP_RES_SUCCESS)
        {   // only send when parameter were given correctly
            app_cyclesData.txLength = 2;
        }
        else
        {
            SYS_CONSOLE_PRINT("invalid characters\r\n", app_cyclesData.deviceIndex);
        }
    }
    else
    {
        SYS_CONSOLE_PRINT(" *** USAGE: SET_LIGHT <XXXX(dest)> <X(on/off)> ***\r\n");
    }
}

static const SYS_CMD_DESCRIPTOR interface_mode_table[]=
{
    // System Configuration Commands
//    {"---", _INTERFACE_ExitCommandMode, ": Exit Command Mode (---)"},
//
//    {"AT+V", _INTERFACE_QueryFirmwareVersion, ": Query Firmware Version (AT+V)"},
//// <editor-fold defaultstate="collapsed" desc="NOT Implemented at the moment">
//#if false /* NOT Implemented at the moment */
//    {"SF", _INTERFACE_FactoryReset, ": Factory Reset (SF<1,2>)"},
//#endif
//// </editor-fold>
//    {"AT+O", _INTERFACE_Shutdown, "; Shutdown (+O)"},
//    {"AT+R", _INTERFACE_Reboot, ": Reboot (+R)"},
//    {"AT+AS", _INTERFACE_Add2BleSensorList, ": Add to BLE Sensor List (+AS)"},
//    {"AT+CS", _INTERFACE_ClearBleSensorList, ": Clear BLE Sensor List (+CS)"},
//    {"AT+RS", _INTERFACE_ReadBleSensorList, ": Read BLE Sensor List (+RS)"},
//    // GAP Commands
//    //      Scan
//    {"AT+F", _INTERFACE_StartBleScanning, ": Start BLE Scanning (+F)"},
//    {"AT+FE", _INTERFACE_StartExtendedBleScanning, ": Start Extended BLE Scanning (+FE)"},
//    {"AT+X", _INTERFACE_StopBleScanning, ": Stop BLE Scanning (+X)"},
//    // <editor-fold defaultstate="collapsed" desc="NOT Implemented at the moment">
//#if false /* NOT Implemented at the moment */
//    {"AT+SO", _INTERFACE_LowPowerControl, ": Low Power Control (+SO)" },
//#endif    
//    // </editor-fold>
//    // PHY Commands
//    {"+++", data_mode, ": Enter PHY User Input data mode (+++)"}, 
//    {"&&&", exit_data_mode, ": Exit PHY User Input data mode (&&&)"},
//    {"AT+RE", phy_rxenable, ": RX enable (+RE)"},
//    {"AT+SP", phy_pibsetPanId, ": Set PHY PAN ID (+SP)"},
//    {"AT+GP", phy_pibgetPanId, ": Get PHY PAN ID (+GP)"},
//    {"AT+SC", phy_pibsetChannel, ": Set PHY channel (+SC)"},
//    {"AT+GC", phy_pibgetChannel, ": Get PHY channel (+GC)"},
//    {"AT+ST", phy_pibsetTxPwr, ": Set PHY TX power (+ST)"},
//    {"AT+GT", phy_pibgetTxPwr, ": Get PHY TX power (+GT)"},
//    {"AT+TX", phy_txdata, ": TX data (+TX)"},
//    {"AT+SD", phy_pibsetDestAddr, ": Set PHY Destination Address (+SD)"},
//    {"AT+GD", phy_pibgetDestAddr, ": Get PHY Destination Address (+GD)"},
//    {"AT+SS", phy_pibsetSrcAddr, ": Set PHY Source Address (+SS)"},
//    {"AT+GS", phy_pibgetSrcAddr, ": Get PHY Source Address (+GS)"},
//    {"AT+GR", phy_getRssi, ": Get PHY RSSI Value (+GR)"},

    {"GET_DEV_LIST",    _INTERFACE_GetDeviceList, ": Get device list"},
    {"GET_CYC_STATE",   _INTERFACE_GetCycleState, ": Get cycle state"},
    {"RESET",           _INTERFACE_Reset, ": Reset (RESET)"},

    {"GET_DEVICE_INFO", _INTERFACE_GetDeviceInfo, ": Get Device Info (GET_DEVICE_INFO)"},
    {"SET_RGB",         _INTERFACE_SetRgbLed, ": Set RGB LED (SET_RGB)"},
    {"SET_RGB_BLINK",   _INTERFACE_SetRgbLedBlink, ": Set RGB LED blinking (SET_RGB_BLINK)"},
    {"SET_LIGHT",       _INTERFACE_SetLight, ": Set light on/off (SET_LIGHT)"},
};
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
void INTERFACE_Initialize(void) {
    if (!SYS_CMD_ADDGRP(
            interface_mode_table, 
            sizeof(interface_mode_table)/sizeof(*interface_mode_table),
            "HybridIoT", 
            ": Hybrid IoT G3 Coordinator Gateway Commands")
            )
    {
        //APP_GATEWAY_ErrorHandler(APP_GATEWAY_INTERFACE_COMMAND_TABLE_INIT_FAILED);
        SYS_CONSOLE_PRINT("app_interface command table init failed!\r\n");
    }
    
    SYS_CMD_HANDLE handle = SYS_CMD_CallbackRegister(interface_mode_table, _INTERFACE_CommandCallback, 0);
    if (handle == NULL) {
        //APP_GATEWAY_ErrorHandler(APP_GATEWAY_INTERFACE_COMMAND_CALLBACK_REGISTER_FAILED);
        SYS_CONSOLE_PRINT("app_interface command callback register failed!\r\n");
    }
}

void INTERFACE_Tasks(void) {
}


/* *****************************************************************************
 End of File
 */

/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_cycles.c

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
#include "configuration.h"
#include "app_cycles.h"
#include "app_eap_server.h"
#include "app.h"

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
    This structure should be initialized by the APP_CYCLES_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_CYCLES_DATA app_cyclesData;


// *****************************************************************************
// *****************************************************************************
// Section: Function Declaration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

static void _APP_CYCLES_OpenSocket(void)
{
    IPV6_ADDR targetAddress;
    uint16_t shortAddress, panId;
    uint8_t eui64[8];
    char targetAddressString[50 + 1];

    /* Create link-local address based on short address and PAN ID */
    shortAddress = APP_EAP_SERVER_GetDeviceAddress(app_cyclesData.deviceIndex, eui64);
    panId = APP_G3_MANAGEMENT_GetPanId();
    TCPIP_Helper_StringToIPv6Address(APP_TCPIP_MANAGEMENT_IPV6_LINK_LOCAL_ADDRESS_G3, &targetAddress);
    targetAddress.v[8] = (uint8_t) (panId >> 8);
    targetAddress.v[9] = (uint8_t) panId;
    targetAddress.v[14] = (uint8_t) (shortAddress >> 8);
    targetAddress.v[15] = (uint8_t) shortAddress;
    TCPIP_Helper_IPv6AddressToString(&targetAddress, targetAddressString, sizeof(targetAddressString) - 1);

    /* Close socket if already opened */
    if(app_cyclesData.socket != INVALID_SOCKET)
    {
        //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "APP_CYCLES: close old socket with %d\r\n", app_cyclesData.deviceIndex);
        TCPIP_UDP_Close(app_cyclesData.socket);
    }

    /* Open UDP client socket */
    //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "APP_CYCLES: open socket with %d\r\n", app_cyclesData.deviceIndex);
    app_cyclesData.socket = TCPIP_UDP_ClientOpen(IP_ADDRESS_TYPE_IPV6,
            APP_CYCLES_SOCKET_PORT, (IP_MULTI_ADDRESS*) &targetAddress);
    if(app_cyclesData.socket == INVALID_UDP_SOCKET)
    {
        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "APP_CYCLES: open socket failed\r\n");
    }
}

static void _APP_CYCLES_CloseSocket(void)
{
    TCPIP_UDP_Discard(app_cyclesData.socket);
    TCPIP_UDP_Close(app_cyclesData.socket);
    app_cyclesData.socket = INVALID_SOCKET;
}

static void _APP_CYCLES_SendData(void)
{
    uint16_t availableTxBytes;

    if (app_cyclesData.availableBuffers == false)
    {
        /* Full buffers, wait for availability to send the packet */
        //SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: Full buffers, wait for availability to send the packet\r\n");
        app_cyclesData.packetPending = true;
        return;
    }

    app_cyclesData.packetPending = false;

    /* Get the number of bytes that can be written to the socket */
    availableTxBytes = TCPIP_UDP_PutIsReady(app_cyclesData.socket);
    if (availableTxBytes < app_cyclesData.txLength)
    {
        //SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: Not enough bytes available in UDP socket\r\n");
        return;
    }

    /* Put UPD data to socket*/
    TCPIP_UDP_ArrayPut(app_cyclesData.socket, app_cyclesData.txData, app_cyclesData.txLength);

    /* Send the UDP request */
    TCPIP_UDP_Flush(app_cyclesData.socket);
    app_cyclesData.txLength = 0;

    app_cyclesData.sendDelayExpired = false;
    app_cyclesData.sendHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
            (uintptr_t) &app_cyclesData.sendDelayExpired, APP_CYCLES_TIME_BTW_SENDING_MS, SYS_TIME_SINGLE);
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_CYCLES_Initialize ( void )

  Remarks:
    See prototype in app_cycles.h.
 */

void APP_CYCLES_Initialize ( void )
{
    /* Place the application's state machine in its initial state. */
    app_cyclesData.state = APP_CYCLES_STATE_WAIT_TCPIP_READY;

    /* Initialize application variables */
    app_cyclesData.socket = INVALID_SOCKET;
    app_cyclesData.cycleIndex = 0;
    app_cyclesData.numDevicesJoined = 0;
    app_cyclesData.timeExpired = false;
    app_cyclesData.availableBuffers = true;
    app_cyclesData.packetPending = false;
    app_cyclesData.sendDelayExpired = true;
}


/******************************************************************************
  Function:
    void APP_CYCLES_Tasks ( void )

  Remarks:
    See prototype in app_cycles.h.
 */

void APP_CYCLES_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( app_cyclesData.state )
    {
        /* Application's initial state. */
        case APP_CYCLES_STATE_WAIT_TCPIP_READY:
        {
            SYS_STATUS tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if (tcpipStat <= SYS_STATUS_ERROR)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: TCP/IP stack initialization failed!\r\n");
                app_cyclesData.state = APP_CYCLES_STATE_ERROR;
            }
            else if(tcpipStat == SYS_STATUS_READY)
            {
                /* TCP/IP stack ready */
                app_cyclesData.state = APP_CYCLES_STATE_WAIT_FIRST_JOIN;
            }

            break;
        }

        /* State to wait for the first device joined to the G3 network */
        case APP_CYCLES_STATE_WAIT_FIRST_JOIN:
        {
            /* Get number of joined devices */
            app_cyclesData.numDevicesJoined = APP_EAP_SERVER_GetNumDevicesJoined();

            if (app_cyclesData.numDevicesJoined > 0)
            {
                /* First device joined the G3 network. Start timer to wait
                 * before first cycle */
                app_cyclesData.state = APP_CYCLES_STATE_WAIT_FIRST_CYCLE;
                app_cyclesData.timeHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &app_cyclesData.timeExpired, APP_CYCLES_TIME_WAIT_CYCLE_MS,
                        SYS_TIME_SINGLE);
                app_cyclesData.state = APP_CYCLES_STATE_WAIT_FIRST_CYCLE;
            }

            break;
        }

        /* State to wait for first UDP cycle */
        case APP_CYCLES_STATE_WAIT_FIRST_CYCLE:
        {
            if (app_cyclesData.timeExpired == false)
            {
                /* Check number of joined devices */
                uint16_t numDevicesJoined = APP_EAP_SERVER_GetNumDevicesJoined();
                if (numDevicesJoined != app_cyclesData.numDevicesJoined)
                {
                    /* New device(s) joined or left the G3 network. Reload the
                     * timer to wait before first cycle */
                    SYS_TIME_TimerReload(app_cyclesData.timeHandle, 0, SYS_TIME_MSToCount(APP_CYCLES_TIME_WAIT_CYCLE_MS),
                            APP_SYS_TIME_CallbackSetFlag, (uintptr_t) &app_cyclesData.timeExpired, SYS_TIME_SINGLE);
                    app_cyclesData.numDevicesJoined = numDevicesJoined;
                }
            }
            else
            {
                SYS_TIME_TimerDestroy(app_cyclesData.timeHandle);
                app_cyclesData.deviceIndex = 0;
                app_cyclesData.state = APP_CYCLES_STATE_WAIT_FOR_TX_PREPARE;
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "APP_CYCLES: Ready\r\n");
            }

            break;
        }
        
        case APP_CYCLES_STATE_READ_DEV_TYPE:
        {
            if(app_cyclesData.sendDelayExpired)
            {
                _APP_CYCLES_OpenSocket();
                app_cyclesData.txData[0] = 0xF4; // GET_DEVICE_INFO
                app_cyclesData.txLength = 1;
                _APP_CYCLES_SendData();

                app_cyclesData.state = APP_CYCLES_STATE_READ_DEV_TYPE_ANSWER;
                app_cyclesData.timeExpired = false;
                app_cyclesData.timeHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &app_cyclesData.timeExpired, APP_CYCLES_TIMEOUT_MS, SYS_TIME_SINGLE);
            }
            break;
        }

        case APP_CYCLES_STATE_READ_DEV_TYPE_ANSWER:
        {
            uint16_t rxPayloadSize;
            uint8_t udpProtocol;

            if(app_cyclesData.timeExpired == true)
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_CYCLES: READ_DEV_TYPE_ANSWER timeout (deviceIndex: 0x%04X)\r\n", app_cyclesData.deviceIndex);
                if(app_cyclesData.deviceTimeout[app_cyclesData.deviceIndex] < 3)
                {
                    app_cyclesData.deviceTimeout[app_cyclesData.deviceIndex]++;
                }
                if(app_cyclesData.deviceTimeout[app_cyclesData.deviceIndex] >= 3)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_CYCLES: connection lost (deviceIndex: 0x%04X)\r\n", app_cyclesData.deviceIndex);
                    app_cyclesData.deviceType[app_cyclesData.deviceIndex] = 0x00; // invalid
                }
                SYS_TIME_TimerDestroy(app_cyclesData.timeHandle);

                if(app_cyclesData.readDevTypeRequest)
                {
                    app_cyclesData.readDevTypeRequest = false;
                    app_cyclesData.state = APP_CYCLES_STATE_WAIT_FOR_TX_PREPARE;
                }
                else
                {
                    app_cyclesData.aliveCheckIndex++;
                    app_cyclesData.state = APP_CYCLES_STATE_ALIVE_CHECK;
                }
                break;
            }
            else if(app_cyclesData.packetPending == true)
            {
                SYS_TIME_TimerReload(app_cyclesData.timeHandle, 0, SYS_TIME_MSToCount(APP_CYCLES_TIMEOUT_MS),
                        APP_SYS_TIME_CallbackSetFlag, (uintptr_t) &app_cyclesData.timeExpired, SYS_TIME_SINGLE);
                break;
            }

            /* Get number of bytes received */
            rxPayloadSize = TCPIP_UDP_GetIsReady(app_cyclesData.socket);
            if (rxPayloadSize == 0)
            {
                /* No data received */
                break;
            }

            /* Read first received byte (protocol) */
            TCPIP_UDP_Get(app_cyclesData.socket, &udpProtocol);

            if(udpProtocol == 0xF5) // GET_DEVICE_INFO_ANSWER
            {
                TCPIP_UDP_Get(app_cyclesData.socket, &app_cyclesData.deviceType[app_cyclesData.deviceIndex]);
                app_cyclesData.deviceTimeout[app_cyclesData.deviceIndex] = 0; // reset timeout counter
                //SYS_DEBUG_PRINT(SYS_ERROR_INFO, "Device type of 0x%04X: 0x%02X\r\n", app_cyclesData.deviceIndex, app_cyclesData.deviceType[app_cyclesData.deviceIndex]);
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_CYCLES: Wrong UDP reply received (0x%02X)\r\n", udpProtocol);
            }

            SYS_TIME_TimerDestroy(app_cyclesData.timeHandle);
            if(app_cyclesData.readDevTypeRequest)
            {
                app_cyclesData.readDevTypeRequest = false;
                app_cyclesData.state = APP_CYCLES_STATE_WAIT_FOR_TX_PREPARE;
            }
            else
            {
                app_cyclesData.aliveCheckIndex++;
                app_cyclesData.state = APP_CYCLES_STATE_ALIVE_CHECK;
            }
            break;
        }

        case APP_CYCLES_STATE_WAIT_FOR_TX_PREPARE:
        {
            app_cyclesData.timeExpired = false;
            app_cyclesData.timeHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                    (uintptr_t) &app_cyclesData.timeExpired, APP_CYCLES_ALIVE_CHECK_TIME_MS, SYS_TIME_SINGLE);
            app_cyclesData.state = APP_CYCLES_STATE_WAIT_FOR_TX;
            break;
        }

        case APP_CYCLES_STATE_WAIT_FOR_TX:
        {
            uint16_t numDevicesJoined = APP_EAP_SERVER_GetNumDevicesJoined();
            if(numDevicesJoined != app_cyclesData.numDevicesJoined)
            {
                app_cyclesData.numDevicesJoined = numDevicesJoined;
                for(uint16_t i = 0; i < app_cyclesData.numDevicesJoined; i++)
                {
                    // device list may have changed - reset device types and timeouts
                    app_cyclesData.deviceType[i] = 0;
                    app_cyclesData.deviceTimeout[i] = 0;
                }
            }

            if(app_cyclesData.readDevTypeRequest)
            {
                SYS_TIME_TimerDestroy(app_cyclesData.timeHandle);
                app_cyclesData.state = APP_CYCLES_STATE_READ_DEV_TYPE;
                break;
            }

            // UART request (from app_interface) received -> send data
            if(   (app_cyclesData.txLength != 0)
               && (app_cyclesData.sendDelayExpired))
            {
                /* Check for valid deviceIndex */
                if(app_cyclesData.deviceIndex >= app_cyclesData.numDevicesJoined)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "Invalid device index (0x%04X)\r\n", app_cyclesData.deviceIndex);
                    app_cyclesData.txLength = 0;
                    break;
                }
                
                _APP_CYCLES_OpenSocket();
                _APP_CYCLES_SendData();
            }
            else if(app_cyclesData.timeExpired == true)
            {
                SYS_TIME_TimerDestroy(app_cyclesData.timeHandle);
                app_cyclesData.aliveCheckIndex = 0;
                app_cyclesData.state = APP_CYCLES_STATE_ALIVE_CHECK;
            }

            break;
        }

        case APP_CYCLES_STATE_ALIVE_CHECK:
        {
            while(app_cyclesData.deviceTimeout[app_cyclesData.aliveCheckIndex] >= 3)
            {
                app_cyclesData.aliveCheckIndex++;
            }
            if(app_cyclesData.aliveCheckIndex < app_cyclesData.numDevicesJoined)
            {
                app_cyclesData.deviceIndex = app_cyclesData.aliveCheckIndex;
                app_cyclesData.state = APP_CYCLES_STATE_READ_DEV_TYPE;
            }
            else
            {
                //SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_CYCLES: alive check done\r\n");
                if(app_cyclesData.txLength)
                {
                    app_cyclesData.txLength = 0;
                    //SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_CYCLES: skipped TX request during alive check\r\n");
                }
                app_cyclesData.state = APP_CYCLES_STATE_WAIT_FOR_TX_PREPARE;
            }
            break;
        }

        /* Conformance state: Cycling disabled */
        case APP_CYCLES_STATE_CONFORMANCE:
        {
            /* Nothing to do */
            break;
        }

        /* Error state */
        case APP_CYCLES_STATE_ERROR:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            break;
        }
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Interface Functions
// *****************************************************************************
// *****************************************************************************

void APP_CYCLES_AdpBufferIndication(ADP_BUFFER_IND_PARAMS* bufferInd)
{
    //SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_CYCLES: buff large %d medium %d small %d\r\n",
    //        bufferInd->largeBuffersAvailable, bufferInd->mediumBuffersAvailable, bufferInd->smallBuffersAvailable);
    if ((bufferInd->largeBuffersAvailable == 1) && (bufferInd->mediumBuffersAvailable == 1) &&
            (bufferInd->smallBuffersAvailable == 1))
    {
        /* All buffers are available */
        app_cyclesData.availableBuffers = true;

        if (app_cyclesData.packetPending == true)
        {
            /* Send pending packet */
            //SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: send pending packet\r\n");
            _APP_CYCLES_SendData();
        }
    }
    else
    {
        /* At least one type of buffers are full */
        app_cyclesData.availableBuffers = false;
    }
}

void APP_CYCLES_SetConformanceConfig ( void )
{
    /* Disable cycling operation and close socket if already opened */
    app_cyclesData.state = APP_CYCLES_STATE_CONFORMANCE;
    if (app_cyclesData.socket != INVALID_SOCKET)
    {
        TCPIP_UDP_Close(app_cyclesData.socket);
    }
}

/*******************************************************************************
 End of File
 */

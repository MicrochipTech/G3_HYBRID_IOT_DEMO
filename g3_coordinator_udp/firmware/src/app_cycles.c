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

#ifndef APP_CYCLES_METROLOGY_DATA_REQUEST
uint8_t app_cyclesPayload[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, \
        0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
#endif

// Information about Device
APP_COORDINATOR_DEVICE_INFO CACHE_ALIGN appCoordinatorDeviceInfo[APP_COORDINATOR_MAX_DEVICES];

APP_COORDINATOR_CMDS_QUEUE CACHE_ALIGN appCoordCmdsQueue;

static bool isAppCoordCmdsQueueMutexCreated = false;
static OSAL_MUTEX_DECLARE(appCoordCmdsQueueMutex);

static bool isAppCoordInfoMutexCreated = false;
static OSAL_MUTEX_DECLARE(appCoordInfoMutex);

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

uint8_t APP_COORDINATOR_deviceByType(uint8_t type)
{
    return (uint8_t) (type - TYPE_LIGHTING_INDOOR);
}

uint8_t APP_COORDINATOR_deviceTypeByIndex(uint8_t index)
{
    return (uint8_t) (TYPE_LIGHTING_INDOOR + index);
}

bool _APP_COORDINATOR_deviceInit ( void )
{

    if (isAppCoordInfoMutexCreated == false)
    {
        if(OSAL_MUTEX_Create(&(appCoordInfoMutex)) != OSAL_RESULT_SUCCESS)
        {
            return SYS_MODULE_OBJ_INVALID;
        }
        else
        {
            isAppCoordInfoMutexCreated = true;
        }
    }
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    for (int i=0; i<APP_COORDINATOR_MAX_DEVICES; i++)
    {
        appCoordinatorDeviceInfo[i].eap_index = INDEX_UNKNOWN;
        appCoordinatorDeviceInfo[i].type = APP_COORDINATOR_deviceTypeByIndex(i);
        appCoordinatorDeviceInfo[i].sa = 0xFFFF;
        appCoordinatorDeviceInfo[i].joined = 0;
        appCoordinatorDeviceInfo[i].alive = false;
        appCoordinatorDeviceInfo[i].tries = APP_COORDINATOR_ALIVE_TRIES;
        appCoordinatorDeviceInfo[i].cycle = false;
        appCoordinatorDeviceInfo[i].state = false;
        appCoordinatorDeviceInfo[i].stats.numCycles = 0;
        appCoordinatorDeviceInfo[i].stats.numUdpReplies = 0;
        appCoordinatorDeviceInfo[i].stats.numUdpRequests = 0;
        appCoordinatorDeviceInfo[i].stats.timeCountTotal = 0;
    }
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
}

bool APP_COORDINATOR_deviceDoSnapshot(APP_COORDINATOR_DEVICE_INFO device_info[])
{
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    for (uint8_t i=0; i<APP_COORDINATOR_MAX_DEVICES; i++)
    {
        memcpy(&device_info[i], &appCoordinatorDeviceInfo[i], sizeof(APP_COORDINATOR_DEVICE_INFO));
    }
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceSetStateByType(uint8_t type, bool state )
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    bool joined = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].joined;
    bool alive = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].alive;
    
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].state = state;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    
    APP_USI_DEVICE_notifyDeviceStatusChange(type, joined, alive, state);
    
    return true;
}

bool APP_COORDINATOR_deviceGetStateByType(uint8_t type, bool *state)
{   
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    *state = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].state;
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceSetAliveByType(uint8_t type, bool joined, bool alive)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;

    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    bool state = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].state;
    
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].joined = joined;
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].alive = alive;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    
    APP_USI_DEVICE_notifyDeviceStatusChange(type, joined, alive, state);
    
    return true;
}

bool APP_COORDINATOR_deviceGetAliveByType(uint8_t type, bool *alive)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;

    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    *alive = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].alive;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceSetTriesByType(uint8_t type, uint8_t tries)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;

    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].tries = tries;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceGetTriesByType(uint8_t type, uint8_t *tries)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;

    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    *tries = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].tries;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceInfoRefresh(uint16_t eap_index, uint8_t *extAddr, uint16_t shortAddr, bool joined)
{
    uint8_t type = (uint8_t) shortAddr;
    bool state;
            
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;

    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].eap_index = eap_index;
    if (joined)
    {
        appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].sa = shortAddr;
        appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].joined = true;
    }
    else
    {
        appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].sa = 0xFFFF;
        appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].joined = false;
    }
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].alive = false;
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].tries = APP_COORDINATOR_ALIVE_TRIES;
    
    state = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].state;
    
    // Notify Device Status Change
    APP_USI_DEVICE_notifyDeviceStatusChange(type, joined, false, state);
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceGetAliveSnapshot ( APP_COORDINATOR_DEVICE_INFO *device_info_snapshot, uint8_t type )
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    return device_info_snapshot[type - TYPE_LIGHTING_INDOOR].alive;
}

bool APP_COORDINATOR_deviceGetJoinedSnapshot ( APP_COORDINATOR_DEVICE_INFO *device_info_snapshot, uint8_t type )
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    return device_info_snapshot[type - TYPE_LIGHTING_INDOOR].joined;
}

bool APP_COORDINATOR_deviceGetStateSnapshot  ( APP_COORDINATOR_DEVICE_INFO *device_info_snapshot, uint8_t type )
{
    uint8_t state;
    
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    return device_info_snapshot[type - TYPE_LIGHTING_INDOOR].state;
}

uint16_t APP_COORDINATOR_deviceGetShortAddressSnapshot ( APP_COORDINATOR_DEVICE_INFO *device_info_snapshot, uint8_t type )
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return INDEX_UNKNOWN;
    return device_info_snapshot[type - TYPE_LIGHTING_INDOOR].sa;
}

uint8_t APP_COORDINATOR_deviceRefreshCycle()
{
    uint8_t num_dev_cycling = 0;
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP COORDINATOR] - appCoordInfoMutex mutex lock FAILED\r\n");
        return 0;
    }
    
    for (int i=0; i<APP_COORDINATOR_MAX_DEVICES; i++)
    {
        if (appCoordinatorDeviceInfo[i].joined)
        {        
            appCoordinatorDeviceInfo[i].cycle = true;
            num_dev_cycling++;
        }
        else
        {    
            appCoordinatorDeviceInfo[i].cycle = false;
        }
    }
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    
    return num_dev_cycling;
}

static void _APP_COORDINATOR_InitCmdsQueue(void)
{
    
    if (isAppCoordCmdsQueueMutexCreated == false)
    {
        if(OSAL_MUTEX_Create(&(appCoordCmdsQueueMutex)) != OSAL_RESULT_SUCCESS)
        {
            return SYS_MODULE_OBJ_INVALID;
        }
        else
        {
            isAppCoordCmdsQueueMutexCreated = true;
        }
    }
    
    /* Clear DataLog Queue data */
    memset(&appCoordCmdsQueue, 0, sizeof(appCoordCmdsQueue));

    /* Init Queue pointers */
    appCoordCmdsQueue.dataRd = &appCoordCmdsQueue.data[0];
    appCoordCmdsQueue.dataWr = appCoordCmdsQueue.dataRd;
}

bool APP_COORDINATOR_CheckCoordCmdsQueue()
{    
    if (appCoordCmdsQueue.dataSize < APP_COORDINATOR_CMDS_QUEUE_DATA_SIZE)
    {     
        return true;
    }    
    return false;
}

bool APP_COORDINATOR_PushCoordCmdsQueue(APP_COORDINATOR_CMDS_QUEUE_DATA *cmdData)
{
    
    if(OSAL_MUTEX_Lock(&appCoordCmdsQueueMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        return false;
    }
    
    if (appCoordCmdsQueue.dataSize < APP_COORDINATOR_CMDS_QUEUE_DATA_SIZE)
    {
        /* Copy Energy data to the data queue */
        memcpy(appCoordCmdsQueue.dataWr, cmdData, sizeof(APP_COORDINATOR_CMDS_QUEUE_DATA));

        /* Update Queue as a circular buffer */
        appCoordCmdsQueue.dataSize++;
        if (appCoordCmdsQueue.dataWr == &appCoordCmdsQueue.data[APP_COORDINATOR_CMDS_QUEUE_DATA_SIZE - 1])
        {
            appCoordCmdsQueue.dataWr = &appCoordCmdsQueue.data[0];
        }
        else
        {
            appCoordCmdsQueue.dataWr++;
        }

        /* Release mutex */
        (void) OSAL_MUTEX_Unlock(&appCoordCmdsQueueMutex);
        
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_COORDINATOR: PushCmd - Queue Size=%d\r\n", appCoordCmdsQueue.dataSize);
        
        return true;
    }
    
    /* Release mutex */
    (void) OSAL_MUTEX_Unlock(&appCoordCmdsQueueMutex);
    
    return false;
}

static bool _APP_COORDINATOR_PopCoordCmdsQueue(APP_COORDINATOR_CMDS_QUEUE_DATA *cmdData)
{
    
    if(OSAL_MUTEX_Lock(&appCoordCmdsQueueMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        return false;
    }
    
    if (appCoordCmdsQueue.dataSize)
    {
        /* Copy data to the data pointer */
        memcpy(cmdData, appCoordCmdsQueue.dataRd, sizeof(APP_COORDINATOR_CMDS_QUEUE_DATA));

        /* Update Queue as a circular buffer */
        appCoordCmdsQueue.dataSize--;
        if (appCoordCmdsQueue.dataRd == &appCoordCmdsQueue.data[APP_COORDINATOR_CMDS_QUEUE_DATA_SIZE - 1])
        {
            appCoordCmdsQueue.dataRd = &appCoordCmdsQueue.data[0];
        }
        else
        {
            appCoordCmdsQueue.dataRd++;
        }

        /* Release mutex */
        (void) OSAL_MUTEX_Unlock(&appCoordCmdsQueueMutex);
        
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_COORDINATOR: PopCmd - Queue Size=%d\r\n", appCoordCmdsQueue.dataSize);
        
        return true;
    }
    
    /* Release mutex */
    (void) OSAL_MUTEX_Unlock(&appCoordCmdsQueueMutex);
        
    return false;
}

static void _APP_CYCLES_SendPacket(IPV6_ADDR *targetAddress, uint8_t *data, uint16_t len)
{
    /* Close socket if already opened */
    if (app_cyclesData.socket != INVALID_SOCKET)
    {
        TCPIP_UDP_Close(app_cyclesData.socket);
    }

    /* Open UDP client socket */
    app_cyclesData.socket = TCPIP_UDP_ClientOpen(IP_ADDRESS_TYPE_IPV6,
            APP_CYCLES_SOCKET_PORT, (IP_MULTI_ADDRESS*) targetAddress);


    /* Put the first byte: 0x01 (UDP request) */
    //TCPIP_UDP_Put(app_cyclesData.socket, 1);
    // The Command is embedded into the data buffer
    TCPIP_UDP_ArrayPut(app_cyclesData.socket, data, len);
    
#ifdef APP_CYCLES_METROLOGY_DATA_REQUEST
    /* Write the remaining UDP payload bytes. Implemented in a loop, processing
     * up to 16 bytes at a time. This limits memory usage while maximizing
     * performance. */
    chunkSize = 16;
    payloadSize = app_cyclesData.packetSize - 1;
    for (uint16_t written = 0; written < payloadSize; written += chunkSize)
    {
        if (written + chunkSize > payloadSize)
        {
            /* Treat the last chunk */
            chunkSize = payloadSize - written;
        }

        TCPIP_UDP_ArrayPut(app_cyclesData.socket, app_cyclesPayload, chunkSize);
    }
#endif
    
    /* Send the UDP request */
    app_cyclesData.timeCountUdpRequest = SYS_TIME_Counter64Get();
    TCPIP_UDP_Flush(app_cyclesData.socket);

#ifdef APP_CYCLES_METROLOGY_DATA_REQUEST
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_CYCLES: UDP packet size %hu\r\n", app_cyclesData.packetSize);
#endif

    /* Update statistics */
    app_cyclesData.numUdpRequests++;
    if (app_cyclesData.pStatsEntry != NULL)
        app_cyclesData.pStatsEntry->numUdpRequests++;
}

void _APP_CYCLES_UpdateDestinationAddress(uint16_t sa, uint16_t panId, IPV6_ADDR *targetAddress)
{
    TCPIP_Helper_StringToIPv6Address(APP_TCPIP_MANAGEMENT_IPV6_LINK_LOCAL_ADDRESS_G3, targetAddress);
    targetAddress->v[8] = (uint8_t) (panId >> 8);
    targetAddress->v[9] = (uint8_t) panId;
    targetAddress->v[14] = (uint8_t) (sa >> 8);
    targetAddress->v[15] = (uint8_t) sa;
}

static bool _APP_CYCLES_RefreshDeviceCycle(uint16_t *index)
{
    uint16_t i;
    // Refresh Device Index to be cycled
    for (i=*index; i < APP_COORDINATOR_MAX_DEVICES; i++)
    {
        if (appCoordinatorDeviceInfo[i].cycle)
        {
            if (appCoordinatorDeviceInfo[i].sa != 0xFFFF)
            {
                break;
            }
        }
    }
    
    *index = i;
    
    if (i == APP_COORDINATOR_MAX_DEVICES)
        return false; // No more devices to be cycled
    
    return true;
}

static void _APP_CYCLES_StartDeviceCycle(uint16_t device_index)
{

    uint16_t panId;
    uint8_t eui64[8];
    
    /* Create link-local address based on short address and PAN ID */
    APP_EAP_SERVER_GetDeviceAddress(appCoordinatorDeviceInfo[device_index].eap_index, eui64);
    panId = APP_G3_MANAGEMENT_GetPanId();
       
    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_CYCLES: Starting cycle for (SA: 0x%04X, PANid: 0x%04X,"
            " EUI64: 0x%02X%02X%02X%02X%02X%02X%02X%02X) -\r\n", appCoordinatorDeviceInfo[device_index].sa, panId, 
            eui64[0], eui64[1], eui64[2], eui64[3], eui64[4], eui64[5], eui64[6], eui64[7]);

    appCoordinatorDeviceInfo[device_index].stats.numCycles++;
}

static void _APP_CYCLES_StartCycle(void)
{
    app_cyclesData.deviceIndex = 0;
    app_cyclesData.timeCountTotalCycle = 0;    
    app_cyclesData.numDevicesCycling = APP_COORDINATOR_deviceRefreshCycle();
            
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "APP_CYCLES: Starting cycle %u. %hu nodes in cycle.\r\n",
            app_cyclesData.cycleIndex, app_cyclesData.numDevicesCycling);
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
    app_cyclesData.transfer_state = APP_CYCLES_TRANSFER_STATE_WAIT;

    /* Initialize application variables */
    app_cyclesData.socket = INVALID_SOCKET;
    app_cyclesData.transferFlag = false;
    app_cyclesData.timeCountTotal = 0;
    app_cyclesData.numUdpRequests = 0;
    app_cyclesData.numUdpReplies = 0;
    app_cyclesData.cycleIndex = 0;
    app_cyclesData.numDevicesJoined = 0;
    app_cyclesData.timeDataExpired = false;
    app_cyclesData.timeCycleExpired = false;
    app_cyclesData.availableBuffers = true;
    app_cyclesData.packetPending = false;
    app_cyclesData.freetransferFlag = true;
    
    //SYS_CONSOLE_HANDLE myConsoleHandle;
    //myConsoleHandle = SYS_CONSOLE_HandleGet(SYS_CONSOLE_INDEX_1);
    //if (myConsoleHandle != SYS_CONSOLE_HANDLE_INVALID)
    //{
    //    SYS_CONSOLE_Message(myConsoleHandle, "APP_CYCLES init\r\n");
    //}
    
    // Initialize Device Information
    _APP_COORDINATOR_deviceInit();
    // Initialize Device Cmds Queue
    _APP_COORDINATOR_InitCmdsQueue();
    
}

void APP_CYCLES_TRANSFER_Tasks()
{

    switch (app_cyclesData.transfer_state)
    {
        case APP_CYCLES_TRANSFER_STATE_WAIT:
            if (app_cyclesData.transferFlag)
            {
                /* Someone wants to transmit */
                app_cyclesData.transfer_state = APP_CYCLES_TRANSFER_STATE_SEND_DATA;
            }
            break;
            
        case APP_CYCLES_TRANSFER_STATE_SEND_DATA:
            if (app_cyclesData.availableBuffers)
            {         
                char targetAddressString[50 + 1];
                uint16_t panId;
                
                panId = APP_G3_MANAGEMENT_GetPanId();
                _APP_CYCLES_UpdateDestinationAddress(app_cyclesData.shortAddress, panId, &app_cyclesData.targetAddress);
                TCPIP_Helper_IPv6AddressToString(&app_cyclesData.targetAddress, targetAddressString, sizeof(targetAddressString) - 1);
                if (app_cyclesData.shortAddress != 0xFFFF)
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_CYCLES: Sending Packet to %s\r\n", targetAddressString);
                    _APP_CYCLES_SendPacket(&app_cyclesData.targetAddress, app_cyclesPayload, app_cyclesData.packetSize);                
                    if (app_cyclesData.answerFlag)
                    {
                        /* Create timer for timeout to detect UDP reply not received */
                        app_cyclesData.timeDataExpired = false;
                        app_cyclesData.timeDataHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &app_cyclesData.timeDataExpired , app_cyclesData.answerTimeout_ms, SYS_TIME_SINGLE);
                        app_cyclesData.transfer_state = APP_CYCLES_TRANSFER_STATE_WAIT_DATA;
                    }
                    else
                    {
                        app_cyclesData.timeDataExpired = true;
                        app_cyclesData.answerOK = true;
                        app_cyclesData.transfer_state = APP_CYCLES_TRANSFER_STATE_WAIT;
                        /* For the next transfer */
                        app_cyclesData.transferFlag = false;
                    }
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_CYCLES: Impossible to Send Packet to %s\r\n", targetAddressString);
                    app_cyclesData.timeDataExpired = true;
                    app_cyclesData.answerOK = false;
                    app_cyclesData.transfer_state = APP_CYCLES_TRANSFER_STATE_WAIT;
                    /* For the next transfer */
                    app_cyclesData.transferFlag = false;
                }
            }
            break; 

        case APP_CYCLES_TRANSFER_STATE_WAIT_DATA:
        {
            uint64_t currentTimeCount, elapsedTimeCount;
            uint16_t rxPayloadSize;
            uint8_t udpProtocol;
            uint8_t tries;
            bool payloadOk = true;

            if ((app_cyclesData.timeDataExpired == true) && (app_cyclesData.availableBuffers == true))
            {
                /* UDP reply not received */
                app_cyclesData.answerOK = false;
                currentTimeCount = SYS_TIME_Counter64Get();
                elapsedTimeCount = currentTimeCount - app_cyclesData.timeCountUdpRequest;
                if (app_cyclesData.pStatsEntry != NULL)
                    app_cyclesData.pStatsEntry->timeCountTotal += elapsedTimeCount;
                app_cyclesData.timeCountTotal += elapsedTimeCount;
                app_cyclesData.timeCountTotalCycle += elapsedTimeCount;
                
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_CYCLES: UDP Device Info reply not received (timeout %u ms)\r\n",
                        SYS_TIME_CountToMS(elapsedTimeCount));

                /* Free Transfer State */
                app_cyclesData.transferFlag = false;
                app_cyclesData.transfer_state = APP_CYCLES_TRANSFER_STATE_WAIT;
                break;
            }

            /* Get number of bytes received */
            rxPayloadSize = TCPIP_UDP_GetIsReady(app_cyclesData.socket);

            if (rxPayloadSize == 0)
            {
                /* No data received */
                break;
            }

            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: RECEIVED PACKET\r\n");

            app_cyclesData.answerOK = true;
            app_cyclesData.timeDataExpired = true;
            // Type == ShortAddress - Refresh Alive tries
            
            /* UDP frame received. Compute round-trip time. */
            elapsedTimeCount = SYS_TIME_Counter64Get() - app_cyclesData.timeCountUdpRequest;
            if (app_cyclesData.pStatsEntry != NULL)
                app_cyclesData.pStatsEntry->timeCountTotal += elapsedTimeCount;
            app_cyclesData.timeCountTotal += elapsedTimeCount;
            app_cyclesData.timeCountTotalCycle += elapsedTimeCount;
            SYS_TIME_TimerDestroy(app_cyclesData.timeDataHandle);

            /* Read first received byte (protocol) */
            TCPIP_UDP_Get(app_cyclesData.socket, &udpProtocol);

            if (udpProtocol == CMD_GET_DEVICE_INFO_RESP)
            {
                /* Get the Device Information */
                TCPIP_UDP_Get(app_cyclesData.socket, &udpProtocol);
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "APP_CYCLES: UDP Device Type = 0x%02X\r\n",udpProtocol);
            }
            else
            {
                /* Wrong UDP protocol, it must be 0x02 (UDP reply) */
                payloadOk = false;
            }

            if (payloadOk == true)
            {
                /* Update statistics */
                app_cyclesData.numUdpReplies++;
                if (app_cyclesData.pStatsEntry != NULL)
                    app_cyclesData.pStatsEntry->numUdpReplies++;
                // Refresh tries for this short address == type
                APP_COORDINATOR_deviceSetTriesByType(app_cyclesData.shortAddress, APP_COORDINATOR_ALIVE_TRIES);
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "APP_CYCLES: UDP Device Info reply received from 0x%04X (%u ms)\r\n", 
                        app_cyclesData.shortAddress, SYS_TIME_CountToMS(elapsedTimeCount));
            }
            else
            {
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "APP_CYCLES: Wrong UDP Device Info reply received (%u ms)\r\n",
                        SYS_TIME_CountToMS(elapsedTimeCount));
            }

            /* Received UDP frame processed, we can discard it */
            TCPIP_UDP_Discard(app_cyclesData.socket);

            app_cyclesData.transfer_state = APP_CYCLES_TRANSFER_STATE_WAIT;
            
            /* Free Transfer State */
            app_cyclesData.transferFlag = false;

            break;
        }    
        default:
            break;
    }
}

/******************************************************************************
  Function:
    void APP_CYCLES_Tasks ( void )

  Remarks:
    See prototype in app_cycles.h.
 */

void APP_CYCLES_Tasks ( void )
{
    
    APP_CYCLES_TRANSFER_Tasks();
    
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
                SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: Go to Start Cycle\r\n");
                /* First device joined the G3 network. Start timer to wait
                 * before first cycle */
                app_cyclesData.state = APP_CYCLES_STATE_START_CYCLE;
                app_cyclesData.timeCycleHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &app_cyclesData.timeCycleExpired, APP_CYCLES_TIME_WAIT_FIRST_CYCLE_MS,
                        SYS_TIME_SINGLE);
            }

            break;
        }           

        /* State to wait for UDP cycle */
        case APP_CYCLES_STATE_START_CYCLE:
        {
            /* If pending packets, send it */
            if ((app_cyclesData.freetransferFlag) && (!app_cyclesData.transferFlag))
            {
                // Next Cmds from Queue
                APP_COORDINATOR_CMDS_QUEUE_DATA cmd;
                if (_APP_COORDINATOR_PopCoordCmdsQueue(&cmd))
                {
                    app_cyclesData.freetransferFlag = false;
                    app_cyclesData.transferFlag = true;
                    app_cyclesData.shortAddress = appCoordinatorDeviceInfo[cmd.index].sa;
                    memcpy(&app_cyclesPayload[0], &cmd.data, cmd.length);
                    app_cyclesData.packetSize = cmd.length;
                    app_cyclesData.answerFlag = cmd.answer;
                    app_cyclesData.answerOK = false;
                    app_cyclesData.answerTimeout_ms = APP_CYCLES_TIMEOUT_MS;
                    // No stats
                    app_cyclesData.pStatsEntry = NULL;
                    app_cyclesData.state = APP_CYCLES_STATE_WAIT_QUEUE_CMD;
                    app_cyclesData.next_state = APP_CYCLES_STATE_START_CYCLE;
                    break;
                }
            }
            
            if (app_cyclesData.timeCycleExpired == false)
            {
                /* Check number of joined devices */
                uint16_t numDevicesJoined = APP_EAP_SERVER_GetNumDevicesJoined();
                if (numDevicesJoined == 0)
                {
                    app_cyclesData.state = APP_CYCLES_STATE_WAIT_FIRST_JOIN;
                    break;
                }
                
                if (numDevicesJoined != app_cyclesData.numDevicesJoined)
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: New devices on the network\r\n");
                    /* New device(s) joined or left the G3 network. Reload the
                     * timer to wait before first cycle */
                    app_cyclesData.numDevicesJoined = numDevicesJoined;
                    SYS_TIME_TimerReload(app_cyclesData.timeCycleHandle, 0, SYS_TIME_MSToCount(APP_CYCLES_TIME_WAIT_FIRST_CYCLE_MS),
                            APP_SYS_TIME_CallbackSetFlag, (uintptr_t) &app_cyclesData.timeCycleExpired, SYS_TIME_SINGLE);
                }
            }
            else
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "APP_CYCLES: Go to Start Device Cycle\r\n");
                /* Waiting time expired. Start first cycle */
                _APP_CYCLES_StartCycle();
                app_cyclesData.timeCycleExpired == true;
                bool pendingDevice = _APP_CYCLES_RefreshDeviceCycle(&app_cyclesData.deviceIndex);
                if (pendingDevice)
                {
                    app_cyclesData.state = APP_CYCLES_STATE_START_DEVICE_CYCLE;
                }
                else
                {
                    //No more devices pending to be cycled - only happens with 1 device
                    app_cyclesData.numDevicesCycling = 0;
                    app_cyclesData.state = APP_CYCLES_STATE_WAIT_FIRST_JOIN;
                }                
            }
            break;
        }   
        
        case APP_CYCLES_STATE_START_DEVICE_CYCLE:        
            
            // Check first if any additional message into the queue
            if ((app_cyclesData.freetransferFlag) && (!app_cyclesData.transferFlag))
            {
                // Next Cmds from Queue
                APP_COORDINATOR_CMDS_QUEUE_DATA cmd;
                if (_APP_COORDINATOR_PopCoordCmdsQueue(&cmd))
                {
                    app_cyclesData.freetransferFlag = false;
                    app_cyclesData.transferFlag = true;
                    app_cyclesData.shortAddress = appCoordinatorDeviceInfo[cmd.index].sa;
                    memcpy(&app_cyclesPayload[0], &cmd.data, cmd.length);
                    app_cyclesData.packetSize = cmd.length;
                    app_cyclesData.answerFlag = cmd.answer;
                    app_cyclesData.answerOK = false;
                    app_cyclesData.answerTimeout_ms = APP_CYCLES_TIMEOUT_MS;
                    // No stats
                    app_cyclesData.pStatsEntry = NULL;
                    app_cyclesData.state = APP_CYCLES_STATE_WAIT_QUEUE_CMD;
                    app_cyclesData.next_state = APP_CYCLES_STATE_START_DEVICE_CYCLE;
                    break;
                    
                }else if (app_cyclesData.timeCycleExpired) 
                {    
                    app_cyclesData.freetransferFlag = false;
                    app_cyclesData.transferFlag = true;
                    // Destination Address
                    _APP_CYCLES_StartDeviceCycle(app_cyclesData.deviceIndex);
                    app_cyclesData.shortAddress = appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].sa;
                    // Packet
                    app_cyclesPayload[0] = CMD_GET_DEVICE_INFO;
                    app_cyclesData.packetSize = 1;
                    // Answer Handling
                    app_cyclesData.answerFlag = true;
                    app_cyclesData.answerOK = false;
                    app_cyclesData.answerTimeout_ms = APP_CYCLES_TIMEOUT_MS;
                    // Destination Stats
                    app_cyclesData.pStatsEntry = &appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].stats;
                    app_cyclesData.state = APP_CYCLES_STATE_NEXT_DEVICE_CYCLE;
                    /* Allow transfer */
                    app_cyclesData.transferFlag = true;
                }
                else 
                {
                    // Nothing to send
                }
            }
            break;

        /* State to wait for the next device UDP cycle */
        case APP_CYCLES_STATE_NEXT_DEVICE_CYCLE:
        {
            if (!app_cyclesData.transferFlag)
            {   
                // depends on answerOK
                if (app_cyclesData.answerOK)
                {
                    if (!appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].alive)
                    {
                        APP_COORDINATOR_deviceSetAliveByType(appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].type, true, true);
                    }
                    APP_COORDINATOR_deviceSetTriesByType(appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].type, APP_COORDINATOR_ALIVE_TRIES);
                }
                else
                {                    
                    appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].tries--;
                    if (appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].tries == 0)
                    {
                        /* Device not alive */
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP COORDINATOR] - Device type 0x%02X not alive (tries=0)\r\n", appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].type);
                        APP_EAP_SERVER_KickDevice(appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].sa);
                        APP_COORDINATOR_deviceSetAliveByType(appCoordinatorDeviceInfo[app_cyclesData.deviceIndex].type, false, false);                        
                    }
                }
                app_cyclesData.freetransferFlag = true;
                app_cyclesData.numDevicesCycling--;
                app_cyclesData.deviceIndex++;
                bool pendingDevice = _APP_CYCLES_RefreshDeviceCycle(&app_cyclesData.deviceIndex);
                
                if ((!app_cyclesData.numDevicesCycling) || (!pendingDevice))
                {
                    app_cyclesData.state = APP_CYCLES_STATE_START_CYCLE;
                    /* Start again with first device */
                    app_cyclesData.cycleIndex++;
                    /* Start timer to wait before next cycle */
                    app_cyclesData.timeCycleExpired = false;
                    app_cyclesData.timeCycleHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                            (uintptr_t) &app_cyclesData.timeCycleExpired, APP_CYCLES_TIME_WAIT_CYCLE_MS, SYS_TIME_SINGLE);
                    break;
                }
                else
                {                   
                    app_cyclesData.state = APP_CYCLES_STATE_START_DEVICE_CYCLE;
                    /* Start timer to wait before next device cycle */
                    app_cyclesData.timeCycleExpired = false;
                    app_cyclesData.timeCycleHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                            (uintptr_t) &app_cyclesData.timeCycleExpired, APP_CYCLES_TIME_BTW_DEVICE_CYCLES_MS, SYS_TIME_SINGLE);
                }
            }
            break;
        }            
        case APP_CYCLES_STATE_WAIT_QUEUE_CMD:
        {
            if (!app_cyclesData.transferFlag)
            {   
                app_cyclesData.freetransferFlag = true;
                app_cyclesData.state = app_cyclesData.next_state;
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
    if ((bufferInd->largeBuffersAvailable == 1) && (bufferInd->mediumBuffersAvailable == 1) &&
            (bufferInd->smallBuffersAvailable == 1))
    {
        /* All buffers are available */
        app_cyclesData.availableBuffers = true;
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

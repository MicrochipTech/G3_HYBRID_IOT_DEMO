/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_cycles.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_CYCLES_Initialize" and "APP_CYCLES_Tasks" prototypes) and some of them
    are only used internally by the application (such as the "APP_CYCLES_STATES"
    definition). Both are defined here for convenience.
*******************************************************************************/

#ifndef _APP_CYCLES_H
#define _APP_CYCLES_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "system/time/sys_time.h"
#include "library/tcpip/tcpip.h"
#include "user.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************

/* If APP_CYCLES_METROLOGY_DATA_REQUEST macro is defined, metrology data is
 * requested in cycles through UDP */
//#define APP_CYCLES_METROLOGY_DATA_REQUEST

/* Time to wait before start cycling in ms */
#define APP_CYCLES_TIME_WAIT_FIRST_CYCLE_MS 60000
#define APP_CYCLES_TIME_WAIT_CYCLE_MS 60000

/* Time between device cycles in ms */
#define APP_CYCLES_TIME_BTW_DEVICE_CYCLES_MS 500

/* Timeout in ms to consider reply not received - 6500 msec > 2 * net_traversal_time (3000 msecs) */
/* RREP_WAIT (2) < ADP_NET_TRAVERSAL_TIME (3) */
#define APP_CYCLES_TIMEOUT_MS 8000

#ifndef APP_CYCLES_METROLOGY_DATA_REQUEST
    /* UDP packet size in bytes */
    #define APP_CYCLES_PACKET_SIZE_1 64
    #define APP_CYCLES_PACKET_SIZE_2 300
    #define APP_CYCLES_PACKET_SIZE_3 1000

    /* UDP port for UDP responder (conformance) */
    #define APP_CYCLES_SOCKET_PORT   APP_UDP_SOCKET
#else
    /* Port number for UDP metrology. This port can be compressed using 6LowPAN
     * (rfc4944, rfc6282) (0xF0B0 - 0xF0BF) */
    #define APP_CYCLES_SOCKET_PORT 0xF0B0
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    APP_CYCLES_STATE_WAIT_TCPIP_READY = 0,

    /* State to wait for the first device joined to the G3 network */
    APP_CYCLES_STATE_WAIT_FIRST_JOIN,

    /* State to wait for first UDP cycle */
    APP_CYCLES_STATE_START_CYCLE,
            
    APP_CYCLES_STATE_START_DEVICE_CYCLE,
    APP_CYCLES_STATE_NEXT_DEVICE_CYCLE,           

    /* Wait QUEUE CMD transaction */
    APP_CYCLES_STATE_WAIT_QUEUE_CMD,

    /* State to wait for the next device UDP cycle */
    APP_CYCLES_STATE_WAIT_NEXT_DEVICE_CYCLE,

#if SYS_CONSOLE_DEVICE_MAX_INSTANCES > 0U
    /* State to show cycle report */
    APP_CYCLES_STATE_SHOW_REPORT,
#endif

    /* Conformance state: Cycling disabled */
    APP_CYCLES_STATE_CONFORMANCE,

    /* Error state */
    APP_CYCLES_STATE_ERROR,

} APP_CYCLES_STATES;

typedef enum
{
    APP_CYCLES_TRANSFER_STATE_WAIT = 0,
    APP_CYCLES_TRANSFER_STATE_SEND_DATA,
    APP_CYCLES_TRANSFER_STATE_WAIT_DATA,

} APP_CYCLES_TRANSFER_STATES;

typedef enum
{
    APP_COORDINATOR_DEVICE_STATE_OUT = 0,
    APP_COORDINATOR_DEVICE_STATE_JOINED = 1,
    APP_COORDINATOR_DEVICE_STATE_ALIVE = 2
}APP_COORDINATOR_DEVICE_STATE;

// COORDINATOR CMDS QUEUE
#define CMD_DATA_SIZE 16
typedef struct
{
    // Device Index
    uint8_t index;
    // DATA INFORMATION
    uint8_t data[CMD_DATA_SIZE];
    // DATA INFORMATION LENGTH
    uint8_t length;
    // ANSWER EXPECTED
    bool answer;
} APP_COORDINATOR_CMDS_QUEUE_DATA;

#define APP_COORDINATOR_CMDS_QUEUE_DATA_SIZE  10

typedef struct
{
  APP_COORDINATOR_CMDS_QUEUE_DATA data[APP_COORDINATOR_CMDS_QUEUE_DATA_SIZE];
  APP_COORDINATOR_CMDS_QUEUE_DATA * dataRd;
  APP_COORDINATOR_CMDS_QUEUE_DATA * dataWr;
  uint8_t dataSize;
} APP_COORDINATOR_CMDS_QUEUE;

// *****************************************************************************
/* Cycles Statistics Entry

  Summary:
    Holds cycles statistics data for a specific device.

  Description:
    This structure holds the cycles statistics data for a specific device.

  Remarks:
    None.
 */

typedef struct
{
    /* Total time count between UDP requests and replies */
    uint64_t timeCountTotal;

    /* Total number of cycles */
    uint32_t numCycles;

    /* Total number of UDP requests sent for this device */
    uint32_t numUdpRequests;

    /* Total number of UDP replies received for this device */
    uint32_t numUdpReplies;
    
} APP_CYCLES_STATISTICS_ENTRY;

#define APP_COORDINATOR_MAX_DEVICES 12   // TYPE_PANEL_LED - TYPE_LIGHTING_INDOOR + 1

#define APP_COORDINATOR_ALIVE_TRIES 3

#define INDEX_UNKNOWN 255

typedef struct
{
    /* Total time count between UDP requests and replies */
    uint8_t eap_index;
    /* Total time count between UDP requests and replies */
    uint8_t type;
    /* Total time count between UDP requests and replies */
    uint16_t sa;
    
    bool    joined;
    
    bool    alive; 
    
    uint8_t tries;
    
    bool    cycle;
    
    bool    state; /* For Lighting devices */
    
    APP_CYCLES_STATISTICS_ENTRY stats;
    
} APP_COORDINATOR_DEVICE_INFO;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* Total time count between UDP requests and replies */
    uint64_t timeCountTotal;

    /* Total time count between UDP requests and replies for the current cycle */
    uint64_t timeCountTotalCycle;

    /* Time counter corresponding to UDP request */
    uint64_t timeCountUdpRequest;

    /* Handle for waiting time before first cycle and timeout */
    SYS_TIME_HANDLE timeCycleHandle;
    
    /* Handle for waiting time UDP Data interchange answer */
    SYS_TIME_HANDLE timeDataHandle;

    /* UDP socket handle */
    UDP_SOCKET socket;

    /* Pointer to current statistics entry */
    APP_CYCLES_STATISTICS_ENTRY* pStatsEntry;

    /* Total number of UDP requests sent */
    uint32_t numUdpRequests;

    /* Total number of UDP replies received */
    uint32_t numUdpReplies;

    /* UDP cycle index */
    uint32_t cycleIndex;

    /* Device index to send ping to all connected devices */
    uint16_t deviceIndex;

    /* Number of devices joined to the network */
    uint16_t numDevicesJoined;
    
    /* Number of devices cycling to the network */
    uint16_t numDevicesCycling;

#ifndef APP_CYCLES_METROLOGY_DATA_REQUEST
    /* UDP packet size */
    uint16_t packetSize;
#endif

    /* The application's current state */
    APP_CYCLES_STATES state;
    
    /* The application's current state */
    APP_CYCLES_STATES next_state;
    
    APP_CYCLES_TRANSFER_STATES transfer_state;

    /* Timer Cycle expired flag */
    bool timeCycleExpired;
    
    /* Timer Data expired flag */
    bool timeDataExpired;

    /* Flag to indicate that ADP buffers are available */
    bool availableBuffers;

    /* Flag to indicate that packet is pending to be sent because of buffer
     * availability */
    bool packetPending;
    
    /* Allow to transmit */
    bool freetransferFlag;
    
    /* Allow to transmit */
    bool transferFlag;
    
    /* Flag to indicate request with response */
    bool answerFlag;
    
    /* Flag to indicate request with response */
    bool answerOK;
    
    /* Answer Timeout */
    uint32_t answerTimeout_ms;
    
    /* Target Address */
    uint16_t shortAddress;
    
    /* Target Address */
    IPV6_ADDR targetAddress;
    
} APP_CYCLES_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_CYCLES_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_CYCLES_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_CYCLES_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_CYCLES_Initialize ( void );

/*******************************************************************************
  Function:
    void APP_CYCLES_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_CYCLES_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_CYCLES_Tasks( void );

// *****************************************************************************
// *****************************************************************************
// Section: Application Interface Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_CYCLES_AdpBufferIndication(ADP_BUFFER_IND_PARAMS* bufferInd)

  Summary:
    Indicates to the cycles application an ADP Buffer Indication event.

  Description:
    This function indicates to the cycles application an ADP Buffer Indication
    event.

  Precondition:
    APP_CYCLES_Initialize should be called before calling this routine.

  Parameters:
    bufferInd - Pointer to bitmap providing availability of Tx buffers

  Returns:
    None.

  Example:
    <code>
    static void _ADP_BufferIndication(ADP_BUFFER_IND_PARAMS* bufferInd)
    {
        APP_CYCLES_AdpBufferIndication(bufferInd);
    }
    </code>

  Remarks:
    None.
*/

void APP_CYCLES_AdpBufferIndication(ADP_BUFFER_IND_PARAMS* bufferInd);

/*******************************************************************************
  Function:
    void APP_CYCLES_SetConformanceConfig ( void )

  Summary:
    Disables cycling operation.

  Description:
    This function configures cycles application for Conformance Test. Cycling
    operation is disabled.

  Precondition:
    APP_CYCLES_Initialize should be called before calling this routine.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_CYCLES_SetConformanceConfig();
    </code>

  Remarks:
    None.
*/

void APP_CYCLES_SetConformanceConfig ( void );


uint8_t APP_COORDINATOR_deviceTypeByIndex(uint8_t index);

void APP_CYCLES_GetDeviceIndexInfo(uint16_t deviceIndex, uint16_t *sa, uint16_t *panId, uint8_t *eui64, IPV6_ADDR *targetAddress);

bool APP_COORDINATOR_deviceDoSnapshot(APP_COORDINATOR_DEVICE_INFO device_info[]);

bool APP_COORDINATOR_deviceGetAliveSnapshot( APP_COORDINATOR_DEVICE_INFO *device_info_snapshot, uint8_t type );

bool APP_COORDINATOR_deviceGetJoinedSnapshot( APP_COORDINATOR_DEVICE_INFO *device_info_snapshot, uint8_t type );

uint16_t APP_COORDINATOR_deviceGetShortAddressSnapshot( APP_COORDINATOR_DEVICE_INFO *device_info_snapshot, uint8_t type );

bool APP_COORDINATOR_deviceSetStateByType(uint8_t type, bool state );

bool APP_COORDINATOR_deviceSetAliveByType(uint8_t type, bool joined, bool alive );

bool APP_COORDINATOR_deviceSetTriesByType(uint8_t type, uint8_t tries );

bool APP_COORDINATOR_deviceGetStateByType(uint8_t type, bool *state);

bool APP_COORDINATOR_deviceGetAliveByType(uint8_t type, bool *alive);

bool APP_COORDINATOR_deviceGetTriesByType(uint8_t type, uint8_t *tries);

bool APP_COORDINATOR_PushCoordCmdsQueue(APP_COORDINATOR_CMDS_QUEUE_DATA *cmdData);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_CYCLES_H */

/*******************************************************************************
 End of File
 */


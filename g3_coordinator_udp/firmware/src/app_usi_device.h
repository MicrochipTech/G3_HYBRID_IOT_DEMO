/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_usi_device.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_USI_DEVICE_Initialize" and "APP_USI_DEVICE_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_USI_DEVICE_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_USI_DEVICE_H
#define _APP_USI_DEVICE_H

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

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

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
    APP_USI_DEVICE_STATE_INIT=0,            
    /* TODO: Define states used by the application state machine. */
    APP_USI_DEVICE_STATE_CONFIG,
    APP_USI_DEVICE_STATE_READY,
    APP_USI_DEVICE_STATE_PING_DEVICE,
    APP_USI_DEVICE_STATE_PING_DEVICE_ANSWER,
    APP_USI_DEVICE_STATE_DELAY,
    APP_USI_DEVICE_STATE_ERROR            
} APP_USI_DEVICE_STATES;


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
    /* The application's current state */
    APP_USI_DEVICE_STATES state;
    APP_USI_DEVICE_STATES nextState;

    /* TODO: Define any additional data used by the application. */
    SRV_USI_HANDLE srvUSIHandle;
    
    /* Handle for heartbeat timeout */
    SYS_TIME_HANDLE timeHeartbeatHandle;
    
    /* Timer Heartbeat expired flag */
    bool timeHeartbeatExpired;
    
    /* Timer Delay */
    SYS_TIME_HANDLE timerDelay;
    
    /* Timer Delay value */
    uint32_t delayMs;
    
    /* Command to send to G3 device */
    APP_INTERFACE_DEV_CMD deviceCmd;
    
    /* Flag for Command to send to G3 device */
    bool deviceCmdFlag;

} APP_USI_DEVICE_DATA;

typedef enum
{
    
    /* Host Commands */
    CMD_GET_DEVICES = 0xE0,
    CMD_GET_DEVICES_ANSWER,
    CMD_DEVICE_NOTIFICATION,
    CMD_RESET_NOTIFICATION,
    CMD_HEARTBEAT
} APP_USI_DEVICE_CMDS;

typedef struct
{
    /* Device Index */
    uint16_t index;
    /* Packet To send */
    uint8_t data[16];
    /* Packet Length */
    uint8_t length;
    /* Packet Length */
    bool answer;
    
} APP_USI_DEV_CMD;  

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

#define APP_USI_DEVICE_TIME_HEARTBEAT_MS 10000

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************

#define APP_USI_DEVICE_Send_ResetNotification() APP_USI_DEVICE_Send_Command(CMD_RESET_NOTIFICATION)
#define APP_USI_DEVICE_Send_Heartbeat()         APP_USI_DEVICE_Send_Command(CMD_HEARTBEAT)
#define APP_USI_DEVICE_Send_Emergency()         APP_USI_DEVICE_Send_Command(CMD_EMERGENCY)

// *****************************************************************************

void APP_USI_DEVICE_Send_Message(uint8_t *buffer, uint16_t length );

void APP_USI_DEVICE_notifyDeviceStatusChange(uint8_t type, bool joined, bool alive, bool state);

/*******************************************************************************
  Function:
    void APP_USI_DEVICE_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_USI_DEVICE_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_USI_DEVICE_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_USI_DEVICE_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_USI_DEVICE_Tasks ( void )

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
    APP_USI_DEVICE_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_USI_DEVICE_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_USI_DEVICE_H */

/*******************************************************************************
 End of File
 */


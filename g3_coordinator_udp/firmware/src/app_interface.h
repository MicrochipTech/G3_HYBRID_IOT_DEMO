/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_interface.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_INTERFACE_Initialize" and "APP_INTERFACE_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_INTERFACE_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_INTERFACE_H
#define _APP_INTERFACE_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
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
#define APP_INTERFACE_DEFAULT_PWD                   "PIC"
#define APP_INTERFACE_PWD_SIZE                      6
#define APP_INTERFACE_TASK_DFLT_DELAY_MS_BETWEEN_STATES   10
#define APP_INTERFACE_TIMEOUT_PING_MS               2000    


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
    APP_INTERFACE_STATE_INIT=0,
    APP_INTERFACE_STATE_PROMPT,
    APP_INTERFACE_STATE_IDLE,
    APP_INTERFACE_STATE_SW_RESET,
    APP_INTERFACE_STATE_PRINT_HELP,
    APP_INTERFACE_STATE_PRINT_REG_DEVICES,
    APP_INTERFACE_STATE_PING_DEVICE,
    APP_INTERFACE_STATE_PING_DEVICE_ANSWER,
    APP_INTERFACE_STATE_DELAY,
    APP_INTERFACE_STATE_WAIT_DATA            
    /* TODO: Define states used by the application state machine. */

} APP_INTERFACE_STATES;


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
    /* Device Index */
    uint16_t index;
    /* Packet To send */
    uint8_t data[16];
    /* Packet Length */
    uint8_t length;
    /* Packet Length */
    bool answer;
    
} APP_INTERFACE_DEV_CMD;

typedef struct
{
    /* The application's current state */
    APP_INTERFACE_STATES state;
    APP_INTERFACE_STATES nextState;
    struct tm sysTime;
    int8_t numCommands;
    int8_t cmdNumToShowHelp;
    SYS_CMD_DESCRIPTOR *pCmdDescToShowHelp;
    SYS_TIME_HANDLE timer;
    uint32_t delayMs;
    APP_INTERFACE_DEV_CMD deviceCmd;
    bool deviceCmdFlag;
    uint32_t cmdTimeout;   // Timeout for pinging a device blocking the console
    /* TODO: Define any additional data used by the application. */

} APP_INTERFACE_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_INTERFACE_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_INTERFACE_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_INTERFACE_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_INTERFACE_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_INTERFACE_Tasks ( void )

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
    APP_INTERFACE_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_INTERFACE_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_INTERFACE_H */

/*******************************************************************************
 End of File
 */


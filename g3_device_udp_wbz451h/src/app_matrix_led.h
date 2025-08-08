/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_matrix_led.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_MATRIX_LED_Initialize" and "APP_MATRIX_LED_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_MATRIX_LED_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_MATRIX_LED_H
#define _APP_MATRIX_LED_H

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
#include "definitions.h"

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
    /* Application's state machine's initial state */
    APP_MATRIX_LED_STATE_INIT = 0,
            
    APP_MATRIX_LED_STATE_WAIT,

    APP_MATRIX_LED_STATE_REFRESH,

    /* Error state */
    APP_MATRIX_LED_STATE_ERROR,

} APP_MATRIX_LED_STATES;

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
    /* Semaphore identifier. Used to suspend task */
    OSAL_SEM_DECLARE(semaphoreID);
    
    /* The application's current state */
    APP_MATRIX_LED_STATES state;
    
    /* Timer Refresh Screen */
    bool timerRefresh_flag;
    
    SYS_TIME_HANDLE timerRefresh_handler;
    
    uint32_t timeout_ms;
    
    /* Flag to indicate if back-off time has expired */
    bool timerSwitchOnOff_flag;
    
    SYS_TIME_HANDLE timerSwitchOnOff_handler;
    
    /* PANEL LED Output Enable State */
    bool panelLEDon;
    
} APP_MATRIX_LED_DATA;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
} APP_MATRIX_LED;

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
    void APP_MATRIX_LED_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_UDP_RESPONDER_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_MATRIX_LED_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_MATRIX_LED_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_UDP_RESPONDER_Tasks ( void )

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
    APP_MATRIX_LED_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_MATRIX_LED_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_UDP_RESPONDER_H */

/*******************************************************************************
 End of File
 */


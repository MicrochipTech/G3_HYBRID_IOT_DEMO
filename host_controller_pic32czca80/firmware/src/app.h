/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_H
#define _APP_H

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
    
#define APP_SYS_FS_SD_VOL           SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0
#define APP_SYS_FS_MOUNT_POINT      SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0
#define APP_SYS_FS_TYPE             FAT
#define APP_SYS_FS_TYPE_STRING      "FATFS"
    
#define APP_DPRINTF(fmt, ...) SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, fmt, ##__VA_ARGS__);

typedef enum
{
    APP_SUCCESS = 0,
    APP_ERR,            //General error        
    APP_ERR_INV,        //Invalid arguments
    APP_ERR_INTF,       //BLE interface (e.g., UART Write) failure
    APP_ERR_CMD,        //Command failed (i.e., wrong response)
    APP_ERR_RSP,        //Bad response
    APP_ERR_NOMEM,      //not enough memory, buffer full
    APP_ERR_EMPTY,      //list is empty
    APP_ERR_NOTFOUND,   //does not exist
    APP_ERR_NORESP,     // no response 
    APP_ERR_WAIT,       
} APP_RESULT;

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
    APP_STATE_INIT,
    APP_STATE_MOUNT_WAIT,
    APP_STATE_SET_CURRENT_DRIVE,
    APP_STATE_READY,
    APP_STATE_ERROR
} APP_STATES;

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
    APP_STATES state;

    /* alarm status */
    bool alarmStatus;
    /* light_indoor status */
    bool lightIndoorStatus;
    /* light_outdoor status */
    bool lightOutdoorStatus;

} APP_DATA;

extern APP_DATA appData;

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
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );

bool APP_SYSFSMounted(void);
bool APP_SYSFSReady(void);

void APP_DelayMS(uint32_t ms);

bool APP_IsTimerExpired(void);

void APP_StartWaitTimer(uint32_t ms);

/*******************************************************************************
  Function:
    void APP_Tasks ( void )

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
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );

// HTTP application processing
#if defined(TCPIP_STACK_USE_HTTP_NET_SERVER)
extern void HTTP_APP_Initialize(void);
#endif // defined(TCPIP_STACK_USE_HTTP_NET_SERVER)
        
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_H */

/*******************************************************************************
 End of File
 */


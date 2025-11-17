/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_http.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_HTTP_Initialize" and "APP_HTTP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_HTTP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_HTTP_H
#define _APP_HTTP_H

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
#define APP_LED_0StateSet()         LED0_Clear()
#define APP_LED_0StateGet()         LED0_Get()
#define APP_LED_0StateClear()       LED0_Set()
#define APP_LED_0StateToggle()      LED0_Toggle()    
    
#define APP_LED_1StateSet()         LED1_Clear()
#define APP_LED_1StateGet()         LED1_Get()
#define APP_LED_1StateClear()       LED1_Set()
#define APP_LED_1StateToggle()      LED1_Toggle()
    
#define APP_HTTP_NOTIF_CALLBACK_COUNT 16
#define APP_HTTP_QUEUE_LENGTH 64
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
/* The application mounts the disk. */
    APP_HTTP_STATE_INIT = 0, 
    APP_HTTP_MOUNT_DISK,

    /* In this state, the application waits for the initialization of the TCP/IP stack
       to complete. */
    APP_HTTP_TCPIP_WAIT_INIT,

    /* In this state, the application can do TCP/IP transactions. */
    APP_HTTP_TCPIP_TRANSACT,

    /* The application waits in this state for the driver to be ready
       before sending the "hello world" message. */
    //APP_HTTP_STATE_WAIT_FOR_READY,

    /* The application waits in this state for the driver to finish
       sending the message. */
    //APP_HTTP_STATE_WAIT_FOR_DONE,

    /* The application does nothing in the idle state. */
    APP_HTTP_STATE_IDLE,

    //
    APP_HTTP_USERIO_LED_DEASSERTED,

    APP_HTTP_USERIO_LED_ASSERTED,

    APP_HTTP_TCPIP_ERROR,

} APP_HTTP_STATES;

typedef enum
{
    APP_HTTP_CONNECT,
    APP_HTTP_DISCONNECT,
    APP_HTTP_CONTROL,
} APP_HTTP_EVENT;

typedef enum
{
    APP_HTTP_STATE_CHANGE,            //HTTP Task state change event
    APP_HTTP_CONNECT_NOTIFY,          //NET/HTTP Connection Update
    APP_HTTP_DEVICE_NOTIFY,           //HTTP device notification Event
} APP_HTTP_NOTIFY_EVENT;


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
    APP_HTTP_STATES state;

    /* TODO: Define any additional data used by the application. */

} APP_HTTP_DATA;

typedef struct
{
    void (*func) (uint32_t event, void * data, uint32_t size);
} APP_HTTP_NOTIF_CALLBACK;

typedef struct
{
    APP_HTTP_STATES taskState;
    //FIXME
//    QueueHandle_t msgQueue;
    APP_HTTP_NOTIF_CALLBACK notifCallbacks[APP_HTTP_NOTIF_CALLBACK_COUNT];
} APP_HTTP_TASK_OBJ;

typedef struct
{
    APP_HTTP_EVENT event;
    void * device;
    uint32_t parmsize;  //size of parameter data
    union
    {
        uint8_t data[APP_QUEUE_MSG_SIZE];
        void * obj;
        struct 
        {
            uint32_t * addr;    //pointer to buffer
            uint32_t buffsize;  //size of buffer
        } buffer;
    } param;
} APP_HTTP_MSG;

typedef struct 
{
    uint32_t id;
    union
    {
        uint32_t value;
        void * data;
    } parm;
} APP_HTTP_NOTIF_DATA;

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
    void APP_HTTP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_HTTP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_HTTP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_HTTP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_HTTP_Tasks ( void )

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
    APP_HTTP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_HTTP_Tasks( void );

void APP_HTTP_ProcessDemoForm(uint8_t * httpDataBuff);
int32_t APP_HTTP_RegisterStateNotification(void (*func)(uint32_t, void *, uint32_t));
APP_RESULT APP_HTTP_UnregisterStateNotification(uint32_t idx);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_HTTP_H */

/*******************************************************************************
 End of File
 */


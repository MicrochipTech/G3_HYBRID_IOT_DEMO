/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_wifi.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_WIFI_Initialize" and "APP_WIFI_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_WIFI_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_WIFI_H
#define _APP_WIFI_H

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

#define TERM_GREEN "\x1B[32m"
#define TERM_RED   "\x1B[31m"
#define TERM_YELLOW "\x1B[33m"
#define TERM_CYAN "\x1B[36m"
#define TERM_WHITE "\x1B[47m"
#define TERM_RESET "\x1B[0m"
#define TERM_BG_RED "\x1B[41m" 
#define TERM_BOLD "\x1B[1m" 
#define TERM_UL "\x1B[4m"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END
#define APP_BUILD_HASH_SZ 5
#define APP_DI_IMAGE_INFO_NUM 2
#define APP_WIFI_MAX_CON_RETRIES 10

#define APP_WIFI_CONFIG_FILE "wifiCfg.txt"
#define APP_WIFI_CONFIG_ADDR_SIZE 53
#define APP_WIFI_CONFIG_SSID "ssid="
#define APP_WIFI_CONFIG_PASS ",key="
#define APP_WIFI_CONFIG_SEC  ",sec="
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_WIFI_NOTIF_CALLBACK_COUNT 6
#define APP_WIFI_QUEUE_COUNT 64
#define WIFI_QUEUE_DATA_SIZE 64
    
#define APP_WIFI_QUEUE_WR_EMPTY (-1)
#define APP_WIFI_QUEUE_RD_EMPTY (-1)
    
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
    APP_WIFI_STATE_INIT=0,

    // State to print Message 
    APP_WIFI_STATE_WINCS_PRINT,

    // Initial state of the application
    APP_WIFI_STATE_WINCS_INIT,

    // State to open the Wi-Fi driver
    APP_WIFI_STATE_WINCS_OPEN_DRIVER,

    // State to retrieve device information
    APP_WIFI_STATE_WINCS_DEVICE_INFO,

    // State to set the regulatory domain for Wi-Fi
    APP_WIFI_STATE_WINCS_SET_REG_DOMAIN,

    // State to configure Wi-Fi parameters
    APP_WIFI_STATE_WINCS_ENABLE_PROV,

    // State to get configuration Wi-Fi parameters
    APP_WIFI_STATE_WINCS_GET_WIFI_PARAMS,
            
    // State to configure Wi-Fi parameters
    APP_WIFI_STATE_WINCS_SET_WIFI_PARAMS,

    // State to create socket
    //APP_WIFI_STATE_WINCS_CREATE_SOCKET,

    // State to handle errors
    APP_WIFI_STATE_WINCS_ERROR,

    // State to perform regular service tasks and wait for callback
    APP_WIFI_STATE_WINCS_SERVICE_TASKS,

    // State to start WiFi provisioning
    APP_WIFI_STATE_WINCS_START_PROVISIONING,

    // State to do nothing in case WiFi connection can`t be established
    APP_WIFI_STATE_WINCS_DO_NOTHING
} APP_WIFI_STATES;

typedef enum
{
    APP_WIFI_OFF = 0,
    APP_WIFI_AVAILABLE = 1,          //Wifi WINCS02 module available
    APP_WIFI_CONNECTED = 2,          //Wifi Connected
    APP_WIFI_SNTP_UP = 4,            //Wifi SNTP UP
    APP_WIFI_MQTT_CONNECTED = 8      //MQTT Connected throught WIFI
} APP_WIFI_STATUS;

typedef enum
{
    APP_WIFI_AVAILABLE_NOTIFY,          //Wifi WINCS02 module available
    APP_WIFI_CONNECTED_NOTIFY,          //Wifi Connected
    APP_WIFI_DISCONNECTED_NOTIFY,       //Wifi Disconnected
    APP_WIFI_SNTP_UP_NOTIFY,            //Wifi SNTP UP
    APP_WIFI_MQTT_CONNECTED_NOTIFY,     //MQTT Connected throught WIFI
    APP_WIFI_MQTT_DISCONNECTED_NOTIFY   //MQTT Disconnected throught WIFI            
} APP_WIFI_NOTIFY_EVENT;

typedef struct
{
    void (*func) (uint32_t event, void * data, uint32_t size);
} APP_WIFI_NOTIF_CALLBACK;

#if 0
typedef struct
{
    APP_WIFI_EVENTS event;
    uint32_t device;
    uint32_t parmSize;
    union
    {
        uint32_t num;
        void * dataPtr;
        uint8_t data[WIFI_QUEUE_DATA_SIZE];
    } param;
} APP_WIFI_MSG;
#endif

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
    APP_WIFI_STATES state;
    /* WIFI status */
    uint32_t status;
    /* Configuration File*/
    SYS_FS_HANDLE cfgFileHandle;

    /* Wi-Fi SSID of Access Point */
    char *ssid;
    /* Wi-Fi password of Access Point */
    char *password;
    /* MQTT cloud connection status */
    bool cloudConnected;
    /* MQTT cloud connection retires */
    uint8_t connectionRetires;
    /* alarm status and published over WINCS02 module */
    bool alarmStatus;
    bool alarmStatusPublished;
    /* light_indoor status and published over WINCS02 module */
    bool lightIndoorStatus;
    bool lightIndoorStatusPublished;
    /* light_outdoor status and published over WINCS02 module */
    bool lightOutdoorStatus;
    bool lightOutdoorStatusPublished;
    /* Counter of received heartbeats (CMD_HEARTBEAT) from coordinator */
    int coordHeartbeatCounter;
    /* Heartbeats published over WINCS02 module */
    int heartbeatsPublished;
    /* MQTT message counter received over WiFi */
    int mqttMessCntWifi;
    /* WIFI Notification callbacks */
    APP_WIFI_NOTIF_CALLBACK notifCallbacks[APP_WIFI_NOTIF_CALLBACK_COUNT];
} APP_WIFI_DATA;
extern APP_WIFI_DATA app_wifiData;

typedef struct
{
    /* Version number structure. */
    struct
    {
        /* Major version number. */
        uint16_t major;

        /* Major minor number. */
        uint16_t minor;

        /* Major patch number. */
        uint16_t patch;
    } version;
} APP_DRIVER_VERSION_INFO;

typedef struct
{
    /* Flag indicating if this information is valid. */
    bool isValid;

    /* Version number structure. */
    struct
    {
        /* Major version number. */
        uint16_t major;

        /* Major minor number. */
        uint16_t minor;

        /* Major patch number. */
        uint16_t patch;
    } version;

    /* Build date/time structure. */
    struct
    {
        uint8_t hash[APP_BUILD_HASH_SZ];

        uint32_t timeUTC;
    } build;
} APP_FIRMWARE_VERSION_INFO;


// *****************************************************************************
/*  Device Information

  Summary:
    Defines the device information.

  Description:
    This data type defines the device information of the WINC.

  Remarks:
    None.
*/

typedef struct
{
    /* Flag indicating if this information is valid. */
    bool isValid;

    /* WINC device ID. */
    uint32_t id;

    /* Number of flash images. */
    uint8_t numImages;

    /* Information for each device image. */
    struct
    {
        /* Sequence number. */
        uint32_t seqNum;

        /* Version information. */
        uint32_t version;

        /* Source address. */
        uint32_t srcAddr;
    } image[APP_DI_IMAGE_INFO_NUM];
} APP_DEVICE_INFO;

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
    void APP_WIFI_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_WIFI_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_WIFI_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

bool APP_WIFI_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_WIFI_Tasks ( void )

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
    APP_WIFI_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_WIFI_Tasks( void );

bool APP_WIFI_GetStatus(uint32_t *status);

uint32_t APP_WIFI_GetConnectedCount(void);

int32_t APP_WIFI_RegisterNotification(void (*func)(uint32_t, void *, uint32_t));

APP_RESULT APP_WIFI_UnregisterNotification(uint32_t idx);


void APP_WIFI_PublishData(char *msg);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_WIFI_H */

/*******************************************************************************
 End of File
 */


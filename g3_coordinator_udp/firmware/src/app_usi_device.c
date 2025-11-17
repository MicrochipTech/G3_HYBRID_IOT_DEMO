/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_usi_device.c

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
#include "app_cycles.h"
#include "app_usi_device.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_USI_DEVICE_DELAY_WAIT_PING_READY_MS 20

APP_COORDINATOR_DEVICE_INFO CACHE_ALIGN device_info_usi[APP_COORDINATOR_MAX_DEVICES];

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_USI_DEVICE_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_USI_DEVICE_DATA app_usi_deviceData;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

#define SRV_USI_PROT_ID_USED SRV_USI_PROT_ID_PHY
#define USI_MESSAGE_LENGTH_MAX 1024

/* TODO:  Add any necessary local functions.
*/

void APP_USI_DEVICE_Send_Message(uint8_t *buffer, uint16_t length )
{
    /* Send USI Message */
    SRV_USI_Send_Message(app_usi_deviceData.srvUSIHandle, SRV_USI_PROT_ID_USED, (uint8_t *)buffer, length);
}

void APP_USI_DEVICE_Send_Command(APP_USI_DEVICE_CMDS cmd )
{
    uint8_t cmd_l;
    
    cmd_l = cmd;
    /* Send USI Message */
    SRV_USI_Send_Message(app_usi_deviceData.srvUSIHandle, SRV_USI_PROT_ID_USED, &cmd_l, 1);
}

void APP_USI_DEVICE_notifyDeviceStatusChange(uint8_t type, bool joined, bool alive, bool state)
{
    uint8_t buffer[3];
    
    memset(buffer,0,3);
    buffer[0] = (uint8_t) CMD_DEVICE_NOTIFICATION;
    buffer[1] = type;
    if (joined)
        buffer[2] |= APP_COORDINATOR_DEVICE_STATE_JOINED;    // Device Joined/Leave
    if (alive)
        buffer[2] |= APP_COORDINATOR_DEVICE_STATE_ALIVE;
    buffer[3] = state;
    APP_USI_DEVICE_Send_Message(buffer, 4);
}

void APP_USI_DEVICE_ProtocolEventHandler(uint8_t *pData, size_t length)
{   
    uint8_t index, type;
    uint16_t numdevices;
    
    APP_COORDINATOR_CMDS_QUEUE_DATA deviceCmd;
    
    /* Protection for invalid length */
    if (!length)
    {
//        LED1_Toggle();
        return;
    }

    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] Received USI message: 0x%02X, 0x%02X, 0x%02X\r\n",pData[0], pData[1], pData[2]);
    
    //pData_t++ ; // Ignore Protocol ID
    //pData_t++ ; // Ignore USI Frame length
    
    /* Process received command */
    switch (*pData++)
    {
        // Commands from the host PIC32CZCA80
        case CMD_GET_DEVICES:
        {
            
            uint8_t eui64[8];
            uint8_t buffer[USI_MESSAGE_LENGTH_MAX];
            uint8_t *pbuffer;
            
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_USI_DEVICE] Get Devices Info\r\n");
            
            // Do SnapShot of information
            APP_COORDINATOR_deviceDoSnapshot(&device_info_usi);
            
            pbuffer = &buffer[0];
            *pbuffer++ = CMD_GET_DEVICES_ANSWER;
            numdevices = APP_EAP_SERVER_GetNumDevicesJoined();
            if (numdevices)
            {
                *pbuffer++ = APP_COORDINATOR_MAX_DEVICES;
                for (int idx = 0; idx < APP_COORDINATOR_MAX_DEVICES; idx++)
                {
                    *pbuffer++ = idx;
                    *pbuffer++ = device_info_usi[idx].type;
                    uint8_t alive = APP_COORDINATOR_DEVICE_STATE_OUT;
                    if (device_info_usi[idx].joined)
                        alive |= APP_COORDINATOR_DEVICE_STATE_JOINED;
                    if (device_info_usi[idx].alive)
                        alive |= APP_COORDINATOR_DEVICE_STATE_ALIVE;
                    *pbuffer++ = alive;
                    *pbuffer++ = device_info_usi[idx].state;
                }
                APP_USI_DEVICE_Send_Message(buffer, 1 + 1 + (APP_COORDINATOR_MAX_DEVICES * 4));
            }
            else
            {
                buffer[1] = 0;
                APP_USI_DEVICE_Send_Message(buffer, 2);
            }            
            break;
        }
        case CMD_GET_DEVICE_INFO:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_USI_DEVICE] Get Device Info\r\n");         
            index = *pData++ ;
            type = APP_COORDINATOR_deviceTypeByIndex(index);
            numdevices = APP_EAP_SERVER_GetNumDevicesJoined();

            if (((type >= TYPE_LIGHTING_INDOOR) || (type <= TYPE_PANEL_LED)) && numdevices)
            {                
                deviceCmd.index = index;
                deviceCmd.data[0] = CMD_GET_DEVICE_INFO;
                deviceCmd.length = 1;
                deviceCmd.answer = true; 
                APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
            }
            else
            {
                // Invalid password
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_USI_DEVICE] Invalid Index\r\n");
            }
            break;
        }
        case CMD_SET_LED_RGB:
        {
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_USI_DEVICE] Set LED RGB\r\n");      
            index = *pData++ ;
            type = APP_COORDINATOR_deviceTypeByIndex(index);
            if ((type >= TYPE_LIGHTING_INDOOR) || (type <= TYPE_PANEL_LED))
            {
                APP_COORDINATOR_deviceDoSnapshot(&device_info_usi);            
                bool joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_usi, type);
                if (joined)
                {                 
                    deviceCmd.index = index;
                    deviceCmd.data[0] = CMD_SET_LED_RGB;
                    deviceCmd.data[1] = *pData++; // H
                    deviceCmd.data[2] = *pData++; // S
                    deviceCmd.data[3] = *pData++; // V
                    deviceCmd.length = 4;
                    deviceCmd.answer = false; 
                    APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] Device Type 0x%02X not joined\r\n", type);
                }
            }
            else
            {
                // Invalid password
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] Invalid Type 0x%02X\r\n", type);
            }
            break;  
        }
        case CMD_SET_LED_RGB_BLINK:
        {    
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_USI_DEVICE] Set LED RGB Extended\r\n");      
            index = *pData++ ;
            type = APP_COORDINATOR_deviceTypeByIndex(index);
            if ((type >= TYPE_LIGHTING_INDOOR) || (type <= TYPE_PANEL_LED))
            {
                APP_COORDINATOR_deviceDoSnapshot(&device_info_usi);            
                bool joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_usi, type);
                if (joined)
                {                                
                    //app_usi_deviceData.state = APP_USI_DEVICE_STATE_PING_DEVICE;
                    deviceCmd.index = index;
                    deviceCmd.data[0] = CMD_SET_LED_RGB_BLINK;
                    deviceCmd.data[1] = *pData++; // H
                    deviceCmd.data[2] = *pData++; // S
                    deviceCmd.data[3] = *pData++; // V
                    deviceCmd.data[4] = *pData++; // Blinking frequency
                    deviceCmd.data[5] = *pData++; // 
                    deviceCmd.data[6] = *pData++; // Blinking time
                    deviceCmd.data[7] = *pData++; // 
                    deviceCmd.length = 8;
                    deviceCmd.answer = false; 
                    APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] Device Type 0x%02X not joined\r\n", type);
                }
            }
            else
            {
                // Invalid password
                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] Invalid Type 0x%02X\r\n", type);
            }        
            break;
        }
        case CMD_SET_PANEL_LED:
        {
            bool onoff;
            
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_USI_DEVICE] Set PANEL LED\r\n");
            index = *pData++ ;
            type = APP_COORDINATOR_deviceTypeByIndex(index);

            if (type == TYPE_PANEL_LED)
            {               
                onoff = (*pData++ == 0)? false : true;
                APP_COORDINATOR_deviceDoSnapshot(&device_info_usi);            
                bool joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_usi, type);
                if (joined)
                {
                    deviceCmd.index = index;
                    deviceCmd.index = TYPE_PANEL_LED - TYPE_LIGHTING_INDOOR;  // Fixed
                    deviceCmd.data[0] = CMD_SET_PANEL_LED;
                    deviceCmd.data[1] = *pData++; // 0: Microchip Logo, 1: Alarm
                    deviceCmd.length = 2;
                    deviceCmd.answer = false; 
                    APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                    //APP_COORDINATOR_deviceSetStateByType(type, onoff);
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_USI_DEVICE] Device Type 0x%02X not joined\r\n", type);
                }
            }
            else
            {
                // Invalid password
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_USI_DEVICE] Invalid Type 0x%02X\r\n", type);
            }   
            break;
        }
        case CMD_SET_LIGHT:
        {
            bool onoff;            
            index = *pData++ ;
            type = APP_COORDINATOR_deviceTypeByIndex(index);
            if ((type == TYPE_LIGHTING_INDOOR) || (type == TYPE_LIGHTING_OUTDOOR))
            {
                onoff = *pData++;
                SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_USI_DEVICE] Set Light 0x%02X - %s\r\n", type, onoff? "true" : "false");
                APP_COORDINATOR_deviceDoSnapshot(&device_info_usi);            
                bool joined = APP_COORDINATOR_deviceGetJoinedSnapshot(device_info_usi, type);
                if (joined)
                {
                    //app_usi_deviceData.state = APP_USI_DEVICE_STATE_PING_DEVICE;
                    deviceCmd.index = index;  // Should be 0 or 1
                    deviceCmd.data[0] = CMD_SET_LIGHT;
                    deviceCmd.data[1] =  onoff; // 0: Off, 1: On
                    deviceCmd.length = 2;
                    deviceCmd.answer = false; 
                    APP_COORDINATOR_PushCoordCmdsQueue(&deviceCmd);
                    APP_COORDINATOR_deviceSetStateByType(type, onoff);
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_USI_DEVICE] Device Type 0x%02 not joined\r\n", type);
                }
            }
            else
            {
                // Invalid password
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_USI_DEVICE] Invalid Type 0x%02X\r\n", type);
            }  
            break;
        }            
        default:
            break;
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_USI_DEVICE_Initialize ( void )

  Remarks:
    See prototype in app_usi_device.h.
 */

void APP_USI_DEVICE_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_usi_deviceData.state = APP_USI_DEVICE_STATE_INIT;
    app_usi_deviceData.timerDelay = SYS_TIME_HANDLE_INVALID;
    
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_USI_DEVICE] Init\r\n");

}


/******************************************************************************
  Function:
    void APP_USI_DEVICE_Tasks ( void )

  Remarks:
    See prototype in app_usi_device.h.
 */

void APP_USI_DEVICE_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_usi_deviceData.state )
    {
        case APP_USI_DEVICE_STATE_INIT:
        {   /* Application's initial state. */
            /* Open USI Service */
            app_usi_deviceData.srvUSIHandle = SRV_USI_Open(SRV_USI_INDEX_0);

            if (app_usi_deviceData.srvUSIHandle != DRV_HANDLE_INVALID)
            {
                /* Set Application to next state */
                app_usi_deviceData.state = APP_USI_DEVICE_STATE_CONFIG;
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_USI_DEVICE] USI Opened\r\n");
            }
            else
            {
                /* Set Application to ERROR state */
                app_usi_deviceData.state = APP_USI_DEVICE_STATE_ERROR;
            }
            break;
        }

        case APP_USI_DEVICE_STATE_CONFIG:
        {
            if (SRV_USI_Status(app_usi_deviceData.srvUSIHandle) == SRV_USI_STATUS_CONFIGURED)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] USI Configured\r\n");
                /* Register USI callback */
                SRV_USI_CallbackRegister(app_usi_deviceData.srvUSIHandle,
                        SRV_USI_PROT_ID_USED, APP_USI_DEVICE_ProtocolEventHandler);

                /* Set Application to next state */
                app_usi_deviceData.state = APP_USI_DEVICE_STATE_READY;
                APP_USI_DEVICE_Send_ResetNotification();
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] USI Reset Notification sent\r\n");
                app_usi_deviceData.timeHeartbeatHandle = SYS_TIME_CallbackRegisterMS(APP_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &app_usi_deviceData.timeHeartbeatExpired, APP_USI_DEVICE_TIME_HEARTBEAT_MS,
                        SYS_TIME_PERIODIC);
            }
            break;
        }

        case APP_USI_DEVICE_STATE_READY:
        {
            /* Check USI status in case of USI device has been reset */
            if (SRV_USI_Status(app_usi_deviceData.srvUSIHandle) == SRV_USI_STATUS_NOT_CONFIGURED)
            {
                /* Set Application to next state */
                app_usi_deviceData.state = APP_USI_DEVICE_STATE_ERROR;
            }
            if (app_usi_deviceData.timeHeartbeatExpired)
            {
                app_usi_deviceData.timeHeartbeatExpired = false;
                APP_USI_DEVICE_Send_Heartbeat();
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_USI_DEVICE] USI Heartbeat sent\r\n");
            }
            break;
        }
        /* TODO: implement your application state machine.*/
        case APP_USI_DEVICE_STATE_ERROR:
        {
            SRV_USI_Close(app_usi_deviceData.srvUSIHandle);
            app_usi_deviceData.state = APP_USI_DEVICE_STATE_INIT;
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */

/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

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

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app_coordinator.h"
#include "system/debug/sys_debug.h"
#include "app_wifi.h"
#include <string.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

#define ALARM_LED_On() LED0_Clear()
#define ALARM_LED_Off() LED0_Set()
#define ALARM_LED_OutputEnable() LED0_OutputEnable()


APP_COORDINATOR_DEVICE_INFO appCoordinatorDeviceInfo[APP_COORDINATOR_MAX_DEVICES];

APP_COORDINATOR_CMDS_QUEUE CACHE_ALIGN appCoordCmdsQueue;

static bool isAppCoordCmdsQueueMutexCreated = false;
static OSAL_MUTEX_DECLARE(appCoordCmdsQueueMutex);

static bool isAppCoordInfoMutexCreated = false;
static OSAL_MUTEX_DECLARE(appCoordInfoMutex);

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_COORDINATOR_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

USB_ALIGN APP_COORDINATOR_DATA appCoordinatorData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static bool _APP_COORDINATOR_InitCmdsQueue(void)
{
    
    if (isAppCoordCmdsQueueMutexCreated == false)
    {
        if(OSAL_MUTEX_Create(&(appCoordCmdsQueueMutex)) != OSAL_RESULT_SUCCESS)
        {
            return false;
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
    
    return true;
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
        
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_COORD]: PushCmd - Queue Size=%d\r\n", appCoordCmdsQueue.dataSize);
        
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
        
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_COORD]: PopCmd - Queue Size=%d\r\n", appCoordCmdsQueue.dataSize);
        
        return true;
    }
    
    /* Release mutex */
    (void) OSAL_MUTEX_Unlock(&appCoordCmdsQueueMutex);
        
    return false;
}

int32_t APP_COORDINATOR_RegisterNotification(void (*func)(uint32_t, void *, uint32_t))
{
    uint32_t i;
    
    if (func == NULL)
        return -APP_ERR_INV;
    
    for (i = 0; i < APP_COORDINATOR_NOTIF_CALLBACK_COUNT; i++)
    {
        if (appCoordinatorData.notifCallbacks[i].func == NULL)
        {
           appCoordinatorData.notifCallbacks[i].func = func;
           SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_COORD]: Register Notification %d\r\n", i);
           return i;
        }
    }
    return -APP_ERR_NOMEM;
}

APP_RESULT APP_COORDINATOR_UnregisterNotification(uint32_t idx)
{
    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_COORD]: Unregister Notification %d\r\n", idx);
    
    if (idx < APP_COORDINATOR_NOTIF_CALLBACK_COUNT)
    {
        appCoordinatorData.notifCallbacks[idx].func = NULL;
        
        return APP_SUCCESS;
    }
    return APP_ERR_EMPTY;
}

void APP_COORDINATOR_Notify(APP_COORDINATOR_NOTIFY_EVENT event, void * data, uint32_t size)
{
    uint32_t i;
    
    //Call all state callback functions
    for (i = 0; i < APP_COORDINATOR_NOTIF_CALLBACK_COUNT; i++)
    {
        if (appCoordinatorData.notifCallbacks[i].func != NULL)
        {
            appCoordinatorData.notifCallbacks[i].func(event, data, size);
        }
    }
}

void APP_COORDINATOR_SYS_TIME_CallbackSetFlag(uintptr_t context)
{
    if (context != 0)
    {
        /* Context holds the flag's address */
        *((bool *) context) = true;
    }
}

USB_HOST_EVENT_RESPONSE APP_COORDINATOR_USBHostEventHandler 
(
    USB_HOST_EVENT event, 
    void * eventData,
    uintptr_t context
)
{
    /* The USB Host Layer uses this function to communicate events to the 
       application. In this example only the USB_HOST_EVENT_DEVICE_UNSUPPORTED
       event is handled. */

    switch (event)
    {
        case USB_HOST_EVENT_DEVICE_UNSUPPORTED:
            
            /* The attached device is not supported for some reason */
            break;
            
        case USB_HOST_EVENT_DEVICE_DETACHED:
            appCoordinatorData.deviceWasDetached = true;
            appCoordinatorData.readTransferDone = false;
            break;
            
        default:
            break;
                    
    }
    
    return(USB_HOST_EVENT_RESPONSE_NONE);
}

void APP_COORDINATOR_USBHostCDCAttachEventListener(USB_HOST_CDC_OBJ cdcObj, uintptr_t context)
{
    /* This function gets called when a CDC device is attached. Here, the data 
       structure of the application is modified to reflect the device's 
       attachment. */
    
    appCoordinatorData.deviceIsAttached = true;
    appCoordinatorData.cdcObj = cdcObj;
}


USB_HOST_CDC_EVENT_RESPONSE APP_COORDINATOR_USBHostCDCEventHandler
(
    USB_HOST_CDC_HANDLE cdcHandle,
    USB_HOST_CDC_EVENT event,
    void * eventData,
    uintptr_t context
)
{
    /* This function is called when a CDC Host event has occurred. A pointer to
     * this function is registered after opening the device. See the call to
     * USB_HOST_CDC_EventHandlerSet() function. */

    USB_HOST_CDC_EVENT_ACM_SET_LINE_CODING_COMPLETE_DATA * setLineCodingEventData;
    USB_HOST_CDC_EVENT_ACM_SET_CONTROL_LINE_STATE_COMPLETE_DATA * setControlLineStateEventData;
    USB_HOST_CDC_EVENT_WRITE_COMPLETE_DATA * writeCompleteEventData;
    USB_HOST_CDC_EVENT_READ_COMPLETE_DATA * readCompleteEventData;
    
    switch(event)
    {
        case USB_HOST_CDC_EVENT_ACM_SET_LINE_CODING_COMPLETE:
            
            /* This means the application requested Set Line Coding request is
             * complete. */
            setLineCodingEventData = (USB_HOST_CDC_EVENT_ACM_SET_LINE_CODING_COMPLETE_DATA *)(eventData);
            appCoordinatorData.controlRequestDone = true;
            appCoordinatorData.controlRequestResult = setLineCodingEventData->result;
            break;
            
        case USB_HOST_CDC_EVENT_ACM_SET_CONTROL_LINE_STATE_COMPLETE:
            
            /* This means the application requested Set Control Line State 
             * request has completed. */
            setControlLineStateEventData = (USB_HOST_CDC_EVENT_ACM_SET_CONTROL_LINE_STATE_COMPLETE_DATA *)(eventData);
            appCoordinatorData.controlRequestDone = true;
            appCoordinatorData.controlRequestResult = setControlLineStateEventData->result;
            break;
            
        case USB_HOST_CDC_EVENT_WRITE_COMPLETE:
            
            /* This means an application requested write has completed */
            appCoordinatorData.writeTransferDone = true;
            writeCompleteEventData = (USB_HOST_CDC_EVENT_WRITE_COMPLETE_DATA *)(eventData);
            appCoordinatorData.writeTransferResult = writeCompleteEventData->result;
            break;
            
        case USB_HOST_CDC_EVENT_READ_COMPLETE:
            
            /* This means an application requested read has completed */
            appCoordinatorData.readTransferDone = true;
            readCompleteEventData = (USB_HOST_CDC_EVENT_READ_COMPLETE_DATA *)(eventData);
            appCoordinatorData.readTransferResult = readCompleteEventData->result;
            appCoordinatorData.readTransferLength = readCompleteEventData->length;
            break;
            
        case USB_HOST_CDC_EVENT_DEVICE_DETACHED:
            /* The device was detached */
            appCoordinatorData.deviceWasDetached = true;
            appCoordinatorData.readTransferDone = false;
            
            /* Switch off LED  */
            //LED1_Off();
            break;
            
        default:
            break;
    }
    
    return(USB_HOST_CDC_EVENT_RESPONE_NONE);
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

#define SRV_USI_PROT_ID_USED SRV_USI_PROT_ID_PHY
#define USI_MESSAGE_LENGTH_MAX 256
#define USI_HEARTBEAT_COUNTER_MS 10000

/* TODO:  Add any necessary local functions.
*/

bool APP_COORDINATOR_Prepare2Send_Message(uint8_t index, uint8_t *buffer, uint16_t length, bool answerFlag)
{
    if (appCoordinatorData.freetransferFlag)
    {
        //Don't block this way - risk here
        //appCoordinatorData.freetransferFlag = false;
        appCoordinatorData.transferFlag = true;
        memcpy(appCoordinatorData.transferBuffer, buffer, length);
        appCoordinatorData.transferLength = length;
        appCoordinatorData.transferAnswerFlag = answerFlag;
        appCoordinatorData.transferAnswerOK = false;
        return true;
    }
    return false;
}

void APP_COORDINATOR_Send_Message(uint8_t *buffer, uint16_t length )
{   
    /* Send USI Message */
    SRV_USI_Send_Message(appCoordinatorData.srvUSIHandle, SRV_USI_PROT_ID_USED, (uint8_t *)buffer, length);
}

uint32_t APP_COORDINATOR_GetHeartbeatCount(void)
{
    return appCoordinatorData.heartbeatCounter;
}

uint8_t APP_COORDINATOR_deviceIndexByType(uint8_t type)
{
    return (uint8_t) (type - TYPE_LIGHTING_INDOOR);
}

uint8_t APP_COORDINATOR_deviceTypeByIndex(uint8_t index)
{
    return (uint8_t) (TYPE_LIGHTING_INDOOR + index);
}

bool APP_COORDINATOR_deviceInit ( void )
{

    if (isAppCoordInfoMutexCreated == false)
    {
        if(OSAL_MUTEX_Create(&(appCoordInfoMutex)) != OSAL_RESULT_SUCCESS)
        {
            return false;
        }
        else
        {
            isAppCoordInfoMutexCreated = true;
        }
    }
    
    for (int i=0; i<APP_COORDINATOR_MAX_DEVICES; i++)
    {
        appCoordinatorDeviceInfo[i].index = INDEX_TYPE_LIGHTING_INDOOR + i;
        appCoordinatorDeviceInfo[i].type = TYPE_LIGHTING_INDOOR + i;
        appCoordinatorDeviceInfo[i].alive = APP_COORDINATOR_DEVICE_STATE_OUT;
        appCoordinatorDeviceInfo[i].state = false;
    }
    return true;
}

bool APP_COORDINATOR_deviceDoSnapshot ( APP_COORDINATOR_DEVICE_INFO *device_info )
{
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP_COORD] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    for (uint8_t i=0; i<APP_COORDINATOR_MAX_DEVICES; i++)
    {
        memcpy(&device_info[i], &appCoordinatorDeviceInfo[i], sizeof(APP_COORDINATOR_DEVICE_INFO));
    }
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceSetState (uint8_t type, bool state)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP_COORD] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].state = state;
    //APP_COORDINATOR_notifyDeviceStateChange( type, state);
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceGetState (uint8_t type, bool *state)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP_COORD] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    *state = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].state;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceSetAlive (uint8_t type, uint8_t alive)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP_COORD] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].alive = alive;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

bool APP_COORDINATOR_deviceGetAlive (uint8_t type, uint8_t *alive)
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    
    if (OSAL_MUTEX_Lock(&appCoordInfoMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_FAIL)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP_COORD] - appCoordInfoMutex mutex lock FAILED\r\n");
        return false;
    }
    
    *alive = appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].alive;
    
    OSAL_MUTEX_Unlock(&appCoordInfoMutex);
    return true;
}

uint8_t APP_COORDINATOR_deviceGetStateSnapshot ( APP_COORDINATOR_DEVICE_INFO *device_info, uint8_t type )
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return 0xFF;
    return device_info[type - TYPE_LIGHTING_INDOOR].state;
}

uint8_t APP_COORDINATOR_deviceGetAliveSnapshot ( APP_COORDINATOR_DEVICE_INFO *device_info, uint8_t type )
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return false;
    return device_info[type - TYPE_LIGHTING_INDOOR].alive;
}

uint8_t APP_COORDINATOR_deviceGetIndexSnapshot ( APP_COORDINATOR_DEVICE_INFO *device_info, uint8_t type )
{
    if ((type < TYPE_LIGHTING_INDOOR) || (type > TYPE_PANEL_LED))
        return INDEX_UNKNOWN;
    return device_info[type - TYPE_LIGHTING_INDOOR].index;
}

void APP_COORDINATOR_deviceGetInfoSnapshot ( uint8_t type, uint8_t *index, uint8_t *alive, bool *state)
{
    APP_COORDINATOR_DEVICE_INFO device_info[APP_COORDINATOR_MAX_DEVICES];
    
    APP_COORDINATOR_deviceDoSnapshot(device_info);
    
    *index = APP_COORDINATOR_deviceGetIndexSnapshot(device_info, type);
    *alive = APP_COORDINATOR_deviceGetAliveSnapshot(device_info, type);
    *state = APP_COORDINATOR_deviceGetStateSnapshot(device_info, type);
    
}

void _APP_COORDINATOR_SetAlarmStatus(bool status)
{
    if (status != appCoordinatorData.alarmRegistered)
    {
        if (status)
            ALARM_LED_On();
        else
            ALARM_LED_Off();
    }
    appCoordinatorData.alarmRegistered = status;
}

bool APP_COORDINATOR_GetAlarmStatus(void)
{
    return appCoordinatorData.alarmRegistered;
}

void APP_COORDINATOR_handleEmergency ( uint32_t time_keep_alarm_ms )
{
    
    if (time_keep_alarm_ms != 0)
    {
        appCoordinatorData.remoteStatus |= APP_COORDINATOR_REMOTE_STATUS_EMERGENCY;
    
        // Probably Refresh information
        appCoordinatorData.alarmExpired = false;
        
        if (appCoordinatorData.alarmTimer == SYS_TIME_HANDLE_INVALID)
        {
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_COORD] - creating Alarm Timer %d msecs\r\n", time_keep_alarm_ms);
            // Create Timer to keep alarm notification                
            appCoordinatorData.alarmTimer = SYS_TIME_CallbackRegisterMS(APP_COORDINATOR_SYS_TIME_CallbackSetFlag,
                (uintptr_t) &appCoordinatorData.alarmExpired, time_keep_alarm_ms,
                SYS_TIME_SINGLE);
        }
        else
        {
            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_COORD] - refreshing Alarm Timer %d msecs\r\n", time_keep_alarm_ms);
            // Still on a alarm state
            SYS_TIME_TimerReload(appCoordinatorData.alarmTimer, 0, SYS_TIME_MSToCount(time_keep_alarm_ms),
                    APP_COORDINATOR_SYS_TIME_CallbackSetFlag, (uintptr_t) &appCoordinatorData.alarmExpired, SYS_TIME_SINGLE);
        }        
    }
    else
    {
        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_COORD] - Alarm expired\r\n");
        appCoordinatorData.alarmExpired = true;
    }
}

void APP_COORDINATOR_ProtocolEventHandler(uint8_t *pData, size_t length)
{   
    
    /* Protection for invalid length */
    if (!length)
    {
        LED1_Toggle();
        return;
    }

    SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_COORD]: Received USI message: 0x%02X, 0x%02X, 0x%02X\r\n", pData[0], pData[1], pData[2]);

    /* Process received command because nobody is waiting for this */
    uint8_t *pbuffer;
    uint8_t index;
    uint8_t type;
    uint8_t alive, alive_old;
    bool    state, state_old;
    uint8_t notif[2];
                
    pbuffer = pData;
    //pbuffer++; // USI Protocol ID removal
    //pbuffer++; // USI Frame Length removal
    switch (*pbuffer++)
    {
        // Commands from the host PIC32CZCA80
        case CMD_GET_DEVICES_ANSWER:
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_COORD]: Get Devices Answer\r\n");
            // ANSWER TO CMD_GET_DEVICES out of timing...
            
            if (!appCoordinatorData.transferFlag)    
            {           
                uint16_t numdevices;
                numdevices = *pbuffer++;
                if (numdevices)
                {
                    for (int i = 0; i< numdevices; i++)
                    {
                        index = *pbuffer++;
                        type = *pbuffer++;
                        alive = *pbuffer++;
                        state = *pbuffer++;
                        SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "0x%02X-0x%02X-0x%02X-%d\r\n",index, type, alive, state);
                    }               
                }
            }
            else
            {
                memcpy(appCoordinatorData.transferBuffer, pData, length);
                appCoordinatorData.transferLength = length;
                appCoordinatorData.transferAnswerOK = true;                
                SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_COORD]: Get Devices Answer on transfer\r\n");
            }
            break;
        }
        case CMD_DEVICE_NOTIFICATION:
        {
            // Device Notification from Coordinator...
            type = *pbuffer++;
            alive = *pbuffer++;
            state = *pbuffer++;
            APP_COORDINATOR_deviceGetAlive(type, &alive_old);
            APP_COORDINATOR_deviceGetState(type, &state_old);
            if (alive != alive_old)
            {
                notif[0] = type;
                notif[1] = (alive & APP_COORDINATOR_DEVICE_STATE_ALIVE)? 1 : 0;
                // Update information before notify
                APP_COORDINATOR_deviceSetAlive(type, alive);
                if (alive == APP_COORDINATOR_DEVICE_STATE_OUT)
                {
                    APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_OUT_NOTIFY, (void *)notif, 1);
                }
                else if (alive & APP_COORDINATOR_DEVICE_STATE_JOINED)
                {
                    if (alive & APP_COORDINATOR_DEVICE_STATE_ALIVE)
                    {
                        APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_ALIVE_NOTIFY, (void *)notif, 2);
                    }
                    else
                    {
                        APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_JOINED_NOTIFY, (void *)notif, 1);
                    }
                }
            }
            if (state != state_old) 
            {
                notif[0] = type;
                notif[1] = state;
                APP_COORDINATOR_deviceSetState(type, state);
                APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_STATE_NOTIFY, (void *)notif, 2);
            }
            
            SYS_DEBUG_PRINT(SYS_ERROR_INFO, "[APP_COORD]: Device Notification: 0x%02X - %d - %d\r\n", type, alive, state);

            break;
        }
        case CMD_RESET_NOTIFICATION:
        {
            // First Command sent by Coordinator after start-up
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD]: Coordinator Reset\r\n");
            appCoordinatorData.remoteStatus = APP_COORDINATOR_REMOTE_STATUS_RESET;
            // Initialize access to devices
            APP_COORDINATOR_deviceInit();
            if (appCoordinatorData.timer != SYS_TIME_HANDLE_INVALID)
            {
                SYS_TIME_TimerDestroy(appCoordinatorData.timer);
                appCoordinatorData.timerExpired = true;
            }
            appCoordinatorData.heartbeatCounter = 0;
            // Notify event
            APP_COORDINATOR_Notify(APP_COORDINATOR_RESET_NOTIFY, NULL, 0);
            break;
        }
        case CMD_HEARTBEAT:
        {
            // Heartbeat from Coordinator to Host
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD]: Coordinator Heartbeat\r\n");
            appCoordinatorData.remoteStatus |= APP_COORDINATOR_REMOTE_STATUS_READY;            
            // Notify event
            appCoordinatorData.heartbeatCounter++;
            APP_COORDINATOR_Notify(APP_COORDINATOR_HEARTBEAT_NOTIFY, &appCoordinatorData.heartbeatCounter, 4);
            break;
        }
        case CMD_EMERGENCY:
        {
            // Emergency Button from Coordinator to Host
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD]: Coordinator Emergency\r\n");
            APP_COORDINATOR_handleEmergency(APP_COORDINATOR_TIME_KEEP_ALARM_MS);
            break;
        }
        default:
            break;
    }   
}

/* TODO:  Add any necessary local functions.
*/                        

#define SERIALIZATION_BUFFER_SIZE 1024
uint8_t serializationBufferRx[SERIALIZATION_BUFFER_SIZE];
uint8_t serializationBufferTx[SERIALIZATION_BUFFER_SIZE];
uint16_t indexBufferRx = 0;
uint16_t indexBufferTx = 0;

#define COORD_PREFIX_MSG "[COORD][MSG] - "                    
#define COORD_PREFIX_CMD "[COORD][CMD] - "
#define SPECIAL_BYTE_DELIMITER '#'
#define CONSOLE_FRAME '$'
#define COMMAND_FRAME '%'


void APP_COORDINATOR_SetCoordinatorCmdCallback(APP_COORDINATOR_CMD_CALLBACK callback)
{
    appCoordinatorData.cmdCallback = callback;
}

int sendcmd_to_coordinator(const char *data, uint16_t size)
{  
    if ((indexBufferTx + size) < SERIALIZATION_BUFFER_SIZE)
    {
        memcpy(&serializationBufferTx[indexBufferTx], data, size);
        indexBufferTx+=size;
        return 0;
    }
    return -1;
}

int coordinator_parsing(uint8_t *data, uint16_t size)
{
    int16_t i;
    static bool flag_start = false;
    
    for (i=0; i<size; i++)
    {
        if (data[i] == SPECIAL_BYTE_DELIMITER)
        {
            if (indexBufferRx >= 4)
            {
                // Message End - Received Message 
                serializationBufferRx[indexBufferRx++] = '\0';
                // Decode Frame                
                if (serializationBufferRx[0] == CONSOLE_FRAME)
                {
                    // Message from console
                    SYS_CONSOLE_Message(sysObj.sysConsole0, COORD_PREFIX_MSG);
                    SYS_CONSOLE_Message(sysObj.sysConsole0, (const char *) &serializationBufferRx[1]);
                }else if (serializationBufferRx[0] == COMMAND_FRAME) {
                    /* Command Type == PRINT */
                    //SYS_CONSOLE_Print(sysObj.sysConsole0, "Cmd Type: %c", serializationBufferRx[0]);
                    if (serializationBufferRx[1] == 'P')
                    {
                        /* Command Type == PRINT */
                        SYS_CONSOLE_Message(sysObj.sysConsole0, COORD_PREFIX_CMD);
                        SYS_CONSOLE_Message(sysObj.sysConsole0, (const char *) &serializationBufferRx[1]);
                    //}else {
                        /* Command Type == INFORMATION */
                    //    appCoordinatorData.pCoordinatorCmdCallback(&serializationBufferRx[1]);
                    }
                }else {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "synch failed\r\n");
                }
                indexBufferRx=0;
                flag_start = false;
            }
            else
            {
                // Message Start
                flag_start = true;
            }
        } else {
            if (flag_start)
            {
                serializationBufferRx[indexBufferRx++] = data[i];
            }
        }           
    }   
    
    return 0;
}

/*******************************************************************************
  Function:
    Timer in milliseconds for creating and waiting the delay.
 */

static bool APP_COORDINATOR_TaskDelay(uint32_t ms, SYS_TIME_HANDLE* handle)
{
    // Check if there is the timer has been created and running
    if (*handle == SYS_TIME_HANDLE_INVALID)
    {
        // Create timer
        if (SYS_TIME_DelayMS(ms, handle) != SYS_TIME_SUCCESS)
        {
            return false;
        }
    }
    else
    {
        // Check timer
        if (SYS_TIME_DelayIsComplete(*handle) == true)
        {
            *handle = SYS_TIME_HANDLE_INVALID;
            return true;
        }
    }

    return false;
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_COORDINATOR_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_COORDINATOR_usiInit ( void )
{
    appCoordinatorData.transferState = APP_COORDINATOR_TRANSFER_STATE_WAIT;
    appCoordinatorData.availableBuffers = true;
    appCoordinatorData.transferAnswerFlag = false;
    appCoordinatorData.transferTimeExpired = false;
    appCoordinatorData.transferAnswerOK = false;
    appCoordinatorData.transferFlag = false;
    appCoordinatorData.transferTimeout_ms = 5000;
    appCoordinatorData.freetransferFlag = true;
    
    _APP_COORDINATOR_InitCmdsQueue();
}

/******************************************************************************
  Function:
    void APP_COORDINATOR_usiTasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_COORDINATOR_usiTasks ( void )
{
    switch (appCoordinatorData.transferState)
    {
        case APP_COORDINATOR_TRANSFER_STATE_WAIT:
            if (appCoordinatorData.transferFlag)
            {
                /* Someone wants to transmit */
                appCoordinatorData.transferState = APP_COORDINATOR_TRANSFER_STATE_SEND_DATA;
            }
            break;
            
        case APP_COORDINATOR_TRANSFER_STATE_SEND_DATA:
            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_COORD]: SEND USI PACKET\r\n");
            APP_COORDINATOR_Send_Message(appCoordinatorData.transferBuffer, appCoordinatorData.transferLength);
            if (appCoordinatorData.transferAnswerFlag)
            {
                /* Create timer for timeout to detect UDP reply not received */
                appCoordinatorData.transferTimeExpired = false;
                appCoordinatorData.transferTimeHandle = SYS_TIME_CallbackRegisterMS(APP_COORDINATOR_SYS_TIME_CallbackSetFlag,
                (uintptr_t) &appCoordinatorData.transferTimeExpired , appCoordinatorData.transferTimeout_ms, SYS_TIME_SINGLE);
                appCoordinatorData.transferState = APP_COORDINATOR_TRANSFER_STATE_WAIT_DATA;
            }
            else
            {
                appCoordinatorData.transferTimeExpired = true;
                appCoordinatorData.transferAnswerOK = true;
                appCoordinatorData.transferState = APP_COORDINATOR_TRANSFER_STATE_WAIT;
                /* For the next transfer */
                appCoordinatorData.transferFlag = false;
            }
            break; 

        case APP_COORDINATOR_TRANSFER_STATE_WAIT_DATA:
        {
            if (appCoordinatorData.transferTimeExpired == true)
            {
                /* Reply not received */
                appCoordinatorData.transferAnswerOK = false;
                SYS_DEBUG_PRINT(SYS_ERROR_ERROR, "[APP_COORD]: reply not received from coordinator\r\n");

                /* Free Transfer State */
                appCoordinatorData.transferFlag = false;
                appCoordinatorData.transferState = APP_COORDINATOR_TRANSFER_STATE_WAIT;
                break;
            }

            /* Check if received answer  */
            if (!appCoordinatorData.transferAnswerOK)
            {                
                break;
            }

            SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, "[APP_COORD]: reply received from coordinator\r\n");
            
            appCoordinatorData.transferTimeExpired = true;
            SYS_TIME_TimerDestroy(appCoordinatorData.transferTimeHandle);
            appCoordinatorData.transferFlag = false;
            appCoordinatorData.transferState = APP_COORDINATOR_TRANSFER_STATE_WAIT;            

            break;
        }    
        default:
            break;
    }    
}



void APP_COORDINATOR_Initialize ( void )
{
    
    /* RELATED TO USB HOST */
    /* Initialize the application state machine */
    
    appCoordinatorData.state =  APP_COORDINATOR_STATE_BUS_ENABLE;
    appCoordinatorData.state =  APP_COORDINATOR_STATE_USI_INIT;
    appCoordinatorData.cdcHostLineCoding.dwDTERate     = APP_COORDINATOR_HOST_CDC_BAUDRATE_SUPPORTED;
    appCoordinatorData.cdcHostLineCoding.bDataBits     = (uint8_t)APP_COORDINATOR_HOST_CDC_NO_OF_DATA_BITS;
    appCoordinatorData.cdcHostLineCoding.bParityType   = (uint8_t)APP_COORDINATOR_HOST_CDC_PARITY_TYPE;
    appCoordinatorData.cdcHostLineCoding.bCharFormat   = (uint8_t)APP_COORDINATOR_HOST_CDC_STOP_BITS;
    appCoordinatorData.controlLineState.dtr = 1;
    appCoordinatorData.controlLineState.carrier = 1;
    appCoordinatorData.deviceIsAttached = false;
    appCoordinatorData.deviceWasDetached = false;
    appCoordinatorData.readTransferDone = false;
    appCoordinatorData.writeTransferDone = false;
    appCoordinatorData.controlRequestDone = false;
    appCoordinatorData.timer = SYS_TIME_HANDLE_INVALID;
    appCoordinatorData.timerTimeout_ms = APP_COORDINATOR_TIME_DEVICE_GET_REQ_INIT_MS;
    appCoordinatorData.timerExpired = false;
    appCoordinatorData.alarmTimer = SYS_TIME_HANDLE_INVALID;
    appCoordinatorData.alarmExpired = false;   // Send it at the beginning
    appCoordinatorData.alarmRegistered = false;
    appCoordinatorData.heartbeatCounter = 0;
    appCoordinatorData.remoteStatus = APP_COORDINATOR_REMOTE_STATUS_INIT;
    
    indexBufferRx = 0;
    memset(serializationBufferRx,'\0',SERIALIZATION_BUFFER_SIZE);
    indexBufferTx = 0;
    memset(serializationBufferTx,'\0',SERIALIZATION_BUFFER_SIZE);
    
    SYS_DEBUG_ErrorLevelSet(SYS_ERROR_INFO);
       
    memset(appCoordinatorData.notifCallbacks, 0, sizeof(APP_COORDINATOR_NOTIF_CALLBACK) * APP_COORDINATOR_NOTIF_CALLBACK_COUNT);
       
    USB1_DRD_Set();
    
    USB_HOST_PWR_OutputEnable();
    USB_HOST_PWR_Clear();
    
    /* RELATED TO TRANSFER */
    APP_COORDINATOR_usiInit();
    
    /* RELATED TO DEVICE INFO */
    APP_COORDINATOR_deviceInit();
    
    /* LEDs */
    // Alarm
    ALARM_LED_OutputEnable();
    ALARM_LED_Off();
        
    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - Init\r\n");
}

/******************************************************************************
  Function:
    void APP_COORDINATOR_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_COORDINATOR_Tasks ( void )
{
    /* Check the application's current state. */
   USB_HOST_CDC_RESULT result;
   
   if (appCoordinatorData.deviceWasDetached)
   {
       /* This means the device is not attached. Reset the application state */

       appCoordinatorData.state = APP_COORDINATOR_STATE_WAIT_FOR_DEVICE_ATTACH;
       appCoordinatorData.readTransferDone = false;
       appCoordinatorData.writeTransferDone = false;
       appCoordinatorData.controlRequestDone = false;
       appCoordinatorData.deviceWasDetached = false;
   }


   APP_COORDINATOR_usiTasks();

    switch (appCoordinatorData.state)
    {
        case APP_COORDINATOR_STATE_BUS_ENABLE:

            /* In this state, the application enables the USB Host Bus. Note how
               the CDC Attach event handler is registered before the bus is 
               enabled. */

            USB_HOST_EventHandlerSet(APP_COORDINATOR_USBHostEventHandler, (uintptr_t)0);
            USB_HOST_CDC_AttachEventHandlerSet(APP_COORDINATOR_USBHostCDCAttachEventListener, (uintptr_t) 0);
            USB_HOST_BusEnable(USB_HOST_BUS_ALL);
            /* Wait for a while */
            appCoordinatorData.nextState = APP_COORDINATOR_STATE_WAIT_FOR_BUS_ENABLE_COMPLETE;
            appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
            appCoordinatorData.delayMs = 1;
            break;
        
        case APP_COORDINATOR_STATE_WAIT_FOR_BUS_ENABLE_COMPLETE:

            /* In this state, the application is waiting for the Bus enable to 
               complete. */
            if(USB_HOST_BusIsEnabled(USB_HOST_BUS_ALL))
            {
                /* Wait for a while */
                appCoordinatorData.nextState = APP_COORDINATOR_STATE_WAIT_FOR_DEVICE_ATTACH;
                appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                appCoordinatorData.delayMs = 1;
            }
            break;

        case APP_COORDINATOR_STATE_WAIT_FOR_DEVICE_ATTACH:

            /* In this state, the application is waiting for the device to be
               attached. */
            if(appCoordinatorData.deviceIsAttached)
            {
                /* A CDC device is attached. We can open this device */
                appCoordinatorData.deviceIsAttached = false;
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - Attached USB CDC Device\r\n");
                /* Wait for a while */
                appCoordinatorData.nextState = APP_COORDINATOR_STATE_OPEN_DEVICE;
                appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                appCoordinatorData.delayMs = 1;
            }
            break;

        case APP_COORDINATOR_STATE_OPEN_DEVICE:

            /* In this state, the application opens the attached device */
            appCoordinatorData.cdcHostHandle = USB_HOST_CDC_Open(appCoordinatorData.cdcObj);
            if(appCoordinatorData.cdcHostHandle != USB_HOST_CDC_HANDLE_INVALID)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - Opened USB CDC Device\r\n");
                /* The CDC Device was opened successfully. Set the event handler
                 * and then go to the next state. */
                USB_HOST_CDC_EventHandlerSet(appCoordinatorData.cdcHostHandle, APP_COORDINATOR_USBHostCDCEventHandler, (uintptr_t)0);
                appCoordinatorData.nextState = APP_COORDINATOR_STATE_SET_LINE_CODING;
                appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                appCoordinatorData.delayMs = 1;
            }
            break;

        case APP_COORDINATOR_STATE_SET_LINE_CODING:

            /* Here we set the Line coding. The control request done flag will
             * be set to true when the control request has completed. */

            appCoordinatorData.controlRequestDone = false;
            result = USB_HOST_CDC_ACM_LineCodingSet(appCoordinatorData.cdcHostHandle, NULL, &appCoordinatorData.cdcHostLineCoding);
            
            if(result == USB_HOST_CDC_RESULT_SUCCESS)
            {
                /* We wait for the set line coding to complete */
                appCoordinatorData.nextState = APP_COORDINATOR_STATE_WAIT_FOR_SET_LINE_CODING;
                appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                appCoordinatorData.delayMs = 1;
            }

            break;

        case APP_COORDINATOR_STATE_WAIT_FOR_SET_LINE_CODING:

            if(appCoordinatorData.controlRequestDone)
            {
                if(appCoordinatorData.controlRequestResult != USB_HOST_CDC_RESULT_SUCCESS)
                {
                    /* The control request was not successful. */
                    appCoordinatorData.state = APP_COORDINATOR_STATE_ERROR;
                }
                else
                {
                    /* Next we set the Control Line State */
                    appCoordinatorData.nextState = APP_COORDINATOR_STATE_SEND_SET_CONTROL_LINE_STATE;
                    appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                    appCoordinatorData.delayMs = 1;
                }
            }
            break;

        case APP_COORDINATOR_STATE_SEND_SET_CONTROL_LINE_STATE:

            /* Here we set the control line state */
            appCoordinatorData.controlRequestDone = false;
            result = USB_HOST_CDC_ACM_ControlLineStateSet(appCoordinatorData.cdcHostHandle, NULL, 
                    &appCoordinatorData.controlLineState);

            if(result == USB_HOST_CDC_RESULT_SUCCESS)
            {
                /* We wait for the set line coding to complete */
                appCoordinatorData.nextState = APP_COORDINATOR_STATE_WAIT_FOR_SET_CONTROL_LINE_STATE;
                appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                appCoordinatorData.delayMs = 1;
            }

            break;

        case APP_COORDINATOR_STATE_WAIT_FOR_SET_CONTROL_LINE_STATE:

            /* Here, we wait for the control line state set request to complete */
            if(appCoordinatorData.controlRequestDone)
            {
                if(appCoordinatorData.controlRequestResult != USB_HOST_CDC_RESULT_SUCCESS)
                {
                    /* The control request was not successful. */
                    appCoordinatorData.state = APP_COORDINATOR_STATE_ERROR;
                }
                else
                {
                    /* Turn ON LED to indicate the device is attached and ready 
                       for data transfer. */
                    //LED1_On();

                    /* Now, the application will send an "LED ON" message to the
                       CDC Device. Fill the buffer here. */
                    //appCoordinatorData.cdcWriteSize = sizeof(ledon);
                    //appCoordinatorData.cdcWriteData = ledon;
#define CMD_ENTER "CMDMODE Remote\r\n"
                    sendcmd_to_coordinator(CMD_ENTER,strlen(CMD_ENTER)+1);
                    appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                    appCoordinatorData.delayMs = 5000;
                    //appCoordinatorData.nextState = APP_COORDINATOR_STATE_GET_DATA_FROM_DEVICE ; //APP_COORDINATOR_STATE_SEND_PROMPT_TO_DEVICE;
                    appCoordinatorData.nextState = APP_COORDINATOR_STATE_DELAY;
                }
            }

            break;

        case APP_COORDINATOR_STATE_SEND_PROMPT_TO_DEVICE:

            /* The prompt is sent to the device here. The write transfer done
             * flag is updated in the event handler. */

            appCoordinatorData.writeTransferDone = false;
            appCoordinatorData.cdcWriteData = serializationBufferTx;
            appCoordinatorData.cdcWriteSize = indexBufferTx;
            result = USB_HOST_CDC_Write(appCoordinatorData.cdcHostHandle, NULL, ( void *)appCoordinatorData.cdcWriteData, appCoordinatorData.cdcWriteSize);
            if(result == USB_HOST_CDC_RESULT_SUCCESS)
            {
                appCoordinatorData.state = APP_COORDINATOR_STATE_WAIT_FOR_PROMPT_SEND_COMPLETE;
                appCoordinatorData.delayMs = 1000;
            }
            else
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Error writting CDC\r\n");
            }
            break;

        case APP_COORDINATOR_STATE_WAIT_FOR_PROMPT_SEND_COMPLETE:

            /* Here we check if the write transfer is done. */
            if(appCoordinatorData.writeTransferDone)
            {
                if(appCoordinatorData.writeTransferResult == USB_HOST_CDC_RESULT_SUCCESS)
                {
                    indexBufferTx = 0;
                    /* Now to get data from the device */
                    appCoordinatorData.state = APP_COORDINATOR_STATE_GET_DATA_FROM_DEVICE;
                    appCoordinatorData.timer = SYS_TIME_HANDLE_INVALID;
                }
                else
                {
                    /* Try sending the prompt again. */
                    appCoordinatorData.state = APP_COORDINATOR_STATE_SEND_PROMPT_TO_DEVICE;
                }
            }
            else
            {
                // Wait delay time
                if (APP_COORDINATOR_TaskDelay(appCoordinatorData.delayMs, &appCoordinatorData.timer))
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Write USB CDC timeout\r\n");
                    appCoordinatorData.state = APP_COORDINATOR_STATE_SEND_PROMPT_TO_DEVICE;
                }
            }

            break;

        case APP_COORDINATOR_STATE_GET_DATA_FROM_DEVICE:
            /* Here we request data from the device */
            appCoordinatorData.readTransferDone = false;
            appCoordinatorData.readTransferLength = 0;
            USB_HOST_CDC_TRANSFER_HANDLE transferHandle;
            result = USB_HOST_CDC_Read(appCoordinatorData.cdcHostHandle, &transferHandle, appCoordinatorData.inDataArray, 16);
            if(result == USB_HOST_CDC_RESULT_SUCCESS)
            {
                appCoordinatorData.delayMs = 5000;                
                appCoordinatorData.state = APP_COORDINATOR_STATE_WAIT_FOR_DATA_FROM_DEVICE;
            }
            else
            {
                if (result == USB_HOST_CDC_RESULT_BUSY)
                {
                    appCoordinatorData.delayMs = 5000;                
                    appCoordinatorData.nextState = APP_COORDINATOR_STATE_GET_DATA_FROM_DEVICE;
                    appCoordinatorData.state = APP_COORDINATOR_STATE_DELAY;
                }
                else
                {
                    SYS_DEBUG_PRINT(SYS_ERROR_INFO, "Error reading CDC: 0x%02X\r\n",(uint8_t) result);
                }
            }
            break;

        case APP_COORDINATOR_STATE_WAIT_FOR_DATA_FROM_DEVICE:

            /* Wait for data from device. If the data has arrived, then toggle
             * the LED. */
            if(appCoordinatorData.readTransferDone)
            {
                if(appCoordinatorData.readTransferResult == USB_HOST_CDC_RESULT_SUCCESS)
                {
                    appCoordinatorData.timer = SYS_TIME_HANDLE_INVALID;

                    if ( appCoordinatorData.readTransferLength > 0 )
                    {
                        SYS_DEBUG_PRINT(SYS_ERROR_INFO, "Reading CDC %d bytes\r\n", appCoordinatorData.readTransferLength);
                        coordinator_parsing(appCoordinatorData.inDataArray, appCoordinatorData.readTransferLength);
                        memset(appCoordinatorData.inDataArray,'\0', appCoordinatorData.readTransferLength);
                        /* Switch on LED   */
                        //LED1_Off();

                        /* Fill the buffer. */
                        //appCoordinatorData.cdcWriteSize = sizeof(ledon);
                        //appCoordinatorData.cdcWriteData = ledon;
                        //sendcmd_to_coordinator("\n",1);
                    }
                    else
                    {
                        /* Switch off LED  */
                        //LED1_On();

                        /* Fill the buffer. */
                        //appCoordinatorData.cdcWriteSize = sizeof(ledoff);
                        //appCoordinatorData.cdcWriteData = ledoff;

                    }

                    /* Send the prompt to the device and wait
                     * for data again */
                    appCoordinatorData.state = APP_COORDINATOR_STATE_SEND_PROMPT_TO_DEVICE;
                }
            }
            else
            {
                // Wait delay time
                if (APP_COORDINATOR_TaskDelay(appCoordinatorData.delayMs, &appCoordinatorData.timer))
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Read USB CDC timeout\r\n");
                    appCoordinatorData.state = APP_COORDINATOR_STATE_SEND_PROMPT_TO_DEVICE;
                }
            }
            break;

// STATES related with USI HOST into SERCOM8 - Serial Port

        case APP_COORDINATOR_STATE_USI_INIT:
        {   /* Application's initial state. */
            /* Open USI Service */
            appCoordinatorData.srvUSIHandle = SRV_USI_Open(SRV_USI_INDEX_0);

            if (appCoordinatorData.srvUSIHandle != DRV_HANDLE_INVALID)
            {
                /* Set Application to next state */
                appCoordinatorData.state = APP_COORDINATOR_STATE_USI_CONFIG;
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - USI Opened\r\n");
            }
            else
            {
                /* Set Application to ERROR state */
                appCoordinatorData.state = APP_COORDINATOR_STATE_ERROR;
            }
            break;
        }

        case APP_COORDINATOR_STATE_USI_CONFIG:
        {
            if (SRV_USI_Status(appCoordinatorData.srvUSIHandle) == SRV_USI_STATUS_CONFIGURED)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - USI Configured\r\n");
                /* Register USI callback */
                SRV_USI_CallbackRegister(appCoordinatorData.srvUSIHandle,
                        SRV_USI_PROT_ID_USED, APP_COORDINATOR_ProtocolEventHandler);

                /* Set Application to next state */
                appCoordinatorData.state = APP_COORDINATOR_STATE_USI_READY;
            }
            break;
        }

        case APP_COORDINATOR_STATE_USI_READY:
        {
            /* Check USI status in case of USI device has been reset */
            if (SRV_USI_Status(appCoordinatorData.srvUSIHandle) == SRV_USI_STATUS_NOT_CONFIGURED)
            {
                /* Set Application to next state */
                appCoordinatorData.state = APP_COORDINATOR_STATE_USI_CONFIG;
            }
            else
            {
                if (appCoordinatorData.remoteStatus & APP_COORDINATOR_REMOTE_STATUS_READY)
                {
                    /* Waiting for device information */
                    appCoordinatorData.state = APP_COORDINATOR_STATE_USI_GET_DEVICES;
                    if (appCoordinatorData.timer != SYS_TIME_HANDLE_INVALID)
                    {
                        SYS_TIME_TimerDestroy(appCoordinatorData.timer);
                    }
                    appCoordinatorData.timerExpired = false;
                    appCoordinatorData.timer = SYS_TIME_CallbackRegisterMS(APP_COORDINATOR_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &appCoordinatorData.timerExpired, appCoordinatorData.timerTimeout_ms, SYS_TIME_SINGLE);
                }
            }
            break;
        }

        case APP_COORDINATOR_STATE_USI_GET_DEVICES:
        {
            // Most prioritary, Emergency Messages
            if (appCoordinatorData.remoteStatus & APP_COORDINATOR_REMOTE_STATUS_EMERGENCY)
            {
                if (appCoordinatorData.alarmExpired)
                {
                    appCoordinatorData.alarmExpired = false;
                    _APP_COORDINATOR_SetAlarmStatus(false);
                    // Remove Alarm Timer
                    if (appCoordinatorData.alarmTimer != SYS_TIME_HANDLE_INVALID)
                    {
                        SYS_TIME_TimerDestroy(appCoordinatorData.alarmTimer);
                        appCoordinatorData.alarmTimer = SYS_TIME_HANDLE_INVALID;                 
                    }
                    // Remove Alarm Cmd Timer
                    if (appCoordinatorData.alarmCmdTimer != SYS_TIME_HANDLE_INVALID)
                    {
                        SYS_TIME_TimerDestroy(appCoordinatorData.alarmCmdTimer);
                        appCoordinatorData.alarmCmdTimer = SYS_TIME_HANDLE_INVALID;                 
                    }
                    bool state = false;
                    APP_COORDINATOR_Notify(APP_COORDINATOR_ALARM_NOTIFY, &state, 1);
                    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - Alarm Notification ends\r\n");
                    appCoordinatorData.remoteStatus &= ~APP_COORDINATOR_REMOTE_STATUS_EMERGENCY;
                }
                else
                {                    
                    if (!APP_COORDINATOR_GetAlarmStatus())
                    {
                        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - registering Alarm\r\n");
                        /* Register Alarm */
                        _APP_COORDINATOR_SetAlarmStatus(true);
                        /* Send Emergency Command */
                        appCoordinatorData.state = APP_COORDINATOR_STATE_USI_SEND_CMD_EMERGENCY;
                        // Notify event
                        bool state = true;
                        APP_COORDINATOR_Notify(APP_COORDINATOR_ALARM_NOTIFY, &state, 1);
                        // Register Timer each second to send CMD_EMERGENCY 
                        if (appCoordinatorData.alarmCmdTimer != SYS_TIME_HANDLE_INVALID)
                        {
                            SYS_TIME_TimerDestroy(appCoordinatorData.alarmCmdTimer);
                            appCoordinatorData.alarmCmdTimer = SYS_TIME_HANDLE_INVALID;
                        }
                        appCoordinatorData.alarmCmdExpired = false;
                        appCoordinatorData.alarmCmdTimer = SYS_TIME_CallbackRegisterMS(APP_COORDINATOR_SYS_TIME_CallbackSetFlag,
                        (uintptr_t) &appCoordinatorData.alarmCmdExpired, APP_COORDINATOR_TIME_BTW_ALARM_CMDS_MS, SYS_TIME_PERIODIC);
                        break;
                    } 
                    else
                    {
                        if (appCoordinatorData.alarmCmdExpired)
                        {
                            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - Alarm CMD expired\r\n");                            
                            /* No alarmExpired, send CMD_EMERGENCY */
                            appCoordinatorData.state = APP_COORDINATOR_STATE_USI_SEND_CMD_EMERGENCY;
                            /* Reload */
                            appCoordinatorData.alarmCmdExpired = false;
                            break;
                        }
                    }
                }
            }
            if ((appCoordinatorData.freetransferFlag) && (!appCoordinatorData.transferFlag))
            {
                // Next Cmds from Queue
                APP_COORDINATOR_CMDS_QUEUE_DATA cmd;
                if (_APP_COORDINATOR_PopCoordCmdsQueue(&cmd))
                {
                    appCoordinatorData.freetransferFlag = false;
                    appCoordinatorData.transferFlag = true;
                    memcpy(&appCoordinatorData.transferBuffer, &cmd.data, cmd.length);
                    appCoordinatorData.transferLength = cmd.length;                    
                    appCoordinatorData.transferAnswerFlag = false;
                    appCoordinatorData.transferAnswerOK = true;
                    appCoordinatorData.state = APP_COORDINATOR_STATE_USI_WAIT_SENT_CMD;
                }else if (appCoordinatorData.timerExpired) 
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_COORD] - Get Devices Answer Request\r\n");
                    appCoordinatorData.timerExpired = false;
                    appCoordinatorData.timerTimeout_ms = APP_COORDINATOR_TIME_DEVICE_GET_REQ_MS;
                    appCoordinatorData.freetransferFlag = false;
                    appCoordinatorData.transferFlag = true;
                    appCoordinatorData.transferBuffer[0] = CMD_GET_DEVICES;
                    appCoordinatorData.transferLength = 1;
                    appCoordinatorData.transferAnswerFlag = true;
                    appCoordinatorData.transferAnswerOK = false;
                    appCoordinatorData.state = APP_COORDINATOR_STATE_USI_GET_DEVICES_ANSWER;
                }else {
                    // Nothing to send
                }
            }
            break;
        }

        case APP_COORDINATOR_STATE_USI_GET_DEVICES_ANSWER:
        {
            if (!appCoordinatorData.transferFlag)
            {
                if (appCoordinatorData.transferAnswerOK)
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG, "[APP_COORD] - Get Devices Answer OK\r\n");

                    uint16_t numdevices;
                    uint8_t index;
                    uint8_t type;
                    uint8_t alive, alive_old;
                    bool    state, state_old;
                    uint8_t *pbuffer;
                    uint8_t notif[2];

                    pbuffer = appCoordinatorData.transferBuffer;
                    // First Byte is the command itself
                    if (*pbuffer++ == CMD_GET_DEVICES_ANSWER)
                    {                                                
                        numdevices = *pbuffer++;
                        if (numdevices)
                        {
                            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG,"Index Type Alive State\r\n");
                            SYS_DEBUG_MESSAGE(SYS_ERROR_DEBUG,"----- ---- ----- -----\r\n");
                            for (int i = 0; i< numdevices; i++)
                            {
                                index = *pbuffer++;
                                type = *pbuffer++;
                                alive = *pbuffer++;
                                state = *pbuffer++;
                                APP_COORDINATOR_deviceGetAlive(type, &alive_old);
                                APP_COORDINATOR_deviceGetState(type, &state_old);
                                SYS_DEBUG_PRINT(SYS_ERROR_DEBUG, " 0x%02X 0x%02X 0x%02X(old=0x%02X)  0x%02X(old=0x%02X)\r\n", index, type, alive, alive_old, state, state_old);
                                appCoordinatorDeviceInfo[type - TYPE_LIGHTING_INDOOR].index = index;
                                if (alive != alive_old)
                                {
                                    notif[0] = type;
                                    notif[1] = (alive & APP_COORDINATOR_DEVICE_STATE_ALIVE)? 1 : 0;
                                    APP_COORDINATOR_deviceSetAlive(type, alive);
                                    if (alive == APP_COORDINATOR_DEVICE_STATE_OUT)
                                    {
                                        APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_OUT_NOTIFY, (void *)notif, 1);
                                    }
                                    else if (alive & APP_COORDINATOR_DEVICE_STATE_JOINED)
                                    {
                                        if (alive & APP_COORDINATOR_DEVICE_STATE_ALIVE)
                                        {
                                            APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_ALIVE_NOTIFY, (void *)notif, 2);
                                        }
                                        else
                                        {
                                            APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_JOINED_NOTIFY, (void *)notif, 1);
                                        }
                                    }
                                }                                    
                                if (state != state_old)
                                {
                                    //Notify the Screen and Dashboard
                                    notif[0] = type;
                                    notif[1] = state;
                                    APP_COORDINATOR_deviceSetState(type, state);
                                    APP_COORDINATOR_Notify(APP_COORDINATOR_DEVICE_STATE_NOTIFY, (void *)&notif, 2);
                                }                                
                            }
                        }
                    }
                }
                else
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "[APP_COORD] - Get Devices Answer FAILED\r\n");
                }
                /* Free transfer flag */
                appCoordinatorData.freetransferFlag = true;
                appCoordinatorData.state = APP_COORDINATOR_STATE_USI_READY;
                break;
            }
            break;
        }
        case APP_COORDINATOR_STATE_USI_SEND_CMD_EMERGENCY:
        {
            if ((appCoordinatorData.freetransferFlag) && (!appCoordinatorData.transferFlag))
            {
                uint8_t index;
                uint8_t alive;
                bool state;
                APP_COORDINATOR_deviceGetInfoSnapshot(TYPE_PANEL_LED, &index, &alive, &state);    
                if ((index != INDEX_UNKNOWN) && (alive))
                {
                    appCoordinatorData.freetransferFlag = false;
                    appCoordinatorData.transferFlag = true;
                    appCoordinatorData.transferBuffer[0] = CMD_SET_PANEL_LED;
                    appCoordinatorData.transferBuffer[1] = index;
                    appCoordinatorData.transferBuffer[2] = 1; /* Alarm */
                    appCoordinatorData.transferLength = 3;
                    appCoordinatorData.transferAnswerFlag = false;
                    appCoordinatorData.transferAnswerOK = false;
                    appCoordinatorData.state = APP_COORDINATOR_STATE_USI_WAIT_SENT_CMD;
                }
                else
                {
                    /* Free transfer flag */
                    appCoordinatorData.transferFlag = false;
                    appCoordinatorData.freetransferFlag = true;
                    appCoordinatorData.state = APP_COORDINATOR_STATE_USI_GET_DEVICES;
                    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "[APP_COORD] - Panel Led not alive\r\n");
                }
            }
            break;
        }

        case APP_COORDINATOR_STATE_USI_WAIT_SENT_CMD:
        {
            if (!appCoordinatorData.transferFlag)
            {
                /* Free transfer flag */
                appCoordinatorData.freetransferFlag = true;
                appCoordinatorData.state = APP_COORDINATOR_STATE_USI_GET_DEVICES;
            }
            break;
        }
        case APP_COORDINATOR_STATE_DELAY: {
            // Wait delay time
            if (APP_COORDINATOR_TaskDelay(appCoordinatorData.delayMs, &appCoordinatorData.timer))
       
            {
                // Set next app state
                appCoordinatorData.state = appCoordinatorData.nextState;
            }
            break;
        }

        case APP_COORDINATOR_STATE_ERROR:
            /* An error has occurred */
            break;

        default:
            break;
    }
}
 

/*******************************************************************************
 End of File
 */

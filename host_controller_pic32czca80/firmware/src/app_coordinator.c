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
#include <string.h>

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
    This structure should be initialized by the APP_COORDINATOR_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

USB_ALIGN APP_COORDINATOR_DATA appCoordinatorData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

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


void APP_COORDINATOR_SetCoordinatorCmdCallback(COORDINATOR_CMD_CALLBACK callback)
{
    appCoordinatorData.pCoordinatorCmdCallback = callback;
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

void APP_COORDINATOR_Initialize ( void )
{
         /* Initialize the application state machine */
    
    appCoordinatorData.state =  APP_COORDINATOR_STATE_BUS_ENABLE;
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
    
    indexBufferRx = 0;
    memset(serializationBufferRx,'\0',SERIALIZATION_BUFFER_SIZE);
    indexBufferTx = 0;
    memset(serializationBufferTx,'\0',SERIALIZATION_BUFFER_SIZE);
    
    SYS_DEBUG_ErrorLevelSet(SYS_ERROR_INFO);
       
    USB1_DRD_Set();
    
    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "App init\r\n");
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
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Attached USB CDC Device\r\n");
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
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Opened USB CDC Device\r\n");
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

        case APP_COORDINATOR_STATE_DELAY:
        {
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

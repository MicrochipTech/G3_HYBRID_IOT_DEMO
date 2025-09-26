/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "definitions.h"
#include "app.h"
#include "app_ui.h"
//#include "system_config.h"
//#include "system_definitions.h"

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
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;
static bool SysFSMounted = false;
static SYS_TIME_HANDLE appTimer = SYS_TIME_HANDLE_INVALID;
static volatile bool timerExpired = true;


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


/* TODO:  Add any necessary local functions.
*/

void APP_SYSFSEventHandler(SYS_FS_EVENT event,
                           void* eventData,
                           uintptr_t context)
{
    switch(event)
    {
        case SYS_FS_EVENT_MOUNT:
        {
            if(strcmp((const char *)eventData, APP_SYS_FS_MOUNT_POINT) == 0)
            {
                SysFSMounted = true;
            }

            break;
        }    
        case SYS_FS_EVENT_UNMOUNT:
        {
            if(strcmp((const char *)eventData, APP_SYS_FS_MOUNT_POINT) == 0)
            {
                SysFSMounted = false;
            }
            break;
        }
        default:
            break;
    }
}

bool APP_SYSFSMounted(void)
{
    return SysFSMounted;
}

static void APP_TimerCallback ( uintptr_t context)
{
    timerExpired = true;
}

void APP_DelayMS(uint32_t ms)
{
    SYSTICK_TimerStart();
    
    SYSTICK_DelayMs(ms);
}

bool APP_IsTimerExpired(void)
{
    return timerExpired;
}

void APP_StartWaitTimer(uint32_t ms)
{
    timerExpired = false;
    
    appTimer = SYS_TIME_CallbackRegisterMS(APP_TimerCallback, 1, ms, SYS_TIME_SINGLE);
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Initialize ( void )
{
    appData.state = APP_STATE_INIT;
    
    /* Intialize the app state to wait for media attach. */
    APP_UI_Initialize();
    
    SYS_DEBUG_ErrorLevelSet(SYS_ERROR_FATAL);
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks ( void )
{
    switch(appData.state)
    {
        case APP_STATE_INIT:
        {
            printf(">>>>> Test \r\n");
            SYS_FS_EventHandlerSet(&APP_SYSFSEventHandler, (uintptr_t)NULL);
            
            appData.state = APP_STATE_MOUNT_SYSFS;
            
            break;
        }
        case APP_STATE_MOUNT_SYSFS:
        {
            break;
        }
        case APP_STATE_READY:
        {
            break;
        }
        default:
        {
            break;
        }
    }
        
}


/*******************************************************************************
 End of File
 */

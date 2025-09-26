/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_http.c

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
#include "app_http.h"
#include "app_utils.h"
#include "app_ble_data.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_HTTP_DPRINTF(fmt, ...) SYS_DEBUG_PRINT(SYS_ERROR_INFO, fmt, ##__VA_ARGS__);
#define APP_HTTP_QUEUE_COUNT 64 

#define APP_HTTP_QUEUE_WR_EMPTY (-1)
#define APP_HTTP_QUEUE_RD_EMPTY (-2)

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_HTTP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_HTTP_DATA app_httpData;

APP_HTTP_TASK_OBJ appHttpTask;
static APP_HTTP_MSG msg;
static APP_BLE_MSG appHttpBLEMsg;

struct
{
    int wr;
    int rd;
    APP_HTTP_MSG appHTTPMsg[APP_HTTP_QUEUE_COUNT];
} appHTTPMsgQueue;

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


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_HTTP_Initialize ( void )

  Remarks:
    See prototype in app_http.h.
 */

void APP_HTTP_Initialize ( void )
{
    
    memset(&msg, 0, sizeof(APP_HTTP_MSG));
    memset(appHttpTask.notifCallbacks, 0, sizeof(APP_HTTP_NOTIF_CALLBACK) * APP_HTTP_NOTIF_CALLBACK_COUNT);    
    
    //FIXME QUEUE
    appHTTPMsgQueue.wr = APP_HTTP_QUEUE_WR_EMPTY;
    appHTTPMsgQueue.rd = APP_HTTP_QUEUE_RD_EMPTY;
    
    memset(appHTTPMsgQueue.appHTTPMsg, 0, sizeof(APP_HTTP_MSG) * APP_HTTP_QUEUE_COUNT);    
    
    appHttpTask.taskState = APP_HTTP_STATE_INIT;
            

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

APP_RESULT APP_HTTP_SendMsg(APP_HTTP_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR;
    
    //full
    if ((appHTTPMsgQueue.wr == APP_HTTP_QUEUE_COUNT - 1 && appHTTPMsgQueue.rd == 0) ||
        (appHTTPMsgQueue.wr == appHTTPMsgQueue.rd - 1))
    {
        return APP_ERR_NOMEM;
    }    
    
    //empty
    if (appHTTPMsgQueue.wr == APP_HTTP_QUEUE_WR_EMPTY)
    {
        appHTTPMsgQueue.wr = 0;
        appHTTPMsgQueue.rd = 0;
    }
    else
    {
         appHTTPMsgQueue.wr = (appHTTPMsgQueue.wr + 1) % APP_HTTP_QUEUE_COUNT;
    }
            
    appHTTPMsgQueue.appHTTPMsg[appHTTPMsgQueue.wr] = *msg;
    
    return APP_SUCCESS;
}

APP_RESULT APP_HTTP_ReadMsg(APP_HTTP_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR;
    
        //empty
    if (appHTTPMsgQueue.wr == APP_HTTP_QUEUE_WR_EMPTY)
    {
        return APP_ERR_EMPTY;
    }
    
    memcpy(msg, &appHTTPMsgQueue.appHTTPMsg[appHTTPMsgQueue.rd], sizeof(APP_HTTP_MSG));
    
    if (appHTTPMsgQueue.rd == appHTTPMsgQueue.wr)
    {
        appHTTPMsgQueue.wr = APP_HTTP_QUEUE_WR_EMPTY;
        appHTTPMsgQueue.rd = APP_HTTP_QUEUE_RD_EMPTY;
    }
    else 
    {
        appHTTPMsgQueue.rd = (appHTTPMsgQueue.rd + 1) % APP_HTTP_QUEUE_COUNT;
    }
    
    return APP_SUCCESS;
}

/******************************************************************************
  Function:
    void APP_HTTP_Tasks ( void )

  Remarks:
    See prototype in app_http.h.
 */

void APP_HTTP_Tasks ( void )
{
#if false
    SYS_STATUS          tcpipStat;
    TCPIP_NET_HANDLE    netH;
    int                 nNets;
    static IPV4_ADDR    dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int                 i;
    const char          *netName, *netBiosName;

    switch(app_httpData.state)
    {
        case APP_HTTP_STATE_INIT:
        {
            app_httpData.state = APP_HTTP_MOUNT_DISK;
            break;
        }
        case APP_HTTP_MOUNT_DISK:
        {
            //Wait for SD Card with webpages to be mounted
            if(APP_SYSFSMounted())
            {
                APP_HTTP_DPRINTF("SYS_Initialize: The %s File System is mounted\r\n", APP_SYS_FS_MOUNT_POINT);
                app_httpData.state = APP_HTTP_TCPIP_WAIT_INIT;
            }
            break;
        }
        case APP_HTTP_TCPIP_WAIT_INIT:
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if(tcpipStat < 0)
            {   // some error occurred
                APP_HTTP_DPRINTF("APP: TCP/IP stack initialization failed!\r\n");
                app_httpData.state = APP_HTTP_TCPIP_ERROR;
            }
            else if(tcpipStat == SYS_STATUS_READY)
            {
                // now that the stack is ready we can check the
                // available interfaces and register
                // a Bonjour service

                nNets = TCPIP_STACK_NumberOfNetworksGet();

                for(i = 0; i < nNets; i++)
                {
                    netH = TCPIP_STACK_IndexToNet(i);
                    netName = TCPIP_STACK_NetNameGet(netH);
                    netBiosName = TCPIP_STACK_NetBIOSName(netH);

                    APP_HTTP_DPRINTF("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
                    (void)netName;          // avoid compiler warning 
                    (void)netBiosName;      // if SYS_CONSOLE_PRINT is null macro
                }

                // register the application HTTP processing
                HTTP_APP_Initialize();

                app_httpData.state = APP_HTTP_TCPIP_TRANSACT;
            }

            break;

        case APP_HTTP_TCPIP_TRANSACT:
            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for(i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                if(!TCPIP_STACK_NetIsReady(netH))
                {
                    return;    // interface not ready yet!
                }
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;

                    APP_HTTP_DPRINTF(TCPIP_STACK_NetNameGet(netH));
                    APP_HTTP_DPRINTF(" IP Address: ");
                    APP_HTTP_DPRINTF("%d.%d.%d.%d \r\n", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                }
            }
            break;

        default:
            break;
    }
#endif
}

int32_t APP_HTTP_RegisterStateNotification(void (*func)(uint32_t, void *, uint32_t))
{
    uint32_t i;
    
    if (func == NULL)
        return -APP_ERR_INV;
    
    for (i = 0; i < APP_HTTP_NOTIF_CALLBACK_COUNT; i++)
    {
        if (appHttpTask.notifCallbacks[i].func == NULL)
        {
           appHttpTask.notifCallbacks[i].func = func;
           
           return i;
        }
    }
   
    return -APP_ERR_NOMEM;
}

APP_RESULT APP_HTTP_UnregisterStateNotification(uint32_t idx)
{
    if (idx < APP_HTTP_NOTIF_CALLBACK_COUNT)
    {
        appHttpTask.notifCallbacks[idx].func = NULL;
        
        return APP_SUCCESS;
    }
    
    return APP_ERR_EMPTY;
}

static void APP_HTTP_Notify(APP_HTTP_NOTIFY_EVENT event, void * data, uint32_t size)
{
    uint32_t i;
    
    //Call all state callback functions
    for (i = 0; i < APP_HTTP_NOTIF_CALLBACK_COUNT; i++)
    {
        if (appHttpTask.notifCallbacks[i].func != NULL)
        {
            appHttpTask.notifCallbacks[i].func(event, data, size);
        }
    }
}

APP_RESULT APP_HTTP_SendBLELEDColorSetMsg(APP_BLE_DEVICE_ID device, uint32_t rgb888)
{
    appHttpBLEMsg.param.data[APP_BLE_MSG_DATA_DEVICE] = device;
    
   //generate the HSV values
    appHttpBLEMsg.param.data[APP_BLE_MSG_DATA_OPCODE] = 0x8a; //opcode
    appHttpBLEMsg.param.data[APP_BLE_MSG_DATA_SIZE] = 0x04; //size
    appHttpBLEMsg.param.data[APP_BLE_MSG_DATA_COMMAND] = 0x12; //command

    RGB2HSV(gfxColorChannelRed(rgb888, GFX_COLOR_MODE_RGB_888),
            gfxColorChannelGreen(rgb888, GFX_COLOR_MODE_RGB_888),
            gfxColorChannelBlue(rgb888, GFX_COLOR_MODE_RGB_888),
            &appHttpBLEMsg.param.data[4],
            &appHttpBLEMsg.param.data[5],
            &appHttpBLEMsg.param.data[6]);

    appHttpBLEMsg.parmsize = 7;
    
    if (device == APP_BLE_DEVICE_ALL)
    {
        uint32_t i;
        
        appHttpBLEMsg.cmd = APP_BLE_CMD_ML_CONTROL_CTRL_SET;
        
        for (i = 0; i < APP_BLE_DEVICE_ALL; i++)
        {
            APP_BLED_SetDeviceColor(i, rgb888);   
        }
    }
    else
    {
        appHttpBLEMsg.cmd = APP_BLE_CMD_CONTROL_CTRL_SET;
        
        APP_BLED_SetDeviceColor(device, rgb888);   
    }

return APP_BLE_Send_Msg(&appHttpBLEMsg);   
}
#if false
void APP_HTTP_ProcessDemoForm(uint8_t *httpDataBuff)
{
    const uint8_t * ptr;
    APP_HTTP_NOTIF_DATA data;
    
    ptr = TCPIP_HTTP_NET_ArgGet(httpDataBuff, (const uint8_t *)"mycolora");
    if(ptr)
    {
        data.id = APP_BLE_DEVICE_A;
        data.parm.value = StrToRGB888(ptr + 1);

        APP_HTTP_Notify(APP_HTTP_DEVICE_NOTIFY, &data, sizeof(data));
        
        APP_BLED_SetDeviceColor(APP_BLE_DEVICE_A, data.parm.value);
        
        APP_HTTP_SendBLELEDColorSetMsg(APP_BLE_DEVICE_A, data.parm.value);
    }
    
    ptr = TCPIP_HTTP_NET_ArgGet(httpDataBuff, (const uint8_t *)"mycolorb");
    if(ptr)
    {
        data.id = APP_BLE_DEVICE_B;
        data.parm.value = StrToRGB888(ptr + 1);
        
        APP_HTTP_Notify(APP_HTTP_DEVICE_NOTIFY, &data, sizeof(data));
        
        APP_BLED_SetDeviceColor(APP_BLE_DEVICE_B, data.parm.value);
        
        APP_HTTP_SendBLELEDColorSetMsg(APP_BLE_DEVICE_B, data.parm.value);
    }
        
    ptr = TCPIP_HTTP_NET_ArgGet(httpDataBuff, (const uint8_t *)"mycolorc");
    if(ptr)
    {
        data.id = APP_BLE_DEVICE_C;
        data.parm.value = StrToRGB888(ptr + 1);
        
        APP_HTTP_Notify(APP_HTTP_DEVICE_NOTIFY, &data, sizeof(data));
        
        APP_BLED_SetDeviceColor(APP_BLE_DEVICE_C, data.parm.value);
        
        APP_HTTP_SendBLELEDColorSetMsg(APP_BLE_DEVICE_C, data.parm.value);
    }
}

TCPIP_HTTP_DYN_PRINT_RES TCPIP_HTTP_Print_bleled(TCPIP_HTTP_NET_CONN_HANDLE connHandle, const TCPIP_HTTP_DYN_VAR_DCPT *vDcpt)
{
    // Determine which LED to check
    if(vDcpt->nArgs != 0 && vDcpt->dynArgs->argType == TCPIP_HTTP_DYN_ARG_TYPE_INT32)
    {
        int32_t device = vDcpt->dynArgs->argInt32;
        uint32_t rgb888; 
        
        if (device < APP_BLE_DEVICE_MAX)
        {
            static char rgb888str[APP_BLE_DEVICE_MAX][8];
            
            APP_BLED_GetDeviceColor(device, &rgb888);
            
            snprintf(rgb888str[device], 8, "#%06x", (int) rgb888);
            
            TCPIP_HTTP_NET_DynamicWriteString(vDcpt, rgb888str[device], false);
        }
        else
        {
            TCPIP_HTTP_NET_DynamicWriteString(vDcpt, "#000000", false);
        }

            
    }

    return TCPIP_HTTP_DYN_PRINT_RES_DONE;
}

TCPIP_HTTP_DYN_PRINT_RES TCPIP_HTTP_Print_bletemp(TCPIP_HTTP_NET_CONN_HANDLE connHandle, const TCPIP_HTTP_DYN_VAR_DCPT *vDcpt)
{
    // Determine which LED to check
    if(vDcpt->nArgs != 0 && vDcpt->dynArgs->argType == TCPIP_HTTP_DYN_ARG_TYPE_INT32)
    {
        int32_t device = vDcpt->dynArgs->argInt32;
        uint32_t temp; 
        
        if (device < APP_BLE_DEVICE_MAX)
        {
            static char tempStr[APP_BLE_DEVICE_MAX][4];
            APP_BLE_DEVICE * BLEDev = APP_BLED_GetMultiLinkDemoDevice(device);
            
            APP_BLED_GetDeviceTemp(BLEDev, CELS, &temp);
            
            snprintf(tempStr[device], 4, "%d", (int) temp);
            
            TCPIP_HTTP_NET_DynamicWriteString(vDcpt, tempStr[device], false);
        }
        else
        {
            TCPIP_HTTP_NET_DynamicWriteString(vDcpt, "37", false);
        }
    }

    return TCPIP_HTTP_DYN_PRINT_RES_DONE;
}
#endif

/*******************************************************************************
 End of File
 */

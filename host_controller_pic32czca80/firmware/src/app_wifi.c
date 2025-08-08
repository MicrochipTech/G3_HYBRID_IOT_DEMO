/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_wifi.c

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
#include "wdrv_winc_client_api.h"
#include "app_ui.h"
#include "app_wifi.h"

#define APP_WIFI_DPRINTF(fmt, ...) SYS_DEBUG_PRINT(SYS_ERROR_INFO, fmt, ##__VA_ARGS__);

#define APP_WIFI_SSID       "DEMO_AP"
#define APP_WIFI_AUTH       WDRV_WINC_AUTH_TYPE_WPA_PSK
#define APP_WIFI_BOOTMODE   APP_AP_MODE
#define APP_WIFI_CHANNEL    1
#define APP_WIFI_PSK        "12345678" 
#define APP_WIFI_DHCP_SRV_ADDR      "192.168.1.1"
#define APP_WIFI_DHCP_SRV_NETMASK   "255.255.255.0"
#define APP_TCP_LISTEN_PORT         6666
#define APP_TCP_BUFFER_SIZE         1460

typedef enum
{
    APP_WIFI_CONNECT ,
    APP_WIFI_DISCONNECT,
    APP_WIFI_PROVISION,
}APP_CALLBACK_NOTIFY;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_WIFI_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

typedef struct
{
    WDRV_WINC_BSS_CONTEXT   bss;
    WDRV_WINC_AUTH_CONTEXT auth;
    
}APP_WIFI_CONFIG;

typedef void (*APP_CALLBACK) (APP_CALLBACK_NOTIFY value,void *data);


APP_WIFI_CONFIG appWiFiConfig;
APP_WIFI_DATA app_wifiData;
static DRV_HANDLE wdrvHandle;
static WDRV_WINC_AUTH_CONTEXT authCtx;
static WDRV_WINC_BSS_CONTEXT bssCtx;
static TCPIP_NET_HANDLE netHdl;
static WDRV_WINC_NETWORK_ADDRESS peerAddress;
static APP_CALLBACK pAPPWiFiSocketCallback;
static uint32_t connectedCount = 0;


/*******************************************************************************
  Function:
    void APP_WIFI_Initialize ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

void APP_WIFI_Callback(APP_CALLBACK_NOTIFY value,void *data)
{
    switch (value)
    {
        case APP_WIFI_CONNECT:
        {
            break;
        }
        case APP_WIFI_DISCONNECT:
        {
            app_wifiData.state = APP_WIFI_STA_AP_STATE_DONE;
            
            break;
        }
        default:
        {
            break;
        }
    }
}

uint32_t APP_WIFI_GetConnectedCount(void)
{
    return connectedCount;
}


void APP_WIFI_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_wifiData.state = APP_WIFI_STATE_INIT;
    
    memcpy((uint8_t *)appWiFiConfig.bss.ssid.name,APP_WIFI_SSID,sizeof(APP_WIFI_SSID));
    appWiFiConfig.auth.authType = APP_WIFI_AUTH;
    memcpy((uint8_t *)appWiFiConfig.auth.authInfo.WPAPerPSK.key,APP_WIFI_PSK,sizeof(APP_WIFI_PSK));
    appWiFiConfig.auth.authType = WDRV_WINC_AUTH_TYPE_OPEN;;
    
    pAPPWiFiSocketCallback = APP_WIFI_Callback;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

static void APP_WiFiAPAssocCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, const WDRV_WINC_SSID *const pSSID, const WDRV_WINC_NETWORK_ADDRESS *const pPeerAddress, WDRV_WINC_AUTH_TYPE authType, int8_t rssi)
{
    memcpy(&peerAddress,pPeerAddress,sizeof(WDRV_WINC_NETWORK_ADDRESS));    
    
    app_wifiData.state  = APP_WIFI_AP_WAIT_FOR_STA_IP;
}

static void APP_WiFiAPConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        APP_WIFI_DPRINTF( "AP Mode: Station connected\r\n");
        WDRV_WINC_AssocPeerAddressGet(assocHandle, (WDRV_WINC_MAC_ADDR *const)&peerAddress,(WDRV_WINC_ASSOC_CALLBACK const)&APP_WiFiAPAssocCallback);   
        connectedCount += 1;
        
        APP_UI_SendEvent(APP_EVENT_HTTP_CONNECTED);
     }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        APP_WIFI_DPRINTF( "AP Mode: Station disconnected\r\n");
        (*pAPPWiFiSocketCallback)(APP_WIFI_DISCONNECT, NULL);
        
        connectedCount -= 1;
        
        APP_UI_SendEvent(APP_EVENT_HTTP_DISCONNECTED);
    }
}

static void APP_DHCPS_EventHandler(TCPIP_DHCPS_EVENT_DATA* evData, const void* param)
{
    APP_WIFI_DPRINTF("\r\n APP_DHCPS_EventHandler (%d) \r\n", evData->evType);

    switch (evData->evType)
    {
        case TCPIP_DHCPS_EVENT_REQ_UNKNOWN:
        case TCPIP_DHCPS_EVENT_REQUEST_OFFERRED:
        {
            app_wifiData.state = APP_WIFI_AP_DHCP_EVENT;       
            
            break;
        }
        default:
        {
            break;
        }
    }
}


/******************************************************************************
  Function:
    void APP_WIFI_Tasks ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

void APP_WIFI_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_wifiData.state )
    {
        /* Application's initial state. */
        case APP_WIFI_STATE_INIT:
        {
            if (SYS_STATUS_READY == WDRV_WINC_Status(sysObj.drvWifiWinc))
            {
                APP_WIFI_DPRINTF("WINC STATUS READY \r\n");
                app_wifiData.state = APP_WIFI_STATE_WDRV_INIT_READY;
            }
            
            break;
        }
        case APP_WIFI_STATE_WDRV_INIT_READY:
        {
            wdrvHandle = WDRV_WINC_Open(0, 0);

            if (DRV_HANDLE_INVALID != wdrvHandle)
            {   
                APP_WIFI_DPRINTF("WINC STATUS OPENED \r\n");
                app_wifiData.state = APP_WIFI_STA_AP_STATE_CONFIG;
            }
            break;
        }
        //Configure for STA mode
        case APP_WIFI_STA_AP_STATE_CONFIG:
        {
            /* Preset the error appSocketStaApState incase any following operations fail. */            
            /* Reset the internal BSS context */
            WDRV_WINC_BSSCtxSetDefaults(&bssCtx);
            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetChannel(&bssCtx, APP_WIFI_CHANNEL))
            {
                break;
            }
            WDRV_WINC_BSSCtxSetSSID(&bssCtx, (uint8_t*)appWiFiConfig.bss.ssid.name, strlen((const char *)appWiFiConfig.bss.ssid.name));
            
            /* Reset the internal Auth context */
            WDRV_WINC_AuthCtxSetDefaults(&authCtx);

            /* Prepare the Auth context with desired AP's Security settings */
            if (WDRV_WINC_AUTH_TYPE_OPEN == appWiFiConfig.auth.authType)
            {
                WDRV_WINC_AuthCtxSetOpen(&authCtx);
            }
            else if (WDRV_WINC_AUTH_TYPE_WPA_PSK == appWiFiConfig.auth.authType)
            {
                WDRV_WINC_AuthCtxSetWPA(&authCtx, (uint8_t*)appWiFiConfig.auth.authInfo.WPAPerPSK.key, strlen((const char *)appWiFiConfig.auth.authInfo.WPAPerPSK.key));
            }
            else if (WDRV_WINC_AUTH_TYPE_802_1X_MSCHAPV2 == appWiFiConfig.auth.authType)
            {
                WDRV_WINC_AuthCtxSetWPAEnterpriseMSCHAPv2(&authCtx, (char*)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.domainUserName, (uint8_t*)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password, strlen((const char *)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password), false);
            }
            app_wifiData.state = APP_WIFI_STA_AP_STATE_TCP_INIT;
            
            break;
        }
        case APP_WIFI_STA_AP_STATE_TCP_INIT:
        {
            /* WINC network handle*/
            netHdl = TCPIP_STACK_NetHandleGet("WINC");
            if (true == TCPIP_DHCP_IsEnabled(netHdl)) 
            {
                TCPIP_DHCP_Disable(netHdl);
            }
            /* Enable DHCP Server in AP mode */
            TCPIP_DHCPS_Enable(netHdl);
            /* Register a callback to DHCPS */
            TCPIP_DHCPS_HandlerRegister(netHdl, APP_DHCPS_EventHandler, NULL);
            app_wifiData.state = APP_WIFI_AP_STATE_START;
            break;
        }
        case APP_WIFI_AP_STATE_START:
        {
            /* Preset the error state incase any following operations fail. */                        
            /* Create the AP using the BSS and authentication context. */
            if (WDRV_WINC_STATUS_OK == WDRV_WINC_APStart(wdrvHandle, &bssCtx, &authCtx, NULL, &APP_WiFiAPConnectNotifyCallback))
            {
                APP_WIFI_DPRINTF("AP started, you can connect to %s\r\n", appWiFiConfig.bss.ssid.name);
                APP_WIFI_DPRINTF( "On the android device, connect to %s then run setting app\r\n", appWiFiConfig.bss.ssid.name);
                
                app_wifiData.state = APP_WIFI_AP_STATE_STARTED;
            }
           
            break;
        }
        case APP_WIFI_AP_STATE_STARTED:
        {
            IPV4_ADDR                    apLastIp = {-1};
            IPV4_ADDR                    apIpAddr;
            apIpAddr.Val = TCPIP_STACK_NetAddress(netHdl);
            if ((apLastIp.Val != apIpAddr.Val) && (apLastIp.Val != 0))
            {
                apLastIp.Val = apIpAddr.Val;
                APP_WIFI_DPRINTF("%s \r\n", TCPIP_STACK_NetNameGet(netHdl));
                APP_WIFI_DPRINTF("WINC AP Mode IP Address: ");
                APP_WIFI_DPRINTF("%d.%d.%d.%d \r\n", apIpAddr.v[0], apIpAddr.v[1], apIpAddr.v[2], apIpAddr.v[3]);  
                app_wifiData.state = APP_WIFI_STA_AP_STATE_DONE;
            }              
           
            break;
        }
        case APP_WIFI_AP_DHCP_EVENT:
        {  
#if 0           
            uint16_t leases = 0;
            uint16_t inUse = 0;
            TCPIP_DHCPS_RES retval;
            uint16_t idx;
             
            retval = TCPIP_DHCPS_LeaseEntriesGet(netHdl, &leases, &inUse);
        
            APP_WIFI_DPRINTF("\r\n (%d) retval, (%d) In Use\r\n", retval, inUse);
            if ((TCPIP_DHCPS_RES_OK == retval))
            {
                APP_WIFI_DPRINTF("\r\n (%d) Leases, (%d) In Use\r\n", leases, inUse);
                
                for (idx = 0; idx < leases; idx++)
                {
                    TCPIP_DHCPS_LEASE_INFO leaseInfo;
                    
                    TCPIP_DHCPS_LeaseGetInfo(netHdl, &leaseInfo, idx);

                    APP_WIFI_DPRINTF("\r\n (%d) Lease State (%d) \r\n", idx, leaseInfo.leaseState);
                        
                    if (leaseInfo.leaseState != TCPIP_DHCPS_LEASE_STATE_IDLE)
                    {
                        APP_WIFI_DPRINTF("(%d) Connected MAC:%x:%x:%x:%x:%x:%x \r\n", idx, leaseInfo.macAdd.v[0], leaseInfo.macAdd.v[1], leaseInfo.macAdd.v[2], leaseInfo.macAdd.v[3],leaseInfo.macAdd.v[4], leaseInfo.macAdd.v[5]);
                        APP_WIFI_DPRINTF("(%d) Connected IP:%d.%d.%d.%d \r\n", idx, leaseInfo.ipAddress.v[0], leaseInfo.ipAddress.v[1], leaseInfo.ipAddress.v[2], leaseInfo.ipAddress.v[3]);
                        
                        app_wifiData.state = APP_WIFI_AP_SOCKET_LISTENING;                        
                    }
                }
                
                
            }
#endif            

            app_wifiData.state = APP_WIFI_AP_SOCKET_LISTENING;    
            
            break;
        }
        case APP_WIFI_AP_WAIT_FOR_STA_IP:
        {
            
            app_wifiData.state = APP_WIFI_AP_SOCKET_LISTENING;   
            
            break;
        }
        
        case APP_WIFI_AP_SOCKET_LISTENING:
        {
            break;
        }
        case APP_WIFI_STA_AP_STATE_DONE:
        {
            break;
        }        

        /* TODO: implement your application state machine.*/


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

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

#include "definitions.h"
#include "app_http.h"
#include "app_config.h"
#include "app_ble.h"
#include "app_ble_data.h"
#include "app_ui.h"
#include "app_ble_task.h"

static APP_UI_MSG uiMsg = {0};

struct
{
    int32_t wr;
    int32_t rd;
    APP_UI_MSG appUIMsg[APP_UI_QUEUE_COUNT];
} appUIMsgQueue;



void APP_UI_Initialize(void)
{
    appUIMsgQueue.wr = APP_UI_QUEUE_WR_EMPTY;
    appUIMsgQueue.rd = APP_UI_QUEUE_RD_EMPTY;
    
    memset(appUIMsgQueue.appUIMsg, 0, sizeof(APP_UI_MSG) * APP_UI_QUEUE_COUNT);
}

APP_RESULT APP_UI_SendEvent(APP_UI_EVENTS event)
{
    uiMsg.event = event;
       
    return APP_UI_SendMsg(&uiMsg);
}

APP_RESULT APP_UI_SendMsg(APP_UI_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR;
    
    //full
    if ((appUIMsgQueue.wr == APP_UI_QUEUE_COUNT - 1 && appUIMsgQueue.rd == 0) ||
        (appUIMsgQueue.wr == appUIMsgQueue.rd - 1))
    {
        return APP_ERR_NOMEM;
    }    
    
    //empty
    if (appUIMsgQueue.wr == APP_UI_QUEUE_WR_EMPTY)
    {
        appUIMsgQueue.wr = 0;
        appUIMsgQueue.rd = 0;
    }
    else
    {
         appUIMsgQueue.wr = (appUIMsgQueue.wr + 1) % APP_UI_QUEUE_COUNT;
    }
            
    appUIMsgQueue.appUIMsg[appUIMsgQueue.wr] = *msg;
    
    return APP_SUCCESS;
}

APP_RESULT APP_UI_ReadMsg(APP_UI_MSG * msg)
{
    if (msg == NULL)
        return APP_ERR;
    
        //empty
    if (appUIMsgQueue.wr == APP_UI_QUEUE_WR_EMPTY)
    {
        return APP_ERR_EMPTY;
    }
    
    memcpy(msg, &appUIMsgQueue.appUIMsg[appUIMsgQueue.rd], sizeof(APP_UI_MSG));
    
    if (appUIMsgQueue.rd == appUIMsgQueue.wr)
    {
        appUIMsgQueue.wr = APP_UI_QUEUE_WR_EMPTY;
        appUIMsgQueue.rd = APP_UI_QUEUE_RD_EMPTY;
    }
    else 
    {
        appUIMsgQueue.rd = (appUIMsgQueue.rd + 1) % APP_UI_QUEUE_COUNT;
    }
    
    return APP_SUCCESS;
}

void APP_UI_BLE_EventCallback(uint32_t event, void * data, uint32_t size)
{
    if (event == APP_BLE_STATE_CHANGE)
    {
        APP_BLE_TASK_STATE state = (APP_BLE_TASK_STATE) data;
        
        switch(state)
        {
            case APP_BLE_STATE_IDLE:
            {
                break;
            }
            case APP_BLE_STATE_SCAN_SCANNING:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_SCANNING);            
                break;
            }
            case APP_BLE_STATE_SCAN_COMPLETE:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_SCAN_COMPLETE);    
                break;
            }
            case APP_BLE_STATE_ML_CONNECT_START:
            case APP_BLE_STATE_ML_CONNECT_CONNECTING:
            case APP_BLE_STATE_CONNECT_CONNECTING:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_CONNECTING);    
                break;
            }
            case APP_BLE_STATE_ML_CONNECT_CONNECTED_GETSTATE:
            case APP_BLE_STATE_CONNECT_CONNECTED_GETSTATE:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_SYNCING);    
                break;
            }
            case APP_BLE_STATE_ML_CONNECT_CONNECTED:
            case APP_BLE_STATE_CONNECT_CONNECTED:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_CONNECTED);    
                break;
            }
            case APP_BLE_STATE_DISCONNECT_DISCONNECTING:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_DISCONNECTING);    
                break;
            }
            case APP_BLE_STATE_DISCONNECT_DISCONNECTED:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_DISCONNECTED);    
                break;
            }
            case APP_BLE_STATE_ML_CONNECT_DEVICE_FAILED:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_DEVICE_CONNECT_FAILED);
                break;
            }
            case APP_BLE_STATE_ML_CONNECT_CONNECTED_CTRL_READY:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_CONTROL_READY);
                break;
            }
            case APP_BLE_STATE_ML_CONNECT_CONNECTED_ML_CTRL_FAILED:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_DEVICE_CFG_FAILED);
                break;
            }

            //BLE failed states
            case APP_BLE_STATE_SCAN_FAILED:
            case APP_BLE_STATE_CONNECT_FAILED:
            case APP_BLE_STATE_CONNECT_INIT_FAILED:
            case APP_BLE_STATE_DISCONNECT_FAILED:
            {
                APP_UI_SendEvent(APP_EVENT_BLE_FAILED);    
                break;
            }        
            default:
                break;
        }
    }    
    else if (event == APP_BLE_DEVICE_NOTIFY)
    {
        uiMsg.event = APP_EVENT_BLE_DEVICE_NOTIFY;
        
        size = (size < UI_QUEUE_DATA_SIZE) ? size : UI_QUEUE_DATA_SIZE;
        
        memcpy(uiMsg.param.data, data, size);
        uiMsg.parmSize = size;
        
        APP_UI_SendMsg(&uiMsg);
    }
    else if (event == APP_BLE_SCAN_COUNT_NOTIFY)
    {
        uiMsg.event = APP_EVENT_BLE_SCANNING_UPDATE;
        
        uiMsg.param.num = (uint32_t) data;
                
        APP_UI_SendMsg(&uiMsg);
    }

}

void APP_UI_COORDINATOR_EventCallback(uint32_t event, void * data, uint32_t size)
{
    if (event == APP_COORDINATOR_RESET_NOTIFY)
    {
        uiMsg.event = APP_EVENT_COORD_RESET;
        
        //uiMsg.param.num = (uint32_t) data;
                
        APP_UI_SendMsg(&uiMsg);
    }    
    else if (event == APP_COORDINATOR_HEARTBEAT_NOTIFY)
    {
        uiMsg.event = APP_EVENT_COORD_HEARTBEAT;
        size = (size < UI_QUEUE_DATA_SIZE) ? size : UI_QUEUE_DATA_SIZE;
        memcpy(uiMsg.param.data, data, size);
        uiMsg.parmSize = size;
        
        APP_UI_SendMsg(&uiMsg);
    }
    else if (event == APP_COORDINATOR_ALARM_NOTIFY)
    {
        uiMsg.event = APP_EVENT_COORD_ALARM;
        memcpy(uiMsg.param.data, ((uint8_t *)data), size); 
        uiMsg.parmSize = size;
                
        APP_UI_SendMsg(&uiMsg);
    }
    else if (event == APP_COORDINATOR_DEVICE_OUT_NOTIFY)
    {
        uiMsg.event = APP_EVENT_COORD_DEVICE_LEAVE;
        uiMsg.device = *((uint8_t *)data); 
        uiMsg.parmSize = 0;                
        APP_UI_SendMsg(&uiMsg);
    }
    else if (event == APP_COORDINATOR_DEVICE_JOINED_NOTIFY)
    {
        uiMsg.event = APP_EVENT_COORD_DEVICE_JOIN;
        uiMsg.device = *((uint8_t *)data); 
        uiMsg.parmSize = 0;                
        APP_UI_SendMsg(&uiMsg);
    }
    else if (event == APP_COORDINATOR_DEVICE_ALIVE_NOTIFY)
    {
        uiMsg.event = APP_EVENT_COORD_DEVICE_ALIVE;
        uiMsg.device = *((uint8_t *)data++);
        size--;
        size = (size < UI_QUEUE_DATA_SIZE) ? size : UI_QUEUE_DATA_SIZE;
        memcpy(uiMsg.param.data, ((uint8_t *)data), size);
        uiMsg.parmSize = size;                
        APP_UI_SendMsg(&uiMsg);                
    }
    else if (event == APP_COORDINATOR_DEVICE_STATE_NOTIFY)
    {
        uiMsg.event = APP_EVENT_COORD_DEVICE_STATE;
        uiMsg.device = *((uint8_t *)data++);
        size--;
        size = (size < UI_QUEUE_DATA_SIZE) ? size : UI_QUEUE_DATA_SIZE;
        memcpy(uiMsg.param.data, ((uint8_t *)data), size);
        uiMsg.parmSize = size;                
        APP_UI_SendMsg(&uiMsg);
    }
}

void APP_UI_HTTP_EventCallback(uint32_t event, void * data, uint32_t size)
{
    switch(event)
    {
        case APP_HTTP_CONNECT:
        {
            break;
        }
        case APP_HTTP_DISCONNECT:
        {
            break;
        }
        case APP_HTTP_CONTROL:
        {
            uiMsg.event = APP_EVENT_HTTP_DEVICE_CONTROL;
            
            uiMsg.device = ((APP_HTTP_NOTIF_DATA *)data)->id;
            uiMsg.param.num = ((APP_HTTP_NOTIF_DATA *)data)->parm.value;
                
            APP_UI_SendMsg(&uiMsg);
            
            break;
        }
        default:
        {
            break;
        }
    }    
}

void APP_UI_WIFI_EventCallback(uint32_t event, void * data, uint32_t size)
{
    switch(event)
    {
        case APP_WIFI_AVAILABLE_NOTIFY:
        {
            uiMsg.event = APP_EVENT_WIFI_AVAILABLE;
            APP_UI_SendMsg(&uiMsg);
            break;
        }
        case APP_WIFI_CONNECTED_NOTIFY:
        {
            uiMsg.event = APP_EVENT_WIFI_CONNECTED;
            APP_UI_SendMsg(&uiMsg);
            break;
        }
        case APP_WIFI_DISCONNECTED_NOTIFY:
        {
            uiMsg.event = APP_EVENT_WIFI_DISCONNECTED;
            APP_UI_SendMsg(&uiMsg);
            break;
        }
        case APP_WIFI_MQTT_CONNECTED_NOTIFY:
        {
            uiMsg.event = APP_EVENT_WIFI_MQTT_CONNECTED;
            APP_UI_SendMsg(&uiMsg);
            break;
        }
        case APP_WIFI_MQTT_DISCONNECTED_NOTIFY:
        {
            uiMsg.event = APP_EVENT_WIFI_MQTT_DISCONNECTED;
            APP_UI_SendMsg(&uiMsg);
            break;
        }
        default:
        {
            break;
        }
    }
}


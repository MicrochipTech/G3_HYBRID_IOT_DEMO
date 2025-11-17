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

#include <stdio.h>
#include <string.h>

#include "definitions.h"
#include "app_config.h"
#include "app_ble.h"
#include "app_ble_task.h"

#define APP_QUEUE_RCV_TIMEOUT_TICKS 1000
#define APP_QUEUE_SEND_TIMEOUT_TICKS 1000
#define APP_BLE_CMD_READ_BUFF_BYTES 128
#define APP_QUEUE_CMD_RSP_DELAY_MS 1000
#define BLE_DEFAULT_MODE BLE_DATA_MODE

#if ENABLE_BLE_DEBUG
#define BLE_DPRINTF(fmt, ...) SYS_DEBUG_PRINT(SYS_ERROR_INFO, fmt, ##__VA_ARGS__)
#else
#define BLE_DPRINTF(...) 
#endif

typedef enum
{
    BLE_CMD_MODE,
    BLE_DATA_MODE,
} BLE_UART_MODE;

typedef enum
{
    APP_BLE_INIT,
    APP_BLE_MODULE_INIT,
    APP_BLE_READ_MSG,
    APP_BLE_READ_PIPE,
    APP_BLE_PROC_MSG,
    APP_BLE_PROC_DATA,            
} APP_BLE_STATE;


static BLE_UART_MODE uartMode = BLE_DATA_MODE;

uint8_t readBuffer[APP_BLE_CMD_READ_BUFF_BYTES];

static APP_RESULT BLE_Set_Uart_Mode(BLE_UART_MODE mode)
{
    APP_RESULT retval = APP_ERR_INTF;
    
    if (mode == BLE_CMD_MODE)
    {
#ifdef USE_UART_MODE_PIN
        //Enable command mode
        BLE_UART_MODE_Set();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        BLE_UART_MODE_Clear();
#else
        retval = BLE_Module_Write_Data((uint8_t *) "$$$", 3);
#endif        
        //FIXME DELAY
//        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
#ifdef ENABLE_CMD_MODE_CHECK        
        retval = BLE_Module_Check_Resp("CMD>");
#else   
        BLE_Module_Check_Resp("CMD>");
#endif
        if (retval == APP_SUCCESS)
        {        
            uartMode = BLE_CMD_MODE;
        }
    }
    else if (mode == BLE_DATA_MODE)
    {
#ifdef USE_UART_MODE_PIN        
        BLE_UART_MODE_Clear();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        BLE_UART_MODE_Set();
#else        
        retval = BLE_Module_Write_Data((uint8_t *) "---\r", 4);
#endif       
                //FIXME DELAY
//        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
#ifdef ENABLE_CMD_MODE_CHECK        
        retval = BLE_Module_Check_Resp("END");
#else   
        BLE_Module_Check_Resp("END");
#endif
        if (retval == APP_SUCCESS)
        {
            uartMode = BLE_DATA_MODE;
        }
    }
    
    return retval;
}

void BLE_Intf_Init(bool reset)
{
    if (reset)
    {
        //Reset the module
        //BLE_RESET_Clear();
        APP_DelayMS(100);
        //BLE_RESET_Set();
        APP_DelayMS(100);
        uartMode = BLE_DEFAULT_MODE;
    }
}

APP_RESULT BLE_Module_Check_Resp(char * resp)
{
    uint32_t bytesRead;
    APP_RESULT retval = APP_ERR_RSP;
    
    if (resp == NULL)
        return APP_ERR_INV;

    bytesRead = BLE_UART_Read_Wait(readBuffer,
                              APP_BLE_CMD_READ_BUFF_BYTES,
                              1000);

    if (bytesRead > 0)
    {
        BLE_DPRINTF("RESP: %s \r\n", readBuffer);
        if (strstr((char *) readBuffer, (char *) resp) != NULL)
        {
            retval = APP_SUCCESS;
        }
    }
    else
    {
        BLE_DPRINTF("NORESP \r\n");
    }

#ifdef DUMMY_MODULE
    retval = APP_SUCCESS;
#endif
    
    return retval;
}

APP_RESULT BLE_Module_Enable_Command_Mode(bool enable)
{
    APP_RESULT retval = APP_ERR;
            
    if (enable)
    {
        retval = BLE_Set_Uart_Mode(BLE_CMD_MODE);

    }
    else
    {
        retval = BLE_Set_Uart_Mode(BLE_DATA_MODE);
    }
    
    return retval;
}

APP_RESULT BLE_Module_Send_Cmd_Rsp(char * cmd,
                                       char * resp,
                                       uint32_t waitMS)
{
    size_t bytesWritten = 0, bytesRead = 0;
    size_t cmdSize;
    APP_RESULT retval = APP_ERR;
    
    if (cmd == NULL)
        return APP_ERR_INV;
    
    cmdSize = strlen((const char *) cmd);
    
    bytesWritten = SERCOM4_USART_Write((uint8_t*) cmd, cmdSize);
    if (bytesWritten != cmdSize)
    {
        return APP_ERR_INTF;
    }

    if (resp != NULL)
    {
        uint32_t respBytes = strlen(resp);
        
        if (respBytes > APP_BLE_CMD_READ_BUFF_BYTES)
            return APP_ERR_INV;
        
        retval = APP_ERR_NORESP;
        
        memset(readBuffer, 0, APP_BLE_CMD_READ_BUFF_BYTES);
        
        do
        {
            //Check if data is available
            if (SERCOM4_USART_ReadCountGet() > 0)
            {
                //read data, until size
                bytesRead += SERCOM4_USART_Read(&readBuffer[bytesRead],
                                            respBytes - bytesRead);

                if (bytesRead == respBytes)
                    break;
            }
            else
            {
                //delay for waitInterval
                //FIXME DELAY
                APP_DelayMS(1);
            }
        } while (waitMS--);
        
        if ((bytesRead > 0) && (strstr((char *) readBuffer, (char *) resp) != NULL))
        {
            BLE_DPRINTF("RESP: %d : %s \r\n", bytesRead, readBuffer);
            retval = APP_SUCCESS;
        }
    }
    else
    {
        retval = APP_SUCCESS;
    }

    return retval;
}

APP_RESULT BLE_Module_Write_Data(uint8_t * data, size_t size)
{
    size_t bytes;
    
    if (data == NULL)
        return APP_ERR_INV;
    
    bytes = SERCOM4_USART_Write((uint8_t*) data, size);
    if (bytes < size)
    {
        return APP_ERR_INTF;
    }

    return APP_SUCCESS;
}

//APP_RESULT APP_BLE_Send_Msg(APP_BLE_MSG * msg)
//{
//    if (xQueueSend(appBleTask.msgQueue, msg, APP_QUEUE_SEND_TIMEOUT_TICKS))
//        return APP_SUCCESS;
//    else
//        return APP_ERR;
//
//    return APP_SUCCESS;
//}



size_t BLE_UART_Write_Wait(uint8_t * buff, const size_t size, uint32_t waitMS)
{
    size_t bytesWritten = 0;
    
    if (buff == NULL || size == 0)
        return 0;
    
    do
    {
        bytesWritten += SERCOM4_USART_Write(buff, size - bytesWritten);

        if (bytesWritten == size)
            break;
  
        APP_DelayMS(1);
        
    } while (waitMS--);
    
    return bytesWritten;
    
}

size_t BLE_UART_Write(uint8_t * buff, const size_t size)
{
    size_t bytesWritten = 0;
    
    if (buff == NULL || size == 0)
        return 0;
    
    for(;;)
    {
        bytesWritten += SERCOM4_USART_Write(buff, size - bytesWritten);

        if (bytesWritten == size)
            break;
    }
    
    return bytesWritten;
}

size_t BLE_UART_Read_Wait(uint8_t * buff,
                         const size_t size,
                         uint32_t waitMS)
{
    size_t bytesRead = 0;
    
    if (buff == NULL || size == 0)
        return 0;
    
    do
    {
        //Check if data is available
        if (SERCOM4_USART_ReadCountGet() > 0)
        {
            //read data, until size
            bytesRead += SERCOM4_USART_Read(&buff[bytesRead],
                                            size - bytesRead);
            
            if (bytesRead == size)
                break;
        }
        else
        {
            APP_DelayMS(1);
        }
    } while (waitMS--);
    
    
    return bytesRead;
}

size_t BLE_UART_Read(uint8_t * buff, const size_t size)
{
    size_t totalBytesRead = 0;
    size_t bytesRead = 0;
    
    if (buff == NULL || size == 0)
        return 0;
    
    do
    {
        bytesRead = 0;
        
        //Check if data is available
        if (SERCOM4_USART_ReadCountGet() > 0)
        {        
            //read data, until size
            bytesRead = SERCOM4_USART_Read(&buff[totalBytesRead],
                                            size - totalBytesRead);
            
            totalBytesRead += bytesRead;
            
            if (totalBytesRead == size)
                break;
            
            //wait for more data
            APP_DelayMS(1);
        }
    } while (bytesRead > 0);
    
    
    return totalBytesRead;
}

int32_t APP_BLE_RegisterStateNotification(void (*func)(uint32_t, void *, uint32_t))
{
    uint32_t i;
    
    if (func == NULL)
        return -APP_ERR_INV;
    
    for (i = 0; i < APP_BLE_NOTIF_CALLBACK_COUNT; i++)
    {
        if (appBleTask.notifCallbacks[i].func == NULL)
        {
           appBleTask.notifCallbacks[i].func = func;
           
           return i;
        }
    }
   
    return -APP_ERR_NOMEM;
}

APP_RESULT APP_BLE_UnregisterStateNotification(uint32_t idx)
{
    if (idx < APP_BLE_NOTIF_CALLBACK_COUNT)
    {
        appBleTask.notifCallbacks[idx].func = NULL;
        
        return APP_SUCCESS;
    }
    
    return APP_ERR_EMPTY;
}

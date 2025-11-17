/*******************************************************************************
 app_ble.h

  Company
    Microchip Technology Inc.

  File Name
 app_ble.h

  Summary
    

  Description
    

  Remarks:
    None.
*******************************************************************************/

#ifndef APP_BLE_H
#define	APP_BLE_H

#ifdef	__cplusplus
extern "C" {
#endif

//#define DUMMY_MODULE 1
#define APP_BLE_QUEUE_COUNT 64
#define APP_QUEUE_MSG_SIZE  128
#define APP_QUEUE_MSG_STR_SIZE (APP_QUEUE_MSG_SIZE/2)
#define APP_BLE_CMD_TYPE_MASK (0xFF00u)

//RNBD Commands

    
typedef enum
{
    //Setup commands
    APP_BLE_SETUP_CMDS = 0x0200,
    APP_BLE_CMD_CMD_MODE = APP_BLE_SETUP_CMDS,
    APP_BLE_CMD_DATA_MODE,
    APP_BLE_CMD_ABORT,
            
    //Scan commands
    APP_BLE_SCAN_CMDS = 0x0300,
    APP_BLE_CMD_SCAN_START = APP_BLE_SCAN_CMDS,
    APP_BLE_CMD_SCAN_STOP,
    APP_BLE_CMD_SCAN_GET,
            
    //Connect Commands
    APP_BLE_CONNECT_CMDS = 0x0400,
    APP_BLE_CMD_CONNECT_START = APP_BLE_CONNECT_CMDS,
    APP_BLE_CMD_CONNECT_MULTI_START,
    APP_BLE_CMD_CONNECT_STOP,
            
    //Control Commands
    APP_BLE_CMD_CONTROL_START,
    APP_BLE_CMD_CONTROL_CTRL_SET, //Write data to control enpoint 
    APP_BLE_CMD_ML_CONTROL_CTRL_SET, //Write data to control enpoint 
            

    APP_BLE_DISCONNECT_CMDS = 0x0500,
    APP_BLE_CMD_DISCONNECT = APP_BLE_DISCONNECT_CMDS,
            
    //Raw Write Commands
    APP_BLE_WRITE_CMDS = 0x0600,
    APP_BLE_CMD_WRITE_STR,
            
    //Generic Commands
    APP_BLE_GENERIC = 0x0700,
    APP_BLE_DATA_READY = APP_BLE_GENERIC, //data is available from BLE device
            
    //Peripheral Control Commands
    APP_BLE_CTRL = 0x0800,
    APP_BLE_CTRL_SET_LED,      //LED control
    
} APP_BLE_CMD;

typedef enum
{
    APP_BLE_MSG_DATA_DEVICE = 0,
    APP_BLE_MSG_DATA_OPCODE = 1,
    APP_BLE_MSG_DATA_SIZE = 2,
    APP_BLE_MSG_DATA_COMMAND = 3,
} APP_BLE_MSG_DATA;

typedef struct
{
    APP_BLE_CMD cmd;
    void * device;
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
    uint32_t parmsize;  //size of parameter data
} APP_BLE_MSG;

    
//Write data to BLE module
size_t BLE_UART_Write_Wait(uint8_t * buff,
                          const size_t size,
                          uint32_t waitMS);

//Read data from BLE module
size_t BLE_UART_Read_Wait(uint8_t * buff,
                         const size_t size,
                         uint32_t waitMS);

size_t BLE_UART_Read(uint8_t * buff, const size_t size);

//Send command to BLE module and check response
APP_RESULT BLE_Module_Send_Cmd_Rsp(char * cmd,
                                       char * resp,
                                       uint32_t waitMS);

APP_RESULT BLE_Module_Enable_Command_Mode(bool enable);

APP_RESULT BLE_Module_Write_Data(uint8_t * data, size_t size);
APP_RESULT BLE_Module_Check_Resp(char * resp);

//send a message to BLE App Queue
APP_RESULT APP_BLE_Send_Msg(APP_BLE_MSG * msg);
APP_RESULT APP_BLE_Read_Msg(APP_BLE_MSG * msg);

int32_t APP_BLE_RegisterStateNotification(void (*func)(uint32_t, void *, uint32_t));
APP_RESULT APP_BLE_UnregisterStateNotification(uint32_t idx);

void BLE_Intf_Init(bool);
void APP_BLE_Initialize(void);
void APP_BLE_Tasks (void);



#ifdef	__cplusplus

#endif

#endif	/* APP_BLE_H */


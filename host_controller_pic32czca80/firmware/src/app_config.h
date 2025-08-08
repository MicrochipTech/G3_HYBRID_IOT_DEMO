/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _APP_CONFIG_H    /* Guard against multiple inclusion */
#define _APP_CONFIG_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

//INTERFACE CONFIGS
#define ENABLE_CMD_MODE_CHECK 1  //Enables response check when switching between CMD/DATA Uart Mode
//#define USE_UART_MODE_PIN 1   //Enables use of UART mode pin for switching between CMD/DATA Uart Mode

//DEBUG CONFIGS
#define ENABLE_BLE_DEBUG 1      //Enable debug logs in BLE interface code
#define ENABLE_UI_DEBUG 1       //Enable debug logs in UI code
#define ENABLE_BLE_TASK_DEBUG 1 //Enable debug logs in BLE task code
    
//#define ENABLE_DISCONNECT_BUTTON 1
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */

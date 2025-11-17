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

#ifndef _APP_MSG_H    /* Guard against multiple inclusion */
#define _APP_MSG_H


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

typedef enum
{
    APP_MSG_BLE_TASK,
    APP_MSG_UI_TASK,
    APP_MSG_WEB_TASK,
    APP_MSG_MAX_TASK,
} APP_MSG_ID;
    
typedef struct 
{
    uint32_t msgID;
    
} APP_MSG;
    
    
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_MSG_H */

/* *****************************************************************************
 End of File
 */

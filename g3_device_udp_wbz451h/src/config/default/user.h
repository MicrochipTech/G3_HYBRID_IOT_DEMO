/*******************************************************************************
  User Configuration Header

  File Name:
    user.h

  Summary:
    Build-time configuration header for the user defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    It only provides macro definitions for build-time configuration options

*******************************************************************************/

#ifndef USER_H
#define USER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: User Configuration macros
// *****************************************************************************
// *****************************************************************************

#define PANEL_LED_BLUE_CTRL    
    
#ifndef PANEL_LED_BLUE_CTRL
#define USER_BLINK_LED_On()           USER_LED_Set()
#define USER_BLINK_LED_Off()          USER_LED_Clear()
#define USER_BLINK_LED_Toggle()       USER_LED_Toggle()
#endif
    
#define CLEAR_WATCHDOG()              WDT_Clear()
    
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // USER_H
/*******************************************************************************
 End of File
*/

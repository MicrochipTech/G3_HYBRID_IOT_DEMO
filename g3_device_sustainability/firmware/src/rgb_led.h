/*******************************************************************************
  RGB LED Color control Header file

  Company:
    Microchip Technology Inc.

  File Name:
    rgb_led.h

  Summary:
    This file contains the Application Transparent Server Role functions for this project.

  Description:
    This file contains the Application Transparent Server Role functions for this project.
    The implementation of demo mode is included in this file.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
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
//DOM-IGNORE-END

#ifndef _RGB_LED_H
#define _RGB_LED_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "system/time/sys_time.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
typedef enum
{
    /* Application's state machine's initial state. */
    APP_G3_RGB_STATE_INIT = 0,

    /* State to wait for new RGB data */
    APP_G3_RGB_STATE_WAIT_NEW_DATA,

    /* State to set new RGB data */
    APP_G3_RGB_STATE_SET_RGB_DATA,

    /* State to set new RGB data including blinking frequency and time */
    APP_G3_RGB_STATE_SET_RGB_BLINK_DATA,

    /* State to wait for blink time to finish */
    APP_G3_RGB_STATE_WAIT_BLINK_FINISH,

    /* Error state */
    APP_G3_RGB_STATE_ERROR,

} APP_G3_RGB_STATES;

typedef struct
{
    /* The application's current state */
    APP_G3_RGB_STATES state;

    /* Flag to indicate if new RGB data have been received */
    bool newData;
    
    uint8_t rgbValues[3];
    uint16_t blinkFreq;
    uint16_t blinkTime;
    SYS_TIME_HANDLE freqHandle;
    SYS_TIME_HANDLE timeHandle;
    bool freqExpired;
    bool timeExpired;

} APP_G3_RGB_DATA;

extern APP_G3_RGB_DATA app_g3_rgbData;

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************
void RGB_LED_Handle(void);

/****************************************************************
Turn off RGB LED.
****************************************************************/
void RGB_LED_Off(void);

/**************************************************************************//**
Set brightness level
******************************************************************************/
void RGB_LED_SetBrightnessLevel(uint8_t level);

/**************************************************************************//**
Set the color using Hue and Saturation as parameters
******************************************************************************/
void RGB_LED_SetLedColorHS(uint16_t hue, uint8_t saturation);

/**************************************************************************//**
Set the color using Hue, Saturation and brightness level as parameters
******************************************************************************/
void RGB_LED_SetLedColorHSV(uint8_t hue, uint8_t saturation, uint8_t level);

/**************************************************************************//**
\brief Set the color using X and Y as parameters
******************************************************************************/
void RGB_LED_SetLedColorXY(uint16_t x, uint16_t y);

#endif
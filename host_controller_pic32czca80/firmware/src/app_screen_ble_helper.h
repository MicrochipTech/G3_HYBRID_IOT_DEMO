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
#ifndef APP_SCREEN_BLE_HELPER_H
#define	APP_SCREEN_BLE_HELPER_H

#ifdef	__cplusplus
extern "C" {
#endif

APP_BLE_DEVICE * Screen_GetActiveDevice(void);
void Screen_SetActiveDevice(APP_BLE_DEVICE * device);

APP_RESULT Control_SendBLELEDOnOffMsg(APP_BLE_MSG * bleMsg, bool on, APP_BLE_DEVICE_ID device);
APP_RESULT Control_SendBLELEDColorSetMsg(APP_BLE_MSG * bleMsg, APP_UI_LED_CFG * ledCfg, APP_BLE_DEVICE_ID device);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_SCREEN_BLE_HELPER_H */


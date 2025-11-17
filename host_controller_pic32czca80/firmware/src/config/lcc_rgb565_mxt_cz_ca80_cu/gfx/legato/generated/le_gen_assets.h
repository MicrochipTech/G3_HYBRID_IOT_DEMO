/*******************************************************************************
 Module for Microchip Legato Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    le_gen_assets.h

  Summary:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.


  Description:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.

*******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C)  Microchip Technology Inc. and its subsidiaries.
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

// DOM-IGNORE-END

#ifndef LE_GEN_ASSETS_H
#define LE_GEN_ASSETS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

#include "gfx/legato/legato.h"

extern const lePalette leGlobalPalette;

/*****************************************************************************
 * Legato Graphics Asset Location IDs
 *****************************************************************************/
/*********************************
 * Legato Asset Memory Location
 * Name:          SDCard
 ***********************************/
#define LE_STREAM_LOCATION_ID_SDCard    1

/*****************************************************************************
 * Legato Graphics Image Assets
 *****************************************************************************/
/*********************************
 * Legato Image Asset
 * Name:   ConnectButton_100
 * Size:   100x100 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ConnectButton_100;

/*********************************
 * Legato Image Asset
 * Name:   ControlButton_100
 * Size:   100x100 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ControlButton_100;

/*********************************
 * Legato Image Asset
 * Name:   MchpLogo_100
 * Size:   100x32 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage MchpLogo_100;

/*********************************
 * Legato Image Asset
 * Name:   BulbOff15
 * Size:   15x24 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage BulbOff15;

/*********************************
 * Legato Image Asset
 * Name:   BulbOn30
 * Size:   30x32 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage BulbOn30;

/*********************************
 * Legato Image Asset
 * Name:   Knob30
 * Size:   30x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Knob30;

/*********************************
 * Legato Image Asset
 * Name:   Home40
 * Size:   40x34 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Home40;

/*********************************
 * Legato Image Asset
 * Name:   Thermo15
 * Size:   15x34 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Thermo15;

/*********************************
 * Legato Image Asset
 * Name:   Scan40
 * Size:   40x40 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Scan40;

/*********************************
 * Legato Image Asset
 * Name:   ScrollKnob10
 * Size:   10x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ScrollKnob10;

/*********************************
 * Legato Image Asset
 * Name:   ConnectButton_60
 * Size:   60x60 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ConnectButton_60;

/*********************************
 * Legato Image Asset
 * Name:   Disconnect60
 * Size:   60x60 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Disconnect60;

/*********************************
 * Legato Image Asset
 * Name:   id60
 * Size:   60x60 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage id60;

/*********************************
 * Legato Image Asset
 * Name:   Notify200
 * Size:   200x60 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Notify200;

/*********************************
 * Legato Image Asset
 * Name:   NotifyCancel200
 * Size:   200x58 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage NotifyCancel200;

/*********************************
 * Legato Image Asset
 * Name:   NotifyOk_200
 * Size:   200x57 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage NotifyOk_200;

/*********************************
 * Legato Image Asset
 * Name:   DeviceSelect100
 * Size:   100x102 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage DeviceSelect100;

/*********************************
 * Legato Image Asset
 * Name:   progress_anim0
 * Size:   100x20 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage progress_anim0;

/*********************************
 * Legato Image Asset
 * Name:   progress_anim1
 * Size:   100x20 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage progress_anim1;

/*********************************
 * Legato Image Asset
 * Name:   progress_anim2
 * Size:   100x20 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage progress_anim2;

/*********************************
 * Legato Image Asset
 * Name:   progress_anim3
 * Size:   100x20 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage progress_anim3;

/*********************************
 * Legato Image Asset
 * Name:   ColorPickerBlueBack200_565
 * Size:   200x199 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ColorPickerBlueBack200_565;

/*********************************
 * Legato Image Asset
 * Name:   DeviceSelect60
 * Size:   60x61 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage DeviceSelect60;

/*********************************
 * Legato Image Asset
 * Name:   Disconnect40
 * Size:   40x40 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Disconnect40;

/*********************************
 * Legato Image Asset
 * Name:   Slider50
 * Size:   49x250 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Slider50;

/*********************************
 * Legato Image Asset
 * Name:   DeviceNoSelect60
 * Size:   60x61 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage DeviceNoSelect60;

/*********************************
 * Legato Image Asset
 * Name:   Check30
 * Size:   30x22 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Check30;

/*********************************
 * Legato Image Asset
 * Name:   ColorPickerBlueBack200_888
 * Size:   200x199 pixels
 * Type:   RGB Data
 * Format: RGB_888
 ***********************************/
extern leImage ColorPickerBlueBack200_888;

/*********************************
 * Legato Image Asset
 * Name:   DeviceSelect40Bulb
 * Size:   40x41 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage DeviceSelect40Bulb;

/*********************************
 * Legato Image Asset
 * Name:   DeviceNoSelect40
 * Size:   40x41 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage DeviceNoSelect40;

/*********************************
 * Legato Image Asset
 * Name:   bulb40
 * Size:   40x38 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage bulb40;

/*********************************
 * Legato Image Asset
 * Name:   ControlButton40
 * Size:   40x38 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ControlButton40;

/*********************************
 * Legato Image Asset
 * Name:   Bulb80
 * Size:   80x76 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Bulb80;

/*********************************
 * Legato Image Asset
 * Name:   Disconnect20
 * Size:   20x20 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Disconnect20;

/*********************************
 * Legato Image Asset
 * Name:   bleTab60
 * Size:   65x60 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage bleTab60;

/*********************************
 * Legato Image Asset
 * Name:   bleTabA60
 * Size:   65x60 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage bleTabA60;

/*********************************
 * Legato Image Asset
 * Name:   graphtab60
 * Size:   60x56 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage graphtab60;

/*********************************
 * Legato Image Asset
 * Name:   GraphTabA60
 * Size:   60x56 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage GraphTabA60;

/*********************************
 * Legato Image Asset
 * Name:   WifiTab60
 * Size:   60x56 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage WifiTab60;

/*********************************
 * Legato Image Asset
 * Name:   WifiTabA60
 * Size:   60x56 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage WifiTabA60;

/*********************************
 * Legato Image Asset
 * Name:   InfoGraphic
 * Size:   280x277 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage InfoGraphic;

/*********************************
 * Legato Image Asset
 * Name:   QRCode2
 * Size:   160x158 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage QRCode2;

/*********************************
 * Legato Image Asset
 * Name:   BatteryCharger
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage BatteryCharger;

/*********************************
 * Legato Image Asset
 * Name:   ElectricityMeter
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage ElectricityMeter;

/*********************************
 * Legato Image Asset
 * Name:   EnergyStorage
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage EnergyStorage;

/*********************************
 * Legato Image Asset
 * Name:   EVCharger
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage EVCharger;

/*********************************
 * Legato Image Asset
 * Name:   G3Tab60
 * Size:   60x56 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage G3Tab60;

/*********************************
 * Legato Image Asset
 * Name:   Hybrid_IoT_Demo
 * Size:   426x362 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Hybrid_IoT_Demo;

/*********************************
 * Legato Image Asset
 * Name:   InverterBlue
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage InverterBlue;

/*********************************
 * Legato Image Asset
 * Name:   LiquidDetector
 * Size:   120x117 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage LiquidDetector;

/*********************************
 * Legato Image Asset
 * Name:   HeatPump
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage HeatPump;

/*********************************
 * Legato Image Asset
 * Name:   IndoorLight
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage IndoorLight;

/*********************************
 * Legato Image Asset
 * Name:   OutdoorLight
 * Size:   121x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage OutdoorLight;

/*********************************
 * Legato Image Asset
 * Name:   LightOff
 * Size:   106x46 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage LightOff;

/*********************************
 * Legato Image Asset
 * Name:   LightOn
 * Size:   106x46 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage LightOn;

/*********************************
 * Legato Image Asset
 * Name:   NextPage
 * Size:   121x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage NextPage;

/*********************************
 * Legato Image Asset
 * Name:   ConnectIcon
 * Size:   20x20 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage ConnectIcon;

/*********************************
 * Legato Image Asset
 * Name:   ConnectIconGreen
 * Size:   20x20 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage ConnectIconGreen;

/*********************************
 * Legato Image Asset
 * Name:   ConnectIconRed
 * Size:   20x20 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage ConnectIconRed;

/*********************************
 * Legato Image Asset
 * Name:   ConnectIconYellow
 * Size:   20x20 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage ConnectIconYellow;

/*********************************
 * Legato Image Asset
 * Name:   CloudGreen
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage CloudGreen;

/*********************************
 * Legato Image Asset
 * Name:   CloudRed
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage CloudRed;

/*********************************
 * Legato Image Asset
 * Name:   WifiRed
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage WifiRed;

/*********************************
 * Legato Image Asset
 * Name:   WifiGreen
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage WifiGreen;

/*********************************
 * Legato Image Asset
 * Name:   CloudYellow
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage CloudYellow;

/*********************************
 * Legato Image Asset
 * Name:   IndoorLightOn
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage IndoorLightOn;

/*********************************
 * Legato Image Asset
 * Name:   OutdoorLightOn
 * Size:   121x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage OutdoorLightOn;

/*********************************
 * Legato Image Asset
 * Name:   WifiYellow
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage WifiYellow;

/*********************************
 * Legato Image Asset
 * Name:   g3Green
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage g3Green;

/*********************************
 * Legato Image Asset
 * Name:   g3Red
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage g3Red;

/*********************************
 * Legato Image Asset
 * Name:   AlarmIcon_1
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage AlarmIcon_1;

/*********************************
 * Legato Image Asset
 * Name:   AlarmIcon50
 * Size:   50x50 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage AlarmIcon50;

/*********************************
 * Legato Image Asset
 * Name:   EmergencyButton
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage EmergencyButton;

/*********************************
 * Legato Image Asset
 * Name:   PanelLed
 * Size:   120x120 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage PanelLed;

/*****************************************************************************
 * Legato Graphics Font Assets
 *****************************************************************************/
/*********************************
 * Legato Font Asset
 * Name:         NotoSans_Regular
 * Height:       21
 * Baseline:     22
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  1
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont NotoSans_Regular;

/*********************************
 * Legato Font Asset
 * Name:         TitleFont
 * Height:       21
 * Baseline:     12
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  14
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont TitleFont;

/*********************************
 * Legato Font Asset
 * Name:         ButtonFont
 * Height:       21
 * Baseline:     10
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  12
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont ButtonFont;

/*********************************
 * Legato Font Asset
 * Name:         TempFont
 * Height:       21
 * Baseline:     19
 * Style:        Antialias
 * Glyph Count:  218
 * Range Count:  15
 * Glyph Ranges: 0xA
                 0x20-0xF8
***********************************/
extern leRasterFont TempFont;

/*********************************
 * Legato Font Asset
 * Name:         TempUnitFont
 * Height:       21
 * Baseline:     12
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  17
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont TempUnitFont;

/*********************************
 * Legato Font Asset
 * Name:         DeviceNameFont
 * Height:       21
 * Baseline:     19
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  2
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont DeviceNameFont;

/*********************************
 * Legato Font Asset
 * Name:         NotifFont
 * Height:       21
 * Baseline:     15
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  11
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont NotifFont;

/*********************************
 * Legato Font Asset
 * Name:         Tiny
 * Height:       21
 * Baseline:     9
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  7
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont Tiny;

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   58
 *****************************************************************************/

// language IDs
#define language_Default    0

// string IDs
#define stringID_TempSensor    0
#define stringID_DefaultTemp    1
#define stringID_ConnectedString    2
#define stringID_SmartSignalingString    3
#define stringID_HomeString    4
#define stringID_HeatPumpString    5
#define stringID_DeviceAString    6
#define stringID_DeviceA    7
#define stringID_WaitString    8
#define stringID_InterfaceStr    9
#define stringID_DeviceInfo    10
#define stringID_LabelPanelLedWidget    11
#define stringID_SignalingWallConnectionStatus    12
#define stringID_ConnectingString    13
#define stringID_DemoName    14
#define stringID_SolarInverterString    15
#define stringID_IntfValueStr    16
#define stringID_DeviceBString    17
#define stringID_LightingIndoorString    18
#define stringID_EVChargerString    19
#define stringID_FailedString    20
#define stringID_TempUnit    21
#define stringID_LiquidDetectionString    22
#define stringID_String_1    23
#define stringID_EnergyStorageString    24
#define stringID_DisconnectedString    25
#define stringID_IPAddrStr    26
#define stringID_DeviceB    27
#define stringID_DevicesString    28
#define stringID_LightOffLabel    29
#define stringID_SSIDStr    30
#define stringID_NetWebURLValue    31
#define stringID_IPAddrValueStr    32
#define stringID_StartString    33
#define stringID_ReleasedLabel    34
#define stringID_NextLabel    35
#define stringID_LightingWallConnectionStatus    36
#define stringID_ConnectString    37
#define stringID_PressedLabel    38
#define stringID_ElectricityMeterString    39
#define stringID_ControlString    40
#define stringID_EmergencyButtonString    41
#define stringID_NetWebURLStr    42
#define stringID_SSIDValueStr    43
#define stringID_SelectDevice    44
#define stringID_ColorChannels    45
#define stringID_BLEDeviceInfo    46
#define stringID_DeviceC    47
#define stringID_LabelEmergencyButtonWidget    48
#define stringID_BatteryChargerString    49
#define stringID_SWallConnectionStatus    50
#define stringID_ZeroValueStr    51
#define stringID_WiFiDeviceInfo    52
#define stringID_DisconnectString    53
#define stringID_LightingOutdoorString    54
#define stringID_Connections    55
#define stringID_LightOnLabel    56
#define stringID_AllString    57

extern const leStringTable stringTable;


// string list
extern leTableString string_TempSensor;
extern leTableString string_DefaultTemp;
extern leTableString string_ConnectedString;
extern leTableString string_SmartSignalingString;
extern leTableString string_HomeString;
extern leTableString string_HeatPumpString;
extern leTableString string_DeviceAString;
extern leTableString string_DeviceA;
extern leTableString string_WaitString;
extern leTableString string_InterfaceStr;
extern leTableString string_DeviceInfo;
extern leTableString string_LabelPanelLedWidget;
extern leTableString string_SignalingWallConnectionStatus;
extern leTableString string_ConnectingString;
extern leTableString string_DemoName;
extern leTableString string_SolarInverterString;
extern leTableString string_IntfValueStr;
extern leTableString string_DeviceBString;
extern leTableString string_LightingIndoorString;
extern leTableString string_EVChargerString;
extern leTableString string_FailedString;
extern leTableString string_TempUnit;
extern leTableString string_LiquidDetectionString;
extern leTableString string_String_1;
extern leTableString string_EnergyStorageString;
extern leTableString string_DisconnectedString;
extern leTableString string_IPAddrStr;
extern leTableString string_DeviceB;
extern leTableString string_DevicesString;
extern leTableString string_LightOffLabel;
extern leTableString string_SSIDStr;
extern leTableString string_NetWebURLValue;
extern leTableString string_IPAddrValueStr;
extern leTableString string_StartString;
extern leTableString string_ReleasedLabel;
extern leTableString string_NextLabel;
extern leTableString string_LightingWallConnectionStatus;
extern leTableString string_ConnectString;
extern leTableString string_PressedLabel;
extern leTableString string_ElectricityMeterString;
extern leTableString string_ControlString;
extern leTableString string_EmergencyButtonString;
extern leTableString string_NetWebURLStr;
extern leTableString string_SSIDValueStr;
extern leTableString string_SelectDevice;
extern leTableString string_ColorChannels;
extern leTableString string_BLEDeviceInfo;
extern leTableString string_DeviceC;
extern leTableString string_LabelEmergencyButtonWidget;
extern leTableString string_BatteryChargerString;
extern leTableString string_SWallConnectionStatus;
extern leTableString string_ZeroValueStr;
extern leTableString string_WiFiDeviceInfo;
extern leTableString string_DisconnectString;
extern leTableString string_LightingOutdoorString;
extern leTableString string_Connections;
extern leTableString string_LightOnLabel;
extern leTableString string_AllString;

void initializeStrings(void);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* LE_GEN_ASSETS_H */

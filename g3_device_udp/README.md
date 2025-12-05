# G3_HYBRID_IOT_DEMO - G3 Devices <!-- omit in toc -->

<img src="../images/IoT-Made-Easy-Logo.png" width=100>

> "IoT Made Easy!" - This is an application using the unified G3-Hybrid PLC+RF protocol.

Devices: **| PIC32CX-BZ | PL460 |**<br>
Features: **| G3 Hybrid protocol |**


## ⚠ Disclaimer <!-- omit in toc -->

<p><span style="color:red"><b>
THE SOFTWARE ARE PROVIDED "AS IS" AND GIVE A PATH FOR SELF-SUPPORT AND SELF-MAINTENANCE. This repository contains example code intended to help accelerate client product development. </br>

For additional Microchip repos, see: <a href="https://github.com/Microchip-MPLAB-Harmony" target="_blank">https://github.com/Microchip-MPLAB-Harmony</a>

Checkout the <a href="https://microchipsupport.force.com/s/" target="_blank">Technical support portal</a> to access our knowledge base, community forums or submit support ticket requests.
</span></p></b>

## Contents 
- [Introduction](#introduction)
- [Bill of materials](#bill-of-materials)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
    - [Development Tools](#development-tools)
    - [MCC Content Libraries](#mcc-content-libraries)
    - [Harmony MCC Configuration](#harmony-mcc-configuration)
    - [Application](#application)
- [Board Programming](#board-programming)
- [Run the demo](#run-the-demo)


## Introduction

According with G3 technologies[*](#links) each G3 network requires the existence of a G3 Coordinator and G3 Devices. G3 Hybrid device runs on a WBZ451 Curiosity Board connected with a PL460-EK using an adaptation board.

## Bill of materials

| TOOLS                                                                                                                                     | QUANTITY |
| :---------------------------------------------------------------------------------------------------------------------------------------- | :------- |
| [PIC32CX-BZ2 and WBZ451 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV96B94A)                           | 1        |
| [PL460 Evaluation Kit (rev4)](https://www.microchip.com/en-us/development-tool/ev13l63a)                                                         | 1        |
| [MikroBUS to PL460-EK adaptation board](docs/WBZ451mikroBUStoPL460EKadapter.png)                                                          | 1        |

[TOP](#contents)

## Hardware Setup

- For G3 Hybrid devices, the PL460-EK rev4 need to be modified with these changes:
  - Replace C9 by a 10K Pull Down resistor to GND (PL460_NRST)
  - Include 10K Pull Up resistor to 3V3 on PL460_ENABLE and cut trace to XPLAINED PRO connector
  - Include 10K Pull Down resistor to GND on PL460_STBY and cut trace to XPLAINED PRO connector

- Connect the PL460-EK to MikroBUS connector of WBZ451 with the adaptation board and supply it with the provided +15V Power Supply
- Connect the +5V power supply on WBZ451 uUSB connector J7
- Connect a USB cable on J7 for device programming and debugging with terminal program

![G3 Hybrid Device Design](docs/WBZ451_hybrid_device.png)  

[TOP](#contents)

## Software Setup
### Development Tools
  - MPLAB® X IDE v6.25
  - MPLAB® X IDE plug-ins: MPLAB® Code Configurator (MCC) v5.7.1 and above
  - MPLAB® XC32 C/C++ Compiler v4.60
  - MPLAB® Harmony v3
  - Device Pack: PIC32CZ-CA80_DFP (1.4.243)

### MCC Content Libraries
| Harmony V3 component   | version   |
| :----------------------| :---------|
| core                   | v3.13.5   |
| wireless_pic32cxbz_wbz | v1.2.0    |
| wireless_15_4_phy      | v1.2.0    |
| csp                    | v3.19.1   |
| net                    | v3.12.0   |
| CMSIS_5                | v5.8.0    |
| CMSIS-FreeRTOS         | v10.5.1   |
| smartenergy            | v1.2.1    |
| smartenergy_g3         | v1.0.1    |
| bsp                    | v3.20.1   |
| wolfssl                | v5.6.7-E1 |
| crypto                 | v4.0.0-E1 |

### Harmony MCC Configuration

#### Full Configuration

The full MCC configuration is:
![G3 coordinator MCC configuraion](docs/MCCfull.png)

#### System Console and Debugging
The system console is configured to use SERCOM1 in USART mode and is accessible via the DEBUG USB connector.

![G3 Device MCC SERCOM1 Configuration](docs/MCC_SERCOM1_console.png)
![G3 Device MCC SERCOM1 Pins Configuration](docs/MCC_Pins_SERCOM1.png)
![G3 Device MCC Console+Debug Configuration](docs/MCC_console_debug.png)

#### G3 and PL460-EK interface

The G3 device is configured to use SERCOM0 in SPI mode to access the PL460-EK.

![G3 Device MCC SERCOM0 Configuration](docs/MCC_SERCOM0_pl460.png)

The project uses MAC real time features on FCC band with default values for PLC PHY coupling. 

![G3 Device MACrt for FCC band Configuration](docs/MCC_G3macrt_config.png)

The PIN configuration for the PL460 interface is:

![G3 Device PL460 Interface Pin Configuration](docs/MCC_Pins_PL460.png)

The G3 stack full configuration is:

![G3 Device Stack Full Configuration](docs/MCC_G3stackfull.png)

The G3 stack is configured in mode Hybrid PLC & RF with PAN Device as role.

![G3 Device Stack Configuration](docs/MCC_G3stack_device_hybrid.png)

The Crypto configuration to accomplish with G3 Security features is:

![G3 Device Stack Crypto Configuration](docs/MCC_crypto_config.png)

#### RGB Led Configuration
The application identify some events acting over the RGB Led pins. Its configuration is based on Timer Counters in PWM mode:

![G3 Coordinator MCC Timer Counter in PWM Configuration](docs/MCC_TCx_PWM_ledRGB.png)

![G3 Coordinator MCC RGB Led Pin Configuration](docs/MCC_ledRGB_pins.png)

#### Watchdog Configuration
The Watchdog is enabled to avoid any unhandled situation on the application.

![G3 Device MCC Watchdog Configuration](docs/MCC_FusesWatchdog.png)

[TOP](#contents)

## Application

<b>The main functionalities of the G3 device are:</b>
* Register into G3 Network created by the G3 Coordinator
* Receive commands from G3 coordinator to act/get information to/from G3 device
* Notify alarms to G3 Coordinator

### G3 Hybrid devices

The G3 devices able to connect into the G3 coordinator and their functionalties are:

| NAME            | DEVICE_TYPE | DEMO                   | FEATURE                        |
| :-              | :-          | :-                     | :-                             |
|Indoor Lighting  |0x10         |Smart Lighting Demo     |Controls the indoor light state |
|Outdoor Lighting |0x11         |Smart Lighting Demo     |Controls the outdoor light state|
|Liquid Detector  |0x13         |Sustainability Wall Demo|Monitors availability           |
|Solar Inverter   |0x14         |Sustainability Wall Demo|Monitors availability           |
|Battery Charger  |0x15         |Sustainability Wall Demo|Monitors availability           |
|Energy Storage   |0x16         |Sustainability Wall Demo|Monitors availability           |
|Heat Pump        |0x17         |Sustainability Wall Demo|Monitors availability           |
|EV Charger       |0x18         |Sustainability Wall Demo|Monitors availability           |
|Electricity Meter|0x19         |Sustainability Wall Demo|Monitors availability           |
|Emergency Button |0x1A         |Hybrid IoT BP           |Generate Alarms                 |
|LED Panel        |0x1B         |Hybrid IoT BP           |Controls LED Panel state        |

### G3 Hybrid device specific configuration  

The G3 Hybrid device has been configured fixing some parameters:

- <b>PAN_ID</b>: PAN ID identifies the G3 network in use. It is masked to be on 0x782X range. 
- <b>ADP PIBs</b>: These ADP Pibs have been set according with the network: MaxHops, RREQWait, RREPWait and NetTraversalTime.
- <b>RF Duty Cycle</b>: the limit has been fixed to 100% removing any transmission restriction

### G3 Hybrid device applications  

The G3 device is based on different application files:
- <b>app_g3_management</b>: keeps the G3 device feature running including registering. Additionally a protection mechanism to reset the device if not traffic is received for a while has been implemented too. Besides, the "User Button" is monitored and an alarm is generated if it is pressed during 2 or more seconds. 
- <b>app_tcpip_management</b>: keeps the TCP/IP stack available to be able to interact with the network at UDP layer and also keep the UDP responder server where the alarms are received.
- <b>app_udp_responder</b>: provides a UDP server where receive any command from coordinator.

### Communication Protocol

The communication protocol starts with the G3 device registering process interchange. After the device has joined the G3 network, the device is included into the pool of devices to be ping from the coordinator in a cycling way (each minute in a normal situation) to keep their availability. The ping mechanism is based on the request of the device type and the answer from the device. When a device is alive, any additional command to interact with it can be sent.

![G3 Device to Coordinator packets interchange](docs/CommunicationProtocol.png)

### G3 Device Commands Interchange

| ID | NAME                 | SOURCE         | DESTINATION   | FEATURE                                             |
| :- | :-                   | :-             | :-            | :-                                                  |
|0xF4|GET_DEVICE_INFO       |COORD           |ANY DEVICE     |Get the Device Type Information                      |
|0xF5|GET_DEVICE_INFO_ANSWER|DEVICE          |COORD          |Provides the Device Type Information                 |
|0xF6|SET_RGB_LED           |COORD           |ANY DEVICE     |Set the RGB LED colour                               |
|0xF8|SET_RGB_LED_BLINK     |COORD           |ANY DEVICE     |Set the RGB LED colour with a frequency during a time|
|0xFA|SET_PANEL_INFO        |COORD           |PANEL LED      |Set the information shown in the Panel LED           |
|0xFC|EMERGENCY             |EMERGENCY BUTTON|COORD          |Emergency alarm after pressing the Emergency Button  |
|0xFE|SET_LIGHT             |COORD           |LIGHTING DEVICE|Set the light state of a Lighting Device             |

## Board Programming
Programming the application can be done using MPLAB X IDE
- Open the given project using MPLAB X IDE
- Select the connected hardware tool in the project properties
- Make and program device

[TOP](#contents)

## Run the demo

After powering up the WBZ451 (5V Power Supply) + PL460 (15V Power Supply), the G3 device starts trying to join a G3 Network, the RGB LED blinks on green. When the device has joined the corresponding G3 network, the RGB LED keeps green for about 10 seconds and the Blue "User Led" will start blinking with a cadency of 0.5 secs if connected through RF or 1 sec if connected through PLC.

Each time the device is pinged from the LCD Touch Screen or the Cloud, the RGB Led will blink for 10 seconds in the corresponding colour (typically cyan).

An alarm can be generated pressing the "User Button" for more than 2 secs, the RGB will keep in red for 2 seconds.

<b>UART interface</b>  
For debugging purposes, a UART interface to the PC is implemented. A serial port terminal (e.g. PuTTY) can be used to open a connection to the device.  
  
USART configuration:
- Baud rate: 115 200 Hz
- Parity mode: no parity
- Stop bit mode: 1 Stop bit

## Links

More Information about G3 can be found on:
- [G3 Alliance](https://g3-alliance.com/)
- [G3 Technologies](https://g3-alliance.com/technologies/)

More information about devices and hardware can be found on:
- [PL460 Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/SE/ProductDocuments/DataSheets/PL460-Data-Sheet-DS60001666.pdf)
- [PL460 EK](https://www.microchip.com/en-us/development-tool/ev13l63a)
- [PL460-EK User Guide](https://ww1.microchip.com/downloads/aemDocuments/documents/MPU32/ProductDocuments/UserGuides/PL460-EK-User-Guide-DS50003322.pdf)
- [WBZ451 Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/WSG/ProductDocuments/DataSheets/PIC32CX-BZ2-and-WBZ45-Family-Data-Sheet-DS70005504.pdf)
- [WBZ451 Curiosity Board](https://www.microchip.com/en-us/development-tool/ev96b94a)
- [WBZ451 Curiosity Board User Guide](https://ww1.microchip.com/downloads/aemDocuments/documents/WSG/ProductDocuments/UserGuides/WBZ451-Curiosity-Board-User-Guide-DS50003367.pdf)

More information about the Sustainability Wall reference designs configured as G3 devices can be found on:

- [Liquid Detection Reference Design](https://www.microchip.com/en-us/development-tool/EV24U22A)
- [Solar Microinverter Reference Design](https://www.microchip.com/en-us/tools-resources/reference-designs/grid-connected-solar-microinverter)
- [Solar MPPT Battery charger Reference Design](https://www.microchip.com/en-us/tools-resources/reference-designs/solar-mppt-battery-charger-reference-design)
- [Energy Storage Reference Design](https://www.microchip.com/en-us/tools-resources/reference-designs/high-voltage-auxiliary-e-fuse-reference-design)
- [Heat Pump Reference Design](https://www.microchip.com/en-us/tools-resources/reference-designs/11-kw-totem-pole-demonstration-application)
- [EV Charger Reference Design](https://www.microchip.com/en-us/tools-resources/reference-designs/three-phase-ac-commercial-with-ocpp-and-display-electric-vehicle-charger-reference-design)
- [Electricity Meter Reference Design](https://www.microchip.com/en-us/development-tool/EV58E84A)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

[TOP](#contents)

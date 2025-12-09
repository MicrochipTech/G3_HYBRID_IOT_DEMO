# G3 HYBRID COORDINATOR <!-- omit in toc -->

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
- [Bill of Material](#bill-of-material)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
  - [Development Tools](#development-tools)
  - [MCC Content Libraries](#mcc-content-libraries)
  - [Harmony MCC Configuration](#harmony-mcc-configuration)
  - [Application](#application)
- [Board Programming](#board-programming)
- [Run the demo](#run-the-demo)
- [Links](#links)

## Introduction

According with G3 technologies[*](#links) each G3 network requires the existence of a G3 Coordinator. G3 Hybrid coordinator runs on a WBZ451 Curiosity Board connected with a PL460-EK using an adaptation board   

## Bill of Material

| TOOLS | QUANTITY |
| :- | :- |
| [PIC32CX-BZ2 and WBZ451 Curiosity Development Board](https://www.microchip.com/en-us/development-tool/EV96B94A) | 1 |
| [PL460 Evaluation Kit (rev4)](https://www.microchip.com/en-us/development-tool/ev13l63a) | 1 |
| [MikroBUS to PL460-EK adaptation board](docs/WBZ451mikroBUStoPL460EKadapter.png) | 1 |

## Hardware Setup

- The PL460-EK rev4 need to be modified with these changes:
  - Replace C9 by a 10K Pull Down resistor to GND (PL460_NRST)
  - Include 10K Pull Up resistor to 3V3 on PL460_ENABLE and cut trace to XPLAINED PRO connector
  - Include 10K Pull Down resistor to GND on PL460_STBY and cut trace to XPLAINED PRO connector

- Connect the PL460-EK to MikroBUS connector of WBZ451 with the adaptation board and supply it with the provided +15V Power Supply
- Connect PB13 and PB12 (available removing R11 and R16) on WBZ451 acting like coordinator to PD24 and PD25 available on J401 of PIC32CZCA80 Host Controller - Serial Port Communication. Connect also GND - pins 2 or 19 on XPLAINED PRO.
- Connect the +5V power supply on WBZ451 uUSB connector J7
- Connect a USB cable on J7 for device programming and debugging with terminal program

![G3 Hybrid Coordinator Design](docs/WBZ451_hybrid_coordinator.png)

## Software Setup
## Development Tools
  - MPLAB X v6.25
  - MPLAB® XC32 C/C++ Compiler v4.60
  - MPLAB® X IDE plug-ins: MPLAB® Code Configurator (MCC) v5.7.1 and above
  - Device Pack: PIC32CX-BZ2-DFP (1.4.243)
	
## MCC Content Libraries

| Harmony MCC dependencies | version  |
| :-                       | :-       |
| bsp                      | v3.20.1  |
| csp                      | v3.19.1  |
| core                     | v3.13.5  |
| CMSIS_5                  | v5.8.0   |
| wireless_pic32cxbz_wbz   | v1.2.0   |
| wolfssl                  | v5.6.7-E1|
| crypto                   | v4.0.0-E1|
| wireless_15_4_phy        | v1.2.0   |
| CMSIS-FreeRTOS           | v10.5.1  |
| smartenergy              | v1.2.1   |
| smartenergy_g3           | v1.0.1   |
| net                      | v3.12.0  |


## Harmony MCC Configuration

### Full Configuration

The full MCC configuration is:
![G3 coordinator MCC configuraion](docs/MCCconfiguration.png)

### System Console, Debugging and Command Line Interface
The system console is configured to use SERCOM1 in USART mode and is accessible via the DEBUG USB connector.

![G3 Coordinator MCC SERCOM1 Configuration](docs/MCC_SERCOM1_console_cmdline.png)
![G3 Coordinator MCC SERCOM1 Pins Configuration](docs/MCC_Pins_SERCOM1.png)

In addition to standard console functions, it supports debugging and provides a command line interface for direct interaction with the board.

![G3 Coordinator MCC Console+Debug+CmdLine Configuration](docs/MCCConsoleDebugCmdLine.png)

### G3 and PL460-EK interface

The G3 coordinator is configured to use SERCOM0 in SPI mode to access the PL460-EK.

![G3 Coordinator MCC SERCOM0 Configuration](docs/MCC_SERCOM0_spi_pl460.png)

The project uses MAC real time features on FCC band with default values for PLC PHY coupling. 

![G3 Coordinator MACrt for FCC band Configuration](docs/MCC_G3macrt.png)

The PIN configuration for the PL460 interface is:

![G3 Coordinator PL460 Interface Pin Configuration](docs/MCC_Pins_PL460.png)

The G3 stack full configuration is:

![G3 Coordinator Stack Full Configuration](docs/MCC_G3stack_main.png)

The G3 stack is configured in mode Hybrid PLC & RF with PAN Coordinator as role.

![G3 Coordinator Stack Configuration](docs/MCC_G3stack.png)

### USI Serialization with Host Controller
The application manages communication with the PIC32CZCA Host Controller by utilizing SERCOM3 in Serial Port mode.

![G3 Coordinator MCC SERCOM3 Configuration](docs/MCC_SERCOM3_usi.png)
![G3 Coordinator MCC SERCOM3 Pins Configuration](docs/MCC_Pins_SERCOM3.png)

This communication is based on the USI (Universal Serial Interface) Service from Smart Energy. 

![G3 Coordinator MCC USI service Configuration](docs/MCC_USI.png)

### RGB Led Configuration
The application identify some events acting over the RGB Led. Its configuration is:

![G3 Coordinator MCC RGB Led Pin Configuration](docs/MCC_Pins_LedRGB.png)

### Watchdog Configuration
The Watchdog is enabled to avoid any unhandled situation on the application.

![G3 Coordinator MCC Watchdog Configuration](docs/MCC_FusesWatchdog.png)

[TOP](#contents)

## Application

<b>The main functionalities of the G3 Coordinator are:</b>
* Register G3 devices in the G3 Network and assign a short address and MAC layer encryption key
* Pinging G3 devices in a loop way to keep the information about their availability
* Send commands to act/get information to/from G3 devices according with their functionality
* Notify alarms from Emergency Buttom

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

### G3 Hybrid coordinator specific configuration  

The G3 Hybrid coordinator has been configured fixing some parameters:
- <b>Short Address</b>: assigned short address is fixed according with the device type functionality of the G3 device.
- <b>Black List Table Entry TTL</b>: fixed to zero as the short address is fixed by device type. It avoids issues with joins from the same device.
- <b>PAN_ID</b>: PAN ID identifies the G3 network in use. It is masked to be on 0x782X range. 
- <b>PSK</b>: Pre-shared Key used on the registering process. Avoids to register any unexpected G3 device. A fixed value different from default used on G3 certification has been configured.
- <b>ADP PIBs</b>: These ADP Pibs have been set according with the network: MaxHops, RrepWait and NetTraversalTime.
- <b>MAC Tables</b>: The Device Table size has been set to 1 to allow fixed addressing without security problems.
- <b>RF Duty Cycle</b>: the limit has been fixed to 100% removing any transmission restriction

### G3 Hybrid coordinator applications  

The G3 coordinator is based on different application files:
- app_g3_management: keeps the G3 coordinator feature running. 
- app_tcpip_management: keeps the TCP/IP stack available to be able to interact with the network at UDP layer and also keep the UDP responder server where the alarms are received.
- app_eap_server: provides the G3 coordinator registering and short address asignation feature.
- app_udp_responder: provides a UDP server where receive any notification from devices like alarms.
- app_cycling: provides the mechanism to transmit/receive information to/from the devices registered in the network; additionally implements a pinging cycling procedure to keep their availability. Besides, includes a queue for sending any additional command to the devices with the highest priority.
- app_interface: implements a command line mechanism to interface with the G3 network (through the queue implemented in the app_cycling) and manage local information and features (like registered devices information)
- app_usi_device: implements a mechanisms to serialize the command/notifications interchange between the G3 coordinator an the Host Controller based on PIC32CZCA80.

![G3 coordinator apps](docs/G3coordinatorApps.png)

### Communication Protocol

The communication protocol starts with the G3 registering process interchange. After the device has joined the G3 network, the device is included into the pool of devices to ping in a cycling way (each minute in a normal situation) to keep their availability. The ping mechanism is based on the request of the device type and the answer from the device. When a device is alive, any additional command to interact with it can be sent.

![G3 coordinator packets interchange](docs/CommunicationProtocol.png)

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

### G3 Cycling State Machine

The state machine of the G3 Coordinator cycling can be summarize on:

![G3 cycling state machine](docs/G3coordinatorCyclingStateMachine.png)

### Communication Protocol between G3 Coordinator and Host Controller

The communication protocol between the G3 coodinator and the Host Controller runs over the USI Service serialization from <a href="https://github.com/Microchip-MPLAB-Harmony/smartenergy" target="_blank">Microhip MPLAB Harmony smartenergy repository</a>.

Communication is initiated when the G3 Coordinator sends a notification of a reset (under normal conditions) or a heartbeat (if an unmanaged reset occurs on the host). Following this event, the host controller begins to periodically request complete device information, typically every minute, to monitor device availability.

The communication protocol utilizes G3 Coordinator commands to manage and interact with G3 devices on the network. It also includes supplementary commands to handle and notify information or events reported by the G3 Coordinator.

| ID   | NAME                    | SOURCE | DESTINATION | FEATURE                                      |
| :--- | :---------------------- | :----- | :---------- | :------------------------------------------- |
| 0xF4 | GET_DEVICE_INFO         | HOST   | COORD       | Get the Device Type Information              |
| 0xF6 | SET_RGB_LED             | HOST   | COORD       | Set the RGB LED colour                       |
| 0xF8 | SET_RGB_LED_BLINK       | HOST   | COORD       | As previous blinking with a freq a while     |
| 0xFA | SET_PANEL_INFO          | HOST   | COORD       | Set the information shown in the Panel LED   |
| 0xFC | EMERGENCY               | COORD  | HOST        | Emergency Alarm received                     |
| 0xFE | SET_LIGHT               | HOST   | COORD       | Set the light state of a Lighting Device     |
| 0xE0 | CMD_GET_DEVICES         | HOST   | COORD       | Request Registered Devices to Coordinator    |
| 0xE1 | CMD_GET_DEVICES_ANSWER  | COORD  | HOST        | Answer to request                            |
| 0xE2 | CMD_DEVICE_NOTIFICATION | COORD  | HOST        | Change of device information                 |
| 0xE3 | CMD_RESET_NOTIFICATION  | COORD  | HOST        | Coordinator reset occured                    |
| 0xE4 | CMD_HEARTBEAT           | COORD  | HOST        | Coordinator heartbeat, received periodically |

### G3 Command Line Interface

The project includes a CLI with these commands:

| COMMAND | PARAMS | Description |
| :- | :- | :- | 
|SET_LIGHT|<X(dest)> <0-1>|Set light 0:off, 1:on|
|SET_PANEL_INFO|<X(dest)> <0-1>|Set Panel Led (0:Logo, 1:Alarm)|
|SET_RGB|<X(dest)> <X(H)> <X(S)> <X(V)>|Set RGB Led colour - HSV Format|
|SET_RGBB|<X(dest)> <X(H)> <X(S)> <X(V)> <X(freq)> <X(time)>|Set RGB Led Colour, Blink and Duration|
|PING|<X(dest)>| Ping device X|
|REGDEV|None|Show G3 registered devices|
|DBGLVL|<0-4>|Debug Level <Fatal,Error,Warning,Info,Debug>|
|RST|None|Resets the board|
|GET_PIB|<LVL(0-3)> <PIB(hex)> <INDEX(hex)>| Get G3 Stack PIB|
|SET_PIB|<LVL(0-3)> <PIB(hex)> <INDEX(hex)> <LEN> <VALUE(hex)| Set G3 Stack PIB|

where:
| Device | X(dest)
| :- | :- |
|Indoor Lighting|0|
|Outdoor Lighting|1|
|Liquid Detector|3|
|Solar Inverter|4|
|Battery Charger|5|
|Energy Storage|6|
|Heat Pump|7|
|EV Charger|8|
|Electricity Meter|9|
|Emergency Button|10|
|LED Panel|11|

| Color | X(H)|
| :-    | :-  |
|Red    |00   |
|Yellow |2B   |
|Green  |55   |
|Cyan   |80   |
|Blue   |AA   |
|Magenta|D5   |

[TOP](#contents)

## Board Programming

Programming the application can be done using MPLAB X IDE
- Open the given project using MPLAB X IDE
- Select the connected hardware tool in the project properties
- Make and program device

[TOP](#contents)

## Run the demo

After powering up the WBZ451 (5V Power Supply) + PL460 (15V Power Supply), the coordinator starts creating the G3 Network. It keeps waiting for G3 devices start joining the network through PLC or RF. At the same time the information about the status of the G3 devices is notified to PICZA80 Host Controller through the serial port between both.

Each time an alarm is sent from the Emergency Button, the RGB LED on G3 coordinator keeps on red for 2 seconds.

<b>UART interface</b>  
For debugging purposes, a UART interface to the PC is implemented. A serial port terminal (e.g. PuTTY) can be used to open a connection to the device.  
  
USART configuration:
- Baud rate: 115 200 Hz
- Parity mode: no parity
- Stop bit mode: 1 Stop bit

[TOP](#contents)

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

[TOP](#contents)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

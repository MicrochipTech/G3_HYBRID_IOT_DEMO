/*******************************************************************************
  System Configuration Header

  File Name:
    configuration.h

  Summary:
    Build-time configuration header for the system defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "user.h"
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Configuration
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
/*----------------- WINCS Net System Service Configuration -----------------*/
#define SYS_WINCS_NET_BIND_TYPE0                SYS_WINCS_NET_BIND_LOCAL
#define SYS_WINCS_NET_SOCK_TYPE0                SYS_WINCS_NET_SOCK_TYPE_TCP 
#define SYS_WINCS_NET_SOCK_TYPE_IPv4_0          4
#define SYS_WINCS_NET_SOCK_TYPE_IPv6_LOCAL0     0
#define SYS_WINCS_NET_SOCK_TYPE_IPv6_GLOBAL0    0
#define SYS_WINCS_NET_SOCK_PORT0                80
#define SYS_WINCS_TLS_ENABLE0                   0
/*----------------------------------------------------------------------------*/

/* -----------------WINCS02 MQTT System Service Configuration ----------------- */

#define SYS_WINCS_MQTT_PROTO_VERSION             SYS_WINCS_MQTT_PROTO_VER_3

#define SYS_WINCS_MQTT_CLOUD_URL                 "test.mosquitto.org"
#define SYS_WINCS_MQTT_CLOUD_PORT                1883
#define SYS_WINCS_MQTT_CLIENT_ID                 "mchp_enlit_demo_dev01"
#define SYS_WINCS_MQTT_CLOUD_USER_NAME           ""
#define SYS_WINCS_MQTT_PASSWORD                  ""
#define SYS_WINCS_MQTT_CLEAN_SESSION             true
#define SYS_WINCS_MQTT_KEEP_ALIVE_TIME           60
#define SYS_WINCS_MQTT_SUB_TOPIC_0               "endpointId/dcx/token1"
#define SYS_WINCS_MQTT_SUB_TOPIC_0_QOS           SYS_WINCS_MQTT_QOS0


#define SYS_WINCS_MQTT_PUB_TOPIC_NAME            "endpointId/dcx/token1/json"
#define SYS_WINCS_MQTT_PUB_MSG                   "{\"alarm\": 1}"
#define SYS_WINCS_MQTT_PUB_MSG_QOS_TYPE          SYS_WINCS_MQTT_QOS0
#define SYS_WINCS_MQTT_PUB_MSG_RETAIN            false
#define SYS_WINCS_MQTT_TLS_ENABLE                false
#define SYS_WINCS_MQTT_AZURE_DPS_ENABLE          false
#define SYS_WINCS_MQTT_DEBUG_LOGS                1
#define SYS_WINCS_MQTT_CallbackHandler           APP_MQTT_Callback

/*----------------------------------------------------------------------------*/

/* TIME System Service Configuration Options */
#define SYS_TIME_INDEX_0                            (0)
#define SYS_TIME_MAX_TIMERS                         (25)
#define SYS_TIME_HW_COUNTER_WIDTH                   (32)
#define SYS_TIME_TICK_FREQ_IN_HZ                    (1024)

#define SYS_CONSOLE_INDEX_0                       0





#define SYS_CMD_ENABLE
#define SYS_CMD_DEVICE_MAX_INSTANCES       SYS_CONSOLE_DEVICE_MAX_INSTANCES
#define SYS_CMD_PRINT_BUFFER_SIZE          2560U
#define SYS_CMD_BUFFER_DMA_READY



#define SYS_DEBUG_ENABLE
#define SYS_DEBUG_GLOBAL_ERROR_LEVEL       SYS_ERROR_DEBUG
#define SYS_DEBUG_BUFFER_DMA_READY
#define SYS_DEBUG_USE_CONSOLE
//#define APP_LTE_DEBUG_LOGS


/* File System Service Configuration */

#define SYS_FS_MEDIA_NUMBER               (1U)
#define SYS_FS_VOLUME_NUMBER              (1U)

#define SYS_FS_AUTOMOUNT_ENABLE           true
#define SYS_FS_CLIENT_NUMBER              1U
#define SYS_FS_MAX_FILES                  (5U)
#define SYS_FS_MAX_FILE_SYSTEM_TYPE       (1U)
#define SYS_FS_MEDIA_MAX_BLOCK_SIZE       (512U)
#define SYS_FS_MEDIA_MANAGER_BUFFER_SIZE  (2048U)
#define SYS_FS_USE_LFN                    (1)
#define SYS_FS_FILE_NAME_LEN              (255U)
#define SYS_FS_CWD_STRING_LEN             (1024)


#define SYS_FS_FAT_VERSION                "v0.15"
#define SYS_FS_FAT_READONLY               false
#define SYS_FS_FAT_CODE_PAGE              437
#define SYS_FS_FAT_MAX_SS                 SYS_FS_MEDIA_MAX_BLOCK_SIZE
#define SYS_FS_FAT_ALIGNED_BUFFER_LEN     512





#define SYS_FS_MEDIA_TYPE_IDX0 				SYS_FS_MEDIA_TYPE_SD_CARD
#define SYS_FS_TYPE_IDX0 					FAT
					
#define SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0 			"/mnt/myDrive1"
#define SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0			"/dev/mmcblka1"
								

#define SYS_CONSOLE_DEVICE_MAX_INSTANCES   			(1U)
#define SYS_CONSOLE_UART_MAX_INSTANCES 	   			(1U)
#define SYS_CONSOLE_USB_CDC_MAX_INSTANCES 	   		(0U)
#define SYS_CONSOLE_PRINT_BUFFER_SIZE        		(1024U)




// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
/* I2C Driver Instance 0 Configuration Options */
#define DRV_I2C_INDEX_0                       0
#define DRV_I2C_CLIENTS_NUMBER_IDX0           1
#define DRV_I2C_QUEUE_SIZE_IDX0               2
#define DRV_I2C_CLOCK_SPEED_IDX0              100

/*** WiFi WINC Driver Configuration ***/
#define WDRV_WINC_EIC_SOURCE
#define WDRV_WINC_DEVICE_USE_SYS_DEBUG
#define WDRV_WINC_DEV_RX_BUFF_SZ            2048
#define WDRV_WINC_DEV_SOCK_SLAB_NUM         10
#define WDRV_WINC_DEV_SOCK_SLAB_SZ          1472
#define WINC_SOCK_NUM_SOCKETS               5
#define WINC_SOCK_BUF_RX_SZ                 128
#define WINC_SOCK_BUF_TX_SZ                 128
#define WINC_SOCK_BUF_RX_PKT_BUF_NUM        5
#define WINC_SOCK_BUF_TX_PKT_BUF_NUM        5
#define WDRV_WINC_MOD_DISABLE_OTA


/* USI Service Common Configuration Options */
#define SRV_USI_INSTANCES_NUMBER              1U
#define SRV_USI_USART_CONNECTIONS             1U
#define SRV_USI_CDC_CONNECTIONS               0U
#define SRV_USI_MSG_POOL_SIZE                 5U
/* I2C Driver Common Configuration Options */
#define DRV_I2C_INSTANCES_NUMBER              (1U)



/*** MXT336T Driver Configuration ***/
#define DRV_MAXTOUCH_I2C_MODULE_INDEX   0

/* SDMMC Driver Global Configuration Options */
#define DRV_SDMMC_INSTANCES_NUMBER                       (1U)


/* USI Service Instance 0 Configuration Options */
#define SRV_USI_INDEX_0                       0
#define SRV_USI0_RD_BUF_SIZE                  1024
#define SRV_USI0_WR_BUF_SIZE                  1024


/*** SDMMC Driver Instance 0 Configuration ***/
#define DRV_SDMMC_INDEX_0                                0
#define DRV_SDMMC_IDX0_CLIENTS_NUMBER                    1
#define DRV_SDMMC_IDX0_QUEUE_SIZE                        2
#define DRV_SDMMC_IDX0_PROTOCOL_SUPPORT                  DRV_SDMMC_PROTOCOL_SD
#define DRV_SDMMC_IDX0_CONFIG_SPEED_MODE                 DRV_SDMMC_SPEED_MODE_DEFAULT
#define DRV_SDMMC_IDX0_CONFIG_BUS_WIDTH                  DRV_SDMMC_BUS_WIDTH_4_BIT
#define DRV_SDMMC_IDX0_CARD_DETECTION_METHOD             DRV_SDMMC_CD_METHOD_USE_SDCD





// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************
/* Number of CDC Function driver instances in the application */
#define USB_HOST_CDC_INSTANCES_NUMBER         1U

/* Number of CDC Attach Listeners */ 
#define USB_HOST_CDC_ATTACH_LISTENERS_NUMBER        1U


/* Number High Speed USB Driver instances */ 
#define DRV_USBHS_INSTANCES_NUMBER                       1U

/* Interrupt mode enabled */
#define DRV_USBHS_INTERRUPT_MODE                          true

/* Enables Device Support */
#define DRV_USBHS_DEVICE_SUPPORT                          false

#define DRV_USBHS_ENDPOINTS_NUMBER                        1U

/* Enable Host Support */
#define DRV_USBHS_HOST_SUPPORT                            true

/* Number of NAKs to wait before returning transfer failure */ 
#define DRV_USBHS_HOST_NAK_LIMIT                          2000 

/* Maximum Number of pipes */
#define DRV_USBHS_HOST_PIPES_NUMBER                       10  

/* Attach Debounce duration in milli Seconds */ 
#define DRV_USBHS_HOST_ATTACH_DEBOUNCE_DURATION           500

/* Reset duration in milli Seconds */ 
#define DRV_USBHS_HOST_RESET_DURATION                     250

/* Alignment for buffers that are submitted to USB Driver*/ 
#define USB_ALIGN  CACHE_ALIGN

// *****************************************************************************
// *****************************************************************************
// Section: USB Host Layer Configuration
// *****************************************************************************
// **************************************************************************

/* Total number of devices to be supported */
#define USB_HOST_DEVICES_NUMBER                             3 

/* Number of Target peripheral list (TPL) entries. */
#define  USB_HOST_TPL_ENTRIES                               2 

/* Maximum number of interfaces per device. */
#define USB_HOST_DEVICE_INTERFACES_NUMBER                   5  

/* Number of USB Controllers. */
#define USB_HOST_CONTROLLERS_NUMBER                         1  

/* The maximum number of simultaneous transfers that can be submitted. */ 
#define USB_HOST_TRANSFERS_NUMBER                           10

/* The maximum number of pipes that the USB Host layer can utilize. */
#define USB_HOST_PIPES_NUMBER                               10

/* Number of HUB Function driver instances in the application */
#define USB_HOST_HUB_SUPPORT                  true
#define USB_HOST_HUB_INSTANCES_NUMBER         2
#define USB_HOST_HUB_PORTS_NUMBER             4

/* WINCS02  WIFI System Service Configuration Options */

#define SYS_WINCS_WIFI_DEVMODE              SYS_WINCS_WIFI_MODE_STA

#define SYS_WINCS_WIFI_STA_SSID             "DEMO_AP"
#define SYS_WINCS_WIFI_STA_PWD              "password"
#define SYS_WINCS_WIFI_STA_SECURITY         SYS_WINCS_WIFI_SECURITY_WPA2 
#define SYS_WINCS_WIFI_STA_AUTOCONNECT      true

#define SYS_WINCS_WIFI_PROV_DEVMODE         SYS_WINCS_WIFI_MODE_AP
#define SYS_WINCS_WIFI_PROV_SSID            "AP_HYBRID_IOT"
#define SYS_WINCS_WIFI_PROV_PWD             "microchip"
#define SYS_WINCS_WIFI_PROV_SSID_VISIBILITY false // false = visible
#define SYS_WINCS_WIFI_PROV_SECURITY        SYS_WINCS_WIFI_SECURITY_WPA2
#define SYS_WINCS_WIFI_PROV_MOBILE_APP      1
#define SYS_WINCS_WIFI_PROV_CHANNEL         1
#define SYS_WINCS_WIFI_AP_IP_ADDR           "192.168.1.1"
#define SYS_WINCS_WIFI_AP_IP_POOL_START     "192.168.1.50"
#define SYS_WINCS_WIFI_COUNTRYCODE          "GEN"
#define SYS_WINCS_WIFI_SNTP_ADDRESS          "216.239.35.4"


#define SYS_WINCS_WIFI_CallbackHandler	     APP_WIFI_Callback


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // CONFIGURATION_H
/*******************************************************************************
 End of File
*/

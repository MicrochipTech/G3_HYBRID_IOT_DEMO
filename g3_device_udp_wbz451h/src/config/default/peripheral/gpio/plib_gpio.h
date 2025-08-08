/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************

/*** Macros for PLC_SPI_CS pin ***/
#define PLC_SPI_CS_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<6U))
#define PLC_SPI_CS_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<6U))
#define PLC_SPI_CS_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<6U))
#define PLC_SPI_CS_Get()               ((GPIOB_REGS->GPIO_PORT >> 6U) & 0x1U)
#define PLC_SPI_CS_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<6U))
#define PLC_SPI_CS_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<6U))
#define PLC_SPI_CS_PIN                  GPIO_PIN_RB6
/*** Macros for USER_LED pin ***/
#define USER_LED_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<7U))
#define USER_LED_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<7U))
#define USER_LED_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<7U))
#define USER_LED_Get()               ((GPIOB_REGS->GPIO_PORT >> 7U) & 0x1U)
#define USER_LED_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<7U))
#define USER_LED_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<7U))
#define USER_LED_PIN                  GPIO_PIN_RB7
/*** Macros for PLC_ENABLE pin ***/
#define PLC_ENABLE_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<9U))
#define PLC_ENABLE_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<9U))
#define PLC_ENABLE_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<9U))
#define PLC_ENABLE_Get()               ((GPIOB_REGS->GPIO_PORT >> 9U) & 0x1U)
#define PLC_ENABLE_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<9U))
#define PLC_ENABLE_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<9U))
#define PLC_ENABLE_PIN                  GPIO_PIN_RB9
/*** Macros for PLC_RST pin ***/
#define PLC_RST_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<4U))
#define PLC_RST_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<4U))
#define PLC_RST_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<4U))
#define PLC_RST_Get()               ((GPIOA_REGS->GPIO_PORT >> 4U) & 0x1U)
#define PLC_RST_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<4U))
#define PLC_RST_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<4U))
#define PLC_RST_PIN                  GPIO_PIN_RA4
/*** Macros for PANEL_C pin ***/
#define PANEL_C_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<11U))
#define PANEL_C_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<11U))
#define PANEL_C_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<11U))
#define PANEL_C_Get()               ((GPIOB_REGS->GPIO_PORT >> 11U) & 0x1U)
#define PANEL_C_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<11U))
#define PANEL_C_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<11U))
#define PANEL_C_PIN                  GPIO_PIN_RB11
/*** Macros for PLC_TX_ENABLE pin ***/
#define PLC_TX_ENABLE_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<0U))
#define PLC_TX_ENABLE_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<0U))
#define PLC_TX_ENABLE_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<0U))
#define PLC_TX_ENABLE_Get()               ((GPIOA_REGS->GPIO_PORT >> 0U) & 0x1U)
#define PLC_TX_ENABLE_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<0U))
#define PLC_TX_ENABLE_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<0U))
#define PLC_TX_ENABLE_PIN                  GPIO_PIN_RA0
/*** Macros for PANEL_LAT pin ***/
#define PANEL_LAT_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<1U))
#define PANEL_LAT_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<1U))
#define PANEL_LAT_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<1U))
#define PANEL_LAT_Get()               ((GPIOA_REGS->GPIO_PORT >> 1U) & 0x1U)
#define PANEL_LAT_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<1U))
#define PANEL_LAT_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<1U))
#define PANEL_LAT_PIN                  GPIO_PIN_RA1
/*** Macros for PANEL_OE pin ***/
#define PANEL_OE_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<12U))
#define PANEL_OE_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<12U))
#define PANEL_OE_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<12U))
#define PANEL_OE_Get()               ((GPIOB_REGS->GPIO_PORT >> 12U) & 0x1U)
#define PANEL_OE_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<12U))
#define PANEL_OE_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<12U))
#define PANEL_OE_PIN                  GPIO_PIN_RB12
/*** Macros for PANEL_B pin ***/
#define PANEL_B_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<13U))
#define PANEL_B_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<13U))
#define PANEL_B_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<13U))
#define PANEL_B_Get()               ((GPIOB_REGS->GPIO_PORT >> 13U) & 0x1U)
#define PANEL_B_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<13U))
#define PANEL_B_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<13U))
#define PANEL_B_PIN                  GPIO_PIN_RB13
/*** Macros for PANEL_D pin ***/
#define PANEL_D_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<5U))
#define PANEL_D_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<5U))
#define PANEL_D_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<5U))
#define PANEL_D_Get()               ((GPIOA_REGS->GPIO_PORT >> 5U) & 0x1U)
#define PANEL_D_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<5U))
#define PANEL_D_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<5U))
#define PANEL_D_PIN                  GPIO_PIN_RA5
/*** Macros for PANEL_R2 pin ***/
#define PANEL_R2_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<6U))
#define PANEL_R2_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<6U))
#define PANEL_R2_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<6U))
#define PANEL_R2_Get()               ((GPIOA_REGS->GPIO_PORT >> 6U) & 0x1U)
#define PANEL_R2_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<6U))
#define PANEL_R2_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<6U))
#define PANEL_R2_PIN                  GPIO_PIN_RA6
/*** Macros for PANEL_A pin ***/
#define PANEL_A_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<8U))
#define PANEL_A_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<8U))
#define PANEL_A_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<8U))
#define PANEL_A_Get()               ((GPIOA_REGS->GPIO_PORT >> 8U) & 0x1U)
#define PANEL_A_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<8U))
#define PANEL_A_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<8U))
#define PANEL_A_PIN                  GPIO_PIN_RA8
/*** Macros for PANEL_R1 pin ***/
#define PANEL_R1_Set()               (GPIOA_REGS->GPIO_LATSET = (1U<<7U))
#define PANEL_R1_Clear()             (GPIOA_REGS->GPIO_LATCLR = (1U<<7U))
#define PANEL_R1_Toggle()            (GPIOA_REGS->GPIO_LATINV= (1U<<7U))
#define PANEL_R1_Get()               ((GPIOA_REGS->GPIO_PORT >> 7U) & 0x1U)
#define PANEL_R1_OutputEnable()      (GPIOA_REGS->GPIO_TRISCLR = (1U<<7U))
#define PANEL_R1_InputEnable()       (GPIOA_REGS->GPIO_TRISSET = (1U<<7U))
#define PANEL_R1_PIN                  GPIO_PIN_RA7
/*** Macros for PANEL_CLK pin ***/
#define PANEL_CLK_Set()               (GPIOB_REGS->GPIO_LATSET = (1U<<2U))
#define PANEL_CLK_Clear()             (GPIOB_REGS->GPIO_LATCLR = (1U<<2U))
#define PANEL_CLK_Toggle()            (GPIOB_REGS->GPIO_LATINV= (1U<<2U))
#define PANEL_CLK_Get()               ((GPIOB_REGS->GPIO_PORT >> 2U) & 0x1U)
#define PANEL_CLK_OutputEnable()      (GPIOB_REGS->GPIO_TRISCLR = (1U<<2U))
#define PANEL_CLK_InputEnable()       (GPIOB_REGS->GPIO_TRISSET = (1U<<2U))
#define PANEL_CLK_PIN                  GPIO_PIN_RB2


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

#define    GPIO_PORT_A   (GPIOA_BASE_ADDRESS)
#define    GPIO_PORT_B   (GPIOB_BASE_ADDRESS)
typedef uint32_t GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/


#define     GPIO_PIN_RA0  (0U)
#define     GPIO_PIN_RA1  (1U)
#define     GPIO_PIN_RA2  (2U)
#define     GPIO_PIN_RA3  (3U)
#define     GPIO_PIN_RA4  (4U)
#define     GPIO_PIN_RA5  (5U)
#define     GPIO_PIN_RA6  (6U)
#define     GPIO_PIN_RA7  (7U)
#define     GPIO_PIN_RA8  (8U)
#define     GPIO_PIN_RA11  (11U)
#define     GPIO_PIN_RA12  (12U)
#define     GPIO_PIN_RA13  (13U)
#define     GPIO_PIN_RA14  (14U)
#define     GPIO_PIN_RB0  (16U)
#define     GPIO_PIN_RB2  (18U)
#define     GPIO_PIN_RB3  (19U)
#define     GPIO_PIN_RB4  (20U)
#define     GPIO_PIN_RB5  (21U)
#define     GPIO_PIN_RB6  (22U)
#define     GPIO_PIN_RB7  (23U)
#define     GPIO_PIN_RB8  (24U)
#define     GPIO_PIN_RB9  (25U)
#define     GPIO_PIN_RB10  (26U)
#define     GPIO_PIN_RB11  (27U)
#define     GPIO_PIN_RB12  (28U)
#define     GPIO_PIN_RB13  (29U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE    (-1)

typedef uint32_t GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
	uint32_t xvalue = (uint32_t)value;
    GPIO_PortWrite((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)(0x1U) << (pin & 0xFU), (xvalue) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return ((((GPIO_PortRead((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))))) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (((GPIO_PortLatchRead((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4)))) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))), (uint32_t)0x1U << (pin & 0xFU));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H

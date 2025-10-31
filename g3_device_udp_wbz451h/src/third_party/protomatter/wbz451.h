/*!
 * @file wbz451.h
 *
 * Part of Adafruit's Protomatter library for HUB75-style RGB LED matrices.
 * This file contains WBZ451-MPLAB HARMONY SPECIFIC CODE.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Phil "Paint Your Dragon" Burgess and Jeff Epler for
 * Adafruit Industries, with contributions from the open source community.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#pragma once

#include "definitions.h"

#define _PM_portOutRegister(pin)       &((gpio_registers_t*)(GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))))->GPIO_TRISCLR
#define _PM_portSetRegister(pin)       &((gpio_registers_t*)(GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))))->GPIO_LATSET 
#define _PM_portClearRegister(pin)     &((gpio_registers_t*)(GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))))->GPIO_LATCLR 
#define _PM_portToggleRegister(pin)    &((gpio_registers_t*)(GPIOA_BASE_ADDRESS + (0x100U * (pin>>4U))))->GPIO_LATINV 
#define _PM_delayMicroseconds(us)      APP_MATRIX_LED_TaskDelayUS(us)
        
#define _PM_pinOutput(pin)      GPIO_PinOutputEnable(pin)
#define _PM_pinInput(pin)       GPIO_PinInputEnable(pin)
#define _PM_pinHigh(pin)        GPIO_PinSet(pin)
#define _PM_pinLow(pin)         GPIO_PinClear(pin)
#define _PM_pinToggle(pin)      GPIO_PinToggle(pin)
#define _PM_portBitMask(pin)    (1u << pin)

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _PM_byteOffset(pin) ((pin & 31) / 8)
#define _PM_wordOffset(pin) ((pin & 31) / 16)
#else
#define _PM_byteOffset(pin) (3 - ((pin & 31) / 8))
#define _PM_wordOffset(pin) (1 - ((pin & 31) / 16))
#endif

#define _PM_chunkSize 8

#define _PM_PORT_TYPE uint32_t

// CircuitPython implementation is tied to a specific freq (but the counter
// is dynamically allocated):
#define _PM_timerFreq 64000000

// As currently implemented, there can be only one instance of the
// Protomatter_core struct. This pointer is set up when starting the matrix.
void *_PM_protoPtr = NULL;

// Timer interrupt service routine
void _PM_IRQ_HANDLER(uintptr_t context) {
  _PM_row_handler((Protomatter_core *) context); // In core.c
}

// Initialize, but do not start, timer
void _PM_timerInit(Protomatter_core *core) {
  // Timer is configured on initialization.c
  // Set Timer Callback here
  TC3_CompareCallbackRegister((TC_COMPARE_CALLBACK)_PM_IRQ_HANDLER, (uintptr_t) core);
}

// Set timer period, initialize count value to zero, enable timer.
// Timer must be initialized to 16-bit mode using the init function
// above, but must be inactive before calling this.
inline void _PM_timerStart(Protomatter_core *core, uint32_t period) {
  TC3_Compare16bitCounterSet(0);
  TC3_Compare16bitCounterSet(period);
  TC3_CompareStart();
}

// Return current count value (timer enabled or not).
// Timer must be previously initialized.
inline uint32_t _PM_timerGetCount(Protomatter_core *core) {
  return TC3_Compare16bitCounterGet();
}

// Disable timer and return current count value.
// Timer must be previously initialized.
inline uint32_t _PM_timerStop(Protomatter_core *core) {
  uint32_t count = _PM_timerGetCount(core);
  TC3_CompareStop();
  return count;
}

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

#ifndef _COMMON_H    /* Guard against multiple inclusion */
#define _COMMON_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "definitions.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

#define APP_RES_SUCCESS                         (0x0000U)               /**< Execution successfully. */
#define APP_RES_FAIL                            (0x0001U)               /**< Execution fail. */
#define APP_RES_OOM                             (0x0002U)               /**< Out of memory. */
#define APP_RES_INVALID_PARA                    (0x0003U)               /**< Invalid parameters. */
#define APP_RES_NO_RESOURCE                     (0x0004U)               /**< No resource. */
#define APP_RES_BAD_STATE                       (0x0005U)               /**< Bad State. */
#define APP_RES_PENDING_DUE_TO_SECURITY         (0x0006U)               /**< Pending the request due to security process. */
#define APP_RES_BUSY                            (0x0007U)               /**< Execution fail due to system is busy. */
#define APP_RES_COMPLETE                        (0x1000U)               /**< Some procedure is complete to distinguish execution successfully */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    extern uint16_t COMMON_UintRangeCheck(uint16_t value, uint16_t rangeMin, uint16_t rangeMax);
    extern uint16_t COMMON_AsciiToDec(uint8_t asciiCode, uint8_t *value, uint8_t rangeMin, uint8_t rangeMax);
    extern uint16_t COMMON_U8AsciiToHex(uint8_t *p_asciCode, uint8_t *value);
    extern uint16_t COMMON_U16AsciiToHex(uint8_t *p_asciCode, uint16_t *value);
    extern uint16_t COMMON_U32AsciiToHex(uint8_t *p_asciCode, uint32_t *value);
    extern uint16_t COMMON_StringToHex(uint8_t *p_asciCode, uint8_t *p_hex, uint8_t hexLen);
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H */

/* *****************************************************************************
 End of File
 */

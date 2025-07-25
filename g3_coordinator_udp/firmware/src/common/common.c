/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "common.h"
#include <ctype.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
uint16_t COMMON_UintRangeCheck(uint16_t value, uint16_t rangeMin, uint16_t rangeMax)
{
    if ((value > rangeMax) || (value < rangeMin))
        return APP_RES_INVALID_PARA;
    else
        return APP_RES_SUCCESS;
}
    
uint16_t COMMON_AsciiToDec(uint8_t asciiCode, uint8_t *value, uint8_t rangeMin, uint8_t rangeMax)
{
    if ((asciiCode >= '0') && (asciiCode <= '9'))
        *value = asciiCode - '0';
    else
        return APP_RES_INVALID_PARA;

    return COMMON_UintRangeCheck(*value, rangeMin, rangeMax);
}

uint16_t COMMON_U8AsciiToHex(uint8_t *p_asciCode, uint8_t *value)
{
    unsigned int hexValue;

    if(p_asciCode == NULL)
    {
        return APP_RES_INVALID_PARA;
    }
    for(uint8_t i = 0; i < strlen((char *)p_asciCode); i++)
    {
        if(!isxdigit(p_asciCode[i]))
        {
            return APP_RES_INVALID_PARA;
        }
    }

    sscanf((const char *)&p_asciCode[0], "%02x", &hexValue);
    *value = (uint8_t)hexValue;
    return APP_RES_SUCCESS;
}

uint16_t COMMON_U16AsciiToHex(uint8_t *p_asciCode, uint16_t *value)
{
    unsigned int hexValue;

    if(p_asciCode == NULL)
    {
        return APP_RES_INVALID_PARA;
    }
    for(uint8_t i = 0; i < strlen((char *)p_asciCode); i++)
    {
        if(!isxdigit(p_asciCode[i]))
        {
            return APP_RES_INVALID_PARA;
        }
    }

    sscanf((const char *)&p_asciCode[0], "%04x", &hexValue);
    *value = (uint16_t)hexValue;
    return APP_RES_SUCCESS;
}

uint16_t COMMON_U32AsciiToHex(uint8_t *p_asciCode, uint32_t *value)
{
    unsigned long hexValue;

    if(p_asciCode == NULL)
    {
        return APP_RES_INVALID_PARA;
    }
    for(uint8_t i = 0; i < strlen((char *)p_asciCode); i++)
    {
        if(!isxdigit(p_asciCode[i]))
        {
            return APP_RES_INVALID_PARA;
        }
    }

    sscanf((const char *)&p_asciCode[0], "%08lx", &hexValue);
    *value = (uint32_t)hexValue;
    return APP_RES_SUCCESS;
}

uint16_t COMMON_StringToHex(uint8_t *p_asciCode, uint8_t *p_hex, uint8_t hexLen)//ToDo: need to check the fail case in the code of the caller
{
    uint8_t i;

    for(i = 0; i < hexLen; i++)
    {
        if (COMMON_U8AsciiToHex(&p_asciCode[2*i], (p_hex+i)) != APP_RES_SUCCESS)
            return APP_RES_FAIL;
    }

    return APP_RES_SUCCESS;
}


/* *****************************************************************************
 End of File
 */

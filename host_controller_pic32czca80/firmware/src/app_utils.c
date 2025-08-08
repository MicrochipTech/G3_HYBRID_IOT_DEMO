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

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "definitions.h"

/**************************************************************************//**
Converts Hue/Saturation/Value values of the color to corresponding R/G/B values
******************************************************************************/
void HSV2RGB(unsigned int hue, unsigned int saturation,unsigned int level, unsigned int *calcR, unsigned int *calcG, unsigned int *calcB)
{
  unsigned int var_i;
  float V,H,S, var_h,var_1,var_2,var_3,var_r,var_g,var_b;
  
  H = (float) hue/255;
  S = (float) saturation/255;
  V = (float) level/255;

  if (saturation == 0)
  {
    var_r = V;
    var_g = V;
    var_b = V;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) 
       var_h = 0;
    var_i = (unsigned int)var_h ;
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    switch (var_i)
    {
        case 0:
        { 
            var_r = V;
            var_g = var_3;
            var_b = var_1;
        }
        break;
            
        case 1:
        {
            var_r = var_2;
            var_g = V; 
            var_b = var_1;
        }
        break;
            
        case 2:
        {
            var_r = var_1 ;
            var_g = V; 
            var_b = var_3;                
        }
        break;
            
        case 3:
        {
            var_r = var_1 ;
            var_g = var_2 ;
            var_b = V ;
        }
        break;
            
        case 4:
        {
            var_r = var_3 ; 
            var_g = var_1 ; 
            var_b = V;                
        }
        break;
            
        default:
        {
            var_r = V     ;
            var_g = var_1 ;
            var_b = var_2 ;               
        }
        break;
    }
  }

   *calcR = var_r * 65535;
   *calcG = var_g * 65535;
   *calcB = var_b * 65535;
}

void RGB2HSV(unsigned char r, unsigned char g, unsigned char b, unsigned char * h, unsigned char * s, unsigned char * v)
{
    unsigned char rgbMin, rgbMax;

    rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
    rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

    *v = rgbMax;
    if (*v == 0)
    {
        *h = 0;
        *s = 0;
        return;
    }

    *s = 255 * ((long)(rgbMax - rgbMin)) / *v;
    if (*s == 0)
    {
        *h = 0;
        return;
    }

    if (rgbMax == r)
        *h = 0 + 43 * (g - b) / (rgbMax - rgbMin);
    else if (rgbMax == g)
        *h = 85 + 43 * (b - r) / (rgbMax - rgbMin);
    else
        *h = 171 + 43 * (r - g) / (rgbMax - rgbMin);
}

uint32_t StrToRGB888(const uint8_t * str)
{
    uint32_t i;
    uint32_t val = 0;
    
    SYS_CONSOLE_PRINT("str is %s \r\n", *str);
    for (i = 0; i < 6; i++)
    {
        val <<= 4;
        if (str[i] >= '0' && str[i] <= '9')
            val += str[i] - '0';
        else if (str[i] >= 'a' && str[i] <= 'f')
            val += str[i] - 'a' + 10;
        else if (str[i] >= 'A' && str[i] <= 'F')
            val += str[i] - 'A' + 10;
    }   
    
    SYS_CONSOLE_PRINT("val is 0x%x \r\n", str);
    return val;
}
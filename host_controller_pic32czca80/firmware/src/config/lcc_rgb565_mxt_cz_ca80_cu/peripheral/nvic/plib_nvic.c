/*******************************************************************************
  NVIC PLIB Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    plib_nvic.c

  Summary:
    NVIC PLIB Source File

  Description:
    None

*******************************************************************************/

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

#include "device.h"
#include "plib_nvic.h"


// *****************************************************************************
// *****************************************************************************
// Section: NVIC Implementation
// *****************************************************************************
// *****************************************************************************

void NVIC_Initialize( void )
{
    /* Priority 0 to 7 and no sub-priority. 0 is the highest priority */
    NVIC_SetPriorityGrouping( 0x00 );

    /* Enable NVIC Controller */
    __DMB();
    __enable_irq();

    /* Enable the interrupt sources and configure the priorities as configured
     * from within the "Interrupt Manager" of MHC. */
    NVIC_SetPriority(RTC_TAMPER_IRQn, 7);
    NVIC_EnableIRQ(RTC_TAMPER_IRQn);
    NVIC_SetPriority(RTC_OVF_IRQn, 7);
    NVIC_EnableIRQ(RTC_OVF_IRQn);
    NVIC_SetPriority(RTC_PERIOD_IRQn, 7);
    NVIC_EnableIRQ(RTC_PERIOD_IRQn);
    NVIC_SetPriority(RTC_COMPARE_IRQn, 7);
    NVIC_EnableIRQ(RTC_COMPARE_IRQn);
    NVIC_SetPriority(EIC_EXTINT_7_IRQn, 7);
    NVIC_EnableIRQ(EIC_EXTINT_7_IRQn);
    NVIC_SetPriority(EIC_EXTINT_8_IRQn, 7);
    NVIC_EnableIRQ(EIC_EXTINT_8_IRQn);
    NVIC_SetPriority(DMA_PRI3_IRQn, 7);
    NVIC_EnableIRQ(DMA_PRI3_IRQn);
    NVIC_SetPriority(DMA_PRI2_IRQn, 7);
    NVIC_EnableIRQ(DMA_PRI2_IRQn);
    NVIC_SetPriority(DMA_PRI1_IRQn, 7);
    NVIC_EnableIRQ(DMA_PRI1_IRQn);
    NVIC_SetPriority(DMA_PRI0_IRQn, 7);
    NVIC_EnableIRQ(DMA_PRI0_IRQn);
    NVIC_SetPriority(SERCOM0_6_IRQn, 7);
    NVIC_EnableIRQ(SERCOM0_6_IRQn);
    NVIC_SetPriority(SERCOM0_5_IRQn, 7);
    NVIC_EnableIRQ(SERCOM0_5_IRQn);
    NVIC_SetPriority(SERCOM0_0_IRQn, 7);
    NVIC_EnableIRQ(SERCOM0_0_IRQn);
    NVIC_SetPriority(SERCOM0_1_IRQn, 7);
    NVIC_EnableIRQ(SERCOM0_1_IRQn);
    NVIC_SetPriority(SERCOM0_2_IRQn, 7);
    NVIC_EnableIRQ(SERCOM0_2_IRQn);
    NVIC_SetPriority(SERCOM0_3_IRQn, 7);
    NVIC_EnableIRQ(SERCOM0_3_IRQn);
    NVIC_SetPriority(SERCOM0_4_IRQn, 7);
    NVIC_EnableIRQ(SERCOM0_4_IRQn);
    NVIC_SetPriority(SERCOM1_6_IRQn, 7);
    NVIC_EnableIRQ(SERCOM1_6_IRQn);
    NVIC_SetPriority(SERCOM1_5_IRQn, 7);
    NVIC_EnableIRQ(SERCOM1_5_IRQn);
    NVIC_SetPriority(SERCOM1_0_IRQn, 7);
    NVIC_EnableIRQ(SERCOM1_0_IRQn);
    NVIC_SetPriority(SERCOM1_1_IRQn, 7);
    NVIC_EnableIRQ(SERCOM1_1_IRQn);
    NVIC_SetPriority(SERCOM1_2_IRQn, 7);
    NVIC_EnableIRQ(SERCOM1_2_IRQn);
    NVIC_SetPriority(SERCOM1_3_IRQn, 7);
    NVIC_EnableIRQ(SERCOM1_3_IRQn);
    NVIC_SetPriority(SERCOM1_4_IRQn, 7);
    NVIC_EnableIRQ(SERCOM1_4_IRQn);
    NVIC_SetPriority(SERCOM2_6_IRQn, 7);
    NVIC_EnableIRQ(SERCOM2_6_IRQn);
    NVIC_SetPriority(SERCOM2_5_IRQn, 7);
    NVIC_EnableIRQ(SERCOM2_5_IRQn);
    NVIC_SetPriority(SERCOM2_0_IRQn, 7);
    NVIC_EnableIRQ(SERCOM2_0_IRQn);
    NVIC_SetPriority(SERCOM2_1_IRQn, 7);
    NVIC_EnableIRQ(SERCOM2_1_IRQn);
    NVIC_SetPriority(SERCOM2_2_IRQn, 7);
    NVIC_EnableIRQ(SERCOM2_2_IRQn);
    NVIC_SetPriority(SERCOM2_3_IRQn, 7);
    NVIC_EnableIRQ(SERCOM2_3_IRQn);
    NVIC_SetPriority(SERCOM2_4_IRQn, 7);
    NVIC_EnableIRQ(SERCOM2_4_IRQn);
    NVIC_SetPriority(SERCOM3_6_IRQn, 7);
    NVIC_EnableIRQ(SERCOM3_6_IRQn);
    NVIC_SetPriority(SERCOM3_5_IRQn, 7);
    NVIC_EnableIRQ(SERCOM3_5_IRQn);
    NVIC_SetPriority(SERCOM3_0_IRQn, 7);
    NVIC_EnableIRQ(SERCOM3_0_IRQn);
    NVIC_SetPriority(SERCOM3_1_IRQn, 7);
    NVIC_EnableIRQ(SERCOM3_1_IRQn);
    NVIC_SetPriority(SERCOM3_2_IRQn, 7);
    NVIC_EnableIRQ(SERCOM3_2_IRQn);
    NVIC_SetPriority(SERCOM3_3_IRQn, 7);
    NVIC_EnableIRQ(SERCOM3_3_IRQn);
    NVIC_SetPriority(SERCOM3_4_IRQn, 7);
    NVIC_EnableIRQ(SERCOM3_4_IRQn);
    NVIC_SetPriority(SERCOM4_6_IRQn, 7);
    NVIC_EnableIRQ(SERCOM4_6_IRQn);
    NVIC_SetPriority(SERCOM4_5_IRQn, 7);
    NVIC_EnableIRQ(SERCOM4_5_IRQn);
    NVIC_SetPriority(SERCOM4_0_IRQn, 7);
    NVIC_EnableIRQ(SERCOM4_0_IRQn);
    NVIC_SetPriority(SERCOM4_1_IRQn, 7);
    NVIC_EnableIRQ(SERCOM4_1_IRQn);
    NVIC_SetPriority(SERCOM4_2_IRQn, 7);
    NVIC_EnableIRQ(SERCOM4_2_IRQn);
    NVIC_SetPriority(SERCOM4_3_IRQn, 7);
    NVIC_EnableIRQ(SERCOM4_3_IRQn);
    NVIC_SetPriority(SERCOM4_4_IRQn, 7);
    NVIC_EnableIRQ(SERCOM4_4_IRQn);
    NVIC_SetPriority(SERCOM8_6_IRQn, 7);
    NVIC_EnableIRQ(SERCOM8_6_IRQn);
    NVIC_SetPriority(SERCOM8_5_IRQn, 7);
    NVIC_EnableIRQ(SERCOM8_5_IRQn);
    NVIC_SetPriority(SERCOM8_0_IRQn, 7);
    NVIC_EnableIRQ(SERCOM8_0_IRQn);
    NVIC_SetPriority(SERCOM8_1_IRQn, 7);
    NVIC_EnableIRQ(SERCOM8_1_IRQn);
    NVIC_SetPriority(SERCOM8_2_IRQn, 7);
    NVIC_EnableIRQ(SERCOM8_2_IRQn);
    NVIC_SetPriority(SERCOM8_3_IRQn, 7);
    NVIC_EnableIRQ(SERCOM8_3_IRQn);
    NVIC_SetPriority(SERCOM8_4_IRQn, 7);
    NVIC_EnableIRQ(SERCOM8_4_IRQn);
    NVIC_SetPriority(SDMMC1_IRQn, 7);
    NVIC_EnableIRQ(SDMMC1_IRQn);
    NVIC_SetPriority(USBHS0_IRQn, 6);
    NVIC_EnableIRQ(USBHS0_IRQn);
    NVIC_SetPriority(USBHS1_IRQn, 6);
    NVIC_EnableIRQ(USBHS1_IRQn);

    /* Enable Usage fault */
    SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk);
    /* Trap divide by zero */
    SCB->CCR   |= SCB_CCR_DIV_0_TRP_Msk;

    /* Enable Bus fault */
    SCB->SHCSR |= (SCB_SHCSR_BUSFAULTENA_Msk);

    /* Enable memory management fault */
    SCB->SHCSR |= (SCB_SHCSR_MEMFAULTENA_Msk);

}

void NVIC_INT_Enable( void )
{
    __DMB();
    __enable_irq();
}

bool NVIC_INT_Disable( void )
{
    bool processorStatus = (__get_PRIMASK() == 0U);

    __disable_irq();
    __DMB();

    return processorStatus;
}

void NVIC_INT_Restore( bool state )
{
    if( state == true )
    {
        __DMB();
        __enable_irq();
    }
    else
    {
        __disable_irq();
        __DMB();
    }
}

bool NVIC_INT_SourceDisable( IRQn_Type source )
{
    bool processorStatus;
    bool intSrcStatus;

    processorStatus = NVIC_INT_Disable();
    intSrcStatus = (NVIC_GetEnableIRQ(source) != 0U);
    NVIC_DisableIRQ( source );
    NVIC_INT_Restore( processorStatus );

    /* return the source status */
    return intSrcStatus;
}

void NVIC_INT_SourceRestore( IRQn_Type source, bool status )
{
    if( status ) {
       NVIC_EnableIRQ( source );
    }

    return;
}

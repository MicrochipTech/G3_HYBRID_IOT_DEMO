/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
#pragma config FUSES_USERCFG1_FSEQ_SEQNUM = 0x1U
#pragma config FUSES_USERCFG1_FSEQ_SEQBAR = 0xfffeU
#pragma config FUSES_USERCFG1_AFSEQ_ASEQNUM = 0xffffU
#pragma config FUSES_USERCFG1_AFSEQ_ASEQBAR = 0xffffU
#pragma config FUSES_USERCFG1_FUCFG0_WDT_ENABLE = CLEAR
#pragma config FUSES_USERCFG1_FUCFG0_WDT_WEN = CLEAR
#pragma config FUSES_USERCFG1_FUCFG0_WDT_RUNSTDBY = CLEAR
#pragma config FUSES_USERCFG1_FUCFG0_WDT_ALWAYSON = CLEAR
#pragma config FUSES_USERCFG1_FUCFG0_WDT_PER = 0x0U
#pragma config FUSES_USERCFG1_FUCFG0_WDT_WINDOW = 0x0U
#pragma config FUSES_USERCFG1_FUCFG0_WDT_EWOFFSET = 0x0U
#pragma config FUSES_USERCFG1_FUCFG1_SSXEXDRM = 0xffU
#pragma config FUSES_USERCFG1_FUCFG1_SSXEXEBI = 0xffU
#pragma config FUSES_USERCFG1_FUCFG1_SSXEXSQI0 = 0xffU
#pragma config FUSES_USERCFG1_FUCFG1_SSXEXSQI1 = 0xffU
#pragma config FUSES_USERCFG1_FUCFG2_BOR_HYST = SET
#pragma config FUSES_USERCFG1_FUCFG2_BOR_TRIP = 0x3U
#pragma config FUSES_USERCFG1_FUCFG3_HYST_BOR_VDDIO = SET
#pragma config FUSES_USERCFG1_FUCFG3_BOR_TRIP_VDDIO = 0x3U
#pragma config FUSES_USERCFG1_FUCFG3_HYST_BOR_VDDA = SET
#pragma config FUSES_USERCFG1_FUCFG3_BOR_TRIP_VDDA = 0x3U
#pragma config FUSES_USERCFG1_FUCFG3_HYST_BOR_VDDREG = SET
#pragma config FUSES_USERCFG1_FUCFG5_UCP0 = 0xfU
#pragma config FUSES_USERCFG1_FUCFG5_UCP1 = 0xfU
#pragma config FUSES_USERCFG1_FUCFG5_UCP2 = 0xfU
#pragma config FUSES_USERCFG1_FUCFG5_UCP3 = 0xfU
#pragma config FUSES_USERCFG1_FUCFG6_PFM_ECCCTL = 0x3U
#pragma config FUSES_USERCFG1_FUCFG6_PFM_ECCUNLCK = SET
#pragma config FUSES_USERCFG1_FUCFG7_PFM_TEMP = SET
#pragma config FUSES_USERCFG1_FUCFG8_PFM_UC1WP = CLEAR
#pragma config FUSES_USERCFG1_FUCFG8_PFM_UC2WP = CLEAR
#pragma config FUSES_USERCFG1_FUCFG8_PFM_UC1WPLOCK = CLEAR
#pragma config FUSES_USERCFG1_FUCFG8_PFM_UC2WPLOCK = CLEAR
#pragma config FUSES_USERCFG1_FUCFG9_RAM_INIT_ENB = SET
#pragma config FUSES_USERCFG1_FUCFG9_BISR_RST_EN0 = SET
#pragma config FUSES_USERCFG1_FUCFG16_HSM_PTRMETA0 = 0xffffffffU
#pragma config FUSES_USERCFG1_FUCFG24_HSM_PTRMETA1 = 0xffffffffU
#pragma config FUSES_BOOTCFG1_BLDRCFG_PFM_BCRP = CLEAR
#pragma config FUSES_BOOTCFG1_BLDRCFG_PFM_BCWP = CLEAR
#pragma config FUSES_BOOTCFG1_BLDRCFG_BROM_EN_BFMCHK = NONE
#pragma config FUSES_BOOTCFG1_BLDRCFG_BROM_EN_PLL = CLEAR
#pragma config FUSES_BOOTCFG1_BLDRCFG_BROM_EN_DALUN = SET
#pragma config FUSES_BOOTCFG1_BLDRCFG_BROM_EN_RWLOCKS = SET
#pragma config FUSES_BOOTCFG1_BROM_BSEQ_SEQNUM = 0x1U
#pragma config FUSES_BOOTCFG1_BROM_BSEQ_SEQBAR = 0xfffeU
#pragma config FUSES_BOOTCFG1_BFM_CHK_TABLEPTR_BFM_CHK_TABLEPTR = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_TZ0_CE_ALL0_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_TZ0_CE_ALL1_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_TZ0_CE_ALL2_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_TZ0_CE_ALL3_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_CELOCK_TZ0_CE_ALL0_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_CELOCK_TZ0_CE_ALL1_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_CELOCK_TZ0_CE_ALL2_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_CELOCK_TZ0_CE_ALL3_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_CRCCMD0_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_CRCCMD1_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_CRCCMD2_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_CRCCMD3_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_CRCCMD0_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_CRCCMD1_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_CRCCMD2_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_CRCCMD3_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_HOSTDALELEV0_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_HOSTDALELEV1_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_HOSTDALELEV2_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYVAL_HOSTDALELEV3_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_HOSTDALELEV0_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_HOSTDALELEV1_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_HOSTDALELEV2_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_KEYCONFIG_HOSTDALELEV3_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG1_ROM_CTRLA_SWRST = SET
#pragma config FUSES_BOOTCFG1_ROM_CTRLA_ENABLE = SET
#pragma config FUSES_BOOTCFG1_ROM_CTRLA_PRMWS = 0x7U
#pragma config FUSES_BOOTCFG1_FCR_CTRLA_ARB = SET
#pragma config FUSES_BOOTCFG1_FCR_CTRLA_FWS = 0xfU
#pragma config FUSES_BOOTCFG1_FCR_CTRLA_ADRWS = SET
#pragma config FUSES_BOOTCFG1_FCR_CTRLA_AUTOWS = SET
#pragma config FUSES_BOOTCFG1_FCR_CTRLA_RDBUFWS = 0xfU
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_VREGOUT = 0x2
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_OFFSTDBY = ON
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_SRAM_VLD = CLEAR
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_BKUP_VLD = CLEAR
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_CPEN = 0x7U
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_ULDOEN = SET
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_ULDOSTDBY = ONINSTDBY
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_ULDOLEVEL = 0x3
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_AVREGEN = PLL_EN
#pragma config FUSES_BOOTCFG1_RPMU_VREGCTRL_AVREGSTDBY = ONINSTDBY
#pragma config FUSES_BOOTCFG1_PLL0_CTRL_ENABLE = SET
#pragma config FUSES_BOOTCFG1_PLL0_CTRL_WRTLOCK = SET
#pragma config FUSES_BOOTCFG1_PLL0_CTRL_ONDEMAND = SET
#pragma config FUSES_BOOTCFG1_PLL0_CTRL_REFSEL = DFLL48M
#pragma config FUSES_BOOTCFG1_PLL0_CTRL_BWSEL = BWSEL7
#pragma config FUSES_BOOTCFG1_PLL0_FBDIV_FBDIV = 0x3ffU
#pragma config FUSES_BOOTCFG1_PLL0_REFDIV_REFDIV = 0x3fU
#pragma config FUSES_BOOTCFG1_PLL0_POSTDIVA_POSTDIV = 0x3fU
#pragma config FUSES_BOOTCFG1_PLL0_POSTDIVA_OUTEN = SET
#pragma config FUSES_BOOTCFG1_MCLK_CLKDIV1_MCLK_CLKDIV1 = 0xffffffffU
#pragma config FUSES_BOOTCFG1_GCLK_GENCTRL0_GCLK_GENCTRL0 = 0xffffffffU
#pragma config FUSES_BOOTCFG1_BROM_BOOTCFGCRC0_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG1_BROM_BOOTCFGCRC1_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG1_BROM_BOOTCFGCRC2_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG1_BROM_BOOTCFGCRC3_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG1_BROM_PAGEEND_BROM_PAGEEND = 0xffffffffU
#pragma config FUSES_USERCFG2_FSEQ_SEQNUM = 0x0U
#pragma config FUSES_USERCFG2_FSEQ_SEQBAR = 0xffffU
#pragma config FUSES_USERCFG2_AFSEQ_ASEQNUM = 0xffffU
#pragma config FUSES_USERCFG2_AFSEQ_ASEQBAR = 0xffffU
#pragma config FUSES_USERCFG2_FUCFG0_WDT_ENABLE = CLEAR
#pragma config FUSES_USERCFG2_FUCFG0_WDT_WEN = SET
#pragma config FUSES_USERCFG2_FUCFG0_WDT_RUNSTDBY = SET
#pragma config FUSES_USERCFG2_FUCFG0_WDT_ALWAYSON = CLEAR
#pragma config FUSES_USERCFG2_FUCFG0_WDT_PER = 0x0U
#pragma config FUSES_USERCFG2_FUCFG0_WDT_WINDOW = 0x0U
#pragma config FUSES_USERCFG2_FUCFG0_WDT_EWOFFSET = 0x0U
#pragma config FUSES_USERCFG2_FUCFG1_SSXEXDRM = 0xffU
#pragma config FUSES_USERCFG2_FUCFG1_SSXEXEBI = 0xffU
#pragma config FUSES_USERCFG2_FUCFG1_SSXEXSQI0 = 0xffU
#pragma config FUSES_USERCFG2_FUCFG1_SSXEXSQI1 = 0xffU
#pragma config FUSES_USERCFG2_FUCFG2_BOR_HYST = SET
#pragma config FUSES_USERCFG2_FUCFG2_BOR_TRIP = 0x3U
#pragma config FUSES_USERCFG2_FUCFG3_HYST_BOR_VDDIO = SET
#pragma config FUSES_USERCFG2_FUCFG3_BOR_TRIP_VDDIO = 0x3U
#pragma config FUSES_USERCFG2_FUCFG3_HYST_BOR_VDDA = SET
#pragma config FUSES_USERCFG2_FUCFG3_BOR_TRIP_VDDA = 0x3U
#pragma config FUSES_USERCFG2_FUCFG3_HYST_BOR_VDDREG = SET
#pragma config FUSES_USERCFG2_FUCFG5_UCP0 = 0xfU
#pragma config FUSES_USERCFG2_FUCFG5_UCP1 = 0xfU
#pragma config FUSES_USERCFG2_FUCFG5_UCP2 = 0xfU
#pragma config FUSES_USERCFG2_FUCFG5_UCP3 = 0xfU
#pragma config FUSES_USERCFG2_FUCFG6_PFM_ECCCTL = 0x3U
#pragma config FUSES_USERCFG2_FUCFG6_PFM_ECCUNLCK = SET
#pragma config FUSES_USERCFG2_FUCFG7_PFM_TEMP = SET
#pragma config FUSES_USERCFG2_FUCFG8_PFM_UC1WP = CLEAR
#pragma config FUSES_USERCFG2_FUCFG8_PFM_UC2WP = CLEAR
#pragma config FUSES_USERCFG2_FUCFG8_PFM_UC1WPLOCK = CLEAR
#pragma config FUSES_USERCFG2_FUCFG8_PFM_UC2WPLOCK = CLEAR
#pragma config FUSES_USERCFG2_FUCFG9_RAM_INIT_ENB = SET
#pragma config FUSES_USERCFG2_FUCFG9_BISR_RST_EN0 = SET
#pragma config FUSES_USERCFG2_FUCFG16_HSM_PTRMETA0 = 0xffffffffU
#pragma config FUSES_USERCFG2_FUCFG24_HSM_PTRMETA1 = 0xffffffffU
#pragma config FUSES_BOOTCFG2_BLDRCFG_PFM_BCRP = CLEAR
#pragma config FUSES_BOOTCFG2_BLDRCFG_PFM_BCWP = CLEAR
#pragma config FUSES_BOOTCFG2_BLDRCFG_BROM_EN_BFMCHK = NONE
#pragma config FUSES_BOOTCFG2_BLDRCFG_BROM_EN_PLL = CLEAR
#pragma config FUSES_BOOTCFG2_BLDRCFG_BROM_EN_DALUN = SET
#pragma config FUSES_BOOTCFG2_BLDRCFG_BROM_EN_RWLOCKS = SET
#pragma config FUSES_BOOTCFG2_BROM_BSEQ_SEQNUM = 0x0U
#pragma config FUSES_BOOTCFG2_BROM_BSEQ_SEQBAR = 0xffffU
#pragma config FUSES_BOOTCFG2_BFM_CHK_TABLEPTR_BFM_CHK_TABLEPTR = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_TZ0_CE_ALL0_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_TZ0_CE_ALL1_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_TZ0_CE_ALL2_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_TZ0_CE_ALL3_KEYVAL_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_CELOCK_TZ0_CE_ALL0_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_CELOCK_TZ0_CE_ALL1_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_CELOCK_TZ0_CE_ALL2_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_CELOCK_TZ0_CE_ALL3_CELOCK_TZ0_CE_ALL = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_CRCCMD0_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_CRCCMD1_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_CRCCMD2_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_CRCCMD3_KEYVAL_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_CRCCMD0_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_CRCCMD1_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_CRCCMD2_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_CRCCMD3_KEYCONFIG_CRCCMD = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_HOSTDALELEV0_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_HOSTDALELEV1_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_HOSTDALELEV2_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYVAL_HOSTDALELEV3_KEYVAL_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_HOSTDALELEV0_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_HOSTDALELEV1_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_HOSTDALELEV2_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_KEYCONFIG_HOSTDALELEV3_KEYCONFIG_HOSTDALELEV = 0xffffffffU
#pragma config FUSES_BOOTCFG2_ROM_CTRLA_SWRST = SET
#pragma config FUSES_BOOTCFG2_ROM_CTRLA_ENABLE = SET
#pragma config FUSES_BOOTCFG2_ROM_CTRLA_PRMWS = 0x7U
#pragma config FUSES_BOOTCFG2_FCR_CTRLA_ARB = SET
#pragma config FUSES_BOOTCFG2_FCR_CTRLA_FWS = 0xfU
#pragma config FUSES_BOOTCFG2_FCR_CTRLA_ADRWS = SET
#pragma config FUSES_BOOTCFG2_FCR_CTRLA_AUTOWS = SET
#pragma config FUSES_BOOTCFG2_FCR_CTRLA_RDBUFWS = 0xfU
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_VREGOUT = 0x2
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_OFFSTDBY = ON
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_SRAM_VLD = CLEAR
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_BKUP_VLD = CLEAR
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_CPEN = 0x7U
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_ULDOEN = SET
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_ULDOSTDBY = ONINSTDBY
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_ULDOLEVEL = 0x3
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_AVREGEN = PLL_EN
#pragma config FUSES_BOOTCFG2_RPMU_VREGCTRL_AVREGSTDBY = ONINSTDBY
#pragma config FUSES_BOOTCFG2_PLL0_CTRL_ENABLE = SET
#pragma config FUSES_BOOTCFG2_PLL0_CTRL_WRTLOCK = SET
#pragma config FUSES_BOOTCFG2_PLL0_CTRL_ONDEMAND = SET
#pragma config FUSES_BOOTCFG2_PLL0_CTRL_REFSEL = DFLL48M
#pragma config FUSES_BOOTCFG2_PLL0_CTRL_BWSEL = BWSEL7
#pragma config FUSES_BOOTCFG2_PLL0_FBDIV_FBDIV = 0x3ffU
#pragma config FUSES_BOOTCFG2_PLL0_REFDIV_REFDIV = 0x3fU
#pragma config FUSES_BOOTCFG2_PLL0_POSTDIVA_POSTDIV = 0x3fU
#pragma config FUSES_BOOTCFG2_PLL0_POSTDIVA_OUTEN = SET
#pragma config FUSES_BOOTCFG2_MCLK_CLKDIV1_MCLK_CLKDIV1 = 0xffffffffU
#pragma config FUSES_BOOTCFG2_GCLK_GENCTRL0_GCLK_GENCTRL0 = 0xffffffffU
#pragma config FUSES_BOOTCFG2_BROM_BOOTCFGCRC0_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG2_BROM_BOOTCFGCRC1_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG2_BROM_BOOTCFGCRC2_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG2_BROM_BOOTCFGCRC3_BROM_BOOTCFGCRC = 0xffffffffU
#pragma config FUSES_BOOTCFG2_BROM_PAGEEND_BROM_PAGEEND = 0xffffffffU




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Following MISRA-C rules are deviated in the below code block */
/* MISRA C-2012 Rule 7.2 - Deviation record ID - H3_MISRAC_2012_R_7_2_DR_1 */
/* MISRA C-2012 Rule 11.1 - Deviation record ID - H3_MISRAC_2012_R_11_1_DR_1 */
/* MISRA C-2012 Rule 11.3 - Deviation record ID - H3_MISRAC_2012_R_11_3_DR_1 */
/* MISRA C-2012 Rule 11.8 - Deviation record ID - H3_MISRAC_2012_R_11_8_DR_1 */
// <editor-fold defaultstate="collapsed" desc="DRV_I2C Instance 0 Initialization Data">

/* I2C Client Objects Pool */
static DRV_I2C_CLIENT_OBJ drvI2C0ClientObjPool[DRV_I2C_CLIENTS_NUMBER_IDX0];

/* I2C Transfer Objects Pool */
static DRV_I2C_TRANSFER_OBJ drvI2C0TransferObj[DRV_I2C_QUEUE_SIZE_IDX0];

/* I2C PLib Interface Initialization */
static const DRV_I2C_PLIB_INTERFACE drvI2C0PLibAPI = {

    /* I2C PLib Transfer Read Add function */
    .read_t = (DRV_I2C_PLIB_READ)SERCOM0_I2C_Read,

    /* I2C PLib Transfer Write Add function */
    .write_t = (DRV_I2C_PLIB_WRITE)SERCOM0_I2C_Write,


    /* I2C PLib Transfer Write Read Add function */
    .writeRead = (DRV_I2C_PLIB_WRITE_READ)SERCOM0_I2C_WriteRead,

    /*I2C PLib Transfer Abort function */
    .transferAbort = (DRV_I2C_PLIB_TRANSFER_ABORT)SERCOM0_I2C_TransferAbort,

    /* I2C PLib Transfer Status function */
    .errorGet = (DRV_I2C_PLIB_ERROR_GET)SERCOM0_I2C_ErrorGet,

    /* I2C PLib Transfer Setup function */
    .transferSetup = (DRV_I2C_PLIB_TRANSFER_SETUP)SERCOM0_I2C_TransferSetup,

    /* I2C PLib Callback Register */
    .callbackRegister = (DRV_I2C_PLIB_CALLBACK_REGISTER)SERCOM0_I2C_CallbackRegister,
};


static const DRV_I2C_INTERRUPT_SOURCES drvI2C0InterruptSources =
{
    /* Peripheral has more than one interrupt vector */
    .isSingleIntSrc                        = false,

    /* Peripheral interrupt lines */
   .intSources.multi.i2cInt0   = (int32_t)SERCOM0_6_IRQn,
   .intSources.multi.i2cInt1   = (int32_t)SERCOM0_2_IRQn,
   .intSources.multi.i2cInt2   = (int32_t)SERCOM0_3_IRQn,
   .intSources.multi.i2cInt3   = (int32_t)SERCOM0_4_IRQn,
};

/* I2C Driver Initialization Data */
static const DRV_I2C_INIT drvI2C0InitData =
{
    /* I2C PLib API */
    .i2cPlib = &drvI2C0PLibAPI,

    /* I2C Number of clients */
    .numClients = DRV_I2C_CLIENTS_NUMBER_IDX0,

    /* I2C Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvI2C0ClientObjPool[0],

    /* I2C TWI Queue Size */
    .transferObjPoolSize = DRV_I2C_QUEUE_SIZE_IDX0,

    /* I2C Transfer Objects */
    .transferObjPool = (uintptr_t)&drvI2C0TransferObj[0],

    /* I2C interrupt sources */
    .interruptSources = &drvI2C0InterruptSources,

    /* I2C Clock Speed */
    .clockSpeed = DRV_I2C_CLOCK_SPEED_IDX0,
};
// </editor-fold>

static const WDRV_WINC_SPI_CFG wdrvWincSpiInitData =
{
    .drvIndex           = DRV_SPI_INDEX_0,
    .baudRateInHz       = 1000000,
    .chipSelect         = SYS_PORT_PIN_NONE
};

static const WDRV_WINC_SYS_INIT wdrvWincInitData = {
    .pSPICfg    = &wdrvWincSpiInitData,
    .intSrc     = EIC_PIN_7
};


// <editor-fold defaultstate="collapsed" desc="SRV_USI Instance 0 Initialization Data">

static uint8_t CACHE_ALIGN srvUSI0ReadBuffer[SRV_USI0_RD_BUF_SIZE] = {0};
static uint8_t CACHE_ALIGN srvUSI0WriteBuffer[SRV_USI0_WR_BUF_SIZE] = {0};


static const SRV_USI_USART_INTERFACE srvUsi0InitDataSERCOM8 = {
    .readCallbackRegister = (USI_USART_PLIB_READ_CALLBACK_REG)SERCOM8_USART_ReadCallbackRegister,
    .readData = (USI_USART_PLIB_WRRD)SERCOM8_USART_Read,
    .writeData = (USI_USART_PLIB_WRRD)SERCOM8_USART_Write,
    .intSource = SERCOM8_2_IRQn,
};

static uint8_t CACHE_ALIGN srvUSI0USARTReadBuffer[128] = {0};

static const USI_USART_INIT_DATA srvUsi0InitData = {
    .plib = (void*)&srvUsi0InitDataSERCOM8,
    .pRdBuffer = (void*)srvUSI0ReadBuffer,
    .rdBufferSize = SRV_USI0_RD_BUF_SIZE,
    .usartReadBuffer = (void *)srvUSI0USARTReadBuffer,
    .usartBufferSize = 128,
};

/* srvUSIUSARTDevDesc declared in USI USART service implementation (srv_usi_usart.c) */

static const SRV_USI_INIT srvUSI0Init =
{
    .deviceInitData = (const void * const)&srvUsi0InitData,
    .consDevDesc = &srvUSIUSARTDevDesc,
    .deviceIndex = 0,
    .pWrBuffer = srvUSI0WriteBuffer,
    .wrBufferSize = SRV_USI0_WR_BUF_SIZE
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_INPUT_MXT336T Initialization Data">
/*** MaxTouch Driver Initialization Data ***/
const DRV_MAXTOUCH_INIT drvMAXTOUCHInitData =
{
    .drvOpen                     = DRV_I2C_Open,
    .drvClose                    = DRV_I2C_Close,
    .orientation                 = 0,
    .horizontalResolution        = 800,
    .verticalResolution          = 480,
};

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="DRV_SPI Instance 0 Initialization Data">

/* SPI Client Objects Pool */
static DRV_SPI_CLIENT_OBJ drvSPI0ClientObjPool[DRV_SPI_CLIENTS_NUMBER_IDX0];

/* SPI Transfer Objects Pool */
static DRV_SPI_TRANSFER_OBJ drvSPI0TransferObjPool[DRV_SPI_QUEUE_SIZE_IDX0];

/* SPI PLIB Interface Initialization */
static const DRV_SPI_PLIB_INTERFACE drvSPI0PlibAPI = {

    /* SPI PLIB Setup */
    .setup = (DRV_SPI_PLIB_SETUP)SERCOM2_SPI_TransferSetup,

    /* SPI PLIB WriteRead function */
    .writeRead = (DRV_SPI_PLIB_WRITE_READ)SERCOM2_SPI_WriteRead,

    /* SPI PLIB Transfer Status function */
    .isTransmitterBusy = (DRV_SPI_PLIB_TRANSMITTER_IS_BUSY)SERCOM2_SPI_IsTransmitterBusy,

    /* SPI PLIB Callback Register */
    .callbackRegister = (DRV_SPI_PLIB_CALLBACK_REGISTER)SERCOM2_SPI_CallbackRegister,
};

static const uint32_t drvSPI0remapDataBits[]= { 0x0, 0x1, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU };
static const uint32_t drvSPI0remapClockPolarity[] = { 0x0, 0x20000000 };
static const uint32_t drvSPI0remapClockPhase[] = { 0x10000000, 0x0 };

static const DRV_SPI_INTERRUPT_SOURCES drvSPI0InterruptSources =
{
    /* Peripheral has more than one interrupt vector */
    .isSingleIntSrc                        = false,

    /* Peripheral interrupt lines */
   .intSources.multi.spiTxReadyInt     = (int32_t)SERCOM2_0_IRQn,
   .intSources.multi.spiTxCompleteInt  = (int32_t)SERCOM2_1_IRQn,
   .intSources.multi.spiRxInt          = (int32_t)SERCOM2_2_IRQn,
};

/* SPI Driver Initialization Data */
static const DRV_SPI_INIT drvSPI0InitData =
{
    /* SPI PLIB API */
    .spiPlib = &drvSPI0PlibAPI,

    .remapDataBits = drvSPI0remapDataBits,

    .remapClockPolarity = drvSPI0remapClockPolarity,

    .remapClockPhase = drvSPI0remapClockPhase,

    /* SPI Number of clients */
    .numClients = DRV_SPI_CLIENTS_NUMBER_IDX0,

    /* SPI Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvSPI0ClientObjPool[0],


    /* SPI Queue Size */
    .transferObjPoolSize = DRV_SPI_QUEUE_SIZE_IDX0,

    /* SPI Transfer Objects Pool */
    .transferObjPool = (uintptr_t)&drvSPI0TransferObjPool[0],

    /* SPI interrupt sources (SPI peripheral and DMA) */
    .interruptSources = &drvSPI0InterruptSources,
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_SDMMC Instance 0 Initialization Data">

/* SDMMC Client Objects Pool */
static DRV_SDMMC_CLIENT_OBJ drvSDMMC0ClientObjPool[DRV_SDMMC_IDX0_CLIENTS_NUMBER];

/* SDMMC Transfer Objects Pool */
static DRV_SDMMC_BUFFER_OBJ drvSDMMC0BufferObjPool[DRV_SDMMC_IDX0_QUEUE_SIZE];

static const DRV_SDMMC_PLIB_API drvSDMMC0PlibAPI = {
    .sdhostCallbackRegister = (DRV_SDMMC_PLIB_CALLBACK_REGISTER)SDMMC1_CallbackRegister,
    .sdhostInitModule = (DRV_SDMMC_PLIB_INIT_MODULE)SDMMC1_ModuleInit,
    .sdhostSetClock  = (DRV_SDMMC_PLIB_SET_CLOCK)SDMMC1_ClockSet,
    .sdhostIsCmdLineBusy = (DRV_SDMMC_PLIB_IS_CMD_LINE_BUSY)SDMMC1_IsCmdLineBusy,
    .sdhostIsDatLineBusy = (DRV_SDMMC_PLIB_IS_DATA_LINE_BUSY)SDMMC1_IsDatLineBusy,
    .sdhostSendCommand = (DRV_SDMMC_PLIB_SEND_COMMAND)SDMMC1_CommandSend,
    .sdhostReadResponse = (DRV_SDMMC_PLIB_READ_RESPONSE)SDMMC1_ResponseRead,
    .sdhostSetBlockCount = (DRV_SDMMC_PLIB_SET_BLOCK_COUNT)SDMMC1_BlockCountSet,
    .sdhostSetBlockSize = (DRV_SDMMC_PLIB_SET_BLOCK_SIZE)SDMMC1_BlockSizeSet,
    .sdhostSetBusWidth = (DRV_SDMMC_PLIB_SET_BUS_WIDTH)SDMMC1_BusWidthSet,
    .sdhostSetSpeedMode = (DRV_SDMMC_PLIB_SET_SPEED_MODE)SDMMC1_SpeedModeSet,
    .sdhostSetupDma = (DRV_SDMMC_PLIB_SETUP_DMA)SDMMC1_DmaSetup,
    .sdhostGetCommandError = (DRV_SDMMC_PLIB_GET_COMMAND_ERROR)SDMMC1_CommandErrorGet,
    .sdhostGetDataError = (DRV_SDMMC_PLIB_GET_DATA_ERROR)SDMMC1_DataErrorGet,
    .sdhostClockEnable = (DRV_SDMMC_PLIB_CLOCK_ENABLE)SDMMC1_ClockEnable,
    .sdhostResetError = (DRV_SDMMC_PLIB_RESET_ERROR)SDMMC1_ErrorReset,
    .sdhostIsCardAttached = (DRV_SDMMC_PLIB_IS_CARD_ATTACHED)SDMMC1_IsCardAttached,
    .sdhostIsWriteProtected = (DRV_SDMMC_PLIB_IS_WRITE_PROTECTED)NULL,
};

/*** SDMMC Driver Initialization Data ***/
static const DRV_SDMMC_INIT drvSDMMC0InitData =
{
    .sdmmcPlib                      = &drvSDMMC0PlibAPI,
    .bufferObjPool                  = (uintptr_t)&drvSDMMC0BufferObjPool[0],
    .bufferObjPoolSize              = DRV_SDMMC_IDX0_QUEUE_SIZE,
    .clientObjPool                  = (uintptr_t)&drvSDMMC0ClientObjPool[0],
    .numClients                     = DRV_SDMMC_IDX0_CLIENTS_NUMBER,
    .protocol                       = DRV_SDMMC_IDX0_PROTOCOL_SUPPORT,
    .cardDetectionMethod            = DRV_SDMMC_IDX0_CARD_DETECTION_METHOD,
    .cardDetectionPollingIntervalMs = 0,
    .isWriteProtectCheckEnabled     = false,
    .speedMode                      = DRV_SDMMC_IDX0_CONFIG_SPEED_MODE,
    .busWidth                       = DRV_SDMMC_IDX0_CONFIG_BUS_WIDTH,
	.sleepWhenIdle 					= false,
    .isFsEnabled                    = true,
};
// </editor-fold>




// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Net Presentation Layer Data Definitions */
#include "net_pres/pres/net_pres_enc_glue.h"

static const NET_PRES_TransportObject netPresTransObject0SS = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_TCP_ServerOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_TCP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_TCP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_TCP_IsConnected,
    .fpWasReset          = (NET_PRES_TransBool)TCPIP_TCP_WasReset,
    .fpWasDisconnected   = (NET_PRES_TransBool)TCPIP_TCP_WasDisconnected,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_TCP_Disconnect,
    .fpConnect           = (NET_PRES_TransBool)TCPIP_TCP_Connect,
    .fpClose             = (NET_PRES_TransClose)TCPIP_TCP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_TCP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_TCP_Flush,
    .fpPeek              = (NET_PRES_TransPeek)TCPIP_TCP_ArrayPeek,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_TCP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_TCP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_TCP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_TCP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_TCP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_TCP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_TCP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_TCPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0SC = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_TCP_ClientOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_TCP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_TCP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_TCP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_TCP_IsConnected,
    .fpWasReset          = (NET_PRES_TransBool)TCPIP_TCP_WasReset,
    .fpWasDisconnected   = (NET_PRES_TransBool)TCPIP_TCP_WasDisconnected,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_TCP_Disconnect,
    .fpConnect           = (NET_PRES_TransBool)TCPIP_TCP_Connect,
    .fpClose             = (NET_PRES_TransClose)TCPIP_TCP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_TCP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_TCP_Flush,
    .fpPeek              = (NET_PRES_TransPeek)TCPIP_TCP_ArrayPeek,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_TCP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_TCP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_TCP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_TCP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_TCP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_TCP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_TCP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_TCPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0DS = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_UDP_ServerOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_UDP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_UDP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_UDP_IsConnected,
    .fpWasReset          = NULL,
    .fpWasDisconnected   = NULL,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_UDP_Disconnect,
    .fpConnect          = NULL,
    .fpClose             = (NET_PRES_TransClose)TCPIP_UDP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_UDP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_UDP_Flush,
    .fpPeek              = NULL,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_UDP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_UDP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_UDP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_UDP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_UDP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_UDP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_UDP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_UDPSecurePortGet,
};
static const NET_PRES_TransportObject netPresTransObject0DC = {
    .fpOpen        = (NET_PRES_TransOpen)TCPIP_UDP_ClientOpen,
    .fpLocalBind         = (NET_PRES_TransBind)TCPIP_UDP_Bind,
    .fpRemoteBind        = (NET_PRES_TransBind)TCPIP_UDP_RemoteBind,
    .fpOptionGet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsGet,
    .fpOptionSet         = (NET_PRES_TransOption)TCPIP_UDP_OptionsSet,
    .fpIsConnected       = (NET_PRES_TransBool)TCPIP_UDP_IsConnected,
    .fpWasReset          = NULL,
    .fpWasDisconnected   = NULL,
    .fpDisconnect        = (NET_PRES_TransBool)TCPIP_UDP_Disconnect,
    .fpConnect          = NULL,
    .fpClose             = (NET_PRES_TransClose)TCPIP_UDP_Close,
    .fpSocketInfoGet     = (NET_PRES_TransSocketInfoGet)TCPIP_UDP_SocketInfoGet,
    .fpFlush             = (NET_PRES_TransBool)TCPIP_UDP_Flush,
    .fpPeek              = NULL,
    .fpDiscard           = (NET_PRES_TransDiscard)TCPIP_UDP_Discard,
    .fpHandlerRegister   = (NET_PRES_TransHandlerRegister)TCPIP_UDP_SignalHandlerRegister,
    .fpHandlerDeregister = (NET_PRES_TransSignalHandlerDeregister)TCPIP_UDP_SignalHandlerDeregister,
    .fpRead              = (NET_PRES_TransRead)TCPIP_UDP_ArrayGet,
    .fpWrite             = (NET_PRES_TransWrite)TCPIP_UDP_ArrayPut,
    .fpReadyToRead       = (NET_PRES_TransReady)TCPIP_UDP_GetIsReady,
    .fpReadyToWrite      = (NET_PRES_TransReady)TCPIP_UDP_PutIsReady,
    .fpIsPortDefaultSecure = (NET_PRES_TransIsPortDefaultSecured)TCPIP_Helper_UDPSecurePortGet,
};

static const NET_PRES_INST_DATA netPresCfgs[] = 
{  
        
    {
        .pTransObject_ss = &netPresTransObject0SS,
        .pTransObject_sc = &netPresTransObject0SC,
        .pTransObject_ds = &netPresTransObject0DS,
        .pTransObject_dc = &netPresTransObject0DC,
        .pProvObject_ss = NULL,
        .pProvObject_sc = NULL,
        .pProvObject_ds = NULL,
        .pProvObject_dc = NULL,
    },
        
};

static const NET_PRES_INIT_DATA netPresInitData = 
{
    .numLayers = sizeof(netPresCfgs) / sizeof(NET_PRES_INST_DATA),
    .pInitData = netPresCfgs
};
  
 

// <editor-fold defaultstate="collapsed" desc="File System Initialization Data">

 const SYS_FS_MEDIA_MOUNT_DATA sysfsMountTable[SYS_FS_VOLUME_NUMBER] =
{
    {
        .mountName = SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0,
        .devName   = SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0,
        .mediaType = SYS_FS_MEDIA_TYPE_IDX0,
        .fsType   = SYS_FS_TYPE_IDX0
    },
};


static const SYS_FS_FUNCTIONS FatFsFunctions =
{
    .mount             = FATFS_mount,
    .unmount           = FATFS_unmount,
    .open              = FATFS_open,
    .read_t              = FATFS_read,
    .close             = FATFS_close,
    .seek              = FATFS_lseek,
    .fstat             = FATFS_stat,
    .getlabel          = FATFS_getlabel,
    .currWD            = FATFS_getcwd,
    .getstrn           = FATFS_gets,
    .openDir           = FATFS_opendir,
    .readDir           = FATFS_readdir,
    .closeDir          = FATFS_closedir,
    .chdir             = FATFS_chdir,
    .chdrive           = FATFS_chdrive,
    .write_t             = FATFS_write,
    .tell              = FATFS_tell,
    .eof               = FATFS_eof,
    .size              = FATFS_size,
    .mkdir             = FATFS_mkdir,
    .remove_t            = FATFS_unlink,
    .setlabel          = FATFS_setlabel,
    .truncate          = FATFS_truncate,
    .chmode            = FATFS_chmod,
    .chtime            = FATFS_utime,
    .rename_t            = FATFS_rename,
    .sync              = FATFS_sync,
    .putchr            = FATFS_putc,
    .putstrn           = FATFS_puts,
    .formattedprint    = FATFS_printf,
    .testerror         = FATFS_error,
    .formatDisk        = (FORMAT_DISK)FATFS_mkfs,
    .partitionDisk     = FATFS_fdisk,
    .getCluster        = FATFS_getclusters
};




static const SYS_FS_REGISTRATION_TABLE sysFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
{
    {
        .nativeFileSystemType = FAT,
        .nativeFileSystemFunctions = &FatFsFunctions
    }
};
// </editor-fold>

/******************************************************
 * USB Driver Initialization
 ******************************************************/

static void DRV_USB_VBUSPowerEnable0(uint8_t port, bool enable)
{
    /* Note: When operating in Host mode, the application can specify a Root 
       hub port enable function. The USB Host Controller driver initi data 
       structure has a member for specifying the root hub enable function. 
       This parameter should point to Root hub port enable function. If this 
       parameter is NULL, it implies that the port is always enabled. 

       This function generated by MHC to let the user enable the root hub. 
       User must use the MHC pin configuration utility to configure the pin 
       used for enabling VBUS  */
    if (enable == true)
    {
        /* Enable the VBUS */
        USB_HOST_PWR_Clear();
    }
    else
    {
        /* Disable the VBUS */
        USB_HOST_PWR_Set();
    }
}

static const DRV_USBHS_INIT drvUSBHSInit0 =
{

    /* Interrupt Source for USB module */
    .interruptSource = USBHS1_IRQn,

    /* Interrupt Source for USB module */
    .interruptSourceUSBDma = USBHS1_IRQn,

    /* System module initialization */
    .moduleInit = {0},

    /* USB Controller to operate as USB Host */
    .operationMode = DRV_USBHS_OPMODE_HOST,

    /* Enable High Speed Operation */
    .operationSpeed = USB_SPEED_HIGH,
    
    /* Stop in idle */
    .stopInIdle = true,

    /* Suspend in sleep */
    .suspendInSleep = false,

    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USBHS_ID_1,
    
    /* USB Host Power Enable. USB Driver uses this function to Enable the VBUS */ 
    .portPowerEnable = DRV_USB_VBUSPowerEnable0,
    
    /* Root hub available current in milliamperes */
    .rootHubAvailableCurrent = 500,
};



// <editor-fold defaultstate="collapsed" desc="TCP/IP Stack Initialization Data">
// *****************************************************************************
// *****************************************************************************
// Section: TCPIP Data
// *****************************************************************************
// *****************************************************************************
/*** ARP Service Initialization Data ***/
const TCPIP_ARP_MODULE_CONFIG tcpipARPInitData =
{ 
    .cacheEntries       = TCPIP_ARP_CACHE_ENTRIES,     
    .deleteOld          = TCPIP_ARP_CACHE_DELETE_OLD,    
    .entrySolvedTmo     = TCPIP_ARP_CACHE_SOLVED_ENTRY_TMO, 
    .entryPendingTmo    = TCPIP_ARP_CACHE_PENDING_ENTRY_TMO, 
    .entryRetryTmo      = TCPIP_ARP_CACHE_PENDING_RETRY_TMO, 
    .permQuota          = TCPIP_ARP_CACHE_PERMANENT_QUOTA, 
    .purgeThres         = TCPIP_ARP_CACHE_PURGE_THRESHOLD, 
    .purgeQuanta        = TCPIP_ARP_CACHE_PURGE_QUANTA, 
    .retries            = TCPIP_ARP_CACHE_ENTRY_RETRIES, 
    .gratProbeCount     = TCPIP_ARP_GRATUITOUS_PROBE_COUNT,
};

/*** Announce Discovery Initialization Data ***/
const TCPIP_ANNOUNCE_MODULE_CONFIG tcpipAnnounceInitData =
{ 
    0
};

/*** UDP Sockets Initialization Data ***/
const TCPIP_UDP_MODULE_CONFIG tcpipUDPInitData =
{
    .nSockets       = TCPIP_UDP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_UDP_SOCKET_DEFAULT_TX_SIZE, 
};

/*** TCP Sockets Initialization Data ***/
const TCPIP_TCP_MODULE_CONFIG tcpipTCPInitData =
{
    .nSockets       = TCPIP_TCP_MAX_SOCKETS,
    .sktTxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_TX_SIZE, 
    .sktRxBuffSize  = TCPIP_TCP_SOCKET_DEFAULT_RX_SIZE,
};


/*** HTTP_NET Server Initialization Data ***/
const TCPIP_HTTP_NET_MODULE_CONFIG tcpipHTTPNetInitData =
{
    .nConnections   = TCPIP_HTTP_NET_MAX_CONNECTIONS,
    .dataLen        = TCPIP_HTTP_NET_MAX_DATA_LEN,
    .sktTxBuffSize  = TCPIP_HTTP_NET_SKT_TX_BUFF_SIZE,
    .sktRxBuffSize  = TCPIP_HTTP_NET_SKT_RX_BUFF_SIZE,
    .listenPort     = TCPIP_HTTP_NET_LISTEN_PORT,
    .nDescriptors   = TCPIP_HTTP_NET_DYNVAR_DESCRIPTORS_NUMBER,
    .nChunks        = TCPIP_HTTP_NET_CHUNKS_NUMBER, 
    .maxRecurseLevel= TCPIP_HTTP_NET_MAX_RECURSE_LEVEL,    
    .configFlags    = TCPIP_HTTP_NET_CONFIG_FLAGS,
    .nFileBuffers   = TCPIP_HTTP_NET_FILE_PROCESS_BUFFERS_NUMBER,
    .fileBufferSize = TCPIP_HTTP_NET_FILE_PROCESS_BUFFER_SIZE,
    .chunkPoolRetries = TCPIP_HTTP_NET_CHUNK_RETRIES,
    .fileBufferRetries = TCPIP_HTTP_NET_FILE_PROCESS_BUFFER_RETRIES,
    .dynVarRetries  = TCPIP_HTTP_NET_DYNVAR_PROCESS_RETRIES,
    .connTimeout        = TCPIP_HTTP_NET_CONNECTION_TIMEOUT,
    .http_malloc_fnc    = TCPIP_HTTP_NET_MALLOC_FUNC,
    .http_free_fnc      = TCPIP_HTTP_NET_FREE_FUNC,
    .web_dir            = TCPIP_HTTP_NET_WEB_DIR, 
};

/*** SNTP Client Initialization Data ***/
const TCPIP_SNTP_MODULE_CONFIG tcpipSNTPInitData =
{
    .ntp_server             = TCPIP_NTP_SERVER,
    .ntp_interface          = TCPIP_NTP_DEFAULT_IF,
    .ntp_connection_type    = TCPIP_NTP_DEFAULT_CONNECTION_TYPE,
    .ntp_reply_timeout      = TCPIP_NTP_REPLY_TIMEOUT,
    .ntp_stamp_timeout      = TCPIP_NTP_TIME_STAMP_TMO,
    .ntp_success_interval   = TCPIP_NTP_QUERY_INTERVAL,
    .ntp_error_interval     = TCPIP_NTP_FAST_QUERY_INTERVAL,
};



/*** DHCP client Initialization Data ***/
const TCPIP_DHCP_MODULE_CONFIG tcpipDHCPInitData =
{     
    .dhcpEnable     = false,   
    .dhcpTmo        = TCPIP_DHCP_TIMEOUT,
    .dhcpCliPort    = TCPIP_DHCP_CLIENT_CONNECT_PORT,
    .dhcpSrvPort    = TCPIP_DHCP_SERVER_LISTEN_PORT,

};


/*** ICMP Server Initialization Data ***/
const TCPIP_ICMP_MODULE_CONFIG tcpipICMPInitData = 
{
    0
};










/*** DHCP Server v2 initialization data ***/

TCPIP_DHCPS_CLIENT_OPTION_CONFIG dhcpsOptions0[] =
{
    {
        .optType = TCPIP_DHCPS_CLIENT_OPTION_ROUTER,
        .ipStr = TCPIP_DHCPS_ROUTER_IP_ADDR_IDX0,
    },
    {
        .optType = TCPIP_DHCPS_CLIENT_OPTION_DNS,
        .ipStr = TCPIP_DHCPS_DNS_IP_ADDR_IDX0,
    },
    {
        .optType = TCPIP_DHCPS_CLIENT_OPTION_T1_RENEWAL,
        .mult = TCPIP_DHCPS_T1RENEW_MULT_FACT_IDX0,
        .div = TCPIP_DHCPS_T1RENEW_DIV_FACT_IDX0,
    },
    {
        .optType = TCPIP_DHCPS_CLIENT_OPTION_T2_REBINDING,
        .mult = TCPIP_DHCPS_T2REBIND_MULT_FACT_IDX0,
        .div = TCPIP_DHCPS_T2REBIND_DIV_FACT_IDX0,
    },

};

TCPIP_DHCPS_INTERFACE_CONFIG dhcpsIfConfig[] = 
{
    {
        .ifIndex    = TCPIP_DHCPS_INTERFACE_INDEX_IDX0,
        .configFlags = TCPIP_DHCPS_CONFIG_FLAG_IDX0,
        .leaseEntries = TCPIP_DHCPS_MAX_LEASE_NUM_IDX0,
        .leaseDuration = TCPIP_DHCPS_LEASEDURATION_DFLT_IDX0,
        .minLeaseDuration = TCPIP_DHCPS_LEASEDURATION_MIN_IDX0,
        .maxLeaseDuration = TCPIP_DHCPS_LEASEDURATION_MAX_IDX0,
        .unreqOfferTmo = TCPIP_DHCPS_UNREQ_TMO_IDX0,
        .serverIPAddress = TCPIP_DHCPS_SERVER_IP_ADDRESS_IDX0,
        .startIPAddress = TCPIP_DHCPS_START_IP_ADDR_IDX0,
        .prefixLen = TCPIP_DHCPS_MASK_PREFIX_NUM_IDX0,
        .pOptConfig = dhcpsOptions0,
        .nOptConfigs = sizeof(dhcpsOptions0) / sizeof(*dhcpsOptions0),
    },
};

const TCPIP_DHCPS_MODULE_CONFIG tcpipDHCPSInitData =
{
    .pIfConfig          = dhcpsIfConfig,
    .nConfigs           = sizeof(dhcpsIfConfig) / sizeof(*dhcpsIfConfig),
    .nProbes            = TCPIP_DHCPS_ICMP_PROBES,
    .conflictAttempts   = TCPIP_DHCPS_CONFLICT_ATTEMPTS,
};


/*** DNS Client Initialization Data ***/
const TCPIP_DNS_CLIENT_MODULE_CONFIG tcpipDNSClientInitData =
{
    .deleteOldLease         = TCPIP_DNS_CLIENT_DELETE_OLD_ENTRIES,
    .cacheEntries           = TCPIP_DNS_CLIENT_CACHE_ENTRIES,
    .entrySolvedTmo         = TCPIP_DNS_CLIENT_CACHE_ENTRY_TMO,    
    .nIPv4Entries  = TCPIP_DNS_CLIENT_CACHE_PER_IPV4_ADDRESS,
    .ipAddressType       = TCPIP_DNS_CLIENT_ADDRESS_TYPE,
    .nIPv6Entries  = TCPIP_DNS_CLIENT_CACHE_PER_IPV6_ADDRESS,
};


/*** IPv6 Initialization Data ***/
const TCPIP_IPV6_MODULE_CONFIG  tcpipIPv6InitData = 
{
    .rxfragmentBufSize      = TCPIP_IPV6_RX_FRAGMENTED_BUFFER_SIZE,
    .fragmentPktRxTimeout   = TCPIP_IPV6_FRAGMENT_PKT_TIMEOUT,
};


/*** IPv4 Initialization Data ***/


const TCPIP_IPV4_MODULE_CONFIG  tcpipIPv4InitData = 
{
    .arpEntries = TCPIP_IPV4_ARP_SLOTS, 
};






TCPIP_STACK_HEAP_INTERNAL_CONFIG tcpipHeapConfig =
{
    .heapType = TCPIP_STACK_HEAP_TYPE_INTERNAL_HEAP,
    .heapFlags = TCPIP_STACK_HEAP_USE_FLAGS,
    .heapUsage = TCPIP_STACK_HEAP_USAGE_CONFIG,
    .malloc_fnc = TCPIP_STACK_MALLOC_FUNC,
    .free_fnc = TCPIP_STACK_FREE_FUNC,
    .heapSize = TCPIP_STACK_DRAM_SIZE,
};


const TCPIP_NETWORK_CONFIG __attribute__((unused))  TCPIP_HOSTS_CONFIGURATION[] =
{
    /*** Network Configuration Index 0 ***/
    {
        .interface = TCPIP_NETWORK_DEFAULT_INTERFACE_NAME_IDX0,
        .hostName = TCPIP_NETWORK_DEFAULT_HOST_NAME_IDX0,
        .macAddr = TCPIP_NETWORK_DEFAULT_MAC_ADDR_IDX0,
        .ipAddr = TCPIP_NETWORK_DEFAULT_IP_ADDRESS_IDX0,
        .ipMask = TCPIP_NETWORK_DEFAULT_IP_MASK_IDX0,
        .gateway = TCPIP_NETWORK_DEFAULT_GATEWAY_IDX0,
        .priDNS = TCPIP_NETWORK_DEFAULT_DNS_IDX0,
        .secondDNS = TCPIP_NETWORK_DEFAULT_SECOND_DNS_IDX0,
        .powerMode = TCPIP_NETWORK_DEFAULT_POWER_MODE_IDX0,
        .startFlags = TCPIP_NETWORK_DEFAULT_INTERFACE_FLAGS_IDX0,
        .pMacObject = &TCPIP_NETWORK_DEFAULT_MAC_DRIVER_IDX0,
    },
};

const size_t TCPIP_HOSTS_CONFIGURATION_SIZE = sizeof (TCPIP_HOSTS_CONFIGURATION) / sizeof (*TCPIP_HOSTS_CONFIGURATION);

const TCPIP_STACK_MODULE_CONFIG TCPIP_STACK_MODULE_CONFIG_TBL [] =
{
    {TCPIP_MODULE_IPV4,             &tcpipIPv4InitData},

    {TCPIP_MODULE_ICMP,             0},                             // TCPIP_MODULE_ICMP

    {TCPIP_MODULE_ARP,              &tcpipARPInitData},             // TCPIP_MODULE_ARP
    {TCPIP_MODULE_IPV6,             &tcpipIPv6InitData},            // TCPIP_MODULE_IPV6
    {TCPIP_MODULE_ICMPV6,           0},                             // TCPIP_MODULE_ICMPV6
    {TCPIP_MODULE_NDP,              0},                             // TCPIP_MODULE_NDP
    {TCPIP_MODULE_UDP,              &tcpipUDPInitData},             // TCPIP_MODULE_UDP
    {TCPIP_MODULE_TCP,              &tcpipTCPInitData},             // TCPIP_MODULE_TCP
    {TCPIP_MODULE_DHCP_CLIENT,      &tcpipDHCPInitData},            // TCPIP_MODULE_DHCP_CLIENT
    {TCPIP_MODULE_DHCP_SERVER,      &tcpipDHCPSInitData},           // TCPIP_MODULE_DHCP_SERVER
    {TCPIP_MODULE_ANNOUNCE,         &tcpipAnnounceInitData},        // TCPIP_MODULE_ANNOUNCE
    {TCPIP_MODULE_DNS_CLIENT,       &tcpipDNSClientInitData},       // TCPIP_MODULE_DNS_CLIENT
    {TCPIP_MODULE_SNTP,             &tcpipSNTPInitData},            // TCPIP_MODULE_SNTP

    {TCPIP_MODULE_HTTP_NET_SERVER,  &tcpipHTTPNetInitData},         // TCPIP_MODULE_HTTP_NET_SERVER
    { TCPIP_MODULE_MANAGER,         &tcpipHeapConfig },             // TCPIP_MODULE_MANAGER

// MAC modules
    {TCPIP_MODULE_MAC_WINC,         0},                             // TCPIP_MODULE_MAC_WINC

};

const size_t TCPIP_STACK_MODULE_CONFIG_TBL_SIZE = sizeof (TCPIP_STACK_MODULE_CONFIG_TBL) / sizeof (*TCPIP_STACK_MODULE_CONFIG_TBL);
/*********************************************************************
 * Function:        SYS_MODULE_OBJ TCPIP_STACK_Init()
 *
 * PreCondition:    None
 *
 * Input:
 *
 * Output:          valid system module object if Stack and its componets are initialized
 *                  SYS_MODULE_OBJ_INVALID otherwise
 *
 * Overview:        The function starts the initialization of the stack.
 *                  If an error occurs, the SYS_ERROR() is called
 *                  and the function de-initialize itself and will return false.
 *
 * Side Effects:    None
 *
 * Note:            This function must be called before any of the
 *                  stack or its component routines are used.
 *
 ********************************************************************/


SYS_MODULE_OBJ TCPIP_STACK_Init(void)
{
    TCPIP_STACK_INIT    tcpipInit;

    tcpipInit.pNetConf = TCPIP_HOSTS_CONFIGURATION;
    tcpipInit.nNets = TCPIP_HOSTS_CONFIGURATION_SIZE;
    tcpipInit.pModConfig = TCPIP_STACK_MODULE_CONFIG_TBL;
    tcpipInit.nModules = TCPIP_STACK_MODULE_CONFIG_TBL_SIZE;
    tcpipInit.initCback = 0;

    return TCPIP_STACK_Initialize(0, &tcpipInit.moduleInit);
}
// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

static const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)RTC_Timer32CallbackRegister,
    .timerStart = (SYS_TIME_PLIB_START)RTC_Timer32Start,
    .timerStop = (SYS_TIME_PLIB_STOP)RTC_Timer32Stop,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)RTC_Timer32FrequencyGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)NULL,
};

static const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = RTC_COMPARE_IRQn,
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Instance 0 Initialization Data">


static const SYS_CONSOLE_UART_PLIB_INTERFACE sysConsole0UARTPlibAPI =
{
    .read_t = (SYS_CONSOLE_UART_PLIB_READ)SERCOM1_USART_Read,
    .readCountGet = (SYS_CONSOLE_UART_PLIB_READ_COUNT_GET)SERCOM1_USART_ReadCountGet,
    .readFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_READ_FREE_BUFFFER_COUNT_GET)SERCOM1_USART_ReadFreeBufferCountGet,
    .write_t = (SYS_CONSOLE_UART_PLIB_WRITE)SERCOM1_USART_Write,
    .writeCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_COUNT_GET)SERCOM1_USART_WriteCountGet,
    .writeFreeBufferCountGet = (SYS_CONSOLE_UART_PLIB_WRITE_FREE_BUFFER_COUNT_GET)SERCOM1_USART_WriteFreeBufferCountGet,
};

static const SYS_CONSOLE_UART_INIT_DATA sysConsole0UARTInitData =
{
    .uartPLIB = &sysConsole0UARTPlibAPI,
};

static const SYS_CONSOLE_INIT sysConsole0Init =
{
    .deviceInitData = (const void*)&sysConsole0UARTInitData,
    .consDevDesc = &sysConsoleUARTDevDesc,
    .deviceIndex = 0,
};



// </editor-fold>


static const SYS_CMD_INIT sysCmdInit =
{
    .moduleInit = {0},
    .consoleCmdIOParam = (uint8_t) SYS_CMD_SINGLE_CHARACTER_READ_CONSOLE_IO_PARAM,
	.consoleIndex = 0,
};


static const SYS_DEBUG_INIT debugInit =
{
    .moduleInit = {0},
    .errorLevel = SYS_DEBUG_GLOBAL_ERROR_LEVEL,
    .consoleIndex = 0,
};





// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************

/* MISRAC 2012 deviation block end */

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{

    /* MISRAC 2012 deviation block start */
    /* MISRA C-2012 Rule 2.2 deviated in this file.  Deviation record ID -  H3_MISRAC_2012_R_2_2_DR_1 */

  
    PORT_Initialize();

    CLOCK_Initialize();




    RTC_Initialize();

    EBI_Initialize();

	SDMMC1_Initialize();

	BSP_Initialize();
    SERCOM8_USART_Initialize();

    SERCOM3_USART_Initialize();

    SERCOM2_SPI_Initialize();

    SERCOM1_USART_Initialize();

    EVSYS_Initialize();

    SERCOM0_I2C_Initialize();

	SYSTICK_TimerInitialize();
    DMA_Initialize();

    SERCOM4_USART_Initialize();

    EIC_Initialize();


    /* MISRAC 2012 deviation block start */
    /* Following MISRA-C rules deviated in this block  */
    /* MISRA C-2012 Rule 11.3 - Deviation record ID - H3_MISRAC_2012_R_11_3_DR_1 */
    /* MISRA C-2012 Rule 11.8 - Deviation record ID - H3_MISRAC_2012_R_11_8_DR_1 */

    /* Initialize I2C0 Driver Instance */
    sysObj.drvI2C0 = DRV_I2C_Initialize(DRV_I2C_INDEX_0, (SYS_MODULE_INIT *)&drvI2C0InitData);

    APP_SW_VGPUInit();

    /* Initialize the WINC Driver */
    sysObj.drvWifiWinc = WDRV_WINC_Initialize(0, (SYS_MODULE_INIT*)&wdrvWincInitData);

    DRV_SSD1963_Initialize();


    /* Initialize USI Service Instance 0 */
    sysObj.srvUSI0 = SRV_USI_Initialize(SRV_USI_INDEX_0, (SYS_MODULE_INIT *)&srvUSI0Init);

    sysObj.drvMAXTOUCH = DRV_MAXTOUCH_Initialize(0, (SYS_MODULE_INIT *)&drvMAXTOUCHInitData);

    /* Initialize SPI0 Driver Instance */
    sysObj.drvSPI0 = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&drvSPI0InitData);

   sysObj.drvSDMMC0 = DRV_SDMMC_Initialize(DRV_SDMMC_INDEX_0,(SYS_MODULE_INIT *)&drvSDMMC0InitData);


    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
    H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        
    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);
    
    /* MISRAC 2012 deviation block end */
    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
     H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, (SYS_MODULE_INIT *)&sysConsole0Init);
   /* MISRAC 2012 deviation block end */

    SYS_INP_Init();

    sysObj.sysCommand = (uint32_t) SYS_CMD_Initialize((SYS_MODULE_INIT*)&sysCmdInit);

    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
     H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        
    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);

    /* MISRAC 2012 deviation block end */

    // initialize UI library
    Legato_Initialize();

    /*** File System Service Initialization Code ***/
    (void) SYS_FS_Initialize( (const void *) sysFSInit );

    /* Initialize the USB Host layer */
    sysObj.usbHostObject0 = USB_HOST_Initialize (( SYS_MODULE_INIT *)& usbHostInitData );    

    /* Initialize USB Driver */ 
    sysObj.drvUSBHSObject0 = DRV_USBHS_Initialize(DRV_USBHS_INDEX_0, (SYS_MODULE_INIT *) &drvUSBHSInit0);    


   /* Network Presentation Layer Initialization */
   sysObj.netPres = NET_PRES_Initialize(0, (SYS_MODULE_INIT*)&netPresInitData);
   /* TCPIP Stack Initialization */
   sysObj.tcpip = TCPIP_STACK_Init();
   SYS_ASSERT(sysObj.tcpip != SYS_MODULE_OBJ_INVALID, "TCPIP_STACK_Init Failed" );


    CRYPT_WCCB_Initialize();

    /* MISRAC 2012 deviation block end */
    APP_Initialize();
    APP_BLE_Initialize();
    //APP_HTTP_Initialize();
    //APP_WIFI_Initialize();
    APP_COORDINATOR_Initialize();


    NVIC_Initialize();


    /* MISRAC 2012 deviation block end */
}

/*******************************************************************************
 End of File
*/

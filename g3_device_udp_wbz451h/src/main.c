/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

#define CLKS_PER_LOOP   5
#define CLKS_PER_MS ((CPU_CLOCK_FREQUENCY / 1000000) / CLKS_PER_LOOP)
 
#if false
void APPLICATION_DelayUs(uint16_t us) {
    if (us > 0) {
        long int i = 0;
        for (i = 0; i < CLKS_PER_MS * us; i++) {
            __NOP();
        }
    }
}
 
void APPLICATION_DelayMs(uint16_t ms) {
    if (ms > 0) {
        for (int i = 0; i < ms; i++) {
            APPLICATION_DelayUs(1000);
        }
    }
}
#endif

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
   
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/


/*
  sam3x8e_din.cpp

  Library for the digital inputs on the SAM3X8E.

  By Michael Hirschmugl
*/

#include "sam3x8e_din.h"

/*
  Enables digital input on Pin 20.
*/
void SAM3X8E_DINClass::enable_digital_input(void)
{
    // Pin 20 - PD7
    // PIOD: PIO 14
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_PCER0 = PMC_PCSR0 | DIN_PID;  // PIO: 14
    PMC_WPMR = PMC_WPKEY | WPEN_1;
    
    PIOD_WPMR = PIO_WPKEY | WPEN_0;
    PIOD_PER = PIOC_PSR | (1U << 7);  // PD7 = Pin 20
    PIOD_PUDR = (1U << 7);
    PIOD_ODR = (1U << 7);
    PIOD_IFER = (1U << 7);
    PIOD_LSR = (1U << 7);
    PIOD_DIFSR = (1U << 7);
    PIOD_WPMR = PIO_WPKEY | WPEN_1;
    
}

/*
  Enables interrupts for digital input on Pin 20.
*/
void SAM3X8E_DINClass::enable_digital_input_interrupts(void)
{
    PIOD_WPMR = PIO_WPKEY | WPEN_0;
    PIOD_IER = PIOD_IMR | (1U << 7);
    PIOD_WPMR = PIO_WPKEY | WPEN_1;
    
    INTERRUPT0_ENABLE |= DIN_PID;
    INTERRUPT_PRIORITY_REG_3 |= (uint8_t)(DIG_INP_INTERRUPT_PRIORITY << 16);
}


// Create object
SAM3X8E_DINClass SAM3X8E_DIN = SAM3X8E_DINClass();
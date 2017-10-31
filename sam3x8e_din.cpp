/*
  sam3x8e_din.cpp
*/

#include "sam3x8e_din.h"

void SAM3X8E_DINClass::enable_digital_input(void)
{
    // Pin 20 - PD7
    // PIOD: PIO 14
    PMC_WPMR = WPKEY | 0U;
    PMC_PCER0 = PMC_PCSR0 | (1U << 14);  // PIO: 14
    PMC_WPMR = WPKEY | 1U;
    PIOD_WPMR = PIO_WPMR_KEY | 0U;
    PIOD_PER = PIOC_PSR | (1U << 7);  // PD7 = Pin 20
    PIOD_PUDR = (1U << 7);
    PIOD_ODR = (1U << 7);
    PIOD_IFER = (1U << 7);
    PIOD_LSR = (1U << 7);
    PIOD_DIFSR = (1U << 7);
    PIOD_WPMR = PIO_WPMR_KEY | 1U;
    
}

void SAM3X8E_DINClass::enable_digital_input_interrupts(void)
{
    PIOD_WPMR = PIO_WPMR_KEY | 0U;
    PIOD_IER = PIOD_IMR | (1U << 7);
    PIOD_WPMR = PIO_WPMR_KEY | 1U;
    INTERRUPT_ENABLE |= (1U << 14);
    (*((volatile unsigned long *)(0xE000E400U + (3)))) |=
                                (uint8_t)(DIG_INP_INTERRUPT_PRIORITY << 16);
}


// Create object
SAM3X8E_DINClass SAM3X8E_DIN = SAM3X8E_DINClass();
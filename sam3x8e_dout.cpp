/*
  sam3x8e_dout.cpp

  Library for the digital outputs on the SAM3X8E.

  By Michael Hirschmugl
*/

#include "sam3x8e_dout.h"

/*
  Enables digital output on Pins 94, 95, 96, 97
*/
void SAM3X8E_DOUTClass::enable_digital_output(void)
{
    // Pin 94 - PC12
    // Pin 95 - PC13
    // Pin 96 - PC14
    // Pin 97 - PC15
    // PIOC: PIO 13
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_PCER0 = PMC_PCSR0 | DOUT_PID;  // PIO: 13
    PMC_WPMR = PMC_WPKEY | WPEN_1;
    
    PIOC_WPMR = PIO_WPKEY | WPEN_0;
    PIOC_PER = PIOC_PSR | (1U << 12);  // Pin 94 - PC12
    PIOC_PER = PIOC_PSR | (1U << 13);  // Pin 95 - PC13
    PIOC_PER = PIOC_PSR | (1U << 14);  // Pin 96 - PC14
    PIOC_PER = PIOC_PSR | (1U << 15);  // Pin 97 - PC15
    PIOC_OER = PIOC_OSR | (1U << 12);
    PIOC_OER = PIOC_OSR | (1U << 13);
    PIOC_OER = PIOC_OSR | (1U << 14);
    PIOC_OER = PIOC_OSR | (1U << 15);

    PIOC_WPMR = PIO_WPKEY | WPEN_1;
}

/*
  Enables relay
  
*/
void SAM3X8E_DOUTClass::set_relay(uint32_t relay)
{
  PIOC_SODR = relay;  
}

/*
  Disable relay
  
*/
void SAM3X8E_DOUTClass::reset_relay(uint32_t relay)
{
  PIOC_CODR = relay;  
}




// Create object
SAM3X8E_DOUTClass SAM3X8E_DOUT = SAM3X8E_DOUTClass();
/*
  sam3x8e_adc.cpp

  Library for the AD converter on the SAM3X8E.

  By Michael Hirschmugl
*/

#include "sam3x8e_adc.h"

/*
  Enables analog input.
*/
void SAM3X8E_ADCClass::enable_adc_input(void)
{
    // ADC: PID 37
  
    /*
        Enable Power Management Controller and Clock for ADC
    */
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_PCER1 = PMC_PCSR1 | ADC_PID;  // PID: 37
    PMC_WPMR = PMC_WPKEY | WPEN_1;

}

/*
  Configure ADC.
*/
void SAM3X8E_ADCClass::configure_adc_input(void)
{
    // 10 bit resolution
    
    ADC_WPMR = ADC_WPKEY | WPEN_0;
    
    //ADC config
    ADC_MR = ADC_MR_TRGEN |
             ADC_MR_TRGSEL |
             ADC_MR_LOWRES |
             ADC_MR_SLEEP |
             ADC_MR_FWUP |
             ADC_MR_FREERUN |
             ADC_MR_PRESCAL |
             ADC_MR_STARTUP |
             ADC_MR_SETTLING |
             ADC_MR_ANACH |
             ADC_MR_TRACKTIM |
             ADC_MR_TRANSFER |
             ADC_MR_USEQ;

    //ADC Start
    ADC_CR = ADC_CR_START;

    ADC_WPMR = ADC_WPKEY | WPEN_1;
}

/*
  Software reset ADC.
*/
void SAM3X8E_ADCClass::reset_adc(void)
{

    //ADC Reset
    ADC_CR = ADC_CR_SWRST;

}

/*
  Enables analog input on Pin 81.
  Analog In 3 on the Due board.
*/
void SAM3X8E_ADCClass::enable_ad3(void)
{
    // Pin 81 - Signal: AD4 - I/O line: PA22 - Peripheral: X1 - Channel: CH4

    PIOA_WPMR = PIO_WPKEY | WPEN_0;
    PIOA_PDR = ~PIOA_PSR | (1U << 22);
    PIOA_ODR = ~PIOA_OSR | (1U << 22);
    PIOA_PUDR = PIOA_PUSR | (1U << 22);
    PIOA_WPMR = PIO_WPKEY | WPEN_1;

    
    ADC_WPMR = ADC_WPKEY | WPEN_0;
    //ADC_CHER enable ADC input and assign pin to adc
    ADC_CHER = ADC_CHSR | (1U << 4);

    ADC_WPMR = ADC_WPKEY | WPEN_1;
}

/*
  Enables analog input on Pin 80.
  Analog In 2 on the Due board.
*/
void SAM3X8E_ADCClass::enable_ad2(void)
{
    // Pin 80 - Signal: AD5 - I/O line: PA23 - Peripheral: X1 - Channel: CH5

    PIOA_WPMR = PIO_WPKEY | WPEN_0;
    PIOA_PDR = ~PIOA_PSR | (1U << 23);
    PIOA_ODR = ~PIOA_OSR | (1U << 23);
    PIOA_PUDR = PIOA_PUSR | (1U << 23);
    PIOA_WPMR = PIO_WPKEY | WPEN_1;

    
    ADC_WPMR = ADC_WPKEY | WPEN_0;
    //ADC_CHER enable ADC input and assign pin to adc
    ADC_CHER = ADC_CHSR | (1U << 5);

    ADC_WPMR = ADC_WPKEY | WPEN_1;
}

/*
  Enables analog input on Pin 79.
  Analog In 1 on the Due board.
*/
void SAM3X8E_ADCClass::enable_ad1(void)
{
    // Pin 79 - Signal: AD6 - I/O line: PA24 - Peripheral: X1 - Channel: CH6

    PIOA_WPMR = PIO_WPKEY | WPEN_0;
    PIOA_PDR = ~PIOA_PSR | (1U << 24);
    PIOA_ODR = ~PIOA_OSR | (1U << 24);
    PIOA_PUDR = PIOA_PUSR | (1U << 24);
    PIOA_WPMR = PIO_WPKEY | WPEN_1;

    
    ADC_WPMR = ADC_WPKEY | WPEN_0;
    //ADC_CHER enable ADC input and assign pin to adc
    ADC_CHER = ADC_CHSR | (1U << 6);

    ADC_WPMR = ADC_WPKEY | WPEN_1;
}

/*
  Not used.
*/
void SAM3X8E_ADCClass::enable_adc_input_interrupts(void)
{
// Interrupt ID: 37
}


// Create object
SAM3X8E_ADCClass SAM3X8E_ADC = SAM3X8E_ADCClass();
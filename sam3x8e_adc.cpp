/*
  sam3x8e_adc.cpp

  Library for the AD converter on the SAM3X8E.

  By Michael Hirschmugl
*/

#include "sam3x8e_adc.h"

/*
  
*/
void SAM3X8E_ADCClass::enable_adc_input(void)
{
    // Pin 81 - Signal: AD4 - I/O line: PA22 - Peripheral: X1 - Channel: CH4
    // ADC: PID 37
    // 10 bit resolution
    // Interrupt ID: 37
  
    /*
        Enable Power Management Controller and Clock for ADC
    */
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_PCER1 = PMC_PCSR1 | (1U << 5);  // PID: 37
    PMC_WPMR = PMC_WPKEY | WPEN_1;
    
    //PIOD_WPMR = PIO_WPMR_KEY | WPEN_0; Not mandatory?
    PIOA_WPMR = PIO_WPKEY | WPEN_0;
    PIOA_PDR = (1U << 22);
    PIOA_ODR = (1U << 22);
    PIOA_PUDR = (1U << 22);
    PIOA_WPMR = PIO_WPKEY | WPEN_1;

    //ADC Reset
    ADC_CR = ADC_CR_SWRST;
    
    ADC_WPMR = ADC_WPKEY | WPEN_0;
    //ADC_CHER enable ADC input and assign pin to adc
    ADC_CHER = ADC_CHSR | (1U << 4);
    
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

void SAM3X8E_ADCClass::enable_adc_input_interrupts(void)
{

}


// Create object
SAM3X8E_ADCClass SAM3X8E_ADC = SAM3X8E_ADCClass();
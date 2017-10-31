/*
  sam3x8e_adc.cpp
*/

#include "sam3x8e_adc.h"
#include "intrinsics.h"

void SAM3X8E_ADCClass::enable_adc_input(void)
{
    // Pin 81 - Signal: AD4 - I/O line: PA22 - Peripheral: X1 - Channel: CH4
    // ADC: PID 37
    // 10 bit resolution
    // Interrupt ID: 37
  
    /*
        Enable Power Management Controller and Clock for ADC
    */
    PMC_WPMR = WPKEY | 0U;
    PMC_PCER1 = PMC_PCSR1 | (1U << 5);  // PID: 37
    PMC_WPMR = WPKEY | 1U;
    PIOD_WPMR = PIO_WPMR_KEY | 0U;
    
    PIOA_WPMR = PIO_WPMR_KEY | (0U << 0);
    PIOA_PDR = (1U << 22);
    PIOA_ODR = (1U << 22);
    PIOA_PUDR = (1U << 22);
    PIOA_WPMR = PIO_WPMR_KEY | (1U << 0);

    //ADC Reset
    ADC_CR = (1U << 0);
    
    ADC_WPMR = ADC_WPMR_KEY | (0U << 0);
    //ADC_CHER enable ADC input and assign pin to adc
    ADC_CHER = ADC_CHSR | (1U << 4);
    
    //ADC config
    ADC_MR = ADC_TRGEN | ADC_TRGSEL | ADC_LOWRES | ADC_SLEEP | ADC_FWUP
                       | ADC_FREERUN | ADC_PRESCAL | ADC_STARTUP
                       | ADC_SETTLING | ADC_ANACH | ADC_TRACKTIM
                       | ADC_TRANSFER | ADC_USEQ;

    //ADC Start
    ADC_CR = (1U << 1);

    ADC_WPMR = ADC_WPMR_KEY | (1U << 0);
}

void SAM3X8E_ADCClass::enable_adc_input_interrupts(void)
{

}


// Create object
SAM3X8E_ADCClass SAM3X8E_ADC = SAM3X8E_ADCClass();
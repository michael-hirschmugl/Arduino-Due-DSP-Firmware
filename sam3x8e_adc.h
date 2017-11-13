/*
  sam3x8e_adc.h
*/

#ifndef SAM3X8E_ADC_H
#define SAM3X8E_ADC_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_ADCClass {
public:
	SAM3X8E_ADCClass(void) { };
        
        void enable_adc_input(void);
        void configure_adc_input(void);
        void reset_adc(void);
        void enable_ad3(void);
        void enable_ad2(void);
        void enable_ad1(void);
        void enable_adc_input_interrupts(void);
        
private:

};

extern SAM3X8E_ADCClass SAM3X8E_ADC;

#endif
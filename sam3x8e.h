/*
  sam3x8e.h
*/

#ifndef SAM3X8E_H
#define SAM3X8E_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"
#include "wm8731_setup_definitions.h"

class SAM3X8EClass {
public:
	SAM3X8EClass(void) { };

        
        
        
        void init_clock_for_wm8731(void);
        
        
        
        void init_ssc_clk(void);
        void init_ssc(void);
        void setup_pio_for_ssc(void);
        void setup_ssc_master_transfer(void);
        void ssc_interrupt_setup(void);
        void disable_ssc_interrupt_for_dma(void);
        void enable_digital_input(void);
        void enable_digital_input_interrupts(void);
        void enable_adc_input(void);
        void enable_adc_input_interrupts(void);
        void configure_dma(uint8_t,uint8_t,uint32_t*,uint32_t*,uint32_t,
                           uint8_t,uint8_t);
        void enable_dma_interrupts(uint8_t);
        void enable_dma(void);
        void enable_dma_channel(uint8_t);
        
        void set_dma_btsize(uint8_t, uint32_t);


private:
        uint32_t main_oscillator_frequency;

};

extern SAM3X8EClass SAM3X8E;

#endif
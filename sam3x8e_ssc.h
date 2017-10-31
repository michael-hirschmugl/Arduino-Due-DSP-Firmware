/*
  sam3x8e_ssc.h
*/

#ifndef SAM3X8E_SSC_H
#define SAM3X8E_SSC_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_SSCClass {
public:
	SAM3X8E_SSCClass(void) { };

        void init_ssc_clk(void);
        void init_ssc(void);
        void setup_pio_for_ssc(void);
        void setup_ssc_master_transfer(void);
        void ssc_interrupt_setup(void);
        void disable_ssc_interrupt_for_dma(void);
        
private:

};

extern SAM3X8E_SSCClass SAM3X8E_SSC;

#endif
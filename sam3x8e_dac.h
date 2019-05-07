/*
  sam3x8e_dac.h

  By Michael Hirschmugl
*/

#ifndef SAM3X8E_DAC_H
#define SAM3X8E_DAC_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_DACClass {
public:
	SAM3X8E_DACClass(void) { };
        
        void enable_dac_output(void);
        void configure_dac_output(void);
        void write_dac(uint32_t);
        void write_dac_voltage(int32_t);
        
private:

};

extern SAM3X8E_DACClass SAM3X8E_DAC;

#endif
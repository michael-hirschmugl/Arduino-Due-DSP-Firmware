/*
  sam3x8e_din.h
*/

#ifndef SAM3X8E_DIN_H
#define SAM3X8E_DIN_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_DINClass {
public:
	SAM3X8E_DINClass(void) { };

        void enable_digital_input(void);
        void enable_digital_input_interrupts(void);
        
private:

};

extern SAM3X8E_DINClass SAM3X8E_DIN;

#endif
/*
  sam3x8e_dout.h

  By Michael Hirschmugl
*/

#ifndef SAM3X8E_DOUT_H
#define SAM3X8E_DOUT_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_DOUTClass {
public:
	SAM3X8E_DOUTClass(void) { };

        void enable_digital_output(void);
        
        void set_relay(uint32_t);
        void reset_relay(uint32_t);
        
private:

};

extern SAM3X8E_DOUTClass SAM3X8E_DOUT;

#endif
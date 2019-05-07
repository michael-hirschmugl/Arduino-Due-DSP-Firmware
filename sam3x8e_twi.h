/*
  sam3x8e_twi.h

  By Michael Hirschmugl
*/

#ifndef SAM3X8E_TWI_H
#define SAM3X8E_TWI_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"
#include "wm8731_setup_definitions.h"

class SAM3X8E_TWIClass {
public:
	SAM3X8E_TWIClass(void) { };

        void init_twi1_clk(void);
        void init_twi1(void);
        void setup_pio_for_twi1(void);
        void setup_twi1_master_transfer(void);
        uint8_t send_two_bytes_to_wm8731(uint8_t, uint8_t);
        uint16_t setup_WM8731(void);


private:

};

extern SAM3X8E_TWIClass SAM3X8E_TWI;

#endif
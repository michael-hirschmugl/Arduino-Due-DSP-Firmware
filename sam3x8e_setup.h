/*
  sam3x8e_setup.h
*/

#ifndef SAM3X8E_SETUP_H
#define SAM3X8E_SETUP_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_SETUPClass {
public:
	SAM3X8E_SETUPClass(void) { };
        
        uint8_t init_clock(void);
        void change_flash_read_waitstate(int);
        void enable_main_oscillator(void);
        uint8_t wait_for_main_oscillator(void);
        void set_pll_and_divider(void);
        uint8_t wait_for_pll(void);
        uint8_t select_master_clock(void);
        uint8_t wait_for_master_clock(void);
        void check_main_oscillator_frequency(void);
        
private:
        uint32_t main_oscillator_frequency;

};

extern SAM3X8E_SETUPClass SAM3X8E_SETUP;

#endif
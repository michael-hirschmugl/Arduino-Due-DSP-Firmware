/*
  sam3x8e_wdt.h
*/

#ifndef SAM3X8E_WDT_H
#define SAM3X8E_WDT_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_WDTClass {
public:
	SAM3X8E_WDTClass(void) { };
        
        void disable_watchdog_timer(void);

private:

};

extern SAM3X8E_WDTClass SAM3X8E_WDT;
        
#endif
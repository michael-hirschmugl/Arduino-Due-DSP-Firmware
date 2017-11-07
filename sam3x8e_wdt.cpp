/*
  sam3x8e_wdt.cpp

  Library for the watchdog timer on the SAM3X8E.

  By Michael Hirschmugl
*/

#include "sam3x8e_wdt.h"

/*
  Disables the watchdog timer on the SAM3X8E.
*/
void SAM3X8E_WDTClass::disable_watchdog_timer(void)
{
    (*((volatile unsigned long *)0x400E1A54U)) = (1U << 15);
}

// Create object
SAM3X8E_WDTClass SAM3X8E_WDT = SAM3X8E_WDTClass();
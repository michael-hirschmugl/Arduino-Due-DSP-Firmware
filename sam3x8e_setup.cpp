/*
  sam3x8e_setup.cpp

  General setup library of the SAM3X8E.

  By Michael Hirschmugl
*/

#include "sam3x8e_setup.h"

/*
    Sets the main clock frequency to 84MHz.
    1: NOK (timeout)
    0: OK
*/
uint8_t SAM3X8E_SETUPClass::init_clock(void)
{
    uint8_t i = 0;
    
    change_flash_read_waitstate(5);
    enable_main_oscillator();
    i |= (wait_for_main_oscillator() << 0);
    set_pll_and_divider();
    i |= (wait_for_pll() << 1);
    i |= (select_master_clock() << 2);
    check_main_oscillator_frequency();
    
    if(i > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
    This is needed because the new clock frequency might be too high for the
    flash.
*/
void SAM3X8E_SETUPClass::change_flash_read_waitstate(int waitstate)
{
    EEFC_FMR0 = (waitstate << 8);
    EEFC_FMR1 = (waitstate << 8);
}

/*
    Enables the external crystal oscillator.
*/
void SAM3X8E_SETUPClass::enable_main_oscillator(void)
{
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_CKGR_MOR = PMC_CKGR_MOR_KEY |
                   PMC_CKGR_MOR_MOSCXTEN |
                   PMC_CKGR_MOR_MOSCXTBY |
                   PMC_CKGR_MOR_MOSCRCEN |
                   PMC_CKGR_MOR_MOSCRCF |
                   PMC_CKGR_MOR_MOSCXTST |
                   PMC_CKGR_MOR_MOSCSEL |
                   PMC_CKGR_MOR_CFDEN;
    PMC_WPMR = PMC_WPKEY | WPEN_1;
}

/*
    Waiting for the external crystal oscillator to lock into it's
    new frequency.
    1: timeout
    0: OK
*/
uint8_t SAM3X8E_SETUPClass::wait_for_main_oscillator(void)
{
    uint16_t i = 0;
    
    while(PMC_SR_MOSCXTS != (PMC_SR & PMC_SR_MOSCXTS))
    {
        if(i++ > GLOBAL_TIMEOUT)
        {
            return 1;
        }
    }
    return 0;
}

/*
    Multiplies external clock frequency times 14.
    12MHz * 14 = 168MHz
*/
void SAM3X8E_SETUPClass::set_pll_and_divider(void)
{
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_CKGR_PLLAR = PMC_CKGR_PLLAR_DIVA |
                     PMC_CKGR_PLLAR_PLLACOUNT |
                     PMC_CKGR_PLLAR_MULA |
                     PMC_CKGR_PLLAR_ONE;
    PMC_WPMR = PMC_WPKEY | WPEN_1;
}

/*
    Waiting for the pll to lock into it's new frequency.
    1: timeout
    0: OK
*/
uint8_t SAM3X8E_SETUPClass::wait_for_pll(void)
{
    uint16_t i = 0;
    
    while(PMC_SR_LOCKA != (PMC_SR & PMC_SR_LOCKA))
    {
        if(i++ > GLOBAL_TIMEOUT)
        {
            return 1;
        }
    }
    return 0;
}

/*
    Prescaler divides the pll by factor 2.
    168MHz / 2 = 84MHz
    CSS selects this new clock as master clock.
    1: timeout occured.
    0: OK
*/
uint8_t SAM3X8E_SETUPClass::select_master_clock(void)
{
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_MCKR = (PMC_MCKR & ~PMC_MCKR_PRES_MSK) | PMC_MCKR_PRES;
    if(wait_for_master_clock())
    {
        return 1;
    }
    PMC_MCKR = (PMC_MCKR & ~PMC_MCKR_CSS_MSK) | PMC_MCKR_CSS;
    if(wait_for_master_clock())
    {
        return 1;
    }
    PMC_WPMR = PMC_WPKEY | WPEN_1;
    return 0;
}

/*
    Waiting for the master clock to lock into it's new frequency.
    1: timeout
    0: OK
*/
uint8_t SAM3X8E_SETUPClass::wait_for_master_clock(void)
{
    uint16_t i = 0;
  
    while(PMC_SR_MCKRDY != (PMC_SR & PMC_SR_MCKRDY))
    {
        if(i++ > GLOBAL_TIMEOUT)
        {
            return 1;
        }
    }
    return 0;
}

/*
    Reads the main oscillator frequency and stores the result in
    main_oscillator_frequency.
*/
void SAM3X8E_SETUPClass::check_main_oscillator_frequency(void)
{
    // This should be ready by now
    while(PMC_CKGR_MCFR_MAINFRDY != (PMC_CKGR_MCFR & PMC_CKGR_MCFR_MAINFRDY)){}
    main_oscillator_frequency =
      (((PMC_CKGR_MCFR & PMC_CKGR_MCFR_MAINF_MSK) / 16) * 32000);
}

// Create object
SAM3X8E_SETUPClass SAM3X8E_SETUP = SAM3X8E_SETUPClass();
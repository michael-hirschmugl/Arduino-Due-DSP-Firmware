/*
  sam3x8e_dac.cpp

  Library for the DA converter on the SAM3X8E.

  By Michael Hirschmugl
*/

#include "sam3x8e_dac.h"

/*
  Enables analog output.
*/
void SAM3X8E_DACClass::enable_dac_output(void)
{
    // DAC: PID 38
  
    /*
        Enable Power Management Controller and Clock for DAC
    */
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_PCER1 = PMC_PCSR1 | DAC_PID;  // PID: 38
    PMC_WPMR = PMC_WPKEY | WPEN_1;

}

/*
  Configure DAC on channel 0.
*/
void SAM3X8E_DACClass::configure_dac_output(void)
{
    
    DAC_WPMR = DAC_WPKEY | WPEN_0;
    DAC_CR = 0x01U; // Reset
    DAC_MR = DAC_STARTUP | DAC_REFRESH | DAC_MAXS | DAC_WORD;
    DAC_CHER = 0x01U;   // DAC channel 0
    DAC_WPMR = DAC_WPKEY | WPEN_0;
}

/*
  Write to DAC channel 0.
  uint32_t value ... hex value for DAC
*/
void SAM3X8E_DACClass::write_dac(uint32_t value)
{
    DAC_CDR = 0x0000FFFFU & value;
}

/*
  Write voltage between -3 and +3V to DAC channel 0.
  DAC supports 0.55-2.75V at 12bit
  value need factor 10^6

  example:
  2^12 = 4096
  2.75-0.55 = 2.2V
  2.2V / 4096 = 537µV
  12bit = 0xFFF
  half = 0x7FF -> 0V
  0x000 -> 0.55V -> -3V
  0x7FF -> 2.2V  ->  0V
  0xFFF -> 2.75V -> +3V
  6V -> 12bit -> 1.464mV
  example:
  1.5V
  1.5V * 10^6 = __1500000__
  1.464mV * 10^6 = 1464
  1500000 / 1464 = 1024
  1024 = 0x400
  positive?
  0x7FF + 0x400 = :::0xBFF:::
  example:
  -0.6V
  0.6V * 10^6 = __600000__
  1.464mV * 10^6 = 1464
  600000 / 1464 = 409
  409 = 0x199
  negative?
  0x7FF - 0x199 = :::0x666:::
*/
void SAM3X8E_DACClass::write_dac_voltage(int32_t value)
{
    uint32_t temp = 0x0U;
    temp = (value / 1465);
    temp = temp + 0x07FFU;
    DAC_CDR = (0x0000FFFFU & temp);
}

// Create object
SAM3X8E_DACClass SAM3X8E_DAC = SAM3X8E_DACClass();
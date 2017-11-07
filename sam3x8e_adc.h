/*
  sam3x8e_adc.h
*/

#ifndef SAM3X8E_ADC_H
#define SAM3X8E_ADC_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

/* Hardware triggers are disabled. Starting a conversion is only possible */
/* by software.                                                           */
#define ADC_MR_TRGEN            (1U << 0)
/* TIOA Output of the Timer Counter Channel 2 triggers conversion */
#define ADC_MR_TRGSEL           (0x3U << 1)
/* 10 Bit resolution */
#define ADC_MR_LOWRES           (1U << 4)
/* "Normal" Mode */
#define ADC_MR_SLEEP            (0U << 5)
/* Sleep Mode set by sleep bit */
#define ADC_MR_FWUP             (0U << 6)
/* Never Wait for Trigger */
#define ADC_MR_FREERUN          (1U << 7)
/* ADCClock = MCK / ( (PRESCAL+1) * 2 ) */
#define ADC_MR_PRESCAL          (0x7DU << 8)
/* 512 periods of ADCClock */
#define ADC_MR_STARTUP          (0x8U << 16)
/* Analog settling time: 17 periods of ADCClock */
#define ADC_MR_SETTLING         (0x3U << 20)
/* No analog change on channel switching: DIFF0, GAIN0 and OFF0 are */
/* used for all channels                                            */
#define ADC_MR_ANACH            (0U << 23)
/* Tracking Time = (TRACKTIM + 1) * ADCClock periods */
#define ADC_MR_TRACKTIM         (0x5U << 24)
/* Transfer Period = (TRANSFER * 2 + 3) ADCClock periods */
#define ADC_MR_TRANSFER         (0x6U << 28)
/* Normal Mode: The controller converts channels in a simple numeric order. */
#define ADC_MR_USEQ             (0U << 31)

class SAM3X8E_ADCClass {
public:
	SAM3X8E_ADCClass(void) { };
        
        void enable_adc_input(void);
        void enable_adc_input_interrupts(void);
        
private:

};

extern SAM3X8E_ADCClass SAM3X8E_ADC;

#endif
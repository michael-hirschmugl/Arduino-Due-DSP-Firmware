/*
  sam3x8e_setup_definitions.h

  By Michael Hirschmugl
*/

#ifndef SAM3X8E_SETUP_DEFINITIONS_H
#define SAM3X8E_SETUP_DEFINITIONS_H

/*
    Interrupt Priorities
*/
#define DMAC_INTERRUPT_PRIORITY         (0)
#define SSC_INTERRUPT_PRIORITY          (1)
#define DIG_INP_INTERRUPT_PRIORITY      (5)

/*  Timeout for all setup routines */
#define GLOBAL_TIMEOUT                  (0xFFDCU)

/*
    Relay pinout definitions
    Actually not SAM3X8E specific defines...
*/
#define RELAY_IN_AUDIO                  (1U << 13)
#define RELAY_IN_CV                     (1U << 15)
#define RELAY_MEAS_A1                   (1U << 12)
#define RELAY_MEAS_A2                   (1U << 14)
#define RELAY_ALL                       (0xF000U)

/*
    Main Oscillator Setup
*/
/* The Main Crystal Oscillator is enabled */
#define PMC_CKGR_MOR_MOSCXTEN       (1U << 0)
/* Main Crystall oscillatopr not bypassed */
#define PMC_CKGR_MOR_MOSCXTBY       (0U << 1)
/* The Main On-Chip RC Oscillator is disabled */
#define PMC_CKGR_MOR_MOSCRCEN       (0U << 3)
/* The Fast RC Oscillator Frequency is at 4 MHz (default) */
#define PMC_CKGR_MOR_MOSCRCF        (0x0U << 4)
/* Main Crystal Oscillator Start-up Time */
#define PMC_CKGR_MOR_MOSCXTST       (0xFFU << 8)
/* The Main Crystal Oscillator is selected as Main Oscillator */
#define PMC_CKGR_MOR_MOSCSEL        (1U << 24)
/* The Clock Failure Detector is disabled */
#define PMC_CKGR_MOR_CFDEN          (0U << 25)

/* Divider is bypassed (DIVA=1) */
#define PMC_CKGR_PLLAR_DIVA     (0x01U << 0)
/* Specifies the number of Slow Clock cycles x8 before the LOCKA bit is set */
/* in PMC_SR after CKGR_PLLAR is written.                                   */
#define PMC_CKGR_PLLAR_PLLACOUNT (0x3FU << 8)
/* The PLLA Clock frequency is the PLLA input frequency multiplied          */
/* by MULA + 1                                                              */
#define PMC_CKGR_PLLAR_MULA     (0x0DU << 16)

/* PLLA Clock is selected as master clock source */
#define PMC_MCKR_CSS            (0x2U << 0)
/* Selected clock divided by 2 */
#define PMC_MCKR_PRES           (0x01U << 4)
/* PLLA clock frequency is divided by 1. */
#define PMC_MCKR_PLLADIV2       (0U << 12)
/* UPLL clock frequency is divided by 1. */
#define PMC_MCKR_UPLLDIV2       (0U << 13)

/*
    SSC Controller Setup
*/
//#define SSC_RDATLEN             (0x17U << 0) // 23 + 1 Bit
//#define SSC_RDATLEN             (0x0AU << 0) // 7 + 1 Bit
#define SSC_RDATLEN             (0x0FU << 0) // 15 + 1 Bit
#define SSC_TDATLEN             (0x0FU << 0) // 15 + 1 Bit
//#define SSC_RDATLEN             (0x1FU << 0) // 31 + 1 Bit
//#define SSC_TDATLEN             (0x1FU << 0) // 31 + 1 Bit
/* Receive Clock Selection: RK Pin */
#define SSC_RCKS                (0x2U << 0)
/* Receive Clock Output Mode Selection: NONE */
#define SSC_RCKO                (0x0U << 2)
/* Receive Clock Inversion: The data inputs (Data and Frame Sync signals)   */
/* are sampled on Receive Clock rising edge.                                */
#define SSC_RCKI                (1U << 5)
/* Receive Clock Gating Selection: NONE */
#define SSC_RCKG                (0x0U << 6)
/* Receive Start Selection: Detection of any edge on RF signal */
//#define SSC_RSTART              (0x7U << 8)
#define SSC_RSTART              (0x5U << 8)
/* Receive Start Selection: Detection of rising edge on RF signal */
//#define SSC_RSTART              (0x5U << 8)
/* Receive Stop Selection: After completion of a data transfer when starting */
/* with a Compare 0, the receiver stops the data transfer and waits for a    */
/* new compare 0.                                                            */
#define SSC_RSTOP               (0U << 12)
/* Receive Start Delay: STTDLY clock cycles is inserted between the start    */
/* event and the actual start of reception                                   */
#define SSC_RSTTDLY             (0x01U << 16)
/* Receive Period Divider Selection: If 0, no PERIOD signal is generated     */
#define SSC_RPERIOD             (0x00U << 24)

/* Normal operating mode. */
#define SSC_RLOOP               (0U << 5)
/* The MOST significant bit of the data register is sampled first */
#define SSC_RMSBF               (1U << 7)
/* Data Number per Frame */
#define SSC_RDATNB              (0x0U << 8)
/* Receive Frame Sync Length */
#define SSC_RFSLEN              (0x0U << 16)
/* Receive Frame Sync Output Selection */
#define SSC_RFSOS               (0x0U << 20)
/* Frame Sync Edge Detection: POSITIVE */
#define SSC_RFSEDGE             (0U << 24)
#define SSC_RFSLEN_EXT          (0x0U << 28)

/*
    TWI1 Controller Setup
*/
/* TWI Master Mode Enabled */
#define TWI1_CR_MSEN            (1U << 2)
/* TWI Master Mode disable */
#define TWI1_CR_MSDIS           (0U << 3)
/* TWI Slave Mode Enable */
#define TWI1_CR_SVEN            (0U << 4)
/* TWI Slave Mode disable */
#define TWI1_CR_SVDIS           (1U << 5)
/* Master Read Direction */
#define TWI1_MMR_MREAD          (0U << 12)
/* Device Address */
#define TWI1_MMR_DADR           (0x1AU << 16)
/* Clock Low Divider */
#define TWI1_CWGR_CLDIV         (0xD0U << 0)
/* Clock High Divider */
#define TWI1_CWGR_CHDIV         (0xD0U << 8)
/* Clock Divider */
#define TWI1_CWGR_CKDIV         (0x1U << 16)

/*
    ADC Controller Setup
*/
/* Hardware triggers are disabled. Starting a conversion is only possible */
/* by software.                                                           */
#define ADC_MR_TRGEN            (1U << 0)
/* TIOA Output of the Timer Counter Channel 2 triggers conversion */
#define ADC_MR_TRGSEL           (0x3U << 1)
/* 10 Bit resolution */
//#define ADC_MR_LOWRES           (1U << 4)
/* 12 Bit resolution */
#define ADC_MR_LOWRES           (0U << 4)
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

#endif
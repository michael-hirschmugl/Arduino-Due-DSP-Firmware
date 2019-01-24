/*
  sam3x8e_register_definitions.h

  Defines for peripheral registers of the SAM3X8E.

  By Michael Hirschmugl
*/

#ifndef SAM3X8E_REGISTER_DEFINITIONS_H
#define SAM3X8E_REGISTER_DEFINITIONS_H

#define WPEN_0                  (0U << 0)
#define WPEN_1                  (1U << 0)

#define TWI1_PID                (1U << 23)
#define SSC_PID                 (1U << 26)
#define ADC_PID                 (1U << 5)  // PID 37
#define DIN_PID                 (1U << 14)
#define DOUT_PID                (1U << 13)
#define DAC_PID                 (1U << 6)  // PID 38

/* EEFC Flash Mode Register RW */
#define EEFC_FMR0               (*((volatile unsigned long *)0x400E0A00U))
#define EEFC_FMR1               (*((volatile unsigned long *)0x400E0C00U))

/* PMC (Power Management Controller) Write Protect Mode Register */
#define PMC_WPMR                (*((volatile unsigned long *)0x400E06E4U))
#define PMC_WPKEY               (0x504D43U << 8)

/* PMC Clock Generator Main Oscillator register RW */
#define PMC_CKGR_MOR            (*((volatile unsigned long *)0x400E0620U))
#define PMC_CKGR_MOR_KEY        (0x37U << 16)

/* PMC Status register RO */
#define PMC_SR                  (*((volatile unsigned long *)0x400E0668U))
#define PMC_SR_MOSCXTS          (0U << 0)
#define PMC_SR_LOCKA            (0U << 1)
#define PMC_SR_MCKRDY           (1U << 3)
#define PMC_SR_LOCKU            (1U << 6)
#define PMC_SR_PCKRDY0          (1U << 8)
#define PMC_SR_PCKRDY1          (1U << 9)
#define PMC_SR_PCKRDY2          (1U << 10)
#define PMC_SR_MOSCSELS         (1U << 16)
#define PMC_SR_MOSCRCS          (1U << 17)
#define PMC_SR_CFDEV            (1U << 18)

/* PMC PLLA Register RW */
#define PMC_CKGR_PLLAR          (*((volatile unsigned long *)0x400E0628U))
#define PMC_CKGR_PLLAR_ONE      (1U << 29)

/* PMC Master Clock register RW */
#define PMC_MCKR                (*((volatile unsigned long *)0x400E0630U))
#define PMC_MCKR_CSS_MSK        (0x3U << 0)
#define PMC_MCKR_PRES_MSK       (0x7U << 4)
#define PMC_MCKR_PLLADIV2_MSK   (1U << 12)
#define PMC_MCKR_UPLLDIV2_MSK   (1U << 13)

/* System Clock Enable Register WO */
#define PMC_SCER                (*((volatile unsigned long *)0x400E0600U))
/* Programmable Clock 0 Register RW */
#define PMC_PCK0                (*((volatile unsigned long *)0x400E0640U))

/* PMC Main Clock Frequency Register */
#define PMC_CKGR_MCFR           (*((volatile unsigned long *)0x400E0624U))
#define PMC_CKGR_MCFR_MAINF_MSK (0xFFFFU << 0)
#define PMC_CKGR_MCFR_MAINFRDY  (1U << 16)

/* PMC Peripheral Clock Enable Register 0 WO */
#define PMC_PCER0               (*((volatile unsigned long *)0x400E0610U))
/* PMC Peripheral Clock Status Register 0 RO */
#define PMC_PCSR0               (*((volatile unsigned long *)0x400E0618U))
/* PMC Peripheral Clock Enable Register 1 WO */
#define PMC_PCER1               (*((volatile unsigned long *)0x400E0700U))
/* PMC Peripheral Clock Status Register 1 RO */
#define PMC_PCSR1               (*((volatile unsigned long *)0x400E0708U))

/* PIO Write Protect Mode Registers */
#define PIOA_WPMR               (*((volatile unsigned long *)0x400E0EE4U))
#define PIOB_WPMR               (*((volatile unsigned long *)0x400E10E4U))
#define PIOC_WPMR               (*((volatile unsigned long *)0x400E12E4U))
#define PIOD_WPMR               (*((volatile unsigned long *)0x400E14E4U))
#define PIO_WPKEY               (0x50494FU << 8)

/* PIO Enable Register WO */
#define PIOA_PER                (*((volatile unsigned long *)0x400E0E00U))
#define PIOC_PER                (*((volatile unsigned long *)0x400E1200U))
#define PIOD_PER                (*((volatile unsigned long *)0x400E1400U))

/* PIO Disable Register WO */
#define PIOA_PDR                (*((volatile unsigned long *)0x400E0E04U))
#define PIOB_PDR                (*((volatile unsigned long *)0x400E1004U))

/* PIO Status Register RO */
#define PIOA_PSR                (*((volatile unsigned long *)0x400E0E08U))
#define PIOB_PSR                (*((volatile unsigned long *)0x400E1008U))
#define PIOC_PSR                (*((volatile unsigned long *)0x400E1208U))
#define PIOD_PSR                (*((volatile unsigned long *)0x400E1408U))

/* Output Enable Register WO */
#define PIOA_OER                (*((volatile unsigned long *)0x400E0E10U))
#define PIOC_OER                (*((volatile unsigned long *)0x400E1210U))

/* Output Disable Register WO */
#define PIOA_ODR                (*((volatile unsigned long *)0x400E0E14U))
#define PIOD_ODR                (*((volatile unsigned long *)0x400E1414U))

/* Output Status Register RO */
#define PIOA_OSR                (*((volatile unsigned long *)0x400E0E18U))
#define PIOC_OSR                (*((volatile unsigned long *)0x400E1218U))

/* PIO Set Output Data Register WO */
#define PIOC_SODR               (*((volatile unsigned long *)0x400E1230U))

/* PIO Clear Output Data Register WO */
#define PIOC_CODR               (*((volatile unsigned long *)0x400E1234U))

/* PIO Output Data Status Register WO */
#define PIOC_ODSR               (*((volatile unsigned long *)0x400E1238U))

/* Pull-up Disable Register WO */
#define PIOA_PUDR               (*((volatile unsigned long *)0x400E0E60U))
#define PIOB_PUDR               (*((volatile unsigned long *)0x400E1060U))
#define PIOC_PUDR               (*((volatile unsigned long *)0x400E1260U))
#define PIOD_PUDR               (*((volatile unsigned long *)0x400E1460U))

/* Pad Pull-up Status Register RO */
#define PIOA_PUSR               (*((volatile unsigned long *)0x400E0E68U))
#define PIOB_PUSR               (*((volatile unsigned long *)0x400E1068U))

/* Peripheral AB Select Register RW */
#define PIOA_ABSR               (*((volatile unsigned long *)0x400E0E70U))
#define PIOB_ABSR               (*((volatile unsigned long *)0x400E1070U))

/* Interrupt Enable Register WO */
#define PIOD_IER                (*((volatile unsigned long *)0x400E1440U))
/* Interrupt Mask Register RO */
#define PIOD_IMR                (*((volatile unsigned long *)0x400E1448U))

/* Glitch Input Filter Enable Register WO */
#define PIOD_IFER               (*((volatile unsigned long *)0x400E1420U))

/* Level Select Register WO */
#define PIOD_LSR                (*((volatile unsigned long *)0x400E14C4U))

/* Debouncing Input Filter Select Register WO */
#define PIOD_DIFSR              (*((volatile unsigned long *)0x400E1484U))

/* Pin Data Status Register RO */
#define PIOD_PDSR               (*((volatile unsigned long *)0x400E143CU))

/* Interrupt Control Registers */
#define INTERRUPT0_ENABLE       (*((volatile unsigned long *)0xE000E100U))
#define INTERRUPT1_ENABLE       (*((volatile unsigned long *)0xE000E104U))
#define INTERRUPT0_DISABLE      (*((volatile unsigned long *)0xE000E180U))
#define INTERRUPT0_CLEAR_PENDING (*((volatile unsigned long *)0xE000E280U))
#define INTERRUPT_PRIORITY_REG_3 (*((volatile unsigned long *)(0xE000E400U \
                                 + (3))))
#define INTERRUPT_PRIORITY_REG_6 (*((volatile unsigned long *)(0xE000E400U \
                                 + (6))))

#define DAC_WPMR                (*((volatile unsigned long *)0x400C80E4U))
#define DAC_CR                  (*((volatile unsigned long *)0x400C8000U))
#define DAC_MR                  (*((volatile unsigned long *)0x400C8004U))
#define DAC_WORD                (0x00U << 4)
#define DAC_REFRESH             (0xFFU << 8)
#define DAC_MAXS                (0x01U << 21)
#define DAC_STARTUP             (0x08U << 24)
#define DAC_WPKEY               (0x444143U << 8)
#define DAC_CHER                (*((volatile unsigned long *)0x400C8010U))
#define DAC_CDR                 (*((volatile unsigned long *)0x400C8020U))


/* ADC Write Protect Mode Register */
#define ADC_WPMR                (*((volatile unsigned long *)0x400C00E4U))
#define ADC_WPKEY               (0x414443U << 8)

/* ADC Channel Enable Register WO */
#define ADC_CHER                (*((volatile unsigned long *)0x400C0010U))
/* ADC Channel Status Register RO */
#define ADC_CHSR                (*((volatile unsigned long *)0x400C0018U))

/* ADC Channel Data Register AD3 */
#define ADC_DATA_MEASURE        (*((volatile unsigned long *)0x400C005CU))
/* ADC Channel Data Register AD4 */
#define ADC_CDR_AD4             (*((volatile unsigned long *)0x400C0060U))
/* ADC Channel Data Register AD5 */
#define ADC_CDR_AD5             (*((volatile unsigned long *)0x400C0064U))
/* ADC Channel Data Register AD6 */
#define ADC_CDR_AD6             (*((volatile unsigned long *)0x400C0068U))

/* ADC Control Register */
#define ADC_CR                  (*((volatile unsigned long *)0x400C0000U))
#define ADC_CR_SWRST            (1U << 0)
#define ADC_CR_START            (1U << 1)

/* ADC Mode Register */
#define ADC_MR                  (*((volatile unsigned long *)0x400C0004U))

/* TWI Clock Waveform Generator Register RW */
#define TWI1_CWGR               (*((volatile unsigned long *)0x40090010U))

/* TWI1 Control Register WO */
#define TWI1_CR                 (*((volatile unsigned long *)0x40090000U))
#define TWI1_CR_START           (0U << 0)
#define TWI1_CR_STOP            (1U << 1)
#define TWI1_CR_QUICK           (0U << 6)
#define TWI1_CR_SWRST           (1U << 7)

/* TWI1 Master Mode Register RW */
#define TWI1_MMR                (*((volatile unsigned long *)0x40090004U))

/* TWI1 Transmit Holding Register RW */
#define TWI1_THR                (*((volatile unsigned long *)0x40090034U))

/* TWI1 Status Register RO */
#define TWI1_SR                 (*((volatile unsigned long *)0x40090020U))
#define TWI1_SR_TXRDY           (1U << 2)
#define TWI1_SR_TXCOMP          (1U << 0)
#define TWI1_SR_NACK            (1U << 8)

/* SSC Control Register WO */
#define SSC_CR                  (*((volatile unsigned long *)0x40004000U))
#define SSC_CR_RXEN             (1U << 0)
#define SSC_CR_RXDIS            (0U << 1)
#define SSC_CR_TXEN             (1U << 8)
#define SSC_CR_TXDIS            (0U << 9)
#define SSC_CR_SWRST_SSC        (1U << 15)

/* SSC Clock Mode Register RW */
#define SSC_CMR                 (*((volatile unsigned long *)0x40004004U))
#define SSC_CMR_DIV             (0x000U << 0)

/* SSC Write Protect Mode Register */
#define SSC_WPMR                (*((volatile unsigned long *)0x400040E4U))
#define SSC_WPKEY               (0x535343U << 8)

/* SSC Receive Clock Mode Register RW */
#define SSC_RCMR                (*((volatile unsigned long *)0x40004010U))

/* SSC Receive Frame Mode Register RW */
#define SSC_RFMR                (*((volatile unsigned long *)0x40004014U))

#define SSC_TCMR                (*((volatile unsigned long *)0x40004018U))
#define SSC_TCKS                (0x2U << 0)
#define SSC_TCKO                (0x0U << 2)
#define SSC_TCKI                (1U << 5)
#define SSC_TCKG                (0x0U << 6)
#define SSC_TSTART              (0x1U << 8)
#define SSC_TSTTDLY             (0x01U << 16)
#define SSC_TPERIOD             (0x00U << 24)

#define SSC_TFMR                (*((volatile unsigned long *)0x4000401CU))
#define SSC_TDATDEF             (0U << 5)
#define SSC_TMSBF               (1U << 7)
#define SSC_TDATNB              (0x0U << 8)
#define SSC_TFSLEN              (0x0U << 16)
#define SSC_TFSOS               (0x0U << 20)
#define SSC_TFSDEN              (1U << 23)
#define SSC_TFSEDGE             (0U << 24)
#define SSC_TFSLEN_EXT          (0x0U << 28)

#define SSC_RHR                 (*((volatile unsigned long *)0x40004020U))
#define SSC_RDAT                (0xFFFFFFFFU << 0)

#define SSC_THR                 (*((volatile unsigned long *)0x40004024U))
#define SSC_TDAT                (0xFFFFFFFFU << 0)

#define SSC_RSHR                (*((volatile unsigned long *)0x40004030U))
#define SSC_RSDAT               (0xFFFFU << 0)

#define SSC_TSHR                (*((volatile unsigned long *)0x40004034U))
#define SSC_TSDAT               (0xFFFFU << 0)

#define SSC_SR                  (*((volatile unsigned long *)0x40004040U))
#define SSC_TXRDY               (1U << 0)
#define SSC_TXEMPTY             (1U << 1)
#define SSC_RXRDY               (1U << 4)
#define SSC_OVRUN               (1U << 5)
#define SSC_TXSYN               (1U << 10)
#define SSC_RXSYN               (1U << 11)
#define SSC_TXEN                (1U << 16)
#define SSC_RXEN                (1U << 17)

#define SSC_IER                 (*((volatile unsigned long *)0x40004044U))
#define SSC_IETXRDY             (0U << 0)
#define SSC_IETXEMPTY           (0U << 1)
#define SSC_IERXRDY             (1U << 4)
#define SSC_IEOVRUN             (0U << 5)
#define SSC_IECP0               (0U << 8)
#define SSC_IECP1               (0U << 9)
#define SSC_IETXSYN             (0U << 10)
#define SSC_IERXSYN             (0U << 11)

#define SSC_IDR                 (*((volatile unsigned long *)0x40004048U))
#define SSC_IDTXRDY             (1U << 0)
#define SSC_IDTXEMPTY           (1U << 1)
#define SSC_IDRXRDY             (0U << 4)
#define SSC_IDOVRUN             (1U << 5)
#define SSC_IDCP0               (1U << 8)
#define SSC_IDCP1               (1U << 9)
#define SSC_IDTXSYN             (1U << 10)
#define SSC_IDRXSYN             (1U << 11)

#define SSC_IMR                 (*((volatile unsigned long *)0x4000404CU))
#define SSC_IMTXRDY             (0U << 0)
#define SSC_IMTXEMPTY           (0U << 1)
#define SSC_IMRXRDY             (1U << 4)
#define SSC_IMOVRUN             (0U << 5)
#define SSC_IMCP0               (0U << 8)
#define SSC_IMCP1               (0U << 9)
#define SSC_IMTXSYN             (0U << 10)
#define SSC_IMRXSYN             (0U << 11)


#define DMAC_GCFG               (*((volatile unsigned long *)0x400C4000U))
#define DMAC_ARB_CFG            (1U << 4)
#define DMAC_EN                 (*((volatile unsigned long *)0x400C4004U))
#define DMAC_ENABLE             (1U << 0)
#define DMAC_SREQ               (*((volatile unsigned long *)0x400C4008U))
#define DMAC_DSREQ0             (0U << 1)
#define DMAC_SSREQ0             (0U << 0)
#define DMAC_DSREQ1             (0U << 3)
#define DMAC_SSREQ1             (0U << 2)
#define DMAC_DSREQ2             (0U << 5)
#define DMAC_SSREQ2             (0U << 4)
#define DMAC_DSREQ3             (0U << 7)
#define DMAC_SSREQ3             (0U << 6)
#define DMAC_DSREQ4             (0U << 9)
#define DMAC_SSREQ4             (0U << 8)
#define DMAC_DSREQ5             (0U << 11)
#define DMAC_SSREQ5             (0U << 10)
#define DMAC_CREQ               (*((volatile unsigned long *)0x400C400CU))
#define DMAC_DCREQ0             (0U << 1)
#define DMAC_SCREQ0             (0U << 0)
#define DMAC_DCREQ1             (0U << 3)
#define DMAC_SCREQ1             (0U << 2)
#define DMAC_DCREQ2             (0U << 5)
#define DMAC_SCREQ2             (0U << 4)
#define DMAC_DCREQ3             (0U << 7)
#define DMAC_SCREQ3             (0U << 6)
#define DMAC_DCREQ4             (0U << 9)
#define DMAC_SCREQ4             (0U << 8)
#define DMAC_DCREQ5             (0U << 11)
#define DMAC_SCREQ5             (0U << 10)
#define DMAC_LAST               (*((volatile unsigned long *)0x400C4010U))
#define DMAC_DLAST0             (0U << 1)
#define DMAC_SLAST0             (0U << 0)
#define DMAC_DLAST1             (0U << 3)
#define DMAC_SLAST1             (0U << 2)
#define DMAC_DLAST2             (0U << 5)
#define DMAC_SLAST2             (0U << 4)
#define DMAC_DLAST3             (0U << 7)
#define DMAC_SLAST3             (0U << 6)
#define DMAC_DLAST4             (0U << 9)
#define DMAC_SLAST4             (0U << 8)
#define DMAC_DLAST5             (0U << 11)
#define DMAC_SLAST5             (0U << 10)
#define DMAC_EBCIER             (*((volatile unsigned long *)0x400C4018U))
#define DMAC_EBCIER_BTC0        (1U << 0)
#define DMAC_EBCIER_BTC1        (0U << 1)
#define DMAC_EBCIER_BTC2        (0U << 2)
#define DMAC_EBCIER_BTC3        (0U << 3)
#define DMAC_EBCIER_BTC4        (0U << 4)
#define DMAC_EBCIER_BTC5        (0U << 5)
#define DMAC_EBCIER_CBTC0       (1U << 8)
#define DMAC_EBCIER_CBTC1       (0U << 9)
#define DMAC_EBCIER_CBTC2       (0U << 10)
#define DMAC_EBCIER_CBTC3       (0U << 11)
#define DMAC_EBCIER_CBTC4       (0U << 12)
#define DMAC_EBCIER_CBTC5       (0U << 13)
#define DMAC_EBCIER_ERR0        (1U << 16)
#define DMAC_EBCIER_ERR1        (0U << 17)
#define DMAC_EBCIER_ERR2        (0U << 18)
#define DMAC_EBCIER_ERR3        (0U << 19)
#define DMAC_EBCIER_ERR4        (0U << 20)
#define DMAC_EBCIER_ERR5        (0U << 21)
#define DMAC_EBCIDR             (*((volatile unsigned long *)0x400C401CU))
#define DMAC_EBCIDR_BTC0        (0U << 0)
#define DMAC_EBCIDR_BTC1        (0U << 1)
#define DMAC_EBCIDR_BTC2        (0U << 2)
#define DMAC_EBCIDR_BTC3        (0U << 3)
#define DMAC_EBCIDR_BTC4        (0U << 4)
#define DMAC_EBCIDR_BTC5        (0U << 5)
#define DMAC_EBCIDR_CBTC0       (0U << 8)
#define DMAC_EBCIDR_CBTC1       (0U << 9)
#define DMAC_EBCIDR_CBTC2       (0U << 10)
#define DMAC_EBCIDR_CBTC3       (0U << 11)
#define DMAC_EBCIDR_CBTC4       (0U << 12)
#define DMAC_EBCIDR_CBTC5       (0U << 13)
#define DMAC_EBCIDR_ERR0        (0U << 16)
#define DMAC_EBCIDR_ERR1        (0U << 17)
#define DMAC_EBCIDR_ERR2        (0U << 18)
#define DMAC_EBCIDR_ERR3        (0U << 19)
#define DMAC_EBCIDR_ERR4        (0U << 20)
#define DMAC_EBCIDR_ERR5        (0U << 21)
#define DMAC_EBCIMR             (*((volatile unsigned long *)0x400C4020U))
#define DMAC_EBCIMR_BTC0        (1U << 0)
#define DMAC_EBCIMR_BTC1        (1U << 1)
#define DMAC_EBCIMR_BTC2        (1U << 2)
#define DMAC_EBCIMR_BTC3        (1U << 3)
#define DMAC_EBCIMR_BTC4        (1U << 4)
#define DMAC_EBCIMR_BTC5        (1U << 5)
#define DMAC_EBCIMR_CBTC0       (1U << 8)
#define DMAC_EBCIMR_CBTC1       (1U << 9)
#define DMAC_EBCIMR_CBTC2       (1U << 10)
#define DMAC_EBCIMR_CBTC3       (1U << 11)
#define DMAC_EBCIMR_CBTC4       (1U << 12)
#define DMAC_EBCIMR_CBTC5       (1U << 13)
#define DMAC_EBCIMR_ERR0        (1U << 16)
#define DMAC_EBCIMR_ERR1        (1U << 17)
#define DMAC_EBCIMR_ERR2        (1U << 18)
#define DMAC_EBCIMR_ERR3        (1U << 19)
#define DMAC_EBCIMR_ERR4        (1U << 20)
#define DMAC_EBCIMR_ERR5        (1U << 21)
#define DMAC_EBCISR             (*((volatile unsigned long *)0x400C4024U))
#define DMAC_EBCISR_BTC0        (0U << 0)
#define DMAC_EBCISR_BTC1        (0U << 1)
#define DMAC_EBCISR_BTC2        (0U << 2)
#define DMAC_EBCISR_BTC3        (0U << 3)
#define DMAC_EBCISR_BTC4        (0U << 4)
#define DMAC_EBCISR_BTC5        (0U << 5)
#define DMAC_EBCISR_CBTC0       (0U << 8)
#define DMAC_EBCISR_CBTC1       (0U << 9)
#define DMAC_EBCISR_CBTC2       (0U << 10)
#define DMAC_EBCISR_CBTC3       (0U << 11)
#define DMAC_EBCISR_CBTC4       (0U << 12)
#define DMAC_EBCISR_CBTC5       (0U << 13)
#define DMAC_EBCISR_ERR0        (0U << 16)
#define DMAC_EBCISR_ERR1        (0U << 17)
#define DMAC_EBCISR_ERR2        (0U << 18)
#define DMAC_EBCISR_ERR3        (0U << 19)
#define DMAC_EBCISR_ERR4        (0U << 20)
#define DMAC_EBCISR_ERR5        (0U << 21)
#define DMAC_CHER               (*((volatile unsigned long *)0x400C4028U))
#define DMAC_CHER_ENA0          (1U << 0)
#define DMAC_CHER_ENA1          (0U << 1)
#define DMAC_CHER_ENA2          (0U << 2)
#define DMAC_CHER_ENA3          (0U << 3)
#define DMAC_CHER_ENA4          (0U << 4)
#define DMAC_CHER_ENA5          (0U << 5)
#define DMAC_CHER_SUSP0         (0U << 8)
#define DMAC_CHER_SUSP1         (0U << 9)
#define DMAC_CHER_SUSP2         (0U << 10)
#define DMAC_CHER_SUSP3         (0U << 11)
#define DMAC_CHER_SUSP4         (0U << 12)
#define DMAC_CHER_SUSP5         (0U << 13)
#define DMAC_CHER_KEEP0         (0U << 24)
#define DMAC_CHER_KEEP1         (0U << 25)
#define DMAC_CHER_KEEP2         (0U << 26)
#define DMAC_CHER_KEEP3         (0U << 27)
#define DMAC_CHER_KEEP4         (0U << 28)
#define DMAC_CHER_KEEP5         (0U << 29)
#define DMAC_CHDR               (*((volatile unsigned long *)0x400C402CU))
#define DMAC_CHDR_DIS0          (0U << 0)
#define DMAC_CHDR_DIS1          (0U << 1)
#define DMAC_CHDR_DIS2          (0U << 2)
#define DMAC_CHDR_DIS3          (0U << 3)
#define DMAC_CHDR_DIS4          (0U << 4)
#define DMAC_CHDR_DIS5          (0U << 5)
#define DMAC_CHDR_RES0          (0U << 8)
#define DMAC_CHDR_RES1          (0U << 9)
#define DMAC_CHDR_RES2          (0U << 10)
#define DMAC_CHDR_RES3          (0U << 11)
#define DMAC_CHDR_RES4          (0U << 12)
#define DMAC_CHDR_RES5          (0U << 13)
#define DMAC_CHSR               (*((volatile unsigned long *)0x400C4030U))
#define DMAC_CHSR_ENA0          (1U << 0)
#define DMAC_CHSR_ENA1          (1U << 1)
#define DMAC_CHSR_ENA2          (1U << 2)
#define DMAC_CHSR_ENA3          (1U << 3)
#define DMAC_CHSR_ENA4          (1U << 4)
#define DMAC_CHSR_ENA5          (1U << 5)
#define DMAC_CHSR_SUSP0         (1U << 8)
#define DMAC_CHSR_SUSP1         (1U << 9)
#define DMAC_CHSR_SUSP2         (1U << 10)
#define DMAC_CHSR_SUSP3         (1U << 11)
#define DMAC_CHSR_SUSP4         (1U << 12)
#define DMAC_CHSR_SUSP5         (1U << 13)
#define DMAC_CHSR_EMPT0         (1U << 16)
#define DMAC_CHSR_EMPT1         (1U << 17)
#define DMAC_CHSR_EMPT2         (1U << 18)
#define DMAC_CHSR_EMPT3         (1U << 19)
#define DMAC_CHSR_EMPT4         (1U << 20)
#define DMAC_CHSR_EMPT5         (1U << 21)
#define DMAC_CHSR_STAL0         (1U << 24)
#define DMAC_CHSR_STAL1         (1U << 25)
#define DMAC_CHSR_STAL2         (1U << 26)
#define DMAC_CHSR_STAL3         (1U << 27)
#define DMAC_CHSR_STAL4         (1U << 28)
#define DMAC_CHSR_STAL5         (1U << 29)
#define DMAC_SADDR0(value)      (*((volatile unsigned long *)(0x400C403CU + \
                                (40 * value))))
#define DMAC_SADDR1             (*((volatile unsigned long *)0x400C4064U))
#define DMAC_SADDR2             (*((volatile unsigned long *)0x400C408CU))
#define DMAC_SADDR3             (*((volatile unsigned long *)0x400C40B4U))
#define DMAC_SADDR4             (*((volatile unsigned long *)0x400C40DCU))
#define DMAC_SADDR5             (*((volatile unsigned long *)0x400C4104U))
#define DMAC_DADDR0(value)      (*((volatile unsigned long *)(0x400C4040U + \
                                (40 * value))))
#define DMAC_DADDR1             (*((volatile unsigned long *)0x400C4068U))
#define DMAC_DADDR2             (*((volatile unsigned long *)0x400C4090U))
#define DMAC_DADDR3             (*((volatile unsigned long *)0x400C40B8U))
#define DMAC_DADDR4             (*((volatile unsigned long *)0x400C40E0U))
#define DMAC_DADDR5             (*((volatile unsigned long *)0x400C4108U))
#define DMAC_DSCR0              (*((volatile unsigned long *)0x400C4044U))
#define DMAC_DSCR1              (*((volatile unsigned long *)0x400C406CU))
#define DMAC_DSCR2              (*((volatile unsigned long *)0x400C4094U))
#define DMAC_DSCR3              (*((volatile unsigned long *)0x400C40BCU))
#define DMAC_DSCR4              (*((volatile unsigned long *)0x400C40E4U))
#define DMAC_DSCR5              (*((volatile unsigned long *)0x400C410CU))
#define DMAC_CTRLA0(value)      (*((volatile unsigned long *)(0x400C4048U + \
                                (40 * value))))
#define DMAC_CTRLA0_BTSIZE      (uint16_t)(0x20U << 0)  // 32 bit
#define DMAC_CTRLA0_SCSIZE      (0x0U << 16)
#define DMAC_CTRLA0_DCSIZE      (0x0U << 20)
#define DMAC_CTRLA0_SRC_WIDTH   (0x2U << 24)
#define DMAC_CTRLA0_DST_WIDTH   (0x2U << 28)
#define DMAC_CTRLA0_DONE        (1U << 31)
#define DMAC_CTRLA1             (*((volatile unsigned long *)0x400C4070U))
#define DMAC_CTRLA1_BTSIZE      (0xFFFFU << 0)
#define DMAC_CTRLA1_SCSIZE      (0xFU << 16)
#define DMAC_CTRLA1_DCSIZE      (0xFU << 20)
#define DMAC_CTRLA1_SRC_WIDTH   (0xFU << 24)
#define DMAC_CTRLA1_DST_WIDTH   (0xFU << 28)
#define DMAC_CTRLA1_DONE        (0U << 31)
#define DMAC_CTRLA2             (*((volatile unsigned long *)0x400C4098U))
#define DMAC_CTRLA2_BTSIZE      (0xFFFFU << 0)
#define DMAC_CTRLA2_SCSIZE      (0xFU << 16)
#define DMAC_CTRLA2_DCSIZE      (0xFU << 20)
#define DMAC_CTRLA2_SRC_WIDTH   (0xFU << 24)
#define DMAC_CTRLA2_DST_WIDTH   (0xFU << 28)
#define DMAC_CTRLA2_DONE        (0U << 31)
#define DMAC_CTRLA3             (*((volatile unsigned long *)0x400C40C0U))
#define DMAC_CTRLA3_BTSIZE      (0xFFFFU << 0)
#define DMAC_CTRLA3_SCSIZE      (0xFU << 16)
#define DMAC_CTRLA3_DCSIZE      (0xFU << 20)
#define DMAC_CTRLA3_SRC_WIDTH   (0xFU << 24)
#define DMAC_CTRLA3_DST_WIDTH   (0xFU << 28)
#define DMAC_CTRLA3_DONE        (0U << 31)
#define DMAC_CTRLA4             (*((volatile unsigned long *)0x400C40E8U))
#define DMAC_CTRLA4_BTSIZE      (0xFFFFU << 0)
#define DMAC_CTRLA4_SCSIZE      (0xFU << 16)
#define DMAC_CTRLA4_DCSIZE      (0xFU << 20)
#define DMAC_CTRLA4_SRC_WIDTH   (0xFU << 24)
#define DMAC_CTRLA4_DST_WIDTH   (0xFU << 28)
#define DMAC_CTRLA4_DONE        (0U << 31)
#define DMAC_CTRLA5             (*((volatile unsigned long *)0x400C4110U))
#define DMAC_CTRLA5_BTSIZE      (0xFFFFU << 0)
#define DMAC_CTRLA5_SCSIZE      (0xFU << 16)
#define DMAC_CTRLA5_DCSIZE      (0xFU << 20)
#define DMAC_CTRLA5_SRC_WIDTH   (0xFU << 24)
#define DMAC_CTRLA5_DST_WIDTH   (0xFU << 28)
#define DMAC_CTRLA5_DONE        (0U << 31)
#define DMAC_CTRLB0(value)      (*((volatile unsigned long *)(0x400C404CU + \
                                (40 * value))))
#define DMAC_CTRLB0_SRC_DSCR    (1U << 16)
#define DMAC_CTRLB0_DST_DSCR    (1U << 20)
#define DMAC_CTRLB0_FC          (0x0U << 21)
#define DMAC_CTRLB0_SRC_INCR    (0x2U << 24)
#define DMAC_CTRLB0_DST_INCR    (0x2U << 28)
#define DMAC_CTRLB0_IEN         (0U << 30)
#define DMAC_CTRLB1             (*((volatile unsigned long *)0x400C4074U))
#define DMAC_CTRLB1_SRC_DSCR    (0U << 16)
#define DMAC_CTRLB1_DST_DSCR    (0U << 20)
#define DMAC_CTRLB1_FC          (0xFU << 21)
#define DMAC_CTRLB1_SRC_INCR    (0xFU << 24)
#define DMAC_CTRLB1_DST_INCR    (0xFU << 28)
#define DMAC_CTRLB1_IEN         (0U << 30)
#define DMAC_CTRLB2             (*((volatile unsigned long *)0x400C409CU))
#define DMAC_CTRLB2_SRC_DSCR    (0U << 16)
#define DMAC_CTRLB2_DST_DSCR    (0U << 20)
#define DMAC_CTRLB2_FC          (0xFU << 21)
#define DMAC_CTRLB2_SRC_INCR    (0xFU << 24)
#define DMAC_CTRLB2_DST_INCR    (0xFU << 28)
#define DMAC_CTRLB2_IEN         (0U << 30)
#define DMAC_CTRLB3             (*((volatile unsigned long *)0x400C40C4U))
#define DMAC_CTRLB3_SRC_DSCR    (0U << 16)
#define DMAC_CTRLB3_DST_DSCR    (0U << 20)
#define DMAC_CTRLB3_FC          (0xFU << 21)
#define DMAC_CTRLB3_SRC_INCR    (0xFU << 24)
#define DMAC_CTRLB3_DST_INCR    (0xFU << 28)
#define DMAC_CTRLB3_IEN         (0U << 30)
#define DMAC_CTRLB4             (*((volatile unsigned long *)0x400C40ECU))
#define DMAC_CTRLB4_SRC_DSCR    (0U << 16)
#define DMAC_CTRLB4_DST_DSCR    (0U << 20)
#define DMAC_CTRLB4_FC          (0xFU << 21)
#define DMAC_CTRLB4_SRC_INCR    (0xFU << 24)
#define DMAC_CTRLB4_DST_INCR    (0xFU << 28)
#define DMAC_CTRLB4_IEN         (0U << 30)
#define DMAC_CTRLB5             (*((volatile unsigned long *)0x400C4114U))
#define DMAC_CTRLB5_SRC_DSCR    (0U << 16)
#define DMAC_CTRLB5_DST_DSCR    (0U << 20)
#define DMAC_CTRLB5_FC          (0xFU << 21)
#define DMAC_CTRLB5_SRC_INCR    (0xFU << 24)
#define DMAC_CTRLB5_DST_INCR    (0xFU << 28)
#define DMAC_CTRLB5_IEN         (0U << 30)
#define DMAC_CFG0(value)        (*((volatile unsigned long *)(0x400C4050U + \
                                (40 * value))))
#define DMAC_CFG0_SRC_PER       (0x4U << 0)
#define DMAC_CFG0_DST_PER       (0x0U << 4)
#define DMAC_CFG0_SRC_H2SEL     (1U << 9)
#define DMAC_CFG0_DST_H2SEL     (1U << 13)
#define DMAC_CFG0_SOD(value)    ((0x1U << 16) & (value << 16))
#define DMAC_CFG0_LOCK_IF       (0U << 20)
#define DMAC_CFG0_LOCK_B        (0U << 21)
#define DMAC_CFG0_LOCK_IF_L     (0U << 22)
#define DMAC_CFG0_AHB_PROT      ((0x7U << 24) & (1U << 24))
#define DMAC_CFG0_FIFOCFG       ((0x3U << 28) & (0U << 28))
#define DMAC_CFG1               (*((volatile unsigned long *)0x400C4078U))
#define DMAC_CFG1_SRC_PER       (0xFU << 0)
#define DMAC_CFG1_DST_PER       (0xFU << 4)
#define DMAC_CFG1_SRC_H2SEL     (0U << 9)
#define DMAC_CFG1_DST_H2SEL     (0U << 13)
#define DMAC_CFG1_SOD           (0U << 16)
#define DMAC_CFG1_LOCK_IF       (0U << 20)
#define DMAC_CFG1_LOCK_B        (0U << 21)
#define DMAC_CFG1_LOCK_IF_L     (0U << 22)
#define DMAC_CFG1_AHB_PROT      (0xFU << 24)
#define DMAC_CFG1_FIFOCFG       (0xFU << 28)
#define DMAC_CFG2               (*((volatile unsigned long *)0x400C40A0U))
#define DMAC_CFG2_SRC_PER       (0xFU << 0)
#define DMAC_CFG2_DST_PER       (0xFU << 4)
#define DMAC_CFG2_SRC_H2SEL     (0U << 9)
#define DMAC_CFG2_DST_H2SEL     (0U << 13)
#define DMAC_CFG2_SOD           (0U << 16)
#define DMAC_CFG2_LOCK_IF       (0U << 20)
#define DMAC_CFG2_LOCK_B        (0U << 21)
#define DMAC_CFG2_LOCK_IF_L     (0U << 22)
#define DMAC_CFG2_AHB_PROT      (0xFU << 24)
#define DMAC_CFG2_FIFOCFG       (0xFU << 28)
#define DMAC_CFG3               (*((volatile unsigned long *)0x400C40C8U))
#define DMAC_CFG3_SRC_PER       (0xFU << 0)
#define DMAC_CFG3_DST_PER       (0xFU << 4)
#define DMAC_CFG3_SRC_H2SEL     (0U << 9)
#define DMAC_CFG3_DST_H2SEL     (0U << 13)
#define DMAC_CFG3_SOD           (0U << 16)
#define DMAC_CFG3_LOCK_IF       (0U << 20)
#define DMAC_CFG3_LOCK_B        (0U << 21)
#define DMAC_CFG3_LOCK_IF_L     (0U << 22)
#define DMAC_CFG3_AHB_PROT      (0xFU << 24)
#define DMAC_CFG3_FIFOCFG       (0xFU << 28)
#define DMAC_CFG4               (*((volatile unsigned long *)0x400C40F0U))
#define DMAC_CFG4_SRC_PER       (0xFU << 0)
#define DMAC_CFG4_DST_PER       (0xFU << 4)
#define DMAC_CFG4_SRC_H2SEL     (0U << 9)
#define DMAC_CFG4_DST_H2SEL     (0U << 13)
#define DMAC_CFG4_SOD           (0U << 16)
#define DMAC_CFG4_LOCK_IF       (0U << 20)
#define DMAC_CFG4_LOCK_B        (0U << 21)
#define DMAC_CFG4_LOCK_IF_L     (0U << 22)
#define DMAC_CFG4_AHB_PROT      (0xFU << 24)
#define DMAC_CFG4_FIFOCFG       (0xFU << 28)
#define DMAC_CFG5               (*((volatile unsigned long *)0x400C4118U))
#define DMAC_CFG5_SRC_PER       (0xFU << 0)
#define DMAC_CFG5_DST_PER       (0xFU << 4)
#define DMAC_CFG5_SRC_H2SEL     (0U << 9)
#define DMAC_CFG5_DST_H2SEL     (0U << 13)
#define DMAC_CFG5_SOD           (0U << 16)
#define DMAC_CFG5_LOCK_IF       (0U << 20)
#define DMAC_CFG5_LOCK_B        (0U << 21)
#define DMAC_CFG5_LOCK_IF_L     (0U << 22)
#define DMAC_CFG5_AHB_PROT      (0xFU << 24)
#define DMAC_CFG5_FIFOCFG       (0xFU << 28)

/* DMAC Write Protect Mode Register */
#define DMAC_WPMR               (*((volatile unsigned long *)0x400C41E4U))
#define DMAC_WPKEY              (0x50494FU << 8)

#endif
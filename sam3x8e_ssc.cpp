/*
  sam3x8e_ssc.cpp
*/

#include "sam3x8e_ssc.h"

/*
    Enables the peripheral clock for SSC.
*/
void SAM3X8E_SSCClass::init_ssc_clk(void)
{
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_PCER0 = PMC_PCSR0 | SSC_PER;  //Reading from Enable register??
    PMC_WPMR = PMC_WPKEY | WPEN_1;
}

/*
    Initializes the SSC controller.
*/
void SAM3X8E_SSCClass::init_ssc(void)
{
    init_ssc_clk();
    setup_pio_for_ssc();
}

/*
    The six pins for SSC are configured.
*/
void SAM3X8E_SSCClass::setup_pio_for_ssc(void)
{
    // Peripheral A
    PIOB_WPMR = PIO_WPKEY | WPEN_0;
    PIOB_PDR = ~PIOB_PSR | (1U << 17);
    PIOB_PDR = ~PIOB_PSR | (1U << 18);
    PIOB_PDR = ~PIOB_PSR | (1U << 19);
    PIOB_PUDR = (1U << 17) | (1U << 18) | (1U << 19) | PIOB_PUSR;
    PIOB_ABSR |= (0U << 17);
    PIOB_ABSR |= (0U << 18);
    PIOB_ABSR |= (0U << 19);
    PIOB_WPMR = PIO_WPKEY | WPEN_1;
    // Peripheral B
    PIOA_WPMR = PIO_WPKEY | WPEN_0;
    PIOA_PDR = ~PIOA_PSR | (1U << 14);
    PIOA_PDR = ~PIOA_PSR | (1U << 15);
    PIOA_PDR = ~PIOA_PSR | (1U << 16);
    PIOA_OER = PIOA_OSR | (1U << 16);
    PIOA_PUDR = (1U << 14) | (1U << 15) | (1U << 16) | PIOA_PUSR;
    PIOA_ABSR |= (1U << 14);
    PIOA_ABSR |= (1U << 15);
    PIOA_ABSR |= (1U << 16);
    PIOA_WPMR = PIO_WPKEY | WPEN_1;
}

/*
    Configures SSC for master mode I2S transfer.
*/
void SAM3X8E_SSCClass::setup_ssc_master_transfer(void)
{
    SSC_WPMR = SSC_WPKEY | WPEN_0;
    SSC_CR = SWRST;  // Reset
    
    SSC_CR = RXEN | RXDIS | TXEN | TXDIS;
    SSC_CMR = SSC_DIV; // divider is deactivated (kept for compatibility)
    
    // Clock for receiver and transmitter will both come from RK
    SSC_RCMR = SSC_RCKS | SSC_RCKO | SSC_RCKI | SSC_RCKG | SSC_RSTART
                        | SSC_RSTOP | SSC_RSTTDLY | SSC_RPERIOD;
    
    SSC_RFMR = SSC_RDATLEN | SSC_RLOOP | SSC_RMSBF | SSC_RDATNB
                           | SSC_RFSLEN | SSC_RFSOS | SSC_RFSEDGE
                           | RFSLEN_EXT;
    
    // Transmitter Config
    SSC_TCMR = SSC_TCKS | SSC_TCKI | SSC_TCKO | SSC_TCKG | SSC_TSTART
                        | SSC_TSTTDLY | SSC_TPERIOD;
    
    SSC_TFMR = SSC_TDATLEN | SSC_TDATDEF | SSC_TMSBF | SSC_TDATNB
                           | SSC_TFSLEN | SSC_TFSOS | SSC_TFSEDGE
                           | TFSLEN_EXT;
    
    SSC_IER = SSC_IETXRDY | SSC_IETXEMPTY | SSC_IERXRDY | SSC_IEOVRUN
                          | SSC_IECP0 | SSC_IECP1 | SSC_IETXSYN
                          | SSC_IERXSYN;
    
    SSC_IDR = SSC_IDTXRDY | SSC_IDTXEMPTY | SSC_IDRXRDY | SSC_IDOVRUN
                          | SSC_IDCP0 | SSC_IDCP1 | SSC_IDTXSYN
                          | SSC_IDRXSYN;
    
    SSC_WPMR = SSC_WPKEY | WPEN_1;
}

void SAM3X8E_SSCClass::ssc_interrupt_setup(void)
{
    INTERRUPT0_ENABLE |= (1U << 26);
    (*((volatile unsigned long *)(0xE000E400 + (6)))) |=
                                    (uint8_t)(SSC_INTERRUPT_PRIORITY << 16);
}

void SAM3X8E_SSCClass::disable_ssc_interrupt_for_dma(void)
{
    INTERRUPT0_DISABLE |= (0U << 26);
    INTERRUPT0_CLEAR_PENDING = (0xFFFFFFFFU);
}

// Create object
SAM3X8E_SSCClass SAM3X8E_SSC = SAM3X8E_SSCClass();
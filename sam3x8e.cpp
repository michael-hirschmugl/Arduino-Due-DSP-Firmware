/*
  sam3x8e.cpp
*/

#include "sam3x8e.h"
#include "intrinsics.h"










/*
    Initialization of clock output for WM8731 chip
*/
void SAM3X8EClass::init_clock_for_wm8731(void)
{
    PIOA_WPMR = (0x50494FU << 8) | (0U << 0);
    PIOA_PDR = ~PIOA_PSR | (1U << 1);  // enable peripheral control
    PIOA_PER = PIOA_PSR & ~(1U << 1);
    PIOA_ABSR |= (1U << 1);  // peripherial B selected
    PIOA_WPMR = (0x50494FU << 8) | (1U << 0);
    
    PMC_WPMR = 0x504D4300U;
    PMC_SCER |=	0x0100U;  // page 558
    PMC_PCK0 = 0x01U;  // main crystak osc = 12Mhz
    PMC_WPMR = 0x504D4301U;
}





/*
    Enables the peripheral clock for SSC.
*/
void SAM3X8EClass::init_ssc_clk(void)
{
    PMC_WPMR = 0x504D4300U;
    PMC_PCER0 = PMC_PCSR0 | SSC_PER;
    PMC_WPMR = 0x504D4301U;
}

/*
    Initializes the SSC controller.
*/
void SAM3X8EClass::init_ssc(void)
{
    init_ssc_clk();
    setup_pio_for_ssc();
}

/*
    The six pins for SSC are configured.
    
*/
void SAM3X8EClass::setup_pio_for_ssc(void)
{
    // Peripheral A
    PIOB_WPMR = (0x50494FU << 8) | (0U << 0);
    PIOB_PDR = ~PIOB_PSR | (1U << 17);
    PIOB_PDR = ~PIOB_PSR | (1U << 18);
    PIOB_PDR = ~PIOB_PSR | (1U << 19);
    PIOB_PUDR = (1U << 17) | (1U << 18) | (1U << 19) | PIOB_PUSR;
    PIOB_ABSR |= (0U << 17);
    PIOB_ABSR |= (0U << 18);
    PIOB_ABSR |= (0U << 19);
    PIOB_WPMR = (0x50494FU << 8) | (1U << 0);
    // Peripheral B
    PIOA_WPMR = (0x50494FU << 8) | (0U << 0);
    PIOA_PDR = ~PIOA_PSR | (1U << 14);
    PIOA_PDR = ~PIOA_PSR | (1U << 15);
    PIOA_PDR = ~PIOA_PSR | (1U << 16);
    PIOA_OER = PIOA_OSR | (1U << 16);
    PIOA_PUDR = (1U << 14) | (1U << 15) | (1U << 16) | PIOA_PUSR;
    PIOA_ABSR |= (1U << 14);
    PIOA_ABSR |= (1U << 15);
    PIOA_ABSR |= (1U << 16);
    PIOA_WPMR = (0x50494FU << 8) | (1U << 0);
}

/*
    Configures SSC for master mode I2S transfer.
*/
void SAM3X8EClass::setup_ssc_master_transfer(void)
{
    SSC_WPMR = WPKEY | (0U << 0);
    SSC_CR = SWRST;  // Reset
    
    SSC_CR = RXEN | RXDIS | TXEN | TXDIS;
    SSC_CMR = SSC_DIV; // divider is deaktivated (kept for compatibility)
    
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
    
    SSC_WPMR = WPKEY | (1U << 0);
}

void SAM3X8EClass::ssc_interrupt_setup(void)
{
    INTERRUPT_ENABLE |= (1U << 26);
    (*((volatile unsigned long *)(0xE000E400 + (6)))) |=
                                    (uint8_t)(SSC_INTERRUPT_PRIORITY << 16);
}

void SAM3X8EClass::disable_ssc_interrupt_for_dma(void)
{
    INTERRUPT0_DISABLE |= (0U << 26);
    INTERRUPT0_CLEAR_PENDING = (0xFFFFFFFFU);

}

void SAM3X8EClass::enable_digital_input(void)
{
    // Pin 20 - PD7
    // PIOD: PIO 14
    PMC_WPMR = WPKEY | 0U;
    PMC_PCER0 = PMC_PCSR0 | (1U << 14);  // PIO: 14
    PMC_WPMR = WPKEY | 1U;
    PIOD_WPMR = PIO_WPMR_KEY | 0U;
    PIOD_PER = PIOC_PSR | (1U << 7);  // PD7 = Pin 20
    PIOD_PUDR = (1U << 7);
    PIOD_ODR = (1U << 7);
    PIOD_IFER = (1U << 7);
    PIOD_LSR = (1U << 7);
    PIOD_DIFSR = (1U << 7);
    PIOD_WPMR = PIO_WPMR_KEY | 1U;
    
}

void SAM3X8EClass::enable_digital_input_interrupts(void)
{
    PIOD_WPMR = PIO_WPMR_KEY | 0U;
    PIOD_IER = PIOD_IMR | (1U << 7);
    PIOD_WPMR = PIO_WPMR_KEY | 1U;
    INTERRUPT_ENABLE |= (1U << 14);
    (*((volatile unsigned long *)(0xE000E400U + (3)))) |=
                                (uint8_t)(DIG_INP_INTERRUPT_PRIORITY << 16);
}

void SAM3X8EClass::enable_adc_input(void)
{
    // Pin 81 - Signal: AD4 - I/O line: PA22 - Peripheral: X1 - Channel: CH4
    // ADC: PID 37
    // 10 bit resolution
    // Interrupt ID: 37
  
    /*
        Enable Power Management Controller and Clock for ADC
    */
    PMC_WPMR = WPKEY | 0U;
    PMC_PCER1 = PMC_PCSR1 | (1U << 5);  // PID: 37
    PMC_WPMR = WPKEY | 1U;
    PIOD_WPMR = PIO_WPMR_KEY | 0U;
    
    PIOA_WPMR = PIO_WPMR_KEY | (0U << 0);
    PIOA_PDR = (1U << 22);
    PIOA_ODR = (1U << 22);
    PIOA_PUDR = (1U << 22);
    PIOA_WPMR = PIO_WPMR_KEY | (1U << 0);

    //ADC Reset
    ADC_CR = (1U << 0);
    
    ADC_WPMR = ADC_WPMR_KEY | (0U << 0);
    //ADC_CHER enable ADC input and assign pin to adc
    ADC_CHER = ADC_CHSR | (1U << 4);
    
    //ADC config
    ADC_MR = ADC_TRGEN | ADC_TRGSEL | ADC_LOWRES | ADC_SLEEP | ADC_FWUP
                       | ADC_FREERUN | ADC_PRESCAL | ADC_STARTUP
                       | ADC_SETTLING | ADC_ANACH | ADC_TRACKTIM
                       | ADC_TRANSFER | ADC_USEQ;

    //ADC Start
    ADC_CR = (1U << 1);

    ADC_WPMR = ADC_WPMR_KEY | (1U << 0);
}

void SAM3X8EClass::enable_adc_input_interrupts(void)
{

}

void SAM3X8EClass::configure_dma(uint8_t channel, uint8_t sod,
                                 uint32_t* src, uint32_t* dst,
                                 uint32_t btsize,
                                 uint8_t src_dev,
                                 uint8_t dest_dev)
{
    uint32_t read_dummy = 0;
    uint8_t src_per = 0;
    uint8_t dst_per = 0;
    uint8_t src_h2sel = 0;
    uint8_t dst_h2sel = 0;
    uint8_t fc = 0;
    
    if(src_dev == 9)
    {
        src_per = 0;
        src_h2sel = 0;
    }
    else
    {
        src_per = src_dev;
        src_h2sel = 1;
    }
    
    if(dest_dev == 9)
    {
        dst_per = 0;
        dst_h2sel = 0;
    }
    else
    {
        dst_per = dest_dev;
        dst_h2sel = 1;
    }
    
    if(src_dev == 9)
    {
        if(dest_dev == 9)
        {
            fc = 0x0U;
        }
        else
        {
            fc = 0x1U;
        }
    }
    else
    {
        if(dest_dev == 9)
        {
            fc = 0x2U;
        }
        else
        {
            fc = 0x3U;
        }
      
    }
    
    /*
        pmc_enable_periph_clk(ID_DMAC);
    */
    PMC_WPMR = WPKEY | 0U;
    PMC_PCER1 = PMC_PCSR1 | (1U << 7);  // PID: 39 (DMA)
    PMC_WPMR = WPKEY | 1U;
    
    /*
        dmac_init(DMAC);
        = disable DMA
    */
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_EN = 0U;
    
    /*
        dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
    */
    DMAC_GCFG = DMAC_ARB_CFG; // Round Robin
    
    enable_dma();
    
    DMAC_CFG0(channel) = DMAC_CFG0_SOD(sod) | DMAC_CFG0_AHB_PROT
                                            | DMAC_CFG0_FIFOCFG
                                            | (uint8_t)src_per
                                            | ((uint8_t)dst_per << 4)
                                          | ((uint8_t)(0x1U & dst_h2sel) << 13)
                                          | ((uint8_t)(0x1U & src_h2sel) << 9);
    
    /* Clear any pending interrupts */
    read_dummy = DMAC_EBCISR;
    
    DMAC_SADDR0(channel) = (uint32_t)src;
    DMAC_DADDR0(channel) = (uint32_t)dst;
    
    /*
        dmac_channel_set_descriptor_addr(p_dmac, ul_num, 0);
    */
    DMAC_DSCR0 = (0U << 2);
    
    /*
        dmac_channel_set_ctrlA(p_dmac, ul_num, p_desc->ul_ctrlA);
    */
    DMAC_CTRLA0(channel) = DMAC_CTRLA0_DST_WIDTH | DMAC_CTRLA0_SRC_WIDTH
                                        | (0x0000FFFFU & (btsize));
    
    /*
        dmac_channel_set_ctrlB
    */
    DMAC_CTRLB0(channel) = DMAC_CTRLB0_SRC_DSCR | DMAC_CTRLB0_DST_DSCR
                                       | ((0x7U << 21) & (fc << 21))
                                       | DMAC_CTRLB0_SRC_INCR
                                       | DMAC_CTRLB0_DST_INCR;
    
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);    

}

void SAM3X8EClass::enable_dma(void)
{
    /*
        dmac_enable(DMAC);
    */
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_EN = 1U;
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);
}

void SAM3X8EClass::enable_dma_interrupts(uint8_t channel)
{
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_EBCIER = DMAC_EBCISR | (1U << channel);
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);
    
    INTERRUPT1_ENABLE |= (1U << 7);  // ISR 37 (PID 39?!)
    
    (*((volatile unsigned long *)(0xE000E400 + (9)))) |=
                                (uint8_t)(DMAC_INTERRUPT_PRIORITY << 24);

}

void SAM3X8EClass::enable_dma_channel(uint8_t channel)
{
    /*
        dmac_channel_enable(DMAC, DMA_CH);
    */
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_CHER = (0x0000003FU & (1U << channel));
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);
}



void SAM3X8EClass::set_dma_btsize(uint8_t channel, uint32_t btsize)
{
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_EN = 0U;
    DMAC_CTRLA0(channel) = DMAC_CTRLA0(channel) | (0x0000FFFFU & (btsize));
    enable_dma();
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);


}

// Create object
SAM3X8EClass SAM3X8E = SAM3X8EClass();
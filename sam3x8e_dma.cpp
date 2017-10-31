/*
  sam3x8e_dma.cpp
*/

#include "sam3x8e_dma.h"
#include "intrinsics.h"

void SAM3X8E_DMAClass::configure_dma(uint8_t channel, uint8_t sod,
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

void SAM3X8E_DMAClass::enable_dma(void)
{
    /*
        dmac_enable(DMAC);
    */
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_EN = 1U;
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);
}

void SAM3X8E_DMAClass::enable_dma_interrupts(uint8_t channel)
{
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_EBCIER = DMAC_EBCISR | (1U << channel);
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);
    
    INTERRUPT1_ENABLE |= (1U << 7);  // ISR 37 (PID 39?!)
    
    (*((volatile unsigned long *)(0xE000E400 + (9)))) |=
                                (uint8_t)(DMAC_INTERRUPT_PRIORITY << 24);

}

void SAM3X8E_DMAClass::enable_dma_channel(uint8_t channel)
{
    /*
        dmac_channel_enable(DMAC, DMA_CH);
    */
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_CHER = (0x0000003FU & (1U << channel));
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);
}



void SAM3X8E_DMAClass::set_dma_btsize(uint8_t channel, uint32_t btsize)
{
    DMAC_WPMR = DMAC_WPM_KEY | (0U << 0);
    DMAC_EN = 0U;
    DMAC_CTRLA0(channel) = DMAC_CTRLA0(channel) | (0x0000FFFFU & (btsize));
    enable_dma();
    DMAC_WPMR = DMAC_WPM_KEY | (1U << 0);


}



// Create object
SAM3X8E_DMAClass SAM3X8E_DMA = SAM3X8E_DMAClass();
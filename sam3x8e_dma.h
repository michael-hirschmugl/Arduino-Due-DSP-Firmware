/*
  sam3x8e_dma.h
*/

#ifndef SAM3X8E_DMA_H
#define SAM3X8E_DMA_H

#include <stdint.h>
#include "sam3x8e_register_definitions.h"
#include "sam3x8e_setup_definitions.h"

class SAM3X8E_DMAClass {
public:
	SAM3X8E_DMAClass(void) { };
        
        void configure_dma(uint8_t,uint8_t,uint32_t*,uint32_t*,uint32_t,
                           uint8_t,uint8_t);
        void enable_dma_interrupts(uint8_t);
        void enable_dma(void);
        void enable_dma_channel(uint8_t);
        void set_dma_btsize(uint8_t, uint32_t);
        
private:

};

extern SAM3X8E_DMAClass SAM3X8E_DMA;

#endif
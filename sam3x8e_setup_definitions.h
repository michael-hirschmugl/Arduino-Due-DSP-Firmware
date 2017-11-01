/*
  sam3x8e_setup_definitions.h
*/

#ifndef SAM3X8E_SETUP_DEFINITIONS_H
#define SAM3X8E_SETUP_DEFINITIONS_H

#define DMA_CH                          0
#define DMA_BUF_SIZE                    32
#define DMAC_INTERRUPT_PRIORITY         (0)
#define SSC_INTERRUPT_PRIORITY          (0)
#define DIG_INP_INTERRUPT_PRIORITY      (5)

#define GLOBAL_TIMEOUT                  (0xFFDCU)


/*
    SSC Controller Setup
*/
//#define SSC_RDATLEN             (0x17U << 0) // 23 + 1 Bit
//#define SSC_RDATLEN             (0x0AU << 0) // 7 + 1 Bit
#define SSC_RDATLEN             (0x0FU << 0) // 15 + 1 Bit
#define SSC_TDATLEN             (0x0FU << 0) // 15 + 1 Bit

#endif
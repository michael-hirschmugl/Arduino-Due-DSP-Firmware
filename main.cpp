#include <stdint.h>
#include "intrinsics.h"
#include "sam3x8e_setup.h"
#include "sam3x8e_wdt.h"
#include "sam3x8e_twi.h"
#include "sam3x8e_ssc.h"
#include "sam3x8e_adc.h"
#include "sam3x8e_din.h"
//#include "sam3x8e_dma.h"

#define NCoef                   2
#define DCgain_BP               16   //16*1
#define DCgain_TP               128   //128*1
#define DCgain_HP               1     //1*1
#define prescaling_factor       65536

using namespace std;

void init_clock_for_wm8731(void);

static int      lrtoggle        = 0;

static int32_t  input_l         = 0;
static int32_t  input_l_bypass  = 0;

static int32_t  input_l_x_BP[NCoef+1];
static int32_t  input_l_y_BP[NCoef+1];
static int32_t  input_l_x_TP[NCoef+1];
static int32_t  input_l_y_TP[NCoef+1];
static int32_t  input_l_x_HP[NCoef+1];
static int32_t  input_l_y_HP[NCoef+1];

static int32_t  input_r         = 0;
static int32_t  input_r_bypass  = 0;

static int32_t  input_r_x_BP[NCoef+1];
static int32_t  input_r_y_BP[NCoef+1];
static int32_t  input_r_x_TP[NCoef+1];
static int32_t  input_r_y_TP[NCoef+1];
static int32_t  input_r_x_HP[NCoef+1];
static int32_t  input_r_y_HP[NCoef+1];

static int8_t   input_pointer[NCoef+1];

static int32_t  vol_pot = 0;
static uint8_t  mute = 0;
static uint32_t mute_count = 0;

static int32_t  ACoef_BP[NCoef+1] =
{
          103,
            0,
         -103
};

static int32_t  BCoef_BP[NCoef+1] =
{
           64,
         -117,
           55
};

static int32_t  ACoef_TP[NCoef+1] =
{
           37,
           75,
           37
};

static int32_t  BCoef_TP[NCoef+1] =
{
           64,
         -115,
           52
};

static int32_t  ACoef_HP[NCoef+1] =
{
           70,
            0,
          -70
};

static int32_t  BCoef_HP[NCoef+1] =
{
          128,
          -75,
           19
};

class SSC1
{
public:
    static void Handler();
    static volatile unsigned int ticks;
};

void SSC1::Handler()
{
    uint8_t i = 0;

    if((PIOD_PDSR & 0x80U) == 0x80U)
    {
        mute_count++;
    }
    else
    {
        mute_count = 0;
    }
    if(mute_count > 0xFFFFU)
    {
        mute_count = 0;
        if(mute == 1) mute = 0;
        else mute = 1;
    }
    
    vol_pot = ADC_CDR;

    if(!lrtoggle)
    {
        lrtoggle = 1;
        
        input_l = (int32_t)(SSC_RHR << 16);
        input_l = input_l / prescaling_factor;
        input_l_bypass = input_l / 10;

        i = 0;
        while(i <= NCoef)
        {
            if((input_pointer[i]) < NCoef) input_pointer[i]++;
            else input_pointer[i] = 0;
            i++;
        }
        
        input_l_x_TP[input_pointer[0]] = input_l;
        input_l_y_TP[input_pointer[0]] = ACoef_TP[0] * input_l;
        input_l_x_BP[input_pointer[0]] = input_l;
        input_l_y_BP[input_pointer[0]] = ACoef_BP[0] * input_l;
        input_l_x_HP[input_pointer[0]] = input_l;
        input_l_y_HP[input_pointer[0]] = ACoef_HP[0] * input_l;
        
        i = 1;
        while(i <= NCoef)
        {
            input_l_y_TP[input_pointer[0]] =
                input_l_y_TP[input_pointer[0]] +
                (ACoef_TP[i] * input_l_x_TP[input_pointer[i]]) -
                (BCoef_TP[i] * input_l_y_TP[input_pointer[i]]);
            input_l_y_BP[input_pointer[0]] =
                input_l_y_BP[input_pointer[0]] +
                (ACoef_BP[i] * input_l_x_BP[input_pointer[i]]) -
                (BCoef_BP[i] * input_l_y_BP[input_pointer[i]]);
            input_l_y_HP[input_pointer[0]] =
                input_l_y_HP[input_pointer[0]] +
                (ACoef_HP[i] * input_l_x_HP[input_pointer[i]]) -
                (BCoef_HP[i] * input_l_y_HP[input_pointer[i]]);
            i++;
        }
        
        input_l_y_TP[input_pointer[0]] =
            input_l_y_TP[input_pointer[0]] / BCoef_TP[0];
        input_l_y_BP[input_pointer[0]] =
            input_l_y_BP[input_pointer[0]] / BCoef_BP[0];
        input_l_y_HP[input_pointer[0]] =
            input_l_y_HP[input_pointer[0]] / BCoef_HP[0];
        
        /*
        input_l =
            ((input_l_y_TP[input_pointer[0]]) / DCgain_TP);
*/
        /*
        input_l =
            ((input_l_y_BP[input_pointer[0]]) / DCgain_BP);
*/
        /*
        input_l =
            ((input_l_y_HP[input_pointer[0]]) / DCgain_HP);
*/
        input_l =
            ((input_l_y_TP[input_pointer[0]]) / DCgain_TP) +
            ((input_l_y_BP[input_pointer[0]]) / DCgain_BP) +
            ((input_l_y_HP[input_pointer[0]]) / DCgain_HP) +
            input_l_bypass;

        if(mute) SSC_THR = 0;
        else SSC_THR = (input_l);
    }
    else
    {
        lrtoggle = 0;
        
        input_r = (int32_t)(SSC_RHR << 16);
        input_r = input_r / prescaling_factor;
        input_r_bypass = input_r / 10;

        input_r_x_TP[input_pointer[0]] = input_r;
        input_r_y_TP[input_pointer[0]] = ACoef_TP[0] * input_r;
        input_r_x_BP[input_pointer[0]] = input_r;
        input_r_y_BP[input_pointer[0]] = ACoef_BP[0] * input_r;
        input_r_x_HP[input_pointer[0]] = input_r;
        input_r_y_HP[input_pointer[0]] = ACoef_HP[0] * input_r;
        
        i = 1;
        while(i <= NCoef)
        {
            input_r_y_TP[input_pointer[0]] =
                input_r_y_TP[input_pointer[0]] +
                (ACoef_TP[i] * input_r_x_TP[input_pointer[i]]) -
                (BCoef_TP[i] * input_r_y_TP[input_pointer[i]]);
            input_r_y_BP[input_pointer[0]] =
                input_r_y_BP[input_pointer[0]] +
                (ACoef_BP[i] * input_r_x_BP[input_pointer[i]]) -
                (BCoef_BP[i] * input_r_y_BP[input_pointer[i]]);
            input_r_y_HP[input_pointer[0]] =
                input_r_y_HP[input_pointer[0]] +
                (ACoef_HP[i] * input_r_x_HP[input_pointer[i]]) -
                (BCoef_HP[i] * input_r_y_HP[input_pointer[i]]);
            i++;
        }
        
        input_r_y_TP[input_pointer[0]] =
            input_r_y_TP[input_pointer[0]] / BCoef_TP[0];
        input_r_y_BP[input_pointer[0]] =
            input_r_y_BP[input_pointer[0]] / BCoef_BP[0];
        input_r_y_HP[input_pointer[0]] =
            input_r_y_HP[input_pointer[0]] / BCoef_HP[0];
        /*
        input_r =
            ((input_r_y_TP[input_pointer[0]]) / DCgain_TP);
*/
        /*
        input_r =
            ((input_r_y_BP[input_pointer[0]]) / DCgain_BP);
*/
        /*
        input_r =
            ((input_r_y_HP[input_pointer[0]]) / DCgain_HP);
*/
        input_r =
            ((input_r_y_TP[input_pointer[0]]) / DCgain_TP) +
            ((input_r_y_BP[input_pointer[0]]) / DCgain_BP) +
            ((input_r_y_HP[input_pointer[0]]) / DCgain_HP) +
            input_r_bypass;

        if(mute) SSC_THR = 0;
        else SSC_THR = (input_r);
    }
}

int main()
{
    int i = NCoef;
    int j = 0;

    while(i >= 0)
    {
        input_pointer[i] = j;
        j++;
        i--;
    }

    __disable_interrupt();

    SAM3X8E_WDT.disable_watchdog_timer();

    SAM3X8E_SETUP.init_clock();
    
    init_clock_for_wm8731();
    
    SAM3X8E_TWI.init_twi1();
    SAM3X8E_TWI.setup_twi1_master_transfer();
    SAM3X8E_SSC.init_ssc();

    i =  SAM3X8E_TWI.setup_WM8731();

    SAM3X8E_SSC.setup_ssc_master_transfer();
    SAM3X8E_SSC.ssc_interrupt_setup();
    SAM3X8E_DIN.enable_digital_input();
    SAM3X8E_ADC.enable_adc_input();

    __enable_interrupt();

    while(1)
    {

    }
}

void init_clock_for_wm8731()
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
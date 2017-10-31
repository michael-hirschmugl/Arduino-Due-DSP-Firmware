#include <stdint.h>
#include "intrinsics.h"
#include "sam3x8e.h"
#include "sam3x8e_setup.h"
#include "sam3x8e_wdt.h"
#include "sam3x8e_twi.h"
#include "sam3x8e_ssc.h"
#include "sam3x8e_adc.h"
#include "sam3x8e_din.h"

#define NCoef           2
#define DCgain_BP       192   //64*3
#define DCgain_TP       384   //128*3
#define DCgain_HP       3     //1*3
#define DCgain_MainTP   1

using namespace std;

static int lrtoggle = 0;

static int32_t input_l = 0;

static int32_t input_l_x_BP[NCoef+1];
static int32_t input_l_y_BP[NCoef+1];
static int32_t input_l_x_TP[NCoef+1];
static int32_t input_l_y_TP[NCoef+1];
static int32_t input_l_x_HP[NCoef+1];
static int32_t input_l_y_HP[NCoef+1];
static int32_t input_l_HP_temp = 0;

static int32_t input_l_x_MainTP[NCoef+1];
static int32_t input_l_y_MainTP[NCoef+1];

static int32_t input_r = 0;

static int32_t input_r_x_BP[NCoef+1];
static int32_t input_r_y_BP[NCoef+1];
static int32_t input_r_x_TP[NCoef+1];
static int32_t input_r_y_TP[NCoef+1];
static int32_t input_r_x_HP[NCoef+1];
static int32_t input_r_y_HP[NCoef+1];
static int32_t input_r_HP_temp = 0;

static int32_t input_r_x_MainTP[NCoef+1];
static int32_t input_r_y_MainTP[NCoef+1];

static int8_t input_pointer[NCoef+1];

static int32_t vol_pot = 0;
static uint8_t mute = 0;
static uint32_t mute_count = 0;

static int32_t ACoef_BP[NCoef+1] =
{
    76,
    0,
    -76
};

static int32_t BCoef_BP[NCoef+1] =
{
    64,
    -125,
    62
};

static int32_t ACoef_TP[NCoef+1] =
{
    32,
    64,
    32
};

static int32_t BCoef_TP[NCoef+1] =
{
    64,
    -116,
    53
};

static int32_t ACoef_HP[NCoef+1] =
{
    58,
    -116,
    58
};

static int32_t BCoef_HP[NCoef+1] =
{
    64,
    -116,
    53
};

static int32_t ACoef_MainTP[NCoef+1] =
{
    44,
    88,
     44
};

static int32_t BCoef_MainTP[NCoef+1] =
{
    64,
    81,
    30
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

    if(!lrtoggle)
    {
        lrtoggle = 1;
        
        input_l = (((int32_t)(SSC_RHR << 8)));
        input_l = input_l / 256;

        vol_pot = ADC_CDR;

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
        
        input_l_HP_temp =
            ((input_l_y_HP[input_pointer[0]] * 256) / DCgain_HP);
        
        if(vol_pot != 0) input_l_HP_temp = input_l_HP_temp / (vol_pot/10);
        input_l =
            ((input_l_y_TP[input_pointer[0]] * 256) / DCgain_TP) +
            ((input_l_y_BP[input_pointer[0]] * 256) / DCgain_BP) +
            input_l_HP_temp;
        
        
        input_l_x_MainTP[input_pointer[0]] = (input_l / 256);
        input_l_y_MainTP[input_pointer[0]] = ACoef_MainTP[0] * input_l_x_MainTP[input_pointer[0]];
        
        i = 1;
        while(i <= NCoef)
        {
            input_l_y_MainTP[input_pointer[0]] =
                input_l_y_MainTP[input_pointer[0]] +
                (ACoef_MainTP[i] * input_l_x_MainTP[input_pointer[i]]) -
                (BCoef_MainTP[i] * input_l_y_MainTP[input_pointer[i]]);
            i++;
        }
        
        input_l_y_MainTP[input_pointer[0]] =
            input_l_y_MainTP[input_pointer[0]] / BCoef_MainTP[0];
        
        input_l = ((input_l_y_MainTP[input_pointer[0]] * 128) / DCgain_MainTP);
        
        if(mute) SSC_THR = 0;
        else SSC_THR = input_l;
    }
    else
    {
        lrtoggle = 0;
        
        input_r = (((int32_t)(SSC_RHR << 8)));
        input_r = input_r / 256;

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
        
        input_r_HP_temp =
            ((input_r_y_HP[input_pointer[0]] * 256) / DCgain_HP);
        
        if(vol_pot != 0) input_r_HP_temp = input_r_HP_temp / (vol_pot/10);
        input_r =
            ((input_r_y_TP[input_pointer[0]] * 256) / DCgain_TP) +
            ((input_r_y_BP[input_pointer[0]] * 256) / DCgain_BP) +
            input_r_HP_temp;
        
        
        input_r_x_MainTP[input_pointer[0]] = (input_r / 256);
        input_r_y_MainTP[input_pointer[0]] = ACoef_MainTP[0] * input_r_x_MainTP[input_pointer[0]];
        
        i = 1;
        while(i <= NCoef)
        {
            input_r_y_MainTP[input_pointer[0]] =
                input_r_y_MainTP[input_pointer[0]] +
                (ACoef_MainTP[i] * input_r_x_MainTP[input_pointer[i]]) -
                (BCoef_MainTP[i] * input_r_y_MainTP[input_pointer[i]]);
            i++;
        }
        
        input_r_y_MainTP[input_pointer[0]] =
            input_r_y_MainTP[input_pointer[0]] / BCoef_MainTP[0];
        
        input_r = ((input_r_y_MainTP[input_pointer[0]] * 128) / DCgain_MainTP);
        
        if(mute) SSC_THR = 0;
        else SSC_THR = input_r;
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
    SAM3X8E.init_clock_for_wm8731();
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

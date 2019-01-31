#include <stdint.h>
#include "intrinsics.h"
#include "sam3x8e_setup.h"
#include "sam3x8e_wdt.h"
#include "sam3x8e_twi.h"
#include "sam3x8e_ssc.h"
#include "sam3x8e_adc.h"
#include "sam3x8e_din.h"
#include "sam3x8e_dac.h"
#include "sam3x8e_dout.h"

using namespace std;

const int32_t dac_volt[29] = {
  -1400000,
  -1300000,
  -1200000,
  -1100000,
  -1000000,
  -900000,
  -800000,
  -700000,
  -600000,
  -500000,
  -400000,
  -300000,
  -200000,
  -100000,
  0,
  100000,
  200000,
  300000,
  400000,
  500000,
  600000,
  700000,
  800000,
  900000,
  1000000,
  1100000,
  1200000,
  1300000,
  1400000
};
volatile uint32_t  adc_volt_a1[29];
volatile uint32_t  adc_volt_a2[29];

void init_clock_for_wm8731(void);
void measure_system(void);
int32_t convert_sample_to_voltage(int32_t);
int32_t convert_voltage_to_sample(int32_t);

static   int      lrtoggle  = 0;
volatile int32_t  input_l   = 0;
volatile int32_t  input_r   = 0;
int32_t  coeff_a   = 0;
int32_t  coeff_b   = 0;
int32_t  coeff_c   = 0;

//volatile int32_t  samples[500];
volatile int32_t  sample;
//volatile int      index     = 0;

class SSC1
{
public:
    static void Handler();
    static volatile unsigned int ticks;
};

void SSC1::Handler()
{
    if(!lrtoggle)
    {
        lrtoggle = 1;
        
        input_l = (int32_t)(SSC_RHR);
        
        sample = convert_sample_to_voltage(input_l);
        
        //sample = sample;
        
        sample = convert_voltage_to_sample(sample);

        /*
        if(index > 499)
        {
          index = 0;
        }
        samples[index++] = sample;
        */

        SSC_THR = sample;
    }
    else
    {
        lrtoggle = 0;
        
        input_r = (int32_t)(SSC_RHR);

        SSC_THR = 0x0000U;
    }
}

int main()
{
    volatile int i = 0;
    int done = 0;
    while(!done)
    {
      __disable_interrupt();

      SAM3X8E_WDT.disable_watchdog_timer();

      SAM3X8E_SETUP.init_clock();
      
      init_clock_for_wm8731();
      
      SAM3X8E_TWI.init_twi1();
      SAM3X8E_TWI.setup_twi1_master_transfer();
      SAM3X8E_SSC.init_ssc();

      i = SAM3X8E_TWI.setup_WM8731();

      SAM3X8E_SSC.setup_ssc_master_transfer();
      SAM3X8E_SSC.ssc_interrupt_setup();
      //SAM3X8E_DIN.enable_digital_input();
      SAM3X8E_ADC.enable_adc_input();
      SAM3X8E_ADC.reset_adc();
      //SAM3X8E_ADC.enable_ad1();
      //SAM3X8E_ADC.enable_ad2();
      //SAM3X8E_ADC.enable_ad3();
      SAM3X8E_ADC.enable_measure_adc();
      SAM3X8E_ADC.configure_adc_input();
      
      SAM3X8E_DAC.enable_dac_output();
      SAM3X8E_DAC.configure_dac_output();
      
      SAM3X8E_DOUT.enable_digital_output();
      
      SAM3X8E_DOUT.reset_relay(RELAY_ALL);
      SAM3X8E_DAC.write_dac(0x07FFU);
      
      
      SAM3X8E_DOUT.set_relay(RELAY_IN_AUDIO);
      measure_system();

      while(1)
      {
        SAM3X8E_DAC.write_dac_voltage(-1000000);        
      }
      
      __enable_interrupt();
      if(!i) done = 1;
    }
    
    while(1)
    {
      
    }
}

void init_clock_for_wm8731()
{
    PIOA_WPMR = PIO_WPKEY | WPEN_0;
    PIOA_PDR = ~PIOA_PSR | (1U << 1);  // enable peripheral control
    PIOA_PER = PIOA_PSR & ~(1U << 1);
    PIOA_ABSR |= (1U << 1);  // peripherial B selected
    PIOA_WPMR = PIO_WPKEY | WPEN_1;
    
    PMC_WPMR = PMC_WPKEY | WPEN_0;
    PMC_SCER |=	0x0100U;  // page 558
    PMC_PCK0 = 0x01U;  // main crystak osc = 12Mhz
    PMC_WPMR = PMC_WPKEY | WPEN_1;
}

void measure_system()
{
    volatile int count;
    volatile int points = sizeof(dac_volt)/sizeof(int32_t);
    volatile int repeats = 999999;
    volatile int index;
    volatile int temp = 0;
    float ua1, ua2, ua3, ug1, ug2, ug3, a1, b1, c1;
    index = 0;
    count = 0;
    
    SAM3X8E_DOUT.reset_relay(RELAY_ALL);
    SAM3X8E_DOUT.set_relay(RELAY_MEAS_A2);
    //SAM3X8E_DOUT.set_relay(RELAY_IN_CV);
    
    while(index < points)
    {
      while(count < repeats)
      {
        SAM3X8E_DAC.write_dac_voltage(dac_volt[index]);
        temp = (temp + SAM3X8E_ADC.read_measure_adc(490000))/2;
        count++;
      }
      adc_volt_a1[index] = temp;
      count = 0;
      index++;
    }
    count = 0;
    index = 0;
    //SAM3X8E_DOUT.reset_relay(RELAY_ALL);
    //SAM3X8E_DOUT.set_relay(RELAY_MEAS_A2);
    //SAM3X8E_DOUT.set_relay(RELAY_IN_CV);
    //while(index < points)
    //{
    //  while(count < repeats)
    //  {
    //    SAM3X8E_DAC.write_dac_voltage(dac_volt[index]);
    //    temp = (temp + SAM3X8E_ADC.read_measure_adc())/2;
    //    count++;
    //  }
    //  adc_volt_a2[index] = temp;
    //  count = 0;
    //  index++;
    //}
    //index = 0;
    
    
    //ua1 = ((float)adc_volt_a1[0])/10000;
    //ua2 = ((float)adc_volt_a1[2])/10000;
    //ua3 = ((float)adc_volt_a1[4])/10000;
    //ug1 = (((float)dac_volt[0])/1000000);
    //ug2 = (((float)dac_volt[2])/1000000);
    //ug3 = (((float)dac_volt[4])/1000000);
    
    //a1 = (ug1*(ua2-ua3)+ug2*(ua3-ua1)+ug3*(ua1-ua2))/((ug1-ug2)*(ug1-ug3)*(ug3-ug2));
    //b1 = ((ug1*ug1)*(ua2-ua3)+(ug2*ug2)*(ua3-ua1)+(ug3*ug3)*(ua1-ua2))/((ug1-ug2)*(ug1-ug3)*(ug2-ug3));
    //c1 = ((ug1*ug1)*(ug2*ua3-ug3*ua2)+ug1*((ug3*ug3)*ua2-(ug2*ug2)*ua3)+ug2*ug3*ua1*(ug2-ug3))/((ug1-ug2)*(ug1-ug3)*(ug2-ug3));
    
    //coeff_a = (int32_t)(a1 * 1000);
    //coeff_b = (int32_t)(b1 * 1000);
    //coeff_c = (int32_t)(c1 * 1000);
    
    SAM3X8E_DOUT.reset_relay(RELAY_ALL);
    
    
}

int32_t convert_sample_to_voltage(int32_t sample)
{
  if(sample >= 32767)
  {
    sample = sample - 65535;
    sample = (2850000/32767) * sample;
  }
  else
  {
    sample = (2850000/32767) * sample;
  }
  return sample;
}

int32_t convert_voltage_to_sample(int32_t sample)
{
  volatile int32_t temp = sample;
  uint32_t temp1 = 0;
  if(temp >= 0)
  {
    temp1 = (uint32_t)(temp * 1000);
    temp1 = temp1 / 86975;
    temp = temp1;
  }
  else
  {
    temp1 = (uint32_t)(temp * (-1000));
    temp1 = temp1 / 86975;
    temp = temp1;
    temp = temp * (-1);
    temp = (temp & 0x0000FFFFU) | 0x8000U;
  }
  
  return temp;
}
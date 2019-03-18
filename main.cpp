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
#include <math.h>

using namespace std;

const int32_t dac_volt[3] = {
  -3000000,     // Untere Grenze
  -1500000,     // Arbeitspunkt
  0             // Obere Grenze
};
volatile uint32_t  adc_volt_anode[3];

void    init_clock_for_wm8731(void);
void    measure_system(void);
int32_t convert_sample_to_voltage(int32_t);
int32_t convert_voltage_to_sample(int32_t);

volatile int32_t  input_l   = 0;
volatile int32_t  coeff_a   = 0;
volatile int32_t  coeff_b   = 0;
volatile int32_t  coeff_c   = 0;
volatile int32_t  coeff_g_k = 0;
volatile int32_t  coeff_g_d = 0;
volatile int32_t  z1_i = 0;
volatile int32_t  z2_i = 0;
volatile int32_t  z3_i = 0;
volatile int32_t  y_desired = 0;
volatile int32_t  x_desired = 0;
volatile int32_t  new_bias = 0;

volatile int32_t  sample;
volatile int32_t  delta_x;

volatile int32_t  pre_samples[100];
volatile int32_t  samples[100];
volatile int32_t  counter;

class SSC1
{
public:
    static void Handler();
    static volatile unsigned int ticks;
};

void SSC1::Handler()
{
  input_l = (int32_t)(SSC_RHR);
  //sample = convert_sample_to_voltage(input_l) + dac_volt[1];
  sample = convert_sample_to_voltage(input_l);
  y_desired = ((sample / 1000) * coeff_g_k) + coeff_g_d;
  x_desired = (y_desired / 1000) * z1_i;
  x_desired = x_desired + z2_i;
  x_desired = sqrt(x_desired);
  x_desired = x_desired + coeff_b;
  x_desired = (((-1000)*x_desired) / z3_i)*1000;

  //sample = convert_voltage_to_sample(x_desired - new_bias);
  sample = sample / 1000;
  sample = sample * 1000;
  sample = convert_voltage_to_sample(sample);
  /*
  if(counter < 100)
  {
    pre_samples[counter] = sample;
    sample = convert_voltage_to_sample(sample);
    samples[counter++] = sample;
  }
  else
  {
    counter = 0;
  }
*/
  SSC_THR = sample;
}

int main()
{
    __disable_interrupt();
    
    SAM3X8E_WDT.disable_watchdog_timer();
    
    SAM3X8E_SETUP.init_clock();
    
    init_clock_for_wm8731();
    
    SAM3X8E_TWI.init_twi1();
    SAM3X8E_TWI.setup_twi1_master_transfer();
    SAM3X8E_SSC.init_ssc();
    
    SAM3X8E_TWI.setup_WM8731();
    
    SAM3X8E_SSC.setup_ssc_master_transfer();
    SAM3X8E_SSC.ssc_interrupt_setup();
    SAM3X8E_DIN.enable_digital_input();
    SAM3X8E_ADC.enable_adc_input();
    SAM3X8E_ADC.reset_adc();
    SAM3X8E_ADC.enable_ad1();
    SAM3X8E_ADC.enable_ad2();
    SAM3X8E_ADC.enable_ad3();
    SAM3X8E_ADC.enable_measure_adc();
    SAM3X8E_ADC.configure_adc_input();
    
    SAM3X8E_DAC.enable_dac_output();
    SAM3X8E_DAC.configure_dac_output();
    
    SAM3X8E_DOUT.enable_digital_output();
    
    SAM3X8E_DOUT.reset_relay(RELAY_ALL);        // All Relays OFF
    SAM3X8E_DAC.write_dac(0x07FFU);             // U_cv = 0V
    
    //measure_system();
    
    //SAM3X8E_DAC.write_dac_voltage(new_bias);
    SAM3X8E_DAC.write_dac_voltage(-500000);

    __enable_interrupt();
    
    SAM3X8E_DOUT.set_relay(RELAY_IN_AUDIO);

    while(1){}
}

void init_clock_for_wm8731()
{
    PIOA_WPMR  =  PIO_WPKEY | WPEN_0;
    PIOA_PDR   =  ~PIOA_PSR | (1U << 1);          // enable peripheral control
    PIOA_PER   =  PIOA_PSR & ~(1U << 1);
    PIOA_ABSR |=  (1U << 1);                      // peripherial B selected
    PIOA_WPMR  =  PIO_WPKEY | WPEN_1;
    
    PMC_WPMR   =  PMC_WPKEY | WPEN_0;
    PMC_SCER  |=  0x0100U;                        // page 558
    PMC_PCK0   =  0x01U;                          // main crystak osc = 12Mhz
    PMC_WPMR   =  PMC_WPKEY | WPEN_1;
}

void measure_system()
{
    volatile int points = sizeof(dac_volt)/sizeof(int32_t);
    volatile int index;
    int i,j;
    int temp,temp1;
    float ua1, ua2, ua3, ug1, ug2, ug3, a1, b1, c1;
    float z1,z2,z3;
    index = 0;
    i = index;
    j = points;
    
    SAM3X8E_DOUT.reset_relay(RELAY_ALL);        // All Relays OFF
    SAM3X8E_DOUT.set_relay(RELAY_MEAS_A2);      // Relay Preamp Measurement ON
    
    while(i < j)
    {
      SAM3X8E_DOUT.reset_relay(RELAY_ALL);
      SAM3X8E_DOUT.set_relay(RELAY_MEAS_A2);
      SAM3X8E_DAC.write_dac_voltage(dac_volt[index]);              // Set U_cv
      adc_volt_anode[index] = SAM3X8E_ADC.measure_preamp_anode();  // Read U_a
      i++;
      index = i;
    }
    
    ua1 = ((float)adc_volt_anode[0])/1000000;
    ua2 = ((float)adc_volt_anode[1])/1000000;
    ua3 = ((float)adc_volt_anode[2])/1000000;
    ug1 = (((float)dac_volt[0])/1000000);
    ug2 = (((float)dac_volt[1])/1000000);
    ug3 = (((float)dac_volt[2])/1000000);
    
    // Koeffizienten für quadratische Funktion
    a1 = (ug1*(ua2-ua3)+ug2*(ua3-ua1)+ug3*(ua1-ua2))/
         ((ug1-ug2)*(ug1-ug3)*(ug3-ug2));
    b1 = ((ug1*ug1)*(ua2-ua3)+(ug2*ug2)*(ua3-ua1)+(ug3*ug3)*(ua1-ua2))/
         ((ug1-ug2)*(ug1-ug3)*(ug2-ug3));
    c1 = ((ug1*ug1)*(ug2*ua3-ug3*ua2)+ug1*((ug3*ug3)*ua2-(ug2*ug2)*ua3)+
         ug2*ug3*ua1*(ug2-ug3))/((ug1-ug2)*(ug1-ug3)*(ug2-ug3));
    
    // Skalieren der Koeffizienten
    //coeff_a = (int32_t)(a1 * 1000);
    coeff_b = (int32_t)(b1 * 1000);
    //coeff_c = (int32_t)(c1 * 1000);
    
    // Koeffizienten für lineaere Funktion
    coeff_g_k = (int32_t)(((ua1 - ua3)/(ug1 - ug3))*1000);
    coeff_g_d = (int32_t)((ua3 - (coeff_g_k * ug3))*1000000);
    
    // Hilfswerte für Linearisierung
    z1 = 4*a1;
    z2 = (-4)*a1*c1+(b1*b1);
    z3 = 2*a1;
    z1_i = (int32_t)(z1 * 1000);
    z2_i = (int32_t)(z2 * 1000000);
    z3_i = (int32_t)(z3 * 1000);
    
    // Neuen Arbeitspunkt berechnen
    y_desired = ((dac_volt[1] / 1000) * coeff_g_k) + coeff_g_d;
    x_desired = (y_desired / 1000) * z1_i;
    x_desired = x_desired + z2_i;
    x_desired = sqrt(x_desired);
    x_desired = x_desired + coeff_b;
    x_desired = (((-1000)*x_desired) / z3_i)*1000;
    
    new_bias = x_desired;                       // Neuer Arbeitspunkt
    
    SAM3X8E_DOUT.reset_relay(RELAY_ALL);        // All Relays OFF
}

int32_t convert_sample_to_voltage(int32_t sample)
{
  if(sample >= 32767)
  {
    sample = sample - 65535;
    sample = (1200000/32767) * sample;
  }
  else
  {
    sample = (1200000/32767) * sample;
  }
  return sample;
}

int32_t convert_voltage_to_sample(int32_t sample)
{
  //volatile int32_t temp = sample;
  //int16_t test = 0;
  //uint32_t temp1 = 0;
  /*
  if(temp >= 0)
  {
    temp1 = (uint32_t)(temp * 1000);
    temp1 = temp1 / 36621;
    temp = (temp1 & 0x0000FFFFU);
  }
  else
  {
    temp1 = (uint32_t)(temp * (-1000));
    temp1 = temp1 / 36621;
    temp = (-1)*temp1;
    test = (int16_t)((temp) & 0x0000FFFFU);
    temp = (int32_t)test;
    //sample = temp;
  }
*/
  if(sample >= 0)
  {
    sample = (sample * 1000);
    sample = sample / 36621;
    sample = (sample & 0x0000FFFFU);
  }
  else
  {
    sample = (sample * 1000);
    sample = sample / 36621;
    sample = (sample & 0x0000FFFFU);
    sample = (sample | 0x8000U);
  }

  
  return sample;
}
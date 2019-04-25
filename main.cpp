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

/* ------------------- */
/*  MODE OF OPERATION  */
/* ------------------- */
//#define LINEARISATION
//#define OPT_LINEARISATION
//#define PASS_THROUGH
//#define FULL_SWEEP
#define COMP
/* ------------------- */

#define RMS_SAMPLES 1000
#define BIAS -1500000

#define COMP_THRESH_DB -10
#define COMP_BIAS -700000

#ifdef LINEARISATION
const int32_t dac_volt[3] = {
  -3000000,     // Untere Grenze
  BIAS,         // Arbeitspunkt
  0             // Obere Grenze
};
#endif /* LINEARISATION */

#ifdef OPT_LINEARISATION
const int32_t dac_volt[4] = {
  -3000000,     // Untere Grenze
  BIAS,         // Arbeitspunkt
  -700000,
  0             // Obere Grenze
};
#endif /* OPT_LINEARISATION */

#ifdef FULL_SWEEP
const int32_t dac_volt[31] = {
  -3000000,
  -2900000,
  -2800000,
  -2700000,
  -2600000,
  -2500000,
  -2400000,
  -2300000,
  -2200000,
  -2100000,
  -2000000,
  -1900000,
  -1800000,
  -1700000,
  -1600000,
  -1500000,
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
  0
};
#endif /* FULL_SWEEP */

#ifdef LINEARISATION
uint32_t  adc_volt_anode[3];
#endif /* LINEARISATION */
#ifdef OPT_LINEARISATION
uint32_t  adc_volt_anode[4];
#endif /* OPT_LINEARISATION */
#ifdef FULL_SWEEP
uint32_t  adc_volt_anode[31];
#endif /* FULL_SWEEP */

void    init_clock_for_wm8731(void);
#if defined(LINEARISATION) || defined(OPT_LINEARISATION) || defined(FULL_SWEEP)
void    measure_system(void);
#endif /* LINEARISATION or OPT_LINEARISATION or FULL_SWEEP */
int32_t convert_sample_to_voltage(int32_t);
int32_t convert_voltage_to_sample(int32_t);

int32_t  input_l   = 0;
int32_t  sample    = 0;

#if defined(LINEARISATION) || defined(OPT_LINEARISATION)
int32_t  coeff_a   = 0;
int32_t  coeff_b   = 0;
int32_t  coeff_c   = 0;
int32_t  coeff_g_k = 0;
int32_t  coeff_g_d = 0;
int32_t  z1_i      = 0;
int32_t  z2_i      = 0;
int32_t  z3_i      = 0;
int32_t  y_desired = 0;
int32_t  x_desired = 0;
int32_t  new_bias  = 0;
#endif /* LINEARISATION or OPT_LINEARISATION */

#ifdef PASS_THROUGH
volatile int32_t  samples[100];
volatile int32_t  counter;
#endif /* PASS_THROUGH */

#ifdef COMP
int32_t rms_tot    = 1;
int32_t rms_res    = 0;
int32_t rms_w      = RMS_SAMPLES;
int32_t rms_new    = 0;
int32_t rms_last   = 0;
int32_t rms_count  = 0;
int32_t rms_loop[RMS_SAMPLES];
int32_t rms_loop_ptr = 0;
int32_t u_cv       = 0;
int32_t iCompThreshRMS     = 0;
float fCompThreshRMS       = 0;
int32_t iCompThreshAMP     = 0;
float fCompThreshAMP       = 0;
#endif /* COMP */

class SSC1
{
public:
    static void Handler();
    static volatile unsigned int ticks;
};

void SSC1::Handler()
{
  input_l = (int32_t)(SSC_RHR);

#if defined(LINEARISATION) || defined(OPT_LINEARISATION)
  sample = convert_sample_to_voltage(input_l) + BIAS;
#endif /* LINEARISATION or OPT_LINEARISATION */

#ifdef PASS_THROUGH
  sample = convert_sample_to_voltage(input_l);
#endif /* PASS_THROUGH */
  
#ifdef COMP
  sample = convert_sample_to_voltage(input_l);
#endif /* COMP */

#if defined(LINEARISATION) || defined(OPT_LINEARISATION)
  y_desired = ((sample / 1000) * coeff_g_k) + coeff_g_d;
  x_desired = (y_desired / 1000) * z1_i;
  x_desired = x_desired + z2_i;
  x_desired = (int32_t)sqrt(x_desired);
  x_desired = x_desired + coeff_b;
  x_desired = (((-1000)*x_desired) / z3_i)*1000;
#endif /* LINEARISATION or OPT_LINEARISATION */

#ifdef COMP
  /* RMS Computation Algorithm */
  rms_new = (sample/10000)*(sample/10000);
  
  rms_last = rms_loop[rms_loop_ptr];
  
  rms_tot = ((rms_tot - rms_last) + rms_new);
  rms_res = (int32_t)sqrt(rms_tot/rms_w);
  /* Ergebnis des RMS ist etwa RMS/100 */

  rms_loop[rms_loop_ptr++] = rms_new;
    
  if(rms_loop_ptr == RMS_SAMPLES){ rms_loop_ptr = 0; }
  
  /* Compression */
  if(rms_res < iCompThreshRMS)
  {
    SAM3X8E_DAC.write_dac_voltage(COMP_BIAS);
  }
  else
  {
    u_cv = COMP_BIAS - ((rms_res * 14140) - iCompThreshAMP);
    SAM3X8E_DAC.write_dac_voltage(u_cv);
  }
  
  /* Output */
  sample = sample / 1000;
  sample = sample * 1000;
  sample = convert_voltage_to_sample(sample);
#endif /* COMP */

#if defined(LINEARISATION) || defined(OPT_LINEARISATION)
  sample = convert_voltage_to_sample(x_desired - new_bias);
#endif /* LINEARISATION or OPT_LINEARISATION */
  
#ifdef PASS_THROUGH
  sample = sample / 1000;
  sample = sample * 1000;
  
  if(counter < 100)
  {
    samples[counter] = sample;
    counter++;
  }
  else
  {
    counter = 0;
  }
  
  sample = convert_voltage_to_sample(sample);
#endif /* PASS_THROUGH*/
  
  SSC_THR = sample;
}

int main()
{
    __disable_interrupt();
    
    #ifdef COMP
    int i = 0;
    while(i < RMS_SAMPLES)
    {
      rms_loop[i++] = 0;
    }
    i = 0;
    #endif /* COMP */
    
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
    
#if defined(LINEARISATION) || defined(OPT_LINEARISATION)
    measure_system();
    SAM3X8E_DAC.write_dac_voltage(new_bias);
    __enable_interrupt();
    SAM3X8E_DOUT.set_relay(RELAY_IN_AUDIO);
#endif /* LINEARISATION or OPT_LINEARISATION */
    
#ifdef FULL_SWEEP
    measure_system();
#endif /* FULL_SWEEP */

#ifdef PASS_THROUGH
    SAM3X8E_DAC.write_dac_voltage(BIAS);
    __enable_interrupt();
    SAM3X8E_DOUT.set_relay(RELAY_IN_AUDIO);
#endif /* PASS_THROUGH */
    
#ifdef COMP
    //measure_system();
    fCompThreshRMS = COMP_THRESH_DB;
    fCompThreshRMS = fCompThreshRMS / 20;
    fCompThreshRMS = (pow(10,fCompThreshRMS)*1.5/sqrt(2));
    iCompThreshRMS = (int32_t)(fCompThreshRMS*100);
    fCompThreshAMP = fCompThreshRMS * sqrt(2) * 1000000;
    iCompThreshAMP = (int32_t)fCompThreshAMP;
    SAM3X8E_DAC.write_dac_voltage(COMP_BIAS);
    __enable_interrupt();
    SAM3X8E_DOUT.set_relay(RELAY_IN_AUDIO);
#endif /* COMP */

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

#if defined(LINEARISATION) || defined(OPT_LINEARISATION) || defined(FULL_SWEEP)
void measure_system()
{
    int points = sizeof(dac_volt)/sizeof(int32_t);
    int i = 0;
    #ifndef FULL_SWEEP
    float ua1, ua2, ua3, ug1, ug2, ug3, a1, b1, c1;
    float z1, z2, z3;
    #endif

    SAM3X8E_DOUT.reset_relay(RELAY_ALL);        // All Relays OFF
    SAM3X8E_DOUT.set_relay(RELAY_MEAS_A2);      // Relay Preamp Measurement ON
        
    while(i < points)
    {
      SAM3X8E_DOUT.reset_relay(RELAY_ALL);
      SAM3X8E_DOUT.set_relay(RELAY_MEAS_A2);
      SAM3X8E_DAC.write_dac_voltage(dac_volt[i]);              // Set U_cv
      adc_volt_anode[i] = SAM3X8E_ADC.measure_preamp_anode();  // Read U_a
      i++;
    }

    #ifndef FULL_SWEEP
    #ifdef LINEARISATION
    ua1 = ((float)adc_volt_anode[0])/1000000;
    ua2 = ((float)adc_volt_anode[1])/1000000;
    ua3 = ((float)adc_volt_anode[2])/1000000;
    ug1 = (((float)dac_volt[0])/1000000);
    ug2 = (((float)dac_volt[1])/1000000);
    ug3 = (((float)dac_volt[2])/1000000);
    #endif /* LINEARISATION */
    #ifdef OPT_LINEARISATION
    ua1 = ((float)adc_volt_anode[1])/1000000;
    ua2 = ((float)adc_volt_anode[2])/1000000;
    ua3 = ((float)adc_volt_anode[3])/1000000;
    ug1 = (((float)dac_volt[1])/1000000);
    ug2 = (((float)dac_volt[2])/1000000);
    ug3 = (((float)dac_volt[3])/1000000);
    #endif /* OPT_LINEARISATION */
    
    // Koeffizienten für quadratische Funktion
    a1 = (ug1*(ua2-ua3)+ug2*(ua3-ua1)+ug3*(ua1-ua2))/
         ((ug1-ug2)*(ug1-ug3)*(ug3-ug2));
    b1 = ((ug1*ug1)*(ua2-ua3)+(ug2*ug2)*(ua3-ua1)+(ug3*ug3)*(ua1-ua2))/
         ((ug1-ug2)*(ug1-ug3)*(ug2-ug3));
    c1 = ((ug1*ug1)*(ug2*ua3-ug3*ua2)+ug1*((ug3*ug3)*ua2-(ug2*ug2)*ua3)+
         ug2*ug3*ua1*(ug2-ug3))/((ug1-ug2)*(ug1-ug3)*(ug2-ug3));
    
    // Skalieren der Koeffizienten
    /* coeff_a = (int32_t)(a1 * 1000); legacy... */
    coeff_b = (int32_t)(b1 * 1000);
    /* coeff_c = (int32_t)(c1 * 1000); legacy... */
    
    // Koeffizienten für lineaere Funktion
    #ifdef OPT_LINEARISATION
    ua1 = ((float)adc_volt_anode[0])/1000000;
    ug1 = (((float)dac_volt[0])/1000000);
    #endif /* OPT_LINEARISATION */
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
    y_desired = ((BIAS / 1000) * coeff_g_k) + coeff_g_d;
    x_desired = (y_desired / 1000) * z1_i;
    x_desired = x_desired + z2_i;
    x_desired = (int32_t)sqrt(x_desired);
    x_desired = x_desired + coeff_b;
    x_desired = (((-1000)*x_desired) / z3_i)*1000;
    
    new_bias = x_desired;                       // Neuer Arbeitspunkt
    #endif
    
    SAM3X8E_DOUT.reset_relay(RELAY_ALL);        // All Relays OFF
}
#endif /* LINEARISATION or OPT_LINEARISATION or FULL_SWEEP */

int32_t convert_sample_to_voltage(int32_t sample)
{
  int max_out = 3300000; // Eingangsspannungsbereich
  
  if(sample >= 32767) // (2^16)/2
  {
    sample = sample - 65535;
    sample = ((max_out/2)/32767) * sample;
  }
  else
  {
    sample = ((max_out/2)/32767) * sample;
  }
  return sample;
}

int32_t convert_voltage_to_sample(int32_t sample)
{
  /* Maximaler Ausgangsspannungsbereich ist 1V(RMS), daher 2.82Vpp */
  int quant = 43700; // 2.82V / (2^16) = 43158;
  
  if(sample >= 0)
  {
    sample = (sample * 1000);
    sample = sample / quant;
    sample = (sample & 0x0000FFFFU);
  }
  else
  {
    sample = (sample * 1000);
    sample = sample / quant;
    sample = (sample & 0x0000FFFFU);
    sample = (sample | 0x8000U);
  }

  return sample;
}
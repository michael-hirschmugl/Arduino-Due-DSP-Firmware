/*
  wm8731_setup_definitions.h
*/

#ifndef WM8731_SETUP_DEFINITIONS_H
#define WM8731_SETUP_DEFINITIONS_H

// LEFT LINE IN
#define LRINBOTH                (1U)    // L register controls L/R
#define LINMUTE                 (0U)    // Mute OFF
//#define LINVOL                  (0x17U) // 0dB input
#define LINVOL                  (0x1DU) // +12dB input: 1F, +6dB: 1B, 0dB: 17

// RIGHT LINE IN
#define RLINBOTH                (1U)
#define RINMUTE                 (0U)
//#define RINVOL                  (0x17U)
#define RINVOL                  (0x1DU)

// LEFT HEADPHONE OUT
#define LRHPBOTH                (1U)    // L register controls L/R
#define LZCEN                   (1U)    // Zero crossing detection ON
#define LHPVOL                  (0xf3U) // 0dB output

// RIGHT HEADPHONE OUT
#define RLHPBOTH                (0U)
#define RZCEN                   (1U)
#define RHPVOL                  (0xf3U)

// ANALOG AUDIO PATH CONTROL
#define SIDEATT                 (0x3U)  // -15dB
#define SIDETONE                (0U)    // Disable Side Tone
#define DACSEL                  (1U)    // DAC selected
#define BYPASS                  (0U)    // Bypass OFF
//#define BYPASS                  (1U)    // Bypass ON
#define INSEL                   (0U)    // Line In to ADC
#define MUTEMIC                 (1U)    // Mic Mute ON
#define MICBOOST                (0U)    // Mic Boost OFF

// DIGITAL AUDIO PATH CONTROL
#define HPOR                    (0U)    // Do not store DC offset
#define DACMU                   (0U)    // Soft Mute OFF
#define DEEMPH                  (0x00U) //OFF
//#define DEEMPH                  0x02U //44.1kHz
//#define DEEMPH                  0x03U //48kHz
#define ADCHPD                  (0U)    // HP input filter ON

//POWER DOWN CONTROL
#define PWROFF                  (0U)    // Power ON
#define CLKOUTPUT               (1U)
#define OSCPD                   (1U)
#define OUTPD                   (0U)
#define DACPD                   (0U)
#define ADCPD                   (0U)
#define MICPD                   (1U)
#define LINEINPD                (0U)

// DIGITAL AUDIO INTERFACE FORMAT
#define BCLKINV                 (0U)    // Bit Clock Inverter OFF
#define MS                      (1U)    // Master Mode
#define LRSWAP                  (0U)    // L/R Swap OFF
#define LRP                     (0U)    // Right Channel DAC data when
                                        // DACLRC low
//#define IWL                     (0x3U)  // 32 bit data
#define IWL                     (0x2U)  // 24 bit data
//#define IWL                     0x00U  // 16 bit input
#define FORMAT                  (0x2U)  // I2S

// SAMPLING CONTROL
#define CLKODIV2                (0U)
#define CLKIDIV2                (0U)
/*
    44.1kHz Sample Rate in USB mode:
*/
#define SR                      (0x8U)
#define BOSR                    (0x1U)
/*
    48kHz Sample Rate in USB mode:
*/
//#define SR                      (0x0U)
//#define BOSR                    (0x0U)
#define USB                     (0x1U)

// ACTIVE CONTROL
#define ACTIVE                  (0x1U)  // ON

#endif
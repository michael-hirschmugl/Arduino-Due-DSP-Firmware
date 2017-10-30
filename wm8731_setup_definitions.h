/*
  wm8731_setup_definitions.h
*/

#ifndef WM8731_SETUP_DEFINITIONS_H
#define WM8731_SETUP_DEFINITIONS_H

// LEFT LINE IN
#define LRINBOTH                0
#define LINMUTE                 0
#define LINVOL                  23

// RIGHT LINE IN
#define RLINBOTH                0
#define RINMUTE                 0
#define RINVOL                  23

// LEFT HEADPHONE OUT
#define LRHPBOTH                0
#define LZCEN                   0
#define LHPVOL                  127

// RIGHT HEADPHONE OUT
#define RLHPBOTH                0
#define RZCEN                   0
#define RHPVOL                  127

// ANALOG AUDIO PATH CONTROL
#define SIDEATT                 0
#define SIDETONE                0
#define DACSEL                  1
#define BYPASS                  0
#define INSEL                   0
#define MUTEMIC                 1
#define MICBOOST                0

// DIGITAL AUDIO PATH CONTROL
#define HPOR                    0
#define DACMU                   0
//#define DEEMPH                  0x00U //OFF
//#define DEEMPH                  0x02U //44.1kHz
#define DEEMPH                  0x03U //48kHz
#define ADCHPD                  0U

//POWER DOWN CONTROL
#define PWROFF                  0
#define CLKOUTPUT               1
#define OSCPD                   1
#define OUTPD                   0
#define DACPD                   0
#define ADCPD                   0
#define MICPD                   1
#define LINEINPD                0

// DIGITAL AUDIO INTERFACE FORMAT
#define BCLKINV                 0
#define MS                      0x1U  // Master Mode
#define LRSWAP                  0
#define LRP                     0
#define IWL                     0x2U  // 24 bit input
//#define IWL                     0x00U  // 16 bit input
#define FORMAT                  0x2U  // I2S

// SAMPLING CONTROL
#define CLKODIV2                0
#define CLKIDIV2                0
/*
    44.1kHz Sample Rate in USB mode:
*/
//#define SR                      0x8U 
//#define BOSR                    0x1U
/*
    48kHz Sample Rate in USB mode:
*/
#define SR                      0x0U 
#define BOSR                    0x0U
#define USB                     0x1U

// ACTIVE CONTROL
#define ACTIVE                  1

#endif
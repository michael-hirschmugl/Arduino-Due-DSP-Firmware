# Arduino-Due-DSP
The SAM3X8E on the Arduino Due board used as digital signal processor with help from a WM8731 audio codec chip.

## What I'm trying to accomplish
One stereo input signal filtered with a low-pass, band-pass and high-pass filter.
Adjustable gain on every filter.
Potentiometers to control gain.
A mute button.

## What I have accomplished
- Physical connection between Arduino Due board and the Wolfson WM8731 audio codec chip.
- Initital setup of the SAM3X8E processor.
- Provide a clock signal for the audio codec (from SAM3X8E).
- Configure the two wire interface (TWI) on the SAM3X8E to control the audio codec.
- Initialize the WM8731 audio codec.
- Configure the synchronous serial controller (SSC) on the SAM3X8E to send and receive audio from the audio codec as an I2S stream.
- Configure a digital input on the SAM3X8E to use a physical button as a mute button.
- Configure an analog input on the SAM3X8E to use a potentiometer to control filter gain.
- Four different infinite inpulse response (IIR) filters on each channel (LP, BP, HP and another LP on the mixed signal for noise reduction).
- This document.

## What I still need to accomplish
- Find and define what I still need to accomplish.

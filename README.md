# Kinetis-Snippets

Different baremetal codes getting started with Kinetis FRDM Board K22 using KInetis Design Studio IDE.

1) Project 1 :
ADC_EPWM_VREF : using an ADC channel (SE8) PORTB0 to control the PWM duty cycle.
EPWM works in complementary mode with a frequency of 350 Khz with a deadtime of 200ns 
(see the file EPWM.c and read the comments to adjust the Frequency and Deadtime if necessary).
Channel 0 and channel 1 (on PORT C) of the Flextimer FTM0 are used for the PWM signals.
The ADC reference voltage is the 1.2 internal generated VREF  (VREF_OUT pin) 
!!!!!!!!! Please notice that the line number 173 ( "#define CLOCK_SETUP 1" ) was added to ADC_EPWM_VREF/Includes/system_MK22F51212.h 
for the maximum achievable clock frequency configuration !!!!!!!!!
==> maximum bus clock is then the 60 Mhz used in the configuration of the PWM frequency and deadtime


2) Project 2 :
Using DMA to Emulate ADC Flexible Scan Mode on Kinetis K22.
Project will be uploaded soon

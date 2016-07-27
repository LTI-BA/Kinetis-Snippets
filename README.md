# Kinetis-Snippets

Different baremetal codes getting started with Kinetis FRDM Board K22 using KInetis Design Studio IDE.

1) Project 1 :
ADC_EPWM_VREF : using an ADC channel (SE8) PORTB0 to control the PWM duty cycle.
EPWM works in complementary mode with a frequency of 350 Khz with a deadtime of 200ns 
(see the file EPWM.c and read the comments to adjust the Frequency and Deadtime if necessary).
Channel 0 and channel 1 (on PORT C) of the Flextimer FTM0 are used for the PWM signals.
The ADC reference voltage is the 1.2V internal generated VREF   
!!!!!!!!! Please notice that the line number 173 ( "#define CLOCK_SETUP 1" ) was added to ADC_EPWM_VREF/Includes/system_MK22F51212.h 
for the maximum achievable clock frequency configuration !!!!!!!!!
==> maximum bus clock is then the 60 Mhz used in the configuration of the PWM frequency and deadtime


2) Project 2 :
ADC_DMA_VREF : Using DMA to Emulate ADC Flexible Scan Mode on Kinetis K22.
Some Details :
I am using SW to trigger THE FIRST ADC conversion (just the first one), then the ADC will be triggered from the DMA channel 0,
which transfers the next ADC0 input setting from constant buffer adc_mux to ADC0_SC1A register. 
(writing to the SC1A register initiates the Conversion on the selected channel) 
The Code allows me to read from channel8, then , 9, then 15 and then start all over again from 8 in a circular mode four times.
I calibrated the ADC0 and configured it to the 16-bit mode and activated the necessary clock for it
Then I wrote to SC1A_ADCH(8) to start the conversion of the channel. The COCO Flag should then be the trigger to DMA Channel 1, initiating the transfer from ADC0_RA to adc_result buffer in the SRAM.
Then I linked the channel 1 to the channel 0  ==> Link of DMAChannel 1 is the trigger to DMAchannel 0. So when the transfert of Data of Channel 1 is over, the Channel 0 is initiated. It moves the mux Data (for the ADC) from a saved buffer in RAM (called adc_mux) containing the number 8,9 and 15 to the ADC0_SCA1 register. This Transfer should then start the new conversion and so, the second cycle begins... and so on (never stops).
I am using the internal VREF (VREF_OUT pin) as a reference  the ADC to achieve more stable ADC conversions.
Hardware Average for ADC conversions (32 samples averaged) was also used.


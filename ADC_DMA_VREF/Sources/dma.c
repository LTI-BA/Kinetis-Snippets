/*
 * dma.c
 *
 *  Created on: 23.07.2016
 *      Author: Lanwer
 */


#include "dma.h"


void DMA_init(void) {

   extern uint16_t adc_result[TOTAL_CONVERSIONS_NUMBER];
   extern uint8_t adc_mux[TOTAL_CHANNEL_NUMBER];

   adc_mux[0] = 9;
   adc_mux[1] = 15;
   adc_mux[2] = 8;



   // Enable clock for DMAMUX and DMA
   SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
   SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;


   //Channel 0 transfers next ADC0 input setting from constant buffer to ADC0_SC1A.
   //**** DMA transfer request source – always requestor
   DMAMUX_CHCFG0 = DMAMUX_CHCFG_ENBL_MASK |DMAMUX_CHCFG_SOURCE(63) ;

   //**** Source address, constant buffer in SRAM
   DMA_TCD0_SADDR = (uint32_t)&adc_mux[0];

   //**** Destination address, ADC0 control register
   DMA_TCD0_DADDR = (uint32_t)&ADC0_SC1A;

   //**** Source address increment, data is 8-bit, 1 byte
   DMA_TCD0_SOFF = 0x01;

   //**** Destination address increment in bytes, no increment needed
   DMA_TCD0_DOFF = 0x00;

   //**** Source and destination data width specification, both source and destination are 8-bit
   DMA_TCD0_ATTR = DMA_ATTR_SSIZE(0)| DMA_ATTR_DSIZE(0);

   //**** Number of bytes for minor loop (one data transfer), ADC0 input setting value is
   //**** 8 bits long, so 1-byte transfer
   DMA_TCD0_NBYTES_MLNO = 0x01;

   //**** Channel linking and major loop setting reload value after major loop finish,
   //**** no linking after minor loop, major loop transfers number 0x03
   DMA_TCD0_CITER_ELINKNO = 0x03;

   //**** Channel linking and major loop setting, no linking after minor loop,
   //**** major loop transfers number 0x03
   DMA_TCD0_BITER_ELINKNO = 0x03;

   //**** Source address reload after major loop finish, must be subtracted from last
   //**** pointer value, sampling channel number is 3 each and 1 byte long, 1 × 3 = 3
   //**** and must be subtract -3
   DMA_TCD0_SLAST = -3;

   //**** Destination address reload after major loop finish, no address reload needed
   DMA_TCD0_DLASTSGA = 0x00;

   //**** Common channel setting, no linking after major loop, no IRQ request enable
   DMA_TCD0_CSR = 0x00;


// ******************************************************************************************************************

	//Channel 21 transfers ADC0 result data from ADC0_RA to SRAM buffer.
	// Enable Channel 1 and set ADC0 as DMA request source (source number 40)
	DMAMUX_CHCFG1 = DMAMUX_CHCFG_ENBL_MASK |DMAMUX_CHCFG_SOURCE(40);

	//**** Source address, ADC0_RA
	DMA_TCD1_SADDR = (uint32_t) &ADC0_RA;

	//**** Destination address, SRAM buffer [0]
	DMA_TCD1_DADDR = (uint32_t)&adc_result[0];

	//**** Source address increment; data is still read for the same address, no increment needed
	DMA_TCD1_SOFF = 0x00;

	//**** Destination address increment in bytes, increment for next buffer address
	//**** 16 bit => 2 bytes
	DMA_TCD1_DOFF = 0x02;

	//**** Source and destination data width specification, both source and destination is 16-bit
	DMA_TCD1_ATTR = DMA_ATTR_SSIZE(1)| DMA_ATTR_DSIZE(1);

	//**** Number of bytes for minor loop (one data transfer), ADC0 result is 16 bits long, so
	//**** 2-byte transfer
	DMA_TCD1_NBYTES_MLNO = 0x02;

	//**** Channel linking and major loop setting reload value after major loop finishes,
	//**** linking after minor loop is enabled, major loop transfers number 12 (0x0C).
	//DMA_TCD1_CITER_ELINKNO = (DMA_CITER_ELINKNO_ELINK_MASK|0x0C);
	DMA_TCD1_CITER_ELINKNO = (DMA_CITER_ELINKNO_ELINK_MASK | 0x0C);

	//**** Channel linking and major loop setting, linking after minor loop is enabled to
	//**** channel 0 (0x0000), major loop transfers number 12 (0x0C)
	//DMA_TCD1_BITER_ELINKNO = (DMA_BITER_ELINKNO_ELINK_MASK|0x0C);
	DMA_TCD1_BITER_ELINKNO  =(DMA_BITER_ELINKNO_ELINK_MASK|0x0000|0x0C);
	//**** Source address reload after major loop finishes, no reload needed

	DMA_TCD1_SLAST = 0x00;

	//**** Destination address reload after major loop finishes,
	//**** must be subtracted from last pointer value, sample number is 12 each and 2 bytes long,
	//**** 2 × 12 = 24 and must be subtract -24
	DMA_TCD1_DLASTSGA = -24;

	//**** Common channel setting, linking after major loop enable to channel 0,
	//**** IRQ request is generated after major loop complete
	DMA_TCD1_CSR = DMA_CSR_INTMAJOR_MASK |DMA_CSR_MAJORELINK_MASK | DMA_CSR_MAJORLINKCH(0);

	// Enable request signal for channel
	DMA_ERQ = DMA_ERQ_ERQ1_MASK;



}

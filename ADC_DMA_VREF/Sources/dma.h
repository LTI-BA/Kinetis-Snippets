/*
 * dma.h
 *
 *  Created on: 23.07.2016
 *      Author: Lanwer
 */

#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_


#include "MK22F51212.h"

#define TOTAL_CONVERSIONS_NUMBER 16
#define TOTAL_CHANNEL_NUMBER 3

uint16_t adc_result[TOTAL_CONVERSIONS_NUMBER];
uint8_t adc_mux[TOTAL_CHANNEL_NUMBER];


void DMA_init(void);

#endif /* SOURCES_DMA_H_ */



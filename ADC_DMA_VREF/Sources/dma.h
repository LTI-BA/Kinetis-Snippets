/*
 * dma.h
 *
 *  Created on: 23.07.2016
 *      Author: Lanwer
 */

#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_


#include "MK22F51212.h"

#define total_conversions_number 16
uint16_t adc_result[total_conversions_number];
#define total_channel_number 3
uint8_t adc_mux[total_channel_number];


void DMA_init(void);

#endif /* SOURCES_DMA_H_ */



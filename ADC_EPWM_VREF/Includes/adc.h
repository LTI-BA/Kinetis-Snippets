/*
 * adc.h
 *
 *  Created on: 10.07.2016
 *      Author: Lanwer
 */

#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_

void ADC_init(void) ;
unsigned short ADC_read(unsigned char ch) ;
int ADC_calibrate(void) ;



#endif /* INCLUDES_ADC_H_ */

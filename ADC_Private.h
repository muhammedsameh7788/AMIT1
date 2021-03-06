/*
 * ADC_Private.h
 *
 *  Created on: Sep 19, 2021
 *      Author: gerges
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX    *((volatile u8*)0x27)
#define ADCSRA   *((volatile u8*)0x26)
#define ADC      *((volatile u16*)0x24)
#define SFIOR    *((volatile u8*)0x50)

#endif /* ADC_PRIVATE_H_ */

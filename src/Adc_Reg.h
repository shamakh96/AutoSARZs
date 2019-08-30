/*
 * Adc_MemMap.h
 *
 *  Created on: Aug 28, 2019
 *      Author: r
 */

#ifndef ADC_REG_H_
#define ADC_REG_H_

/*
 * ADC Registers
 */

#define ACSR			(*(volatile unsigned char*)( 0x08 ))
#define ADMUX			(*(volatile unsigned char*)( 0x07 ))
#define ADCSRA			(*(volatile unsigned char*)( 0x06 ))
#define ADCH			(*(volatile unsigned char*)( 0x05 ))
#define ADCL			(*(volatile unsigned char*)( 0x04 ))
#define SFIOR			(*(volatile unsigned char*)( 0x30 ))


/*
 * ACSR Pins
 */

#define ACIS0						0
#define ACIS1						1
#define ACIC						2
#define ACIE						3
#define ACI							4
#define ACO							5
#define ACBG						6
#define ACD							7
/*
 * ADMUX Pins
 */

#define MUX0						0
#define MUX1						1
#define MUX2						2
#define MUX3						3
#define MUX4						4
#define ADLAR						5
#define REFS0						6
#define REFS1						7
/*
 * ADCSRA Pins
 */
#define ADPS0						0
#define ADPS1						1
#define ADPS2						2
#define ADIE						3
#define ADIF						4
#define ADATE						5
#define ADSC						6
#define ADEN						7

/*
 * SFIOR Pins
 */
#define ADTS0						5
#define ADTS1						6
#define ADTS2						7



#define ADCSRA_Prescaller_Mask 		0x07


#endif /* ADC_REG_H_ */

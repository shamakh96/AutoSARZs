/*
 * Adc_Cfg.h
 *
 *  Created on: Aug 28, 2019
 *      Author: r
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

#define TRUE						(1u)
#define FALSE						(0u)

#define AdcDeInitApi				TRUE
#define AdcDevErrorDetect			TRUE
#define AdcEnableStartStopGroupApi	TRUE
#define AdcGrpNotifCapability		FALSE
#define AdcHwTriggerApi				TRUE
#define AdcReadGroupApi				TRUE


#define NO_CONFIGURED_GROUPS 		(8u)
#define NO_CONFIGURED_CHANNELS 		(8u)
#define MAX_CHANNELS_IN_GROUP		(1u)

#define NO_SAMPLES					(10u)			/// whatsoever
#define DEFAULT_SINGLE_ACCESS		(1u)			/// single access mode

#define ADC_HWUNIT_0				(0u)

#define ADC_GROUP_0					(0u)
#define ADC_GROUP_1					(1u)
#define ADC_GROUP_2					(2u)
#define ADC_GROUP_3					(3u)
#define ADC_GROUP_4					(4u)
#define ADC_GROUP_5					(5u)
#define ADC_GROUP_6					(6u)
#define ADC_GROUP_7					(7u)

#define ADC_CHANNEL_0				(0u)
#define ADC_CHANNEL_1				(1u)
#define ADC_CHANNEL_2				(2u)
#define ADC_CHANNEL_3				(3u)
#define ADC_CHANNEL_4				(4u)
#define ADC_CHANNEL_5				(5u)
#define ADC_CHANNEL_6				(6u)
#define ADC_CHANNEL_7				(7u)



#endif /* ADC_CFG_H_ */

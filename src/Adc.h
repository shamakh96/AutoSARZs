/*
 * Adc.h
 *
 *  Created on: Aug 28, 2019
 *      Author: r
 */

#ifndef ADC_H_
#define ADC_H_


#include "Std_Types.h"
#include "Adc_Cfg.h"

#define ADC_NOT_INITIALIZED					(0u)
#define ADC_INITIALIZED						(1u)

#define PS_FCPU_2							(1u)
#define PS_FCPU_4							(2u)
#define PS_FCPU_8							(3u)
#define PS_FCPU_16							(4u)
#define PS_FCPU_32							(5u)
#define PS_FCPU_64							(6u)
#define PS_FCPU_128							(7u)

#define ADCSRA_Prescaller_Mask 0x07
#define ADMUX_Channel_Mask 0x07

#define CONVERSION_TIME						(25u)				///whatsoever
#define SAMPLING_TIME						(25u)

#define ADC_RESOLUTION						(10u)

#define ADC_SW_TRIGGER_FREERUN				(0u)
#define	ADC_HW_TRIGGER_EXTERNAL_0			(2u)
#define	ADC_HW_TRIGGER_TIMER0_COM			(3u)
#define	ADC_HW_TRIGGER_TIMER0_OVF			(4u)
#define	ADC_HW_TRIGGER_TIMER1_COMB			(5u)
#define	ADC_HW_TRIGGER_TIMER1_OVF			(6u)
#define	ADC_HW_TRIGGER_TIMER1_CAPEVENT		(7u)


typedef uint8	 	Adc_ChannelType ;
typedef uint8 	 	Adc_GroupType ;
typedef uint8 		Adc_Hw_UnitId ;
typedef int16		Adc_ValueGroupType;
typedef	uint8		Adc_PrescaleType;
typedef uint8 		Adc_ConversionTimeType;
typedef uint8 		Adc_SamplingTimeType;
typedef uint8 		Adc_ResolutionType;
typedef uint8		Adc_StreamNumSampleType; //// how many samples
typedef uint8 		Adc_GroupDefType ;
typedef uint8		Adc_GroupPriorityType ;
typedef uint8		Adc_HwTriggerTimerType;


typedef void(*AdcNotification)(void) ;

typedef enum {
	ADC_IDLE,
	ADC_BUSY,
	ADC_COMPLETED,
	ADC_STREAM_COMPLETED

}Adc_StatusType;

typedef enum {

	ADC_TRIGG_SRC_SW,
	ADC_TRIGG_SRC_HW

}Adc_TriggerSourceType;

typedef enum {

	ADC_CONV_MODE_ONESHOT,
	ADC_CONV_MODE_CONTINUOUS

}Adc_GroupConvModeType;

typedef enum
{
	ADC_STREAM_BUFFER_LINEAR,
	ADC_STREAM_BUFFER_CIRCULAR

}Adc_StreamBufferModeType;

typedef enum
{
	ADC_ACCESS_MODE_SINGLE,
	ADC_ACCESS_MODE_STREAMING

}Adc_GroupAccessModeType;

typedef enum
{
	ADC_ALIGN_LEFT,
	ADC_ALIGN_RIGHT

}Adc_ResultAlignmentType;


typedef enum
{
	AREF,				 // 5 v
	AVCC,
	GND,
	INTERNAL_256		/// 2.56 v  internal

}Adc_RefVoltType ;

typedef enum
{
	Mega_1,
	Mega_2,
	Mega_4,
	Mega_8

}Adc_ClockSourceType ;

typedef enum {

	NO_EDGE,
	ADC_HW_TRIG_BOTH_EDGES,
	ADC_HW_TRIG_FALLING_EDGE,
	ADC_HW_TRIG_RISING_EDGE

}Adc_HwTriggerSignalType;



typedef struct{


	Adc_GroupType 				AdcGroupId ;

	Adc_StatusType 				status ;
	Adc_ValueGroupType* 		AdcGroupBufferPtr ;

	Adc_GroupAccessModeType  	AdcGroupAccessMode ;
	Adc_GroupConvModeType  		AdcGroupConversionMode ;
	Adc_GroupPriorityType		AdcGroupPriority;
	Adc_TriggerSourceType 		AdcGroupTriggSrc ;
	Adc_HwTriggerSignalType		AdcHwTrigSignal	;
	Adc_HwTriggerTimerType		AdcHwTrigTimer  ;
	AdcNotification				AdcNotification ;
	Adc_StreamBufferModeType  	AdcStreamingBufferMode;
	Adc_StreamNumSampleType		AdcStreamingNumSamples ;

	Adc_GroupDefType			AdcGroupDefinition[MAX_CHANNELS_IN_GROUP] ;

} Adc_Group_ConfigType ;


typedef struct {

	Adc_ChannelType				AdcChannelId ;

	Adc_ConversionTimeType 		AdcChannelConvTime ;
	Adc_RefVoltType				AdcChannelRefVoltsrcHigh ;
	Adc_RefVoltType				AdcChannelRefVoltsrcLow ;
	Adc_ResolutionType			AdcChannelResolution ;
	Adc_SamplingTimeType		AdcChannelSampTime ;

}Adc_Channel_ConfigType;

typedef struct {

	Adc_Hw_UnitId 			AdcHwUnitId ;

	Adc_ClockSourceType 	AdcClockSource ;
	Adc_PrescaleType 		AdcPrescale ;

	Adc_Group_ConfigType 	Group [NO_CONFIGURED_GROUPS] ;
	Adc_Channel_ConfigType 	Channel [NO_CONFIGURED_CHANNELS] ;


}Adc_HwUnitType;

typedef struct {

	Adc_ResultAlignmentType 	AdcResultAlignment ;

	Adc_HwUnitType 				HwUnit ;

}Adc_ConfigType ;

/*
 * *********************************************************
 * Function Prototypes
 * *********************************************************
 */

void Adc_Init (const Adc_ConfigType* ConfigPtr);

Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, const Adc_ValueGroupType * DataBufferPtr );

#if (AdcGrpNotifCapability == TRUE)

void Adc_EnableGroupNotification (Adc_GroupType Group);
void Adc_DisableGroupNotification (Adc_GroupType Group);

#endif

#if (AdcHwTriggerApi == TRUE)
void Adc_EnableHardwareTrigger (Adc_GroupType Group );
void Adc_DisableHardwareTrigger(Adc_GroupType Group );
#endif



#if (AdcEnableStartStopGroupApi == TRUE)
void Adc_StartGroupConversion (Adc_GroupType Group);
void Adc_StopGroupConversion (Adc_GroupType Group);
#endif

Adc_StatusType Adc_GetGroupStatus(  Adc_GroupType Group );



#endif /* ADC_H_ */

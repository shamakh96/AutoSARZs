/*
 * adc.c
 *
 *  Created on: Aug 28, 2019
 *      Author: r
 */


#include "Adc.h"

#include "Adc_Reg.h"
#include "Det.h"
#include "avr/interrupt.h"


/*
 * global pointer to the configuration .. set by the Adc_init function
 * to be used by all other services
 */
STATIC Adc_ConfigType*  g_Adc_Configuration_Ptr = NULL_PTR ;
STATIC uint8 Adc_Status = ADC_NOT_INITIALIZED ;
STATIC Boolean newDataFlag = False ;
STATIC uint8 validData[NO_CONFIGURED_GROUPS] = {0} ;



/************************************************************************************
* Service Name: Adc_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the hardware units and driver.
************************************************************************************/
void Adc_Init (const Adc_ConfigType* ConfigPtr)
{

	Adc_Status = ADC_INITIALIZED ;
	g_Adc_Configuration_Ptr = ConfigPtr;


	/***
	 * configure the reference voltage for every channel .. if HW applicable
	 */


	ADMUX = ( ( g_Adc_Configuration_Ptr->HwUnit.Channel[0].AdcChannelRefVoltsrcHigh )  << REFS0 ) ;

	ADCSRA = (STD_ON << ADEN);

	/*
	 * configure the prescaler for every hardware unit
	 */

	ADCSRA = (ADCSRA & 0xF8)  |   (  (g_Adc_Configuration_Ptr->HwUnit.AdcPrescale) &  ADCSRA_Prescaller_Mask );


}

/************************************************************************************
* Service Name: Adc_DeInit
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Returns all ADC HW units to reset state
************************************************************************************/
void Adc_DeInit (void)
{
	uint8 group_index = 0 ;

	Adc_Status = ADC_NOT_INITIALIZED ;

	ADCSRA &= ~(STD_ON << ADEN);

	for (group_index = 0 ; group_index < NO_CONFIGURED_GROUPS ; group_index++)
	{
		g_Adc_Configuration_Ptr->HwUnit.Group[group_index].status = ADC_IDLE ;

	}

	g_Adc_Configuration_Ptr = NULL_PTR ;

}


/************************************************************************************************
* Service Name: Adc_SetupResultBuffer
* Service ID[hex]: 0x0c
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): 	Group 			- Numeric ID of reguested ADC channel group
* 					DataBufferPtr 	- Pointer to result data buffer
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType
* Description:	Initialize ADC Driver with the group specific result buffer start address.
* 				where conversion results will be stored, application has to ensure that
* 				the application buffer can hold all the conversion results of a specific group
*************************************************************************************************/

Std_ReturnType Adc_SetupResultBuffer(
		Adc_GroupType Group,
		const Adc_ValueGroupType * DataBufferPtr
)

{
	Std_ReturnType retValue ;

	if (DataBufferPtr == NULL_PTR)
	{
		retValue = E_NOT_OK ;
	}
	else
	{
		g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupBufferPtr = DataBufferPtr ;
		retValue = E_OK ;

	}


	return retValue ;

}



#if (AdcGrpNotifCapability == TRUE)
/****************************************************************************************
* Service Name: Adc_EnableGroupNotification
* Service ID[hex]: 0x07
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Group	- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enables the Notification mechanism for the requested ADC channel group
***************************************************************************************/


void Adc_EnableGroupNotification (Adc_GroupType Group)
{

	ADCSRA = (ADCSRA & 0xF7)  |  (  1  <<  ADIE  );


}
/****************************************************************************************
* Service Name: Adc_DisableGroupNotification
* Service ID[hex]: 0x08
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Group	- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disables the Notification mechanism for the requested ADC channel group
***************************************************************************************/


void Adc_DisableGroupNotification (Adc_GroupType Group)
{

	ADCSRA &=  ~(  1  <<  ADIE  );


}



#endif


#if (AdcHwTriggerApi == TRUE)
/************************************************************************************
* Service Name: Adc_EnableHardwareTrigger
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Group	- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enables the hardware trigger for the Group
************************************************************************************/
void Adc_EnableHardwareTrigger( Adc_GroupType Group )
{

	Adc_TriggerSourceType trigger ;
	trigger = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupTriggSrc ;

	if (trigger == ADC_TRIGG_SRC_HW )
	{
		ADMUX |= (ADMUX & ~(ADMUX_Channel_Mask) ) | (Group & ADMUX_Channel_Mask) ;
		ADCSRA |= (STD_ON << ADATE )| (STD_ON << ADIE) ;
		SFIOR = (SFIOR & 0x1F)  |  ( g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcHwTrigTimer  <<  ADTS0) ;
		g_Adc_Configuration_Ptr->HwUnit.Group[Group].status =  ADC_BUSY ;
	}
	else
	{}


}
/************************************************************************************
* Service Name: Adc_DisableHardwareTrigger
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Group	- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disables the hardware trigger for the Group
************************************************************************************/
void Adc_DisableHardwareTrigger( Adc_GroupType Group )
{

	Adc_TriggerSourceType trigger ;
	trigger = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupTriggSrc ;

	if (trigger == ADC_TRIGG_SRC_HW )
	{
		ADCSRA &= ~(STD_ON << ADATE ) & ~(STD_ON << ADIE ) ;
		g_Adc_Configuration_Ptr->HwUnit.Group[Group].status =  ADC_IDLE	 ;
	}
	else
	{}

}
#endif



#if (AdcEnableStartStopGroupApi == TRUE)
/************************************************************************************
* Service Name: Adc_StartGroupConversion
* Service ID[hex]: 0x02
* Sync/Async: Asynchronous
* Reentrancy: Reentrant
* Parameters (in): Group	- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Starts the conversion of all channels f the requested adc channel group
************************************************************************************/
void Adc_StartGroupConversion (Adc_GroupType Group)
{

	Adc_TriggerSourceType trigger ;
	trigger = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupTriggSrc ;

	if (trigger == ADC_TRIGG_SRC_SW )
	{
		ADMUX |= (ADMUX & ~(ADMUX_Channel_Mask) ) | (Group & ADMUX_Channel_Mask) ;
		ADCSRA |= (STD_ON  << ADSC ) | (STD_ON << ADIE );
		g_Adc_Configuration_Ptr->HwUnit.Group[Group].status =  ADC_BUSY ;

	}

	else
	{

	}
}

/************************************************************************************
* Service Name: Adc_StopGroupConversion
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Group	- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stops the conversion of all channels f the requested adc channel group
************************************************************************************/
void Adc_StopGroupConversion (Adc_GroupType Group)
{

	Adc_TriggerSourceType trigger ;
	trigger = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupTriggSrc ;

	if (trigger == ADC_TRIGG_SRC_SW )
	{

		ADCSRA &= ~(STD_ON  << ADSC ) & ~(STD_ON << ADIE) ;
		g_Adc_Configuration_Ptr->HwUnit.Group[Group].status =  ADC_IDLE ;

	}
	else
	{

	}

}

#endif


/************************************************************************************
* Service Name: Adc_GetGroupStatus
* Service ID[hex]: 0x09
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Group		- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): None
* Return value: Adc_StatusType	- Conversion Status for the requested Group
* Description: Stops the conversion of all channels f the requested adc channel group
************************************************************************************/
Adc_StatusType Adc_GetGroupStatus(  Adc_GroupType Group )
{

	Adc_StatusType groupStatus ;

	groupStatus = g_Adc_Configuration_Ptr->HwUnit.Group[Group].status ;

	return groupStatus ;


}

#if (AdcReadGroupApi == TRUE)
/************************************************************************************
* Service Name: Adc_GetGroupStatus
* Service ID[hex]: 0x09
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Group			- Numeric ID of requested ADC channel group
* Parameters (inout): None
* Parameters (out): DataBufferPtr 	- ADC results of all channels of the selected group
* Return value: Adc_StatusType	- Conversion Status for the requested Group
* Description: Reads group conversion results of the last completed conversion of requesed group
************************************************************************************/
Std_ReturnType Adc_ReadGroup (
		Adc_GroupType Group,
		Adc_ValueGroupType* DataBufferPtr
)
{

	Adc_ValueGroupType data;
	Adc_ValueGroupType*  bufferPtr;
	Std_ReturnType 	returnValue  = E_NOT_OK ;

	bufferPtr = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupBufferPtr ;

	if (bufferPtr == NULL_PTR)
	{
		returnValue = E_NOT_OK ;
	}
	else
	{
		data = *g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupBufferPtr ;
		*DataBufferPtr = data ;
		returnValue = E_OK ;

	}

	return returnValue ;

}

#endif


Adc_StreamNumSampleType Adc_GetStreamLastPointer (
		Adc_GroupType Group,
		Adc_ValueGroupType ** PtrToSamplePtr

)
{
	Adc_ValueGroupType *dataPtr ;
	Adc_StreamBufferModeType groupBufferMode = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcStreamingBufferMode ;
	Adc_StatusType groupStatus = g_Adc_Configuration_Ptr->HwUnit.Group[Group].status ;
	Adc_GroupConvModeType groupConvMode = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupConversionMode ;
	Adc_GroupAccessModeType groupAccessMode = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupAccessMode ;
	if (groupConvMode == ADC_CONV_MODE_ONESHOT )
	{
		if (groupAccessMode == ADC_ACCESS_MODE_SINGLE)
		{
			if (groupStatus == ADC_COMPLETED )
			{
				g_Adc_Configuration_Ptr->HwUnit.Group[Group].status = ADC_IDLE ;

			}
			else {}
		}
		else{}
	}
	else {}


	dataPtr = g_Adc_Configuration_Ptr->HwUnit.Group[Group].AdcGroupBufferPtr ;


	*PtrToSamplePtr = dataPtr ;



}

ISR (ADC_Vector)
{

	for (uint8 group_index = 0 ; group_index < NO_CONFIGURED_GROUPS ; group_index++)
	{
		if (  g_Adc_Configuration_Ptr->HwUnit.Group[group_index].status  == ADC_BUSY )
		{

			Adc_StreamNumSampleType No_StreamSamples = g_Adc_Configuration_Ptr->HwUnit.Group[group_index].AdcStreamingNumSamples ;
			Adc_StreamBufferModeType groupBufferMode = g_Adc_Configuration_Ptr->HwUnit.Group[group_index].AdcStreamingBufferMode ;


			validData[group_index]++ ;

			if (validData[group_index] = No_StreamSamples )
			{
				g_Adc_Configuration_Ptr->HwUnit.Group[group_index].status = ADC_STREAM_COMPLETED ;


			}

			else if (validData[group_index] < No_StreamSamples)
			{

				g_Adc_Configuration_Ptr->HwUnit.Group[group_index].status = ADC_COMPLETED ;

			}

			else
			{

				if (groupBufferMode == ADC_STREAM_BUFFER_LINEAR )
				{

				}



			}

			g_Adc_Configuration_Ptr->HwUnit.Group[group_index].AdcGroupBufferPtr[validData[group_index]] = ADC ;



		}

	}



}





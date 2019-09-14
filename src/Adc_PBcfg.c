/*
 * Adc_PBcfg.c
 *
 *  Created on: Aug 28, 2019
 *      Author: r
 */


#include "Adc.h"
#include "Adc_Reg.h"

void highLevelFun (void);

Adc_ConfigType ADC_Configurations = {

		ADC_ALIGN_RIGHT,

		{
				ADC_HWUNIT_0,
				Mega_1,
				PS_FCPU_8,

				//// groups configurations

				{
						{
								ADC_GROUP_0,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_0,

								}

						},
						{
								ADC_GROUP_1,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_1,

								}

						},
						{
								ADC_GROUP_2,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_2,

								}

						},
						{
								ADC_GROUP_3,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_3,

								}

						},
						{
								ADC_GROUP_4,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_4,

								}

						},
						{
								ADC_GROUP_5,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_5,

								}

						},
						{
								ADC_GROUP_6,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_6,

								}

						},
						{
								ADC_GROUP_7,									/// group id

								ADC_IDLE,										/*status of the group*/
								NULL_PTR,										/*group buffer address*/

								ADC_ACCESS_MODE_SINGLE,
								ADC_CONV_MODE_ONESHOT,

								0,												//priority
								ADC_TRIGG_SRC_SW,
								NO_EDGE,
								ADC_SW_TRIGGER_FREERUN,

								highLevelFun,									// address of higher level function
								ADC_STREAM_BUFFER_LINEAR,
								DEFAULT_SINGLE_ACCESS,							//no.samples

								{
										ADC_CHANNEL_7,

								}

						}
				},

				/// channels configuration

				{
						{
								ADC_CHANNEL_0,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						},
						{
								ADC_CHANNEL_1,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						},
						{
								ADC_CHANNEL_2,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						},
						{
								ADC_CHANNEL_3,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						},
						{
								ADC_CHANNEL_4,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						},
						{
								ADC_CHANNEL_5,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						},
						{
								ADC_CHANNEL_6,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						},
						{
								ADC_CHANNEL_7,									// channel id

								CONVERSION_TIME,
								AREF,
								GND,
								ADC_RESOLUTION,
								SAMPLING_TIME
						}

				}



		}





};

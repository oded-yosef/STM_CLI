/*******************************************************************
 * File Name: ADC_Mgr.c
 * Date: 28/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#include "main.h"
#include "cmsis_os.h"
#include "ADC_Mgr.h"

extern ADC_HandleTypeDef hadc1;

#define ADC_MAX_READ_TIMEOUT_IN_MILLISECONDS		10

/*******************************************************************
 * Function Name: ADC_Mgr_Get_Raw_Val
 * Description: returns - 0 OK, 1 FAIL
 *******************************************************************/
int ADC_Mgr_Get_Raw_Val( uint32_t ADC_Channel , uint16_t* Raw_Value )
{
	int 							ret_val;
	ADC_ChannelConfTypeDef 			sConfig = {0};

	//default
	ret_val = 0;

	sConfig.Channel = ADC_Channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
	sConfig.Offset = 0;

	if( HAL_ADC_ConfigChannel( &hadc1 , &sConfig ) != HAL_OK )
	{
		return 1;
	}
	osDelay( 5 );
	if( HAL_ADC_Start( &hadc1 ) == HAL_OK )
	{
		if( HAL_ADC_PollForConversion( &hadc1 , ADC_MAX_READ_TIMEOUT_IN_MILLISECONDS ) == HAL_OK )
		{
			*Raw_Value = ( uint16_t )HAL_ADC_GetValue( &hadc1 );
		}
		else
		{
			ret_val = 1;
		}
	}
	else
	{
		ret_val = 1;
	}
	HAL_ADC_Stop( &hadc1 );

	return ret_val;
}

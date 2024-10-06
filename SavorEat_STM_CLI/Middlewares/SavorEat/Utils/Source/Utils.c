/*******************************************************************
 * File Name: Utils.c
 * Date: 13/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#include "cmsis_os.h"
#include "main.h"
#include "Utils.h"

/*******************************************************************
 * Function Name: Utils_ST_Reset
 * Description:
 *******************************************************************/
void Utils_ST_Reset( void )
{
	osDelay( 2000 );
	__disable_irq();
	HAL_NVIC_SystemReset();
}

/*******************************************************************
 * Function Name: Utils_Check_Time_Diff
 * Description:
 *******************************************************************/
int Utils_Check_Time_Diff( uint32_t Start_Time , uint32_t Diff_Time )
{
	uint32_t  			current_time;
	int 				ret_val;

	ret_val = 0;
	current_time = HAL_GetTick();

	if( current_time >= Start_Time )
	{
		if( ( current_time - Start_Time ) >= Diff_Time )
		{
			ret_val = 1;
		}
	}
	else  //wrap around
	{
		if( ( UINT32_MAX - Start_Time + current_time ) >= Diff_Time )
		{
			ret_val = 1;
		}
	}

	return ret_val;
}



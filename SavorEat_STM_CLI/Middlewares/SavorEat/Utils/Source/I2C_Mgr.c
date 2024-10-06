/*******************************************************************
 * File Name: I2C_Mgr.c
 * Date: 29/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#include "main.h"
#include "cmsis_os.h"
#include "I2C_Mgr.h"

#define I2C_READ_WRITE_TIMEOUT  		50

/* I2C4 */
extern I2C_HandleTypeDef hi2c4;

/*******************************************************************
 * Function Name: I2C_Mgr_Read
 * Description:
 *******************************************************************/
int I2C_Mgr_Read( I2C_Bus_e Bus_Num , uint16_t Device_Addr , uint16_t Reg , uint16_t Reg_Size , uint8_t* Data , uint16_t Data_Size )
{
	int							ret_val;
	I2C_HandleTypeDef*			handle_type;

	switch( Bus_Num )
	{
		case I2C4_BUS:
		default:

			handle_type = &hi2c4;

			break;
	}

	ret_val = HAL_I2C_Mem_Read( handle_type , Device_Addr , Reg , Reg_Size , Data , Data_Size , I2C_READ_WRITE_TIMEOUT );

	return ret_val;
}

/*******************************************************************
 * Function Name: I2C_Mgr_Write
 * Description:
 *******************************************************************/
int I2C_Mgr_Write( I2C_Bus_e Bus_Num , uint16_t Device_Addr , uint16_t Reg , uint16_t Reg_Size , uint8_t* Data , uint16_t Data_Size )
{
	int							ret_val;
	I2C_HandleTypeDef*			handle_type;

	switch( Bus_Num )
	{
		case I2C4_BUS:
		default:

			handle_type = &hi2c4;

			break;
	}

	ret_val = HAL_I2C_Mem_Write( handle_type , Device_Addr , Reg , Reg_Size , Data , Data_Size , I2C_READ_WRITE_TIMEOUT );

	return ret_val;
}



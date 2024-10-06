/*******************************************************************
 * File Name: I2C_Mgr.h
 * Date: 29/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#ifndef __I2C_MGR_HH__
#define __I2C_MGR_HH__

typedef enum
{
	I2C4_BUS			= 0
}
	I2C_Bus_e;

int I2C_Mgr_Read( I2C_Bus_e Bus_Num , uint16_t Device_Addr , uint16_t Reg , uint16_t Reg_Size , uint8_t* Data , uint16_t Data_Size );
int I2C_Mgr_Write( I2C_Bus_e Bus_Num , uint16_t Device_Addr , uint16_t Reg , uint16_t Reg_Size , uint8_t* Data , uint16_t Data_Size );

#endif // __I2C_MGR_HH__

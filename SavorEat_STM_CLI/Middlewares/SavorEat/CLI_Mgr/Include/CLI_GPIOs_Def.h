/*******************************************************************
 * File Name: CLI_GPIOs_Def.h
 * Date: 15/01/2024
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#ifndef __CLI_GPIOS_DEF_HH__
#define __CLI_GPIOS_DEF_HH__

/* defines */
#define CLI_GPIOS_NUM		55

/* enum definition */
typedef enum
{
	GPIO_TYPE_INPUT			= 0,
	GPIO_TYPE_OUTPUT		= 1
}
	CLI_GPIO_Type_e;

typedef enum
{
	GPIO_STATE_RESET		= 0,
	GPIO_STATE_SET			= 1
}
	CLI_GPIO_State_e;

/* struct definition */
typedef struct
{
	uint8_t					Type;
	GPIO_TypeDef*			Port;
	uint16_t				Pin;
	char 					Description[ 31 ];
}
	CLI_GPIO_Entity_s;

/* functions declaration */
void CLI_GPIOs_Get_GPIO_Entity( int GPIO_ID , CLI_GPIO_Entity_s* Entity );
int CLI_GPIOs_Get_Action( int GPIO_ID );
int CLI_GPIOs_Set_Action( int GPIO_ID , int State );

#endif //__CLI_GPIOS_DEF_HH__

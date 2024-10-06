/*******************************************************************
 * File Name: CLI_GPIOs_Def.c
 * Date: 15/01/2024
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#include "main.h"
#include "cmsis_os.h"
#include "Utils.h"
#include "CLI_GPIOs_Def.h"

/* defines */

/* enum definition */

/* struct definition */

/* functions declaration */

/* local variables */
static  CLI_GPIO_Entity_s CLI_GPIOs_Arr[ CLI_GPIOS_NUM ] =
{
	{ GPIO_TYPE_INPUT 	, LTC2984_INT_GPIO_Port 		, LTC2984_INT_Pin 				, "LTC2984_INT - PE3" },
	{ GPIO_TYPE_INPUT 	, RELAY_CONTACT_IND_GPIO_Port	, RELAY_CONTACT_IND_Pin 		, "RELAY_CONTACT_IND - PF2" },
	{ GPIO_TYPE_INPUT 	, BRAKE_IND_GPIO_Port 			, BRAKE_IND_Pin 				, "BRAKE_IND - PE9" },
	{ GPIO_TYPE_INPUT 	, K_POWER_IND_GPIO_Port 		, K_POWER_IND_Pin 				, "K_POWER_IND - PE10" },
	{ GPIO_TYPE_INPUT 	, OVEN_DOOR_CLOSE_IND_GPIO_Port	, OVEN_DOOR_CLOSE_IND_Pin 		, "OVEN_DOOR_CLOSE_IND - PE12" },
	{ GPIO_TYPE_INPUT 	, OVEN_DOOR_OPEN_IND_GPIO_Port	, OVEN_DOOR_OPEN_IND_Pin 		, "OVEN_DOOR_OPEN_IND - PE13" },
	{ GPIO_TYPE_INPUT 	, REF_DOOR_OPEN_IND_GPIO_Port	, REF_DOOR_OPEN_IND_Pin 		, "REF_DOOR_OPEN_IND - PE14" },
	{ GPIO_TYPE_INPUT 	, REF_DOOR_CLOSE_IND_GPIO_Port	, REF_DOOR_CLOSE_IND_Pin 		, "REF_DOOR_CLOSE_IND - PE15" },
	{ GPIO_TYPE_INPUT 	, LM_D1_GPIO_Port				, LM_D1_Pin 					, "LM_D1 - PD0" },
	{ GPIO_TYPE_INPUT 	, LM_D2_GPIO_Port				, LM_D2_Pin 					, "LM_D2 - PD1" },
	{ GPIO_TYPE_INPUT 	, LM_D3_GPIO_Port				, LM_D3_Pin 					, "LM_D3 - PD2" },
	{ GPIO_TYPE_INPUT 	, LM_D4_GPIO_Port				, LM_D4_Pin 					, "LM_D4 - PD3" },
	{ GPIO_TYPE_INPUT 	, LM_OT_GPIO_Port				, LM_OT_Pin 					, "LM_OT - PD4" },
	{ GPIO_TYPE_INPUT 	, RELAY_AVAPOR_IND_GPIO_Port	, RELAY_AVAPOR_IND_Pin 			, "RELAY_AVAPOR_IND - PE0" },
	{ GPIO_TYPE_INPUT 	, LMO1T_GPIO_Port				, LMO1T_Pin 					, "LMO1T - PF15" },
	{ GPIO_TYPE_INPUT 	, LMO2T_GPIO_Port				, LMO2T_Pin 					, "LMO2T - PF11" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER1_B_EN_GPIO_Port		, FEEDER1_B_EN_Pin 				, "FEEDER1_B_EN - PC3" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER1_G_EN_GPIO_Port		, FEEDER1_G_EN_Pin 				, "FEEDER1_G_EN - PC2" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER1_R_EN_GPIO_Port		, FEEDER1_R_EN_Pin 				, "FEEDER1_R_EN - PC0" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER2_B_EN_GPIO_Port		, FEEDER2_B_EN_Pin 				, "FEEDER2_B_EN - PC8" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER2_G_EN_GPIO_Port		, FEEDER2_G_EN_Pin 				, "FEEDER2_G_EN - PC7" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER2_R_EN_GPIO_Port		, FEEDER2_R_EN_Pin 				, "FEEDER2_R_EN - PC6" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER3_B_EN_GPIO_Port		, FEEDER3_B_EN_Pin 				, "FEEDER3_B_EN - PC11" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER3_G_EN_GPIO_Port		, FEEDER3_G_EN_Pin 				, "FEEDER3_G_EN - PC10" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER3_R_EN_GPIO_Port		, FEEDER3_R_EN_Pin 				, "FEEDER3_R_EN - PC9" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER4_B_EN_GPIO_Port		, FEEDER4_B_EN_Pin 				, "FEEDER4_B_EN - PG1" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER4_G_EN_GPIO_Port		, FEEDER4_G_EN_Pin 				, "FEEDER4_G_EN - PG0" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER4_R_EN_GPIO_Port		, FEEDER4_R_EN_Pin 				, "FEEDER4_R_EN - PC12" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER5_B_EN_GPIO_Port		, FEEDER5_B_EN_Pin 				, "FEEDER5_B_EN - PG4" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER5_G_EN_GPIO_Port		, FEEDER5_G_EN_Pin 				, "FEEDER5_G_EN - PG3" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER5_R_EN_GPIO_Port		, FEEDER5_R_EN_Pin 				, "FEEDER5_R_EN - PG2" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER6_B_EN_GPIO_Port		, FEEDER6_B_EN_Pin 				, "FEEDER6_B_EN - PG9" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER6_G_EN_GPIO_Port		, FEEDER6_G_EN_Pin 				, "FEEDER6_G_EN - PG8" },
	{ GPIO_TYPE_OUTPUT 	, FEEDER6_R_EN_GPIO_Port		, FEEDER6_R_EN_Pin 				, "FEEDER6_R_EN - PG5" },
	{ GPIO_TYPE_OUTPUT 	, GANTRY_LED_B_EN_GPIO_Port		, GANTRY_LED_B_EN_Pin 			, "GANTRY_LED_B_EN - PF5" },
	{ GPIO_TYPE_OUTPUT 	, GANTRY_LED_G_EN_GPIO_Port		, GANTRY_LED_G_EN_Pin 			, "GANTRY_LED_G_EN - PF4" },
	{ GPIO_TYPE_OUTPUT 	, GANTRY_LED_R_EN_GPIO_Port		, GANTRY_LED_R_EN_Pin 			, "GANTRY_LED_R_EN - PF3" },
	{ GPIO_TYPE_OUTPUT 	, K_POWER_EN_GPIO_Port			, K_POWER_EN_Pin 				, "K_POWER_EN - PE11" },
	{ GPIO_TYPE_OUTPUT 	, LED_B1_EN_GPIO_Port			, LED_B1_EN_Pin 				, "LED_B1_EN - PB2" },
	{ GPIO_TYPE_OUTPUT 	, LED_B2_EN_GPIO_Port			, LED_B2_EN_Pin 				, "LED_B2_EN - PB6" },
	{ GPIO_TYPE_OUTPUT 	, LED_B3_EN_GPIO_Port			, LED_B3_EN_Pin 				, "LED_B3_EN - PB10" },
	{ GPIO_TYPE_OUTPUT 	, LED_B4_EN_GPIO_Port			, LED_B4_EN_Pin 				, "LED_B4_EN - PB12" },
	{ GPIO_TYPE_OUTPUT 	, LED_G1_EN_GPIO_Port			, LED_G1_EN_Pin 				, "LED_G1_EN - PB1" },
	{ GPIO_TYPE_OUTPUT 	, LED_G2_EN_GPIO_Port			, LED_G2_EN_Pin 				, "LED_G2_EN - PB5" },
	{ GPIO_TYPE_OUTPUT 	, LED_G3_EN_GPIO_Port			, LED_G3_EN_Pin 				, "LED_G3_EN - PB9" },
	{ GPIO_TYPE_OUTPUT 	, LED_G4_EN_GPIO_Port			, LED_G4_EN_Pin 				, "LED_G4_EN - PB15" },
	{ GPIO_TYPE_OUTPUT 	, LED_R1_EN_GPIO_Port			, LED_R1_EN_Pin 				, "LED_R1_EN - PB0" },
	{ GPIO_TYPE_OUTPUT 	, LED_R2_EN_GPIO_Port			, LED_R2_EN_Pin 				, "LED_R2_EN - PB4" },
	{ GPIO_TYPE_OUTPUT 	, LED_R3_EN_GPIO_Port			, LED_R3_EN_Pin 				, "LED_R3_EN - PB8" },
	{ GPIO_TYPE_OUTPUT 	, LED_R4_EN_GPIO_Port			, LED_R4_EN_Pin 				, "LED_R4_EN - PB11" },
	{ GPIO_TYPE_OUTPUT 	, LTC2984_RST_GPIO_Port			, LTC2984_RST_Pin 				, "LTC2984_RST - PE1" },
	{ GPIO_TYPE_OUTPUT 	, MICRO_CLUTCH_B_EN_GPIO_Port	, MICRO_CLUTCH_B_EN_Pin 		, "MICRO_CLUTCH_B_EN - PF10" },
	{ GPIO_TYPE_OUTPUT 	, MICRO_CLUTCH_G_EN_GPIO_Port	, MICRO_CLUTCH_G_EN_Pin 		, "MICRO_CLUTCH_G_EN - PF9" },
	{ GPIO_TYPE_OUTPUT 	, MICRO_CLUTCH_R_EN_GPIO_Port	, MICRO_CLUTCH_R_EN_Pin 		, "MICRO_CLUTCH_R_EN - PF6" },
	{ GPIO_TYPE_OUTPUT 	, K_HEAT_EN_GPIO_Port			, K_HEAT_EN_Pin 				, "K_HEAT_EN - PF1" }
};

/*******************************************************************
 * Function Name: CLI_GPIOs_Get_GPIO_Entity
 * Description:
 *******************************************************************/
void CLI_GPIOs_Get_GPIO_Entity( int GPIO_ID , CLI_GPIO_Entity_s* Entity )
{
	*Entity = CLI_GPIOs_Arr[ GPIO_ID ];
}

/*******************************************************************
 * Function Name: CLI_GPIOs_Get_Action
 * Description:
 *******************************************************************/
int CLI_GPIOs_Get_Action( int GPIO_ID )
{
	return HAL_GPIO_ReadPin( CLI_GPIOs_Arr[ GPIO_ID ].Port , CLI_GPIOs_Arr[ GPIO_ID ].Pin );
}

/*******************************************************************
 * Function Name: CLI_GPIOs_Set_Action
 * Description:
 *******************************************************************/
int CLI_GPIOs_Set_Action( int GPIO_ID , int State )
{
	if( CLI_GPIOs_Arr[ GPIO_ID ].Type == GPIO_TYPE_OUTPUT )
	{
		HAL_GPIO_WritePin( CLI_GPIOs_Arr[ GPIO_ID ].Port , CLI_GPIOs_Arr[ GPIO_ID ].Pin , State );
	}
	else
	{
		return -1;
	}

	return 0;
}

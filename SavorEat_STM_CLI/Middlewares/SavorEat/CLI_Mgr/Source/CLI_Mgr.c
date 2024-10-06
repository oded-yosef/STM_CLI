/*******************************************************************
 * File Name: CLI_Mgr.c
 * Date: 15/01/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "Syslog_Mgr.h"
#include "CLI_Mgr.h"
#include "Utils.h"
#include "ADC_Mgr.h"
#include "CLI_GPIOs_Def.h"
#include "I2C_Mgr.h"

extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim13;
extern SPI_HandleTypeDef hspi4;

/* defines */
#define PWM_EXPANDER_I2C_ADDRESS					0x80
#define PCA9685_REGISTER_MODE1  					0x00
#define PCA9685_MODE1_SLEEP_BIT 					4

#define SPI_COMMAND_TIMEOUT							50 //in milliseconds
#define READ_FROM_RAM           					(uint8_t) 0x03
#define COMMAND_STATUS_REGISTER          			(uint16_t) 0x0000

/* enums */
typedef enum
{
	CLI_MGR_STATE_NOT_INITIALIZED					= 0,
	CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT			= 1,
	CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT			= 2,
	CLI_MGR_STATE_WAIT_FOR_ADC_MENU_INPUT			= 3,
	CLI_MGR_STATE_WAIT_FOR_I2C_MENU_INPUT			= 4,
	CLI_MGR_STATE_WAIT_FOR_SPI_MENU_INPUT			= 5,
	CLI_MGR_STATE_WAIT_FOR_PWM_MENU_INPUT			= 6,

	CLI_MGR_STATE_WAIT_FOR_GPIO_SUB_PHASE_INPUT		= 20,

	CLI_MGR_STATE_ERROR								= 42
}
	CLI_Mgr_State_e;

typedef enum
{
	CLI_MGR_MAIN_MENU								= 0,
	CLI_MGR_GPIO_MENU								= 1,
	CLI_MGR_ADC_MENU								= 2,
	CLI_MGR_I2C_MENU								= 3,
	CLI_MGR_SPI_MENU								= 4,
	CLI_MGR_PWM_MENU								= 5
}
	CLI_Mgr_Menu_e;

typedef enum
{
	GPIO_SUB_PHASE_STATE_IDLE						= 0,
	GPIO_SUB_PHASE_GET_STATE_ID						= 1,
	GPIO_SUB_PHASE_SET_STATE_ID						= 2,
	GPIO_SUB_PHASE_SET_STATE_VALUE					= 3
}
	CLI_Mgr_GPIO_Sub_Phase_State_e;

/* structs */
typedef struct
{
	uint8_t 						CLI_Mgr_State;
	uint8_t 						CLI_Mgr_Menu;
	uint8_t							CLI_Mgr_Sub_Phase;
}
	CLI_Mgr_Properties_s;

/* local functions */
static void CLI_Mgr_Print_Main_Menu( void );
static void CLI_Mgr_Main_Menu_Selection_Handler( char Val );
static void CLI_Mgr_Print_GPIO_Menu( void );
static void CLI_Mgr_GPIO_Menu_Selection_Handler( char Val );
static void CLI_Mgr_GPIO_Sub_Phase_Handler( char Val );
static void CLI_Mgr_Print_ADC_Menu( void );
static void CLI_Mgr_ADC_Menu_Selection_Handler( char Val );
static void CLI_Mgr_Print_I2C_Menu( void );
static void CLI_Mgr_I2C_Menu_Selection_Handler( char Val );
static void CLI_Mgr_Print_SPI_Menu( void );
static void CLI_Mgr_SPI_Menu_Selection_Handler( char Val );
static void CLI_Mgr_Print_PWM_Menu( void );
static void CLI_Mgr_PWM_Menu_Selection_Handler( char Val );

/* local variables */
static CLI_Mgr_Properties_s CLI_Prop = { CLI_MGR_STATE_NOT_INITIALIZED , CLI_MGR_MAIN_MENU , GPIO_SUB_PHASE_STATE_IDLE };

/*******************************************************************
 * Function Name: CLI_Mgr_Handler
 * Description:
 *******************************************************************/
void CLI_Mgr_Handler( char Value )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	switch( CLI_Prop.CLI_Mgr_State )
	{
		case CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT:

			if( Value != 0 )
			{
				CLI_Mgr_Main_Menu_Selection_Handler( Value );
			}

			break;

		case CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT:

			if( Value != 0 )
			{
				CLI_Mgr_GPIO_Menu_Selection_Handler( Value );
			}

			break;

		case CLI_MGR_STATE_WAIT_FOR_ADC_MENU_INPUT:

			if( Value != 0 )
			{
				CLI_Mgr_ADC_Menu_Selection_Handler( Value );
			}

			break;

		case CLI_MGR_STATE_WAIT_FOR_I2C_MENU_INPUT:

			if( Value != 0 )
			{
				CLI_Mgr_I2C_Menu_Selection_Handler( Value );
			}

			break;

		case CLI_MGR_STATE_WAIT_FOR_SPI_MENU_INPUT:

			if( Value != 0 )
			{
				CLI_Mgr_SPI_Menu_Selection_Handler( Value );
			}

			break;

		case CLI_MGR_STATE_WAIT_FOR_PWM_MENU_INPUT:

			if( Value != 0 )
			{
				CLI_Mgr_PWM_Menu_Selection_Handler( Value );
			}

			break;

		case CLI_MGR_STATE_NOT_INITIALIZED:

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\n\n***********************************" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "* Welcome to SavorEat CLI tool!!! *" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "***********************************" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			CLI_Mgr_Print_Main_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT;

			break;

		case CLI_MGR_STATE_WAIT_FOR_GPIO_SUB_PHASE_INPUT:

			if( Value != 0 )
			{
				CLI_Mgr_GPIO_Sub_Phase_Handler( Value );
			}

			break;

		case CLI_MGR_STATE_ERROR:
		default:

			break;
	}
}

/*******************************************************************
 * Function Name: CLI_Mgr_Print_Main_Menu
 * Description:
 *******************************************************************/
static void CLI_Mgr_Print_Main_Menu( void )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\n\n*** Main menu ***\nselect your option:\n1 - GPIO's\n2 - ADC\n3 - I2C\n4 - SPI\n5 - PWM" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "space - print current menu" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
}

/*******************************************************************
 * Function Name: CLI_Mgr_Main_Menu_Selection_Handler
 * Description:
 *******************************************************************/
static void CLI_Mgr_Main_Menu_Selection_Handler( char Val )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	switch( Val )
	{
		case '1':

			CLI_Mgr_Print_GPIO_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_GPIO_MENU;

			break;

		case '2':

			CLI_Mgr_Print_ADC_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_ADC_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_ADC_MENU;

			break;

		case '3':

			CLI_Mgr_Print_I2C_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_I2C_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_I2C_MENU;

			break;

		case '4':

			CLI_Mgr_Print_SPI_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_SPI_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_SPI_MENU;

			break;

		case '5':

			CLI_Mgr_Print_PWM_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_PWM_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_PWM_MENU;

			break;

		case ' ':

			CLI_Mgr_Print_Main_Menu();

			break;

		default:

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nWrong input please select again" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );

			break;
	}
}

/*******************************************************************
 * Function Name: CLI_Mgr_Print_GPIO_Menu
 * Description:
 *******************************************************************/
static void CLI_Mgr_Print_GPIO_Menu( void )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\n\n*** GPIO's menu ***\nselect your option:" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "1 - print GPIO's list\n2 - GPIO get\n3 - GPIO set" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "m - return to main menu\nspace - print current menu" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
}

/*******************************************************************
 * Function Name: CLI_Mgr_GPIO_Menu_Selection_Handler
 * Description:
 *******************************************************************/
static void CLI_Mgr_GPIO_Menu_Selection_Handler( char Val )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];
	CLI_GPIO_Entity_s		gpio_entity;

	switch( Val )
	{
		case '1':

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nGPIO's list:" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			for( int i = 0 ; i < CLI_GPIOS_NUM ; i++ )
			{
				CLI_GPIOs_Get_GPIO_Entity( i , &gpio_entity );
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "%d - %s - %s" , i + 1 , gpio_entity.Description , gpio_entity.Type ? "Output" : "Input" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
				osDelay( 5 );
			}

			break;

		case '2':

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nPlease enter GPIO ID and press return:" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_SUB_PHASE_INPUT;
			CLI_Prop.CLI_Mgr_Sub_Phase = GPIO_SUB_PHASE_GET_STATE_ID;

			break;

		case '3':

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nPlease enter GPIO ID and press return:" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_SUB_PHASE_INPUT;
			CLI_Prop.CLI_Mgr_Sub_Phase = GPIO_SUB_PHASE_SET_STATE_ID;

			break;

		case ' ':

			CLI_Mgr_Print_GPIO_Menu();

			break;

		case 'm':
		case 'M':

			CLI_Mgr_Print_Main_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_MAIN_MENU;

			break;

		default:

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nWrong input please select again" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );

			break;
	}
}

/*******************************************************************
 * Function Name: CLI_Mgr_Print_ADC_Menu
 * Description:
 *******************************************************************/
static void CLI_Mgr_GPIO_Sub_Phase_Handler( char Val )
{
	static uint8_t			gpio_id = 0;
	static uint8_t			gpio_val = 0;
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	switch( CLI_Prop.CLI_Mgr_Sub_Phase )
	{
		case GPIO_SUB_PHASE_GET_STATE_ID:

			if( Val != 13 )
			{
				gpio_id = gpio_id * 10 + ( Val - '0' );
			}
			else
			{
				if( ( gpio_id > 0 ) && ( gpio_id <= CLI_GPIOS_NUM ) )
				{
					snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "GPIO %d = %d" , gpio_id , CLI_GPIOs_Get_Action( gpio_id - 1 ) );
					Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
				}
				else
				{
					snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Wrong GPIO value!!! - please refer to GPIO's list" );
					Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
					CLI_Mgr_Print_GPIO_Menu();
				}
				gpio_id = 0;
				CLI_Prop.CLI_Mgr_Sub_Phase = GPIO_SUB_PHASE_STATE_IDLE;
				CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT;
			}

			break;

		case GPIO_SUB_PHASE_SET_STATE_ID:

			if( Val != 13 )
			{
				gpio_id = gpio_id * 10 + ( Val - '0' );
			}
			else
			{
				if( ( gpio_id > 0 ) && ( gpio_id <= CLI_GPIOS_NUM ) )
				{
					snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Please enter value and press return:");
					Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
					CLI_Prop.CLI_Mgr_Sub_Phase = GPIO_SUB_PHASE_SET_STATE_VALUE;
				}
				else
				{
					snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Wrong GPIO value!!! - please refer to GPIO's list" );
					Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
					gpio_id = 0;
					CLI_Mgr_Print_GPIO_Menu();
					CLI_Prop.CLI_Mgr_Sub_Phase = GPIO_SUB_PHASE_STATE_IDLE;
					CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT;
				}
			}

			break;

		case GPIO_SUB_PHASE_SET_STATE_VALUE:

			if( Val != 13 )
			{
				gpio_val = gpio_val * 10 + ( Val - '0' );
			}
			else
			{
				if( ( gpio_val == GPIO_STATE_RESET ) || ( gpio_val == GPIO_STATE_SET ) )
				{
					if( !CLI_GPIOs_Set_Action( gpio_id - 1 , gpio_val ) )
					{
						snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Set GPIO %d to %d done." , gpio_id , gpio_val );
						Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
					}
					else
					{
						snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Action failed." );
						Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
					}
					gpio_id = 0;
					gpio_val = 0;
					CLI_Prop.CLI_Mgr_Sub_Phase = GPIO_SUB_PHASE_SET_STATE_VALUE;
					CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT;
				}
				else
				{
					snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Wrong set value!!!" );
					Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
					CLI_Mgr_Print_GPIO_Menu();
					gpio_id = 0;
					gpio_val = 0;
					CLI_Prop.CLI_Mgr_Sub_Phase = GPIO_SUB_PHASE_STATE_IDLE;
					CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT;
				}
			}

			break;

		default:

			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_GPIO_MENU_INPUT;

			break;
	}
}

/*******************************************************************
 * Function Name: CLI_Mgr_Print_ADC_Menu
 * Description:
 *******************************************************************/
static void CLI_Mgr_Print_ADC_Menu( void )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\n\n*** ADC menu ***\nselect your option:\n1 - Get ADC channel 0\n2 - Get ADC channel 3\n3 - Get ADC channel 4" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "4 - Get ADC channel 5\n5 - Get ADC channel 6" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "m - return to main menu\nspace - print current menu" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
}

/*******************************************************************
 * Function Name: CLI_Mgr_ADC_Menu_Selection_Handler
 * Description:
 *******************************************************************/
static void CLI_Mgr_ADC_Menu_Selection_Handler( char Val )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];
	uint16_t				adc_raw_val;

	switch( Val )
	{
		case '1':

			if( !ADC_Mgr_Get_Raw_Val( ADC_CHANNEL_0 , &adc_raw_val ) )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC channel 0 raw value - %d" , adc_raw_val );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}
			else
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC get channel 0 raw value error!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case '2':

			if( !ADC_Mgr_Get_Raw_Val( ADC_CHANNEL_3 , &adc_raw_val ) )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC channel 3 raw value - %d" , adc_raw_val );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}
			else
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC get channel 3 raw value error!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case '3':

			if( !ADC_Mgr_Get_Raw_Val( ADC_CHANNEL_4 , &adc_raw_val ) )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC channel 4 raw value - %d" , adc_raw_val );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}
			else
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC get channel 4 raw value error!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case '4':

			if( !ADC_Mgr_Get_Raw_Val( ADC_CHANNEL_5 , &adc_raw_val ) )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC channel 5 raw value - %d" , adc_raw_val );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}
			else
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC get channel 5 raw value error!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case '5':

			if( !ADC_Mgr_Get_Raw_Val( ADC_CHANNEL_6 , &adc_raw_val ) )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC channel 6 raw value - %d" , adc_raw_val );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}
			else
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nADC get channel 6 raw value error!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case ' ':

			CLI_Mgr_Print_ADC_Menu();

			break;

		case 'm':
		case 'M':

			CLI_Mgr_Print_Main_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_MAIN_MENU;

			break;

		default:

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nWrong input please select again" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );

			break;
	}
}

/*******************************************************************
 * Function Name: CLI_Mgr_Print_I2C_Menu
 * Description:
 *******************************************************************/
static void CLI_Mgr_Print_I2C_Menu( void )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\n\n*** I2C menu ***\nselect your option:" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "1 - Read I2C command\n2 - Write I2C command" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "m - return to main menu\nspace - print current menu" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
}

/*******************************************************************
 * Function Name: CLI_Mgr_I2C_Menu_Selection_Handler
 * Description:
 *******************************************************************/
static void CLI_Mgr_I2C_Menu_Selection_Handler( char Val )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];
	uint8_t					temp;

	switch( Val )
	{
		case '1':

			//put PCA9685 device to sleep
			I2C_Mgr_Read( I2C4_BUS , PWM_EXPANDER_I2C_ADDRESS , PCA9685_REGISTER_MODE1 , 1 , &temp , 1 );

			break;

		case '2':

			temp = ( 1 << PCA9685_MODE1_SLEEP_BIT );
			I2C_Mgr_Write( I2C4_BUS , PWM_EXPANDER_I2C_ADDRESS , PCA9685_REGISTER_MODE1 , 1 , &temp , 1 );

			break;

		case ' ':

			CLI_Mgr_Print_I2C_Menu();

			break;

		case 'm':
		case 'M':

			CLI_Mgr_Print_Main_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_MAIN_MENU;

			break;

		default:

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nWrong input please select again" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );

			break;
	}
}

/*******************************************************************
 * Function Name: CLI_Mgr_Print_SPI_Menu
 * Description:
 *******************************************************************/
static void CLI_Mgr_Print_SPI_Menu( void )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\n\n*** SPI menu ***\nselect your option:" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "1 - Receive SPI command\n2 - Transmit SPI command" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "m - return to main menu\nspace - print current menu" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
}

/*******************************************************************
 * Function Name: CLI_Mgr_SPI_Menu_Selection_Handler
 * Description:
 *******************************************************************/
static void CLI_Mgr_SPI_Menu_Selection_Handler( char Val )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];
	HAL_StatusTypeDef 		status;
	uint8_t					tx_buff[ 3 ];
	uint8_t					rx_byte;

	switch( Val )
	{
		case '1':

			//set CS = 0
			HAL_GPIO_WritePin( SPI4_CS_GPIO_Port , SPI4_CS_Pin , GPIO_PIN_RESET );

			status = HAL_SPI_Receive( &hspi4 , &rx_byte , 1 , SPI_COMMAND_TIMEOUT );
			if( status != HAL_OK )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nError receive SPI command." );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			//set CS = 1
			HAL_GPIO_WritePin( SPI4_CS_GPIO_Port , SPI4_CS_Pin , GPIO_PIN_SET );

			break;

		case '2':

			tx_buff[ 0 ] = READ_FROM_RAM;
			tx_buff[ 1 ] = ( COMMAND_STATUS_REGISTER >> 8 ) & 0xFF;
			tx_buff[ 2 ] = COMMAND_STATUS_REGISTER & 0xFF;

			//set CS = 0
			HAL_GPIO_WritePin( SPI4_CS_GPIO_Port , SPI4_CS_Pin , GPIO_PIN_RESET );

			status = HAL_SPI_Transmit( &hspi4 , &tx_buff[ 0 ] , 3 , SPI_COMMAND_TIMEOUT );
			if( status != HAL_OK )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nError transmit SPI command." );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			//set CS = 1
			HAL_GPIO_WritePin( SPI4_CS_GPIO_Port , SPI4_CS_Pin , GPIO_PIN_SET );


			break;

		case ' ':

			CLI_Mgr_Print_SPI_Menu();

			break;

		case 'm':
		case 'M':

			CLI_Mgr_Print_Main_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_MAIN_MENU;

			break;

		default:

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nWrong input please select again" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );

			break;
	}
}

/*******************************************************************
 * Function Name: CLI_Mgr_Print_PWM_Menu
 * Description:
 *******************************************************************/
static void CLI_Mgr_Print_PWM_Menu( void )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\n\n*** PWM menu ***\nselect your option:\n1 - Activate TIM11 PWM (PF7,CN11-11) 24KHz 50%% Duty cycle" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "2 - TIM11 Duty cycle up by 5%%\n3 - TIM11 Duty cycle down by 5%%\n4 - Stop TIM11 PWM" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "5 - Activate TIM13 PWM (PF8,CN11-54) 100Hz 50%% Duty cycle\n6 - TIM13 Duty cycle up by 5%%" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "7 - TIM13 Duty cycle down by 5%%\n8 - Stop TIM13 PWM" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
	snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "m - return to main menu\nspace - print current menu" );
	Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
}

/*******************************************************************
 * Function Name: CLI_Mgr_PWM_Menu_Selection_Handler
 * Description:
 *******************************************************************/
static void CLI_Mgr_PWM_Menu_Selection_Handler( char Val )
{
	char 					data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];

	switch( Val )
	{

		case '1':

			htim11.Instance->CCR1 = 50;
			if( HAL_TIM_PWM_Start( &htim11 , TIM_CHANNEL_1 ) != HAL_OK )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Error activating TIM11 PWM!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case '2':

			if( ( htim11.Instance->CCR1 + 5 ) < 100 )
			{
				htim11.Instance->CCR1 = htim11.Instance->CCR1 + 5;
			}
			else
			{
				htim11.Instance->CCR1 = 100;
			}

			break;

		case '3':

			if( htim11.Instance->CCR1 >= 5 )
			{
				htim11.Instance->CCR1 = htim11.Instance->CCR1 - 5;
			}
			else
			{
				htim11.Instance->CCR1 = 0;
			}

			break;

		case '4':

			if( HAL_TIM_PWM_Stop( &htim11 , TIM_CHANNEL_1 ) != HAL_OK )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Error stopping TIM11 PWM!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case '5':

			htim13.Instance->CCR1 = 50;
			if( HAL_TIM_PWM_Start( &htim13 , TIM_CHANNEL_1 ) != HAL_OK )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Error activating TIM13 PWM!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case '6':

			if( ( htim13.Instance->CCR1 + 5 ) < 100 )
			{
				htim13.Instance->CCR1 = htim13.Instance->CCR1 + 5;
			}
			else
			{
				htim13.Instance->CCR1 = 100;
			}

			break;

		case '7':

			if( htim13.Instance->CCR1 >= 5 )
			{
				htim13.Instance->CCR1 = htim13.Instance->CCR1 - 5;
			}
			else
			{
				htim13.Instance->CCR1 = 0;
			}

			break;

		case '8':

			if( HAL_TIM_PWM_Stop( &htim13 , TIM_CHANNEL_1 ) != HAL_OK )
			{
				snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "Error stopping TIM13 PWM!!!" );
				Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );
			}

			break;

		case ' ':

			CLI_Mgr_Print_PWM_Menu();

			break;

		case 'm':
		case 'M':

			CLI_Mgr_Print_Main_Menu();
			CLI_Prop.CLI_Mgr_State = CLI_MGR_STATE_WAIT_FOR_MAIN_MENU_INPUT;
			CLI_Prop.CLI_Mgr_Menu = CLI_MGR_MAIN_MENU;

			break;

		default:

			snprintf( data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "\nWrong input please select again" );
			Syslog_Mgr_Add_Message( data , LOG_MESSAGE_LEVEL_INFO );

			break;
	}
}

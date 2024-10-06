/*******************************************************************
 * File Name: Main_Task_Mgr.c
 * Date: 13/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/


#include <stdio.h>
#include <string.h>
#include "cmsis_os.h"
#include "main.h"
#include "Utils.h"
#include "FreeRTOS.h"
#include "Main_Task_Mgr.h"
#include "Syslog_Mgr.h"

/* defines */

/*Syslog queue*/
osMailQDef( SyslogQueue , SYSLOG_QUEUE_MSG_NUM , Syslog_Queue_Msg_s );
osMailQId  SyslogQueueHandle;

/* structs definition */

/* local functions */

/* local variables */


/*******************************************************************
 * Function Name: Main_Task_Mgr_Handler
 * Description:
 *******************************************************************/
void Main_Task_Mgr_Handler( void )
{
	osDelay( 1 );
}

/*******************************************************************
 * Function Name: Main_Task_Mgr_Syslog_Queue_Init
 * Description:
 *******************************************************************/
int Main_Task_Mgr_Syslog_Queue_Init( void )
{
	SyslogQueueHandle = osMailCreate( osMailQ( SyslogQueue ) , NULL );
	if( SyslogQueueHandle == NULL )
	{
		Syslog_Mgr_Add_Message( "Error allocating syslog queue." , LOG_MESSAGE_LEVEL_CRIT );
		//TBD error
		return -1;
	}
	return 0;
}

/*******************************************************************
 * Function Name: Main_Task_Mgr_Get_Syslog_Queue_Handle
 * Description:
 *******************************************************************/
osMailQId Main_Task_Mgr_Get_Syslog_Queue_Handle( void )
{
	return SyslogQueueHandle;
}

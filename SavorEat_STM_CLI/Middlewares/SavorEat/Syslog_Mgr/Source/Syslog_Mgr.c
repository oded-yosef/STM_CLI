/*******************************************************************
 * File Name: Syslog_Mgr.c
 * Date: 13/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "Main_Task_Mgr.h"
#include "Syslog_Mgr.h"

/* defines */
#define SYSLOG_THREAD_STACK_SIZE 256

/* structs definition */

/* local functions */
static void Syslog_Mgr_Main_Handler( void const* Argument );

/* local variables */
osThreadId SyslogMgrThread_Handle;

/*******************************************************************
 * Function Name: Syslog_Mgr_Thread_Init
 * Description:
 *******************************************************************/
int Syslog_Mgr_Thread_Init( void )
{
	osThreadDef( SyslogMgrThread , Syslog_Mgr_Main_Handler , osPriorityNormal , 0 , ( uint32_t )SYSLOG_THREAD_STACK_SIZE );
	SyslogMgrThread_Handle = osThreadCreate( osThread( SyslogMgrThread ) , NULL );
	if( SyslogMgrThread_Handle == NULL )
	{
		return -1;
	}
	return 0;
}

/*******************************************************************
 * Function Name: Syslog_Mgr_Main_Handler
 * Description:
 *******************************************************************/
static void Syslog_Mgr_Main_Handler( void const* Argument )
{
	osEvent 						event;
	Syslog_Queue_Msg_s*				syslog_message;

	while( 1 )
	{
		/* Handle syslog */
		event = osMailGet( Main_Task_Mgr_Get_Syslog_Queue_Handle() , MAIL_QUEUE_GET_TIMEOUT_IN_MILLISECONDS );
		if( event.status == osEventMail )
		{
			syslog_message = ( Syslog_Queue_Msg_s* )event.value.p;
			printf( "%s\n" , syslog_message->Msg_Data );
			osMailFree( Main_Task_Mgr_Get_Syslog_Queue_Handle() , event.value.p );
		}
		osDelay( 2 );
	}
}

/*******************************************************************
 * Function Name: Syslog_Mgr_Add_Message
 * Description:
 *******************************************************************/
void Syslog_Mgr_Add_Message( char* Message , Syslog_Msg_Level_e Message_Level )
{
	osStatus						status;
	Syslog_Queue_Msg_s*				message;
	osEvent 						event;

	message = ( Syslog_Queue_Msg_s* )osMailAlloc( Main_Task_Mgr_Get_Syslog_Queue_Handle() , MAIL_QUEUE_GET_TIMEOUT_IN_MILLISECONDS );
	if( message == NULL )//cyclic queue
	{
		event = osMailGet( Main_Task_Mgr_Get_Syslog_Queue_Handle() , MAIL_QUEUE_GET_TIMEOUT_IN_MILLISECONDS );
		if( event.status == osEventMail )
		{
			osMailFree( Main_Task_Mgr_Get_Syslog_Queue_Handle() , event.value.p );
		}
		message = ( Syslog_Queue_Msg_s* )osMailAlloc( Main_Task_Mgr_Get_Syslog_Queue_Handle() , MAIL_QUEUE_GET_TIMEOUT_IN_MILLISECONDS );
	}

	if( message != NULL )
	{
		message->Msg_Level = Message_Level;
		snprintf( message->Msg_Data , SYSLOG_QUEUE_MSG_DATA_LENGTH , "%s" , Message );
		status = osMailPut( Main_Task_Mgr_Get_Syslog_Queue_Handle() , message );
		if( status != osOK  )
		{
			printf( "Syslog_Mgr_Add_Message: osMailPut error\n" );
		}
	}
	else
	{
		printf( "Syslog_Mgr_Add_Message: osMailAlloc Failed\n" );
	}
}


/*******************************************************************
 * File Name: Syslog_Mgr.h
 * Date: 13/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#ifndef __SYSLOG_MGR_HH__
#define __SYSLOG_MGR_HH__

/* defines */

#define SYSLOG_QUEUE_MSG_DATA_LENGTH 			128

/* enum definition */
typedef enum
{
	LOG_MESSAGE_LEVEL_EMERG					= 0,
	LOG_MESSAGE_LEVEL_ALERT					= 1,
	LOG_MESSAGE_LEVEL_CRIT					= 2,
	LOG_MESSAGE_LEVEL_ERR					= 3,
	LOG_MESSAGE_LEVEL_WARN					= 4,
	LOG_MESSAGE_LEVEL_NOTICE				= 5,
	LOG_MESSAGE_LEVEL_INFO					= 6,
	LOG_MESSAGE_LEVEL_DEBUG					= 7
}
	Syslog_Msg_Level_e;

/* struct definition */
typedef struct
{
	char 				Msg_Data[ SYSLOG_QUEUE_MSG_DATA_LENGTH ];
	uint8_t				Msg_Level;
}
	Syslog_Queue_Msg_s;

/* functions declaration */
int Syslog_Mgr_Thread_Init( void );
void Syslog_Mgr_Add_Message( char* Message , Syslog_Msg_Level_e Message_Level );

#endif //__SYSLOG_MGR_HH__

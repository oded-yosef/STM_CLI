/*******************************************************************
 * File Name: Main_Task_Mgr.h
 * Date: 13/11/2023
 * Author: Techdication - Roey Huberman
 * Copyright SavorEat © 2023
 *******************************************************************/

#ifndef __MAIN_TASK_MGR_HH__
#define __MAIN_TASK_MGR_HH__

/* defines */
#define	SYSLOG_QUEUE_MSG_NUM							20
#define SOM_COMM_RX_QUEUE_MSG_NUM						5
#define SOM_COMM_TX_QUEUE_MSG_NUM						5
#define MAIL_QUEUE_GET_TIMEOUT_IN_MILLISECONDS			3

/* enum definition */

/* struct definition */

/* functions declaration */
void Main_Task_Mgr_Handler( void );
int Main_Task_Mgr_Syslog_Queue_Init( void );
osMailQId Main_Task_Mgr_Get_Syslog_Queue_Handle( void );
#endif //__MAIN_TASK_MGR_HH__

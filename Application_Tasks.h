/*
 * Application_Tasks.h
 *
 * Created: 10/14/2019 8:29:09 PM
 *  Author: Abdelrahman Hafez
 */ 


#ifndef APPLICATION_TASKS_H_
#define APPLICATION_TASKS_H_
 #include "FreeRTOS.h"
 #include "task.h"
 #include "queue.h"
 #include <stdint.h>
 #include "GPIO.h"
 
 typedef struct
 {
	 QueueHandle_t	Speed_Q;
	 QueueHandle_t  Direction_Q	;
 } SD_Queue_Struct;
 
 void Speed_Button_Task(void * Speed_Queue);
 void Direction_Button_Task(void * Direction_Queue);
 void Stepper_Motor_Task(void * S_D_Queue);

#endif /* APPLICATION_TASKS_H_ */
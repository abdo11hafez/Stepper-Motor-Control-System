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
 #include <avr/interrupt.h>
 
 typedef struct
 {
	 QueueHandle_t	Speed_Q;
	 QueueHandle_t  Direction_Q	;
	 QueueHandle_t  Step_Q;
 } Parameters_Queue_Struct;
 
 void Interrupt_Init(void);
 void Stepper_Motor_Task(void * S_D_Queue);

#endif /* APPLICATION_TASKS_H_ */

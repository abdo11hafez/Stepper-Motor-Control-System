/*
 * Application_Tasks.c
 *
 * Created: 10/14/2019 8:28:04 PM
 *  Author: Abdelrahman Hafez
 */ 

#include "Application_Tasks.h"

void Speed_Button_Task(void * Speed_Queue)
{
	uint8_t last_status = 0x00 ;
	uint8_t data;
	static uint8_t prev_speed = 0x01;
	while(1)
	{
		GPIO_Read(1,&data) ;
		if((data == 1) && (last_status == 0x00))
		{
			prev_speed += 2 ;
			prev_speed = (prev_speed > 6) ? 1 :prev_speed;
			xQueueOverwrite((QueueHandle_t)Speed_Queue,&prev_speed)	;
		}
		last_status = data;
		vTaskDelay(55);
	}
}

void Direction_Button_Task(void * Direction_Queue)
{
	uint8_t last_status = 0x00 ;
	uint8_t data;
	static uint8_t prev_direction = 0x00;
	while(1)
	{
		GPIO_Read(2,&data) ;
		if((data == 0x02) && (last_status == 0x00))
		{
			prev_direction ^= 0x01 ;
			xQueueOverwrite((QueueHandle_t)Direction_Queue,&prev_direction)	;
		}
		last_status = data;
		vTaskDelay(55);
	}
}

void Stepper_Motor_Task(void* S_D_Queue)
{
	static int motor_angle = 0;
	uint8_t	direction =0x00;
	uint8_t speed = 0x01;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		xQueuePeek( ((SD_Queue_Struct*)S_D_Queue)->Direction_Q, &direction, 0 );
		xQueuePeek( ((SD_Queue_Struct*)S_D_Queue)->Speed_Q, &speed, 0 );
		if(direction == 0x00)
		{
			if (motor_angle==0)
			{
				GPIO_Write(0,1<<0);
				motor_angle++;
			}
			else if (motor_angle==1)
			{
				GPIO_Write(0,1<<1);
				motor_angle++;
			}
			else if (motor_angle==2)
			{
				GPIO_Write(0,1<<2);
				motor_angle++;
			}
			else if (motor_angle==3)
			{
				GPIO_Write(0,1<<3);
				motor_angle =0;
			}
		}
		else if(direction == 0x01)
		{
			if (motor_angle==0)
			{
				GPIO_Write(0,1<<3);
				motor_angle++;
			}
			else if (motor_angle==1)
			{
				GPIO_Write(0,1<<2);
				motor_angle++;
			}
			else if (motor_angle==2)
			{
				GPIO_Write(0,1<<1);
				motor_angle++;
			}
			else if (motor_angle==3)
			{
				GPIO_Write(0,1<<0);
				motor_angle =0;
			}
		}
		vTaskDelayUntil( &xLastWakeTime, speed*150);
	}
}

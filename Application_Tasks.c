/*
 * Application_Tasks.c
 *
 * Created: 10/14/2019 8:28:04 PM
 *  Author: Abdelrahman Hafez
 */ 

#include "Application_Tasks.h"

void Interrupt_Init(void)
{
	MCUCR &=~ 0x0f;
	GICR |= 7<<5;
}


void Stepper_Motor_Task(void * Speed_Direction_Step_Queue)
{
	static int Fullstep_Position = 0;
	static int HalfStep_Position = 0;
	uint8_t	direction =0x00;
	uint8_t speed = 0x01;
	uint8_t StepMode =0x00;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		xQueuePeek( ((Parameters_Queue_Struct*)Speed_Direction_Step_Queue)->Direction_Q, &direction, 0 );
		xQueuePeek( ((Parameters_Queue_Struct*)Speed_Direction_Step_Queue)->Speed_Q, &speed, 0 );
		xQueuePeek( ((Parameters_Queue_Struct*)Speed_Direction_Step_Queue)->Step_Q, &StepMode, 0 );
		if(StepMode==0)
		{
			if(direction == 0x00)
			{
				if (Fullstep_Position==0)
				{
					GPIO_Write(0,1<<0);
					Fullstep_Position++;
				}
				else if (Fullstep_Position==1)
				{
					GPIO_Write(0,1<<1);
					Fullstep_Position++;
				}
				else if (Fullstep_Position==2)
				{
					GPIO_Write(0,1<<2);
					Fullstep_Position++;
				}
				else if (Fullstep_Position==3)
				{
					GPIO_Write(0,1<<3);
					Fullstep_Position =0;
				}
			}
			else if(direction == 0x01)
			{
				if (Fullstep_Position==0)
				{
					GPIO_Write(0,1<<3);
					Fullstep_Position++;
				}
				else if (Fullstep_Position==1)
				{
					GPIO_Write(0,1<<2);
					Fullstep_Position++;
				}
				else if (Fullstep_Position==2)
				{
					GPIO_Write(0,1<<1);
					Fullstep_Position++;
				}
				else if (Fullstep_Position==3)
				{
					GPIO_Write(0,1<<0);
					Fullstep_Position =0;
				}
			}
		}
		else if (StepMode==1)
		{
			if(direction == 0x00)
			{
				if (HalfStep_Position==0)
				{
					GPIO_Write(0,3<<0);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==1)
				{
					GPIO_Write(0,1<<1);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==2)
				{
					GPIO_Write(0,3<<1);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==3)
				{
					GPIO_Write(0,1<<2);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==4)
				{
					GPIO_Write(0,3<<2);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==5)
				{
					GPIO_Write(0,1<<3);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==6)
				{
					GPIO_Write(0,9);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==7)
				{
					GPIO_Write(0,1<<0);
					HalfStep_Position =0;
				}
			}
			else if(direction==1)
			{
				if (HalfStep_Position==0)
				{
					GPIO_Write(0,1<<0);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==1)
				{
					GPIO_Write(0,9);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==2)
				{
					GPIO_Write(0,1<<3);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==3)
				{
					GPIO_Write(0,3<<2);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==4)
				{
					GPIO_Write(0,1<<2);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==5)
				{
					GPIO_Write(0,3<<1);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==6)
				{
					GPIO_Write(0,1<<1);
					HalfStep_Position++;
				}
				else if (HalfStep_Position==7)
				{
					GPIO_Write(0,3<<0);
					HalfStep_Position =0;
				}				
			}
		}
		vTaskDelayUntil( &xLastWakeTime, speed*150);
	}
}

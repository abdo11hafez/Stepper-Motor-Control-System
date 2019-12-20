#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "GPIO.h"
#include "Application_Tasks.h"

Parameters_Queue_Struct Speed_Direction_Step_Queue;
TaskHandle_t  Motor,BTN1,BTN2;
QueueHandle_t Speed_Queue ,Direction_Queue,Step_Queue ;

int main(void) {
	GPIO_Init();
	Interrupt_Init();
	
	Speed_Queue = xQueueCreate(1,1);
	Direction_Queue = xQueueCreate(1,1);
	Step_Queue =  xQueueCreate(1,1);
	
	Speed_Direction_Step_Queue.Speed_Q = Speed_Queue	;
	Speed_Direction_Step_Queue.Direction_Q =	Direction_Queue;
	Speed_Direction_Step_Queue.Step_Q = Step_Queue;
	
	xTaskCreate(Stepper_Motor_Task, "MOTOR",configMINIMAL_STACK_SIZE, &Speed_Direction_Step_Queue,1, &Motor);
	vTaskStartScheduler();
	
	while(1) 
	{

	}
	return 0;
}


ISR(INT0_vect)
{
	// Updating Speed ISR
	static uint8_t prev_speed = 0x01;
	BaseType_t pxHigherPriorityTaskWoken ;
	prev_speed += 2 ;
	prev_speed = (prev_speed > 6) ? 1 :prev_speed;
	xQueueOverwriteFromISR((QueueHandle_t)Speed_Queue,&prev_speed,&pxHigherPriorityTaskWoken)	;
}

ISR(INT1_vect)
{
	// Updating Direction ISR
	BaseType_t pxHigherPriorityTaskWoken ;
	static uint8_t prev_direction = 0x00;
	prev_direction ^= 0x01 ;
	xQueueOverwriteFromISR((QueueHandle_t)Direction_Queue,&prev_direction,&pxHigherPriorityTaskWoken)	;
}

ISR(INT2_vect)
{
	// Updating Step Mode ISR
	BaseType_t pxHigherPriorityTaskWoken ;
	static uint8_t prev_step_mode = 0x00;
	prev_step_mode ^= 0x01 ;
	xQueueOverwriteFromISR((QueueHandle_t)Step_Queue,&prev_step_mode,&pxHigherPriorityTaskWoken)	;
}



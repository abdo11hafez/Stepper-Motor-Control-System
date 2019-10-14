#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "GPIO.h"
#include "Application_Tasks.h"



int main(void) {
	GPIO_Init();
	
	TaskHandle_t  Motor,BTN1,BTN2;
	QueueHandle_t Speed_Queue ,Direction_Queue ;
	SD_Queue_Struct S_D_Queue;
	
	Speed_Queue = xQueueCreate(1,sizeof(uint8_t));
	Direction_Queue = xQueueCreate(1,sizeof(uint8_t));
	
	S_D_Queue.Speed_Q = Speed_Queue	;
	S_D_Queue.Direction_Q =	Direction_Queue;
	
	xTaskCreate(Speed_Button_Task, "BUTTON1",configMINIMAL_STACK_SIZE, (QueueHandle_t)Speed_Queue,2, &BTN1);
	xTaskCreate(Direction_Button_Task, "BUTTON2",configMINIMAL_STACK_SIZE, (QueueHandle_t)Direction_Queue,2, &BTN2);
	xTaskCreate(Stepper_Motor_Task, "MOTOR",configMINIMAL_STACK_SIZE, (SD_Queue_Struct*)&S_D_Queue,1, &Motor);
	vTaskStartScheduler();
	
	while(1) 
	{

	}
	return 0;
}









/*
 * GPIO.c
 *
 *	Updated on : 10/14/2019 3:00:34 PM
 *  Author	   : Abdelrahman Hafez
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "GPIO_Cfg.h"
#include <stdint.h>
typedef struct
{
	uint8_t PortId;				
	uint8_t PortMask;
	uint8_t PortDirection;
	uint8_t UsePullUp;
}GPIO_CfgType;

typedef enum {GPIO_OK =0, GPIO_NOK} GPIO_CheckType;
extern const GPIO_CfgType GPIO_ConfigParam [GPIO_GROUPS_NUMBER];

/*A function to initialize all the GPIO Groups in the configurations*/
GPIO_CheckType GPIO_Init(void);
/*A function to Digital Write data to a specific group*/
GPIO_CheckType GPIO_Write(uint8_t GroupId,uint8_t GroupData);
/*A function to Digital read data from a specific group*/
GPIO_CheckType GPIO_Read(uint8_t GroupId,uint8_t* GroupDataPtr);
	
#endif /* GPIO_H_ */
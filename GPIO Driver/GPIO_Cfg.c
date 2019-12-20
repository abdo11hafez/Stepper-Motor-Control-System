/*
 * GPIO_Cfg.c
 *
 *  Updated on : 10/14/2019 3:00:34 PM
 *  Author	   : Abdelrahman Hafez
 */ 
#include "GPIO.h"
#include "GPIO_Cfg.h"

const GPIO_CfgType GPIO_ConfigParam [GPIO_GROUPS_NUMBER] =
{
	{
		0,						/*PORTA*/
		0x0F,					/*MASK*/
		0xFF,					/*OUTPUT*/
		0x00					/*NO PULLUP*/
	},
	{
		3,						/*PORTD*/
		1<<2,					/*MASK-PIND2*/
		0x00,					/*INPUT*/
		0xff					/* PULLUP*/
	},
	{
		3,						/*PORTD*/
		1<<3,					/*MASK-PIND3*/
		0x00,					/*INPUT*/
		0xff					/* PULLUP*/
	},
	{
		1,						/*PORTB*/
		1<<2,					/*MASK-PINB2*/
		0x00,					/*INPUT*/
		0xff					/* PULLUP*/
	}
};

/*
 * GPIO.c
 *
 *	Updated on : 10/14/2019 3:00:34 PM
 *  Author	   : Abdelrahman Hafez
 */ 
#include "GPIO.h"
#include "GPIO_Cfg.h"
#include <stdint.h>
#include <avr/io.h>
 
#define PORTS_NUMBER			4u

static uint8_t GPIO_GroupState[GPIO_GROUPS_NUMBER] = {0};
	
/*A function to initialize all the GPIO configuration Groups */
GPIO_CheckType GPIO_Init(void)
{
	uint8_t LoopIndex;
	uint8_t ErrorFlag = 0;
	GPIO_CheckType RetVar;
	const GPIO_CfgType * CfgPtr;
	for(LoopIndex = 0; (LoopIndex < GPIO_GROUPS_NUMBER) && (ErrorFlag == 0); LoopIndex ++)
	{
		if(GPIO_ConfigParam[LoopIndex].PortId < PORTS_NUMBER)
		{
			CfgPtr = & GPIO_ConfigParam[LoopIndex];
			switch(CfgPtr->PortId)
			{
				case 0:
				DDRA = (DDRA &~(CfgPtr->PortMask)) | (CfgPtr->PortDirection & CfgPtr->PortMask);
				PORTA = (PORTA &~(CfgPtr->PortMask)) | (CfgPtr->UsePullUp & CfgPtr->PortMask);
				break;	
				case 1:
				DDRB = (DDRB &~(CfgPtr->PortMask)) | (CfgPtr->PortDirection & CfgPtr->PortMask);
				PORTB = (PORTB &~(CfgPtr->PortMask)) | (CfgPtr->UsePullUp & CfgPtr->PortMask);
				break;
				case 2:
				DDRC = (DDRC &~(CfgPtr->PortMask)) | (CfgPtr->PortDirection & CfgPtr->PortMask);
				PORTC = (PORTC &~(CfgPtr->PortMask)) | (CfgPtr->UsePullUp & CfgPtr->PortMask);
				break;
				case 3:
				DDRD = (DDRD &~(CfgPtr->PortMask)) | (CfgPtr->PortDirection & CfgPtr->PortMask);
				PORTD = (PORTD &~(CfgPtr->PortMask)) | (CfgPtr->UsePullUp & CfgPtr->PortMask);
				break;
				default:
				/* Do Nothing */
				break;
			}
			GPIO_GroupState[LoopIndex] = 1;  // indication that this group has been initialized
			RetVar = GPIO_OK;
		}
		else
		{
			/*Invalid GroupId*/
			RetVar = GPIO_NOK;
			ErrorFlag = 1;
		}
	}
	return RetVar;
 }
 
 
/*A function to Digital Write data to a specific group*/ 
GPIO_CheckType GPIO_Write(uint8_t GroupId,uint8_t GroupData)
{
	const GPIO_CfgType * CfgPtr;
	GPIO_CheckType RetVar;
	if (( GroupId <GPIO_GROUPS_NUMBER))
	{
		CfgPtr =  & GPIO_ConfigParam[GroupId];
		if ( (CfgPtr->PortDirection == 0xff) && (GPIO_GroupState[GroupId]==1 ) )
		{
			switch(CfgPtr->PortId)
			{
				case 0:
				PORTA = (PORTA &~(CfgPtr->PortMask)) | (GroupData & CfgPtr->PortMask);
				break;
				case 1:
				PORTB = (PORTB &~(CfgPtr->PortMask)) | (GroupData & CfgPtr->PortMask);
				break;
				case 2:
				PORTC = (PORTC &~(CfgPtr->PortMask)) | (GroupData & CfgPtr->PortMask);
				break;
				case 3:
				PORTD = (PORTD &~(CfgPtr->PortMask)) | (GroupData & CfgPtr->PortMask);
				break;
				default:
				/*Do Nothing*/
				break;
			}
			RetVar = GPIO_OK;
		}
		else RetVar = GPIO_NOK;
	}
	else RetVar = GPIO_NOK;
	
	return RetVar;
}


/*A function to Digital Read data from a specific group*/
GPIO_CheckType GPIO_Read(uint8_t GroupId,uint8_t* GroupDataPtr)
{   const GPIO_CfgType * CfgPtr;
	GPIO_CheckType RetVar;
	CfgPtr =  & GPIO_ConfigParam[GroupId];
	if (( GroupId <GPIO_GROUPS_NUMBER))
	{
		CfgPtr =  & GPIO_ConfigParam[GroupId];
		if ( (CfgPtr->PortDirection == 0x00) && (GPIO_GroupState[GroupId]==1 ) )
		{
			switch(CfgPtr->PortId)
			{
				case 0:
				*GroupDataPtr = (uint8_t)(PINA & CfgPtr->PortMask);
				break;
				case 1:
				*GroupDataPtr = (uint8_t)(PINB & CfgPtr->PortMask);
				break;
				case 2:
				*GroupDataPtr = (uint8_t)(PINC & CfgPtr->PortMask);
				break;
				case 3:
				*GroupDataPtr = (uint8_t)(PIND & CfgPtr->PortMask);
				break;
				default:
				/*Do Nothing*/
				break;	
			}
		RetVar = GPIO_OK ;
		}
		else RetVar = GPIO_NOK ;
	}
	else	RetVar = GPIO_NOK ; 

	return RetVar;
}




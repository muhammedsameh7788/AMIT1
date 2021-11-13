/*
 * Seven_Segment.c
 *
 * Created: 10/16/2021 1:52:16 PM
 *  Author: osama
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "Seven_Segment.h"
#define	F_CPU 16000000UL
#include <util/delay.h>


void Seven_SEGMENT_INIT()
{
	DIO_u8SetPinDirection(DIO_PIN4 , DIO_PORTA , PIN_OUTPUT); //A
	DIO_u8SetPinDirection(DIO_PIN5 , DIO_PORTA , PIN_OUTPUT); //B
	DIO_u8SetPinDirection(DIO_PIN6 , DIO_PORTA , PIN_OUTPUT); //C
	DIO_u8SetPinDirection(DIO_PIN7 , DIO_PORTA , PIN_OUTPUT); //D
	
	DIO_u8SetPinDirection(DIO_PIN3 , DIO_PORTB , PIN_OUTPUT); //EN1
	DIO_u8SetPinDirection(DIO_PIN1 , DIO_PORTB , PIN_OUTPUT); //EN2
}
void Seven_SEGMENT_Enable1()
{
	DIO_u8SetPinValue(DIO_PIN3 , DIO_PORTB , PIN_HIGH);
}
void Seven_SEGMENT_Enable2()
{
	DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTB , PIN_HIGH);
}
void Seven_SEGMENT_Disable1()
{
	DIO_u8SetPinValue(DIO_PIN3 , DIO_PORTB , PIN_LOW);
}
void Seven_SEGMENT_Disable2()
{
	DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTB , PIN_LOW);
}

/*void Seven_SEGMENT_write_number(u8 number)
{
	if (number < 10)
	{
		DIO_u8SetPinValue(DIO_PIN4 , DIO_PORTA , GET_BIT(number , 0)); //A
		DIO_u8SetPinValue(DIO_PIN5 , DIO_PORTA , GET_BIT(number , 1)); //B
		DIO_u8SetPinValue(DIO_PIN6 , DIO_PORTA , GET_BIT(number , 2)); //C
		DIO_u8SetPinValue(DIO_PIN7 , DIO_PORTA , GET_BIT(number , 3)); //D
	}
}
*/
//////////////////////////////////////////
void Seven_SEGMENT_Disable()
{
	DIO_u8SetPinValue(DIO_PIN3 , DIO_PORTB , PIN_LOW);

	DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTB , PIN_LOW);
}
/*
void Seven_SEGMENT_write_number_BARAKAT(u8 number ,u8 SEGMANT)
{
	if(SEGMANT==0)
	{
		DIO_u8SetPinValue(DIO_PIN2 , DIO_PORTB , PIN_HIGH);
		DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTB , PIN_LOW);
		
	}
	else if(SEGMANT==1)
	{
		DIO_u8SetPinValue(DIO_PIN1 , DIO_PORTB , PIN_HIGH);
		DIO_u8SetPinValue(DIO_PIN2 , DIO_PORTB , PIN_LOW);
	}
	else
	{
		/*NOTHING
	}
	if (number < 10)
	{
		DIO_u8SetPinValue(DIO_PIN4 , DIO_PORTA , GET_BIT(number , 0)); //A
		DIO_u8SetPinValue(DIO_PIN5 , DIO_PORTA , GET_BIT(number , 1)); //B
		DIO_u8SetPinValue(DIO_PIN6 , DIO_PORTA , GET_BIT(number , 2)); //C
		DIO_u8SetPinValue(DIO_PIN7 , DIO_PORTA , GET_BIT(number , 3)); //D
	}
	else
	{
		/*NOTHING
	}
}
*/

void _7_SEGMENT_READ(u8 Data)
{
	u8 ten = (Data/10)<<4;
	u8 one =(Data%10)<<4;

	for(u8 i=0;i<2;i++)
	{

		if(i==0)
		{

			DIO_u8SetPinValue(DIO_PIN1,DIO_PORTB,PIN_HIGH);
			
			DIO_u8Set4MSB_BitsValue(DIO_PORTA,ten);
			_delay_ms(5);
			DIO_u8SetPinValue(DIO_PIN1,DIO_PORTB,PIN_LOW);
			

		}
		else
		{
	        DIO_u8SetPinValue(DIO_PIN3,DIO_PORTB,PIN_HIGH);
			DIO_u8Set4MSB_BitsValue(DIO_PORTA,one);
			_delay_ms(5);
			DIO_u8SetPinValue(DIO_PIN3,DIO_PORTB,PIN_LOW);
		}

	}

}
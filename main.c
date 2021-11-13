
#define F_CPU 16000000UL
#include <avr/io.h>

#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"ADC_interface.h"
#include"Seven_Segment.h"
#include"GIE_interface.h"
#include"EXTI_interface.h"
#include"TIMER_Interface.h"
#include"TIMER_Config.h"
#include "eeprom.h"

#include <util/delay.h>

unsigned char bottom1_falg=0;
unsigned char bottom2_falg=0;
unsigned char bottom3_falg=0;
unsigned char k=60;
u32 b_flag=0;
unsigned char f_flag=10;
u16 temp;
u8 D_Count=0;
u8 D_flag=0;



u16 fun_adc_temp()
{
	u16 LOC_u16Analog;
	u16 LOC_u16Digital;
	unsigned int average=0;
	static unsigned char i=0;
	static unsigned int temp_value[10]={0};
	LOC_u16Digital=ADC_u16StartConversion(0);
	LOC_u16Analog=(LOC_u16Digital*5000UL)/1024;
	LOC_u16Analog/=10;
	temp_value[i]=LOC_u16Analog;
	if (i==9)
	{
		i=0;
	}
	else
	{
		i++;
	}
	for(unsigned char j=0;j<10;j++)
	{
		average+=temp_value[j];
	}
	average/=10;



	return average;
}


int main(void)
{

	DIO_u8SetPinDirection(DIO_PIN2,DIO_PORTD,PIN_INPUT);
	DIO_u8SetPinValue(DIO_PIN2,DIO_PORTD,PIN_HIGH);

	DIO_u8SetPinDirection(DIO_PIN3,DIO_PORTD,PIN_INPUT);
	DIO_u8SetPinValue(DIO_PIN3,DIO_PORTD,PIN_HIGH);

	DIO_u8SetPinDirection(DIO_PIN2,DIO_PORTB,PIN_INPUT);
	DIO_u8SetPinValue(DIO_PIN2,DIO_PORTB,PIN_HIGH);

	DIO_u8SetPinDirection(DIO_PIN1,DIO_PORTC,PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN3,DIO_PORTC,PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN4,DIO_PORTC,PIN_OUTPUT);

	u8 temp_temp=0;

	temp_temp=EEPROM_read(0);
	if(temp_temp!=0xFF)
	{
		k=temp_temp;
	}


	ADC_voidInit();

	Seven_SEGMENT_INIT();
	EXTI_voidINT0_Init();
	EXTI_voidINT1_Init();
	EXTI_voidINT2_Init();

	TIMER0_voidInit();
	TIMER2_voidInit();
	GIE_voidEnable();

	TIMER0_voidSetPreloadValue(TIMER0_PRELOAD);
	TIMER2_voidSetPreloadValue(TIMER2_PRELOAD);


	while (1)
	{

		if (bottom1_falg==0)
		{

			DIO_u8SetPinValue(DIO_PIN4,DIO_PORTC,PIN_LOW);
			DIO_u8SetPinValue(DIO_PIN3,DIO_PORTC,PIN_LOW);
			DIO_u8SetPinValue(DIO_PIN1,DIO_PORTC,PIN_LOW);
			Seven_SEGMENT_Disable();
		}
		else
		{

			if((f_flag>10))
			{
				DIO_u8SetPinValue(DIO_PIN4,DIO_PORTC,PIN_LOW);
				DIO_u8SetPinValue(DIO_PIN3,DIO_PORTC,PIN_LOW);
				DIO_u8SetPinValue(DIO_PIN1,DIO_PORTC,PIN_LOW);

				if(D_flag==0)
				{
					_7_SEGMENT_READ(k);
				}
				else
				{

				}



				if(f_flag>11)
				{
					

					if (bottom2_falg==1 )
					{
						if (k!=75)
						{
							k+=5;
						}
						bottom2_falg=0;
					}
					//////////////////////////////////////////////////
					//BOTTOM 3//
					if (bottom3_falg==1)
					{
						if(k!=35)
						{
							k-=5;
						}
						bottom3_falg=0;
					}
					EEPROM_write(0,k);

				}
			}
			else
			{

				f_flag=10;
				b_flag=0;

				temp=fun_adc_temp();
				_7_SEGMENT_READ(temp);

				//JKNJK
				if (k<=(temp-5))
				{

					DIO_u8SetPinValue(DIO_PIN4,DIO_PORTC,PIN_LOW);
					DIO_u8SetPinValue(DIO_PIN3,DIO_PORTC,PIN_HIGH);
					DIO_u8SetPinValue(DIO_PIN1,DIO_PORTC,PIN_HIGH);
				}
				if (k>=(temp+5))
				{
					DIO_u8SetPinValue(DIO_PIN3,DIO_PORTC,PIN_LOW);
					DIO_u8SetPinValue(DIO_PIN4,DIO_PORTC,PIN_HIGH);

					if(D_flag==0)
					{
						DIO_u8SetPinValue(DIO_PIN1,DIO_PORTC,PIN_HIGH);
					}
					else
					{
						DIO_u8SetPinValue(DIO_PIN1,DIO_PORTC,PIN_LOW);
					}
				}

			}
		} 
	}
}


void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(bottom1_falg==0)
	{
		bottom1_falg=1;
	} 
	else
	{
		bottom1_falg=0;
	}
}



void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{

	bottom2_falg=1;
	f_flag++;
	b_flag=0;
	D_flag=0;

}




void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	bottom3_falg=1;
	f_flag++;
	b_flag=0;
	D_flag=0;
}

void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{

	b_flag++;

	if (b_flag==315)
	{	
		f_flag=10;	
	}

	D_Count++;
	if(D_Count==61)
	{
		if(D_flag==0)
		{
			D_flag=1;
		}
		else
		{
			D_flag=0;
		}

		D_Count=0;
	}
	else 
	{
	}

}




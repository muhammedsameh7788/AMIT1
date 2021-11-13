/*
 * eeprom.c
 *
 * Created: 10/29/2021 2:56:18 PM
 *  Author: osama
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "eeprom.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#define	F_CPU 16000000UL

void EEPROM_write(u16 uiAddress, u8 ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

u8 EEPROM_read(u16 uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

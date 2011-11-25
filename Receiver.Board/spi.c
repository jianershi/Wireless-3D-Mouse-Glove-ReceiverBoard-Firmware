/*
 * spi.c
 *
 *  Created on: Nov 19, 2011
 *      Author: Paul Shi
 */


#include "spi.h"

//static void Init(CLK ePrescale = D4, DataOrder eOrder = MSB, ClkPolarity eClkPolarity = Rising, ClkSamplePhase eClkPhase = Leading)
void SPI_Init(SPI_CLK ePrescale, SPI_DataOrder eOrder, SPI_ClkPolarity eClkPolarity , SPI_ClkSamplePhase eClkPhase)
{
	DDRB &= ~_BV(PB4); //set MISO as input
	DDRB |= _BV(PB2) | _BV(PB3) | _BV(PB5); //set SS,MOSI, SCK as output
	//PORTB |= _BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5); //doesn't really matter
	SPCR = _BV(MSTR) | ((uint8_t) (eOrder)) | ((uint8_t) (eClkPolarity)) | ((uint8_t)(eClkPhase))	| (((uint8_t) (ePrescale)) >> 1); // set parameters
	SPSR = ((uint8_t) (ePrescale)) & 0x01; // might enter 2X speed mode
	SPCR |= _BV(SPE); // enable the SPI
}

uint8_t TransChar(uint8_t ucData) {
//	portENTER_CRITICAL();
	SPDR = ucData;
	while(! (SPSR & _BV(SPIF))); //wait until previous transfer compolete
//	portEXIT_CRITICAL();
	return SPDR;
}

void TransBlock(uint8_t *pucSend, uint8_t ucLen,
		uint8_t *pucReceive) {
	uint8_t i;
	uint8_t ucTmp;
	for (i = 0; i < ucLen; i++) {
		ucTmp = TransChar(*(pucSend + i));
		if (pucReceive)
			*(pucReceive + i) = ucTmp;
	}
}

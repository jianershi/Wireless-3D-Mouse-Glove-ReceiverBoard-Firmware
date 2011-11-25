/*
 * spi.h
 *
 *  Created on: Nov 19, 2011
 *      Author: Paul Shi
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <stdio.h>
//#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdint.h>


typedef enum {
	D2 = _BV(SPI2X),
	D4 = 0,
	D8 = ((_BV(SPR0)) << 1) | _BV(SPI2X),
	D16 = (_BV(SPR0)) << 1,
	D32 = ((_BV(SPR1)) << 1) | _BV(SPI2X),
	D64 = (_BV(SPR1)) << 1,
	D128 = (_BV(SPR0) | _BV(SPR1)) << 1,
} SPI_CLK;

typedef enum {
	MSB = 0, LSB = _BV(DORD)
} SPI_DataOrder; //which bit will be transmitted first

typedef enum {
	Rising = 0, Falling = _BV(CPOL)
} SPI_ClkPolarity;

typedef enum {
	Leading = 0, Trailing = _BV(CPHA)
} SPI_ClkSamplePhase;

typedef struct {
	SPI_CLK ePrescale;
	SPI_DataOrder eOrder;
	SPI_ClkPolarity eClkPolarity;
	SPI_ClkSamplePhase eClkPhase;
} Property;


void SPI_Init(SPI_CLK ePrescale, SPI_DataOrder eOrder, SPI_ClkPolarity eClkPolarity , SPI_ClkSamplePhase eClkPhase);

//static void Init(CLK ePrescale = D4, DataOrder eOrder = MSB, ClkPolarity eClkPolarity = Rising,	ClkSamplePhase eClkPhase = Leading);

uint8_t TransChar(uint8_t ucData);
void TransBlock(uint8_t *pucSend, uint8_t ucLen, uint8_t *pucReceive);






//static void TransBlock(uint8_t **ppucBuff, uint8_t ucLen) {
//	TransBlock(*ppucBuff, ucLen, *(ppucBuff + 1));
//}
//
//static void GetProperty(Property *psProperty) {
//	memcpy((void*) &m_sProperty, (const void*) psProperty, sizeof(Property));
//	;
//}
//static void SetProperty(Property *psProperty) {
//	Init(psProperty->ePrescale, psProperty->eOrder,
//			psProperty->eClkPolarity, psProperty->eClkPhase);
//}
//
//
//	CSPI(void);
//	static Property m_sProperty;
//
//
//
//	volatile uint8_t *m_pucPORT;
//	uint8_t m_ucPin;
//
//	CSPIDevice(IOSet *psSet) {
//		m_pucPORT = NULL;
//		m_ucPin = 0; //Bitmask of The Device
//		Init(psSet);
//	}
//
//
//
//
//



#endif /* SPI_H_ */

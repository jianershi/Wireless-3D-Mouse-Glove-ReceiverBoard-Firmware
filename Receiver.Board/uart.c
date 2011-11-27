/*
 * uart.c
 *
 *  Created on: Nov 18, 2011
 *      Author: Paul Shi
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
//#include <util/setbaud.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include <stddef.h>

void (*reset)(void);

static volatile unsigned char UART_TxBuf[UART_TX_BUFFER_SIZE];
//static volatile unsigned char UART_RxBuf[UART_RX_BUFFER_SIZE];
static volatile unsigned char UART_TxHead; //writing --last location written
static volatile unsigned char UART_TxTail; //read    --last location read
static volatile unsigned char UART_RxHead; //writing
static volatile unsigned char UART_RxTail; //read
//static volatile unsigned char UART_LastRxError;

void uart_init(uint32_t baud, enum UART_SPEED_MODE SendingSpeed)
{

	reset=NULL;

	UART_TxHead=0;
	UART_TxTail=0;
	UART_RxHead=0;
	UART_RxTail=0;

	UCSRC = _BV(URSEL)|_BV(UCSZ1)|_BV(UCSZ0); // Asyncrhnous, No Parity, 1 Stop Bit, 8bit



	switch (SendingSpeed)
	{
		case USE_1X:
			UCSRA &= ~_BV(U2X);
			UBRRH=(unsigned char) (UBRR_VALUE(baud)>>8);
			UBRRL=(unsigned char) (UBRR_VALUE(baud) & 0xFF);
			break;
		case USE_2X:
			UCSRA |= _BV(U2X);
			UBRRH=(unsigned char) (UBRR_VALUE_DOUBLE_SPEED(baud)>>8);
			UBRRL=(unsigned char) (UBRR_VALUE_DOUBLE_SPEED(baud) & 0xFF);
			break;

	}



    //Enable receive interrupt, enable Receiver and Transmitter
	//UCSRB = _BV(RXCIE)|_BV(RXEN)|_BV(TXEN);
	UCSRB = _BV(RXEN)|_BV(TXEN);

//    //ENABLE Interrupt
//    if (using_interrupt)
//    {
//
//    	// Bit 7 – RXCIE: RX Complete Interrupt Enable
//    	UCSRB |= _BV(RXCIE);
//
//    	// Bit 6 – TXCIE: TX Complete Interrupt Enable
//    	UCSRB |= _BV(TXCIE);
//
//    	//USART Data Register Empty Interrupt Enable
//    	UCSRB |= _BV(UDRIE);
//
//    	//
//
//    }

}


void uart_putc(unsigned char data)
{

	//while ( !( UCSRA & (1<<UDRE)) ); //Wait for empty transmit buffer, sould be empty because it is suppoed to be called in interrupt
	unsigned char tmpHEAD;
	tmpHEAD=(UART_TxHead+1) & (UART_TX_BUFFER_SIZE-1); //buffer about to full, refuse to write
	while (tmpHEAD==UART_TxTail) ; //wait for freespace

	cli();
	UART_TxHead=tmpHEAD;
	UART_TxBuf[UART_TxHead]=data;
	sei();

	//enable TX interrupt

	 UCSRB |= _BV(UDRIE);

	return;

}

//void uart_puts_p(const char *progmem_s)
//{
//    register char c;
//
//    while ( (c = pgm_read_byte(progmem_s++)) )
//      uart_putc(c);
//
//
//
//}


void uart_puts(const char *s )
{
    while (*s)
      uart_putc(*s++);

}/* uart_puts */



//unsigned char uart_getc()
//{
//	unsigned char tmpTAIL;
//
//	if (UART_RxHead==UART_RxTail)
//	{
//		return 0; //empty buffer
//	}
//
//	tmpTAIL=(UART_RxTail+1) & (UART_RX_BUFFER_SIZE-1);
////	if (tmpTAIL==UART_RxHEAD)
////	{
////		return _BV(8);//error
////	}
//	UART_RxTail=tmpTAIL;
//
//	return UART_RxBuf[UART_RxTail];
//
//
//
//}

/*void uart_gets(const char * s)
{
	while (*s)
	{
		unsigned int tmpChar;
		if (tmpChar>>8)
			return;
		()*s) = uart_getc();
	}


}*/

//Sending Interrupt
ISR(USART_UDRE_vect)
{
	//Write UART_TxBuf
	/*************************************************************************
	Function: UART Data Register Empty interrupt
	Purpose:  called when the UART is ready to transmit the next byte
	**************************************************************************/

	unsigned char tmptail;

	if ( UART_TxHead != UART_TxTail) //sending soft buffer has stuff
	{
		/* calculate and store new buffer index */
		tmptail = (UART_TxTail + 1) & (UART_TX_BUFFER_SIZE-1);
		UART_TxTail = tmptail;
		/* get one byte from buffer and write it to UART */
		UDR = UART_TxBuf[tmptail];  /* start transmission */
	}
	else{
		/* tx buffer empty, disable UDRE interrupt */
		UCSRB &= ~_BV(UDRIE);
	}


}


//Receiving Interrupt
ISR(USART_RXC_vect)
{
//
///*************************************************************************
//Function: UART Receive Complete interrupt
//Purpose:  called when the UART has received a character
//**************************************************************************/
//
//	unsigned char tmphead;
//	unsigned char data;
//	//unsigned char usr;
//	//unsigned char lastRxError;
//
//
//	/* read UART status register and UART data register */
//	//usr  = UART0_STATUS;
//	data = UDR;
//
//
//	/* calculate buffer index */
//	tmphead = ( UART_RxHead + 1) & (UART_RX_BUFFER_SIZE-1);
//
//	//if ( tmphead == UART_RxTail ) {
//	//	/* error: receive buffer overflow */
//	//	lastRxError = UART_BUFFER_OVERFLOW >> 8;
//	//}else{
//		/* store new index */
//		UART_RxHead = tmphead;
//		/* store received data in buffer */
//		UART_RxBuf[tmphead] = data;
//	//}
//	//UART_LastRxError = lastRxError;
//


}

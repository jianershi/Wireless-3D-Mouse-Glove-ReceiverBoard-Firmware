/*
 * main.c
 *
 *  Created on: Nov 18, 2011
 *      Author: Paul Shi
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <avr/pgmspace.h>
#include "nrf24l01p.h"
#include "spi.h"
#include <alloca.h>


void (*reset)(void);


int main(){

	reset=NULL;


//Initializing UART
 uart_init(375000,USE_1X); //set uart baud rate to 500K=500000

//Initializing SPI
 SPI_Init(D2,MSB,Rising,Leading);

//Initializing NRF24L01P
NRF24L01P_Init(NRF24L01P_mProperty);



 sei(); //enable global interrupt





 while(1)
 {

 }

//program should never be here




 return 0;
}

//External Interrupt 1
ISR(INT1_vect)
{
	uint8_t ucTmp3;
	uint8_t * m_pucBuff;
	CEDown();
	 // new data available in the RX FIFO, MCU setit self to Stand-by I mode

	WriteReg(STATUS, 0x7E); // clear the interrupt bit


		ucTmp3 = NOP;

		CMD_2(R_RX_PL_WID, &ucTmp3, 1, &ucTmp3); // read the length of the package

		if (ucTmp3>32)
		{
			CMD(FLUSH_RX);
			WriteReg(STATUS, 0x7E); // clear the interrupt bit
			return;
		}

		//m_pucBuff = (uint8_t*) malloc((ucTmp3+1) * sizeof(uint8_t));
		m_pucBuff = (uint8_t*) alloca((ucTmp3+1) * sizeof(uint8_t));
		// allocate the space for the received data
		if (m_pucBuff==NULL) //alocation fail
			{
				CMD(FLUSH_RX);
				WriteReg(STATUS, 0x7E);
				(*reset)();
			}

		//

		CMD_2(R_RX_PAYLOAD, m_pucBuff, ucTmp3, m_pucBuff); // read the received data from the RX FIFO


		CEUp(); //return to RTX mode

		m_pucBuff[ucTmp3]='\0';


		uart_puts((const char *)m_pucBuff);

		//free (m_pucBuff);



}

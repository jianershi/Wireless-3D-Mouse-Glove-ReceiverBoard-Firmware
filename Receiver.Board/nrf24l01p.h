/*------------------------------------------//
 File Name: Wireless2.4GHz.h
 Established: 2011/3/4
 Written by Gong Zhangxiaowen(Andygongyb)
 E-Mail: andygongyb@gmail.com
 distributed under GPL
 Modified by Jianer Shi 11/19/2011
 //------------------------------------------*/
#ifndef NRF24L01P_H_
#define NRF24L01P_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
//#include <inttypes.h>
#include <stdint.h>

#include <alloca.h>
#include <util/delay.h>
//#include "DataBlock.h"
#include "spi.h"
//#include "Utility.h"
//#include "Stream.h"
#include <string.h>

#define CONFIG		0x00
#define EN_AA		0x01
#define EN_RXADDR	0x02
#define SETUP_AW	0x03
#define SETUP_RETR	0x04
#define RF_CH		0x05
#define RF_SETUP	0x06
#define STATUS		0x07
#define OBSERVE_TX	0x08
#define PRD			0x09
#define RX_ADDR_P0	0x0A
#define RX_ADDR_P1	0x0B
#define RX_ADDR_P2	0x0C
#define RX_ADDR_P3	0x0D
#define RX_ADDR_P4	0x0E
#define RX_ADDR_P5	0x0F
#define TX_ADDR		0x10
#define RX_PW_P0	0x11
#define RX_PW_P1	0x12
#define RX_PW_P2	0x13
#define RX_PW_P3	0x14
#define RX_PW_P4	0x15
#define RX_PW_P5	0x16
#define FIFO_STATUS	0x17
#define DYNPD		0x1C
#define FEATURE		0x1D

#define MASK_RX_DR	6
#define MASK_TX_DS	5
#define MASK_MAX_RT	4
#define EN_CRC		3
#define CRCO		2
#define PWR_UP		1
#define PRIM_RX		0
#define ENAA_P5		5
#define ENAA_P4		4
#define ENAA_P3		3
#define ENAA_P2		2
#define ENAA_P1		1
#define ENAA_P0		0
#define ERX_P5		5
#define ERX_P4		4
#define ERX_P3		3
#define ERX_P2		2
#define ERX_P1		1
#define ERX_P0		0
#define AW			0
#define ARD			4
#define ARC			0
#define CONT_WAVE	7
#define RF_DR_LOW	5
#define PLL_LOCK	4
#define RF_DR_HIGH	3
#define RF_PWR1		2
#define RF_PWR0		1
#define RX_DR		6
#define TX_DS		5
#define MAX_RT		4
#define TX_REUSE	6
#define TX_FULL		5
#define TX_EMPTY	4
#define RX_FULL		1
#define RX_EMPTY	0
#define EN_DPL		2
#define EN_ACK_PAY	1
#define EN_DYN_ACK	0

#define PLOS_CNT_MASK	0xF0
#define ARC_CNT_MASK	0x0F

#define R_REGISTER		0x00
#define W_REGISTER		0x20
#define REGISTER_MASK	0x1F
#define RX_P_NO			0x0E
#define R_RX_PAYLOAD	0x61
#define W_TX_PAYLOAD	0xA0
#define R_RX_PL_WID		0x60
#define W_ACK_PAYLOAD	0xA8
#define FLUSH_TX		0xE1
#define FLUSH_RX		0xE2
#define REUSE_TX_PL		0xE3
#define NOP				0xFF


#define NRF24L01P_CE_PORT	PORTC
#define NRF24L01P_CE_PIN	PC0
#define NRF24L01P_CE_DDR	DDRC

#define NRF24L01P_IRQWRONG_PORT	PORTC
#define NRF24L01P_IRQWRONG_PIN	PC1
#define NRF24L01P_IRQWRONG_DDR	DDRC

#define NRF24L01P_IRQ_PORT	PORTD
#define NRF24L01P_IRQ_PIN	PD3
#define NRF24L01P_IRQ_DDR	DDRD

#define NRF24L01P_CSN_PORT PORTB
#define NRF24L01P_CSN_PIN PB2



typedef struct {
	uint8_t ucCH;
	uint8_t pucAddr[5];
} NRF24L01P_Property_t;

NRF24L01P_Property_t NRF24L01P_mProperty;



void CEDown(void);
void CEUp(void);
void Start_SS(void);
void Stop_SS(void);



void NRF24L01P_Init(NRF24L01P_Property_t NRF24L01P_mProperty);

//uint8_t *m_pucBuff;
//uint8_t m_ucLen;
//uint8_t m_ucPipeID;
//Flag *m_peIfDone;

uint8_t CMD_2(uint8_t ucCMD, uint8_t *pucSend, uint8_t ucLen,
		uint8_t *pucReceive);

uint8_t CMD(uint8_t ucCMD);


//CChildData(uint8_t *pucBuff, uint8_t ucLen, Flag *peIfDone,
//		uint8_t ucPipeID) {
//	m_pucBuff = pucBuff;
//	m_ucLen = ucLen;
//	m_ucPipeID = ucPipeID;
//	m_peIfDone = peIfDone;
//	if (m_peIfDone)
//		*m_peIfDone = Pending;
//}


//	static volatile uint8_t *m_pucPORTCE;
//	static uint8_t m_ucPinCE;
//	static CWireless *m_pInstance; //only one instance allowed to run
//	static Property m_sProperty;
//	static CChildData *m_pTxQueueHead;
//	static CChildData *m_pTxQueueTail;
//	static CChildData *m_pRxQueueHead;
//	static CChildData *m_pRxQueueTail;
//	static volatile uint8_t m_ucFailureCount;
//	static volatile uint8_t m_ucTxQueueLength;
//	static volatile uint8_t m_ucRxQueueLength;


//	static CWireless *GetInstance(void) {
//		if (!m_pInstance) {
//			m_pInstance = new CWireless();
//		}
//		return m_pInstance;
//	}

	//void ChangePins(IOSet *psCSN, IOSet *psCE);
	void SetProperty(NRF24L01P_Property_t *psProperty);
//	void GetProperty(Property *psProperty) {
//		memcpy((void*) psProperty, (const void*) &m_sProperty, sizeof(Property));
//	}

//	virtual void PushString(const char *pcStr);
//
//	virtual void PushHex(uint8_t *pucData, uint8_t ucLen) {
//		AddToQueue(pucData, ucLen);
//	}
//
//	uint16_t AddToQueue(uint8_t *pucBuff, uint8_t ucLen,
//			Flag *peIfDone = NULL);
//	uint8_t GetFromQueue(uint8_t *&pucBuff);
//

	uint8_t ReadReg(uint8_t ucAddr, uint8_t *pucData);
//	uint8_t ReadReg(uint8_t ucAddr, uint8_t *pucBuff, uint8_t ucLen) {
//		for (uint8_t i = 0; i < ucLen; i++)
//			*(pucBuff + i) = NOP; // set the data in the buffer to NOP to prevent malfunction
//		return CMD(R_REGISTER | (REGISTER_MASK & ucAddr), pucBuff, ucLen,
//				pucBuff);
//	}
	uint8_t WriteReg(uint8_t ucAddr, uint8_t ucData);
	uint8_t WriteReg_2(uint8_t ucAddr, uint8_t *pucBuff, uint8_t ucLen);
	void ChangeAddr(uint8_t *pucAddr);


//	uint8_t FlushRxQueue(void);
//
//	uint8_t GetFailureCount(void) {
//		return m_ucFailureCount;
//	}
//
//	uint8_t ResetFailureCount(void) {
//		uint8_t ucTmp = m_ucFailureCount;
//		m_ucFailureCount = 0;
//		return ucTmp;
//	}
//
//	uint8_t GetTxQueueLength(void) {
//		return m_ucTxQueueLength;
//	}
//	uint8_t GetRxQueueLength(void) {
//		return m_ucRxQueueLength;
//	}




#endif /* NRF24L01P_H_ */

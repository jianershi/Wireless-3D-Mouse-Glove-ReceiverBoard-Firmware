#ifndef UART_H
#define UART_H

#include <stdint.h>
//#define UART_BAUD_SELECT(baud,cpu) ((cpu)/((baud)*16l)-1)
//#define UART_BAUD_SELECT_DOUBLE_SPEED(baud,cpu) (((cpu)/((baud)*8l)-1))

//#define UBRR_VALUE (8000000/(500000*16UL)-1)
#define UBRR_VALUE(BAUD) (F_CPU/(BAUD*16UL)-1)
#define UBRR_VALUE_DOUBLE_SPEED(BAUD) (F_CPU/(BAUD*16UL)-1)

/** Size of the circular receive buffer, must be power of 2 */
#ifndef UART_RX_BUFFER_SIZE
#define UART_RX_BUFFER_SIZE 10
#endif
/** Size of the circular transmit buffer, must be power of 2 */
#ifndef UART_TX_BUFFER_SIZE
#define UART_TX_BUFFER_SIZE 512
#endif

enum UART_SPEED_MODE{
	USE_1X,
	USE_2X
};

//enum UART_SPEED_MODE SendingSpeed=USE_1X;


void uart_init(uint32_t baud, enum UART_SPEED_MODE SendingSpeed);
void uart_putc(unsigned char data);
void uart_puts(const char *s );
//void uart_puts_p(const char *progmem_s);
//unsigned char uart_getc();




#endif //UART_H

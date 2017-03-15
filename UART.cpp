/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>

UART::UART(int br, int db, int pr, int sb)
:_baudrate(br), _databits(db), _parity(pr), _stopbits(sb){

	/*Set baud rate */
	UBRR0 = (F_CPU / (16ul * _baudrate)) - 1; //UBRR0 = 51;
	/*Enable receiver and transmitter*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (3<<UCSZ00);//= a setar: (1<<UCSZ01)|(1<<UCSZ00);
}

UART::~UART() {}

void UART::put(unsigned char data){
	/* Wait for empty transmit buffer */
	while( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

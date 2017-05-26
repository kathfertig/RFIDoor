/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

UART * UART::__singleton = 0;


UART::UART(unsigned long br, DataBits_t db, ParityBits_t pr, StopBits_t sb)
:_baudrate(br), _databits(db), _parity(pr), _stopbits(sb){

	if(__singleton) return;
	__singleton = this;

	// seta baudrate
	UBRR0 = (F_CPU / (16ul * _baudrate)) - 1; //UBRR0 = 51;
	//liga TX e RX
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<UDRIE0);


	//set databits
	if (_databits == DATABITS_9){
		UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (3 << UCSZ00); // read, modify e update
		UCSR0B = (UCSR0B & ~(1 << UCSZ02)) | (1 << UCSZ02); // read, modify e update
	}
	else
		UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (_databits << UCSZ00); // read, modify e update


	//set parity
	UCSR0C = (UCSR0C & ~(3 << UPM00)) | (_parity << UPM00); // read, modify e update

	//set stopbits
	/*unsigned char reg = UCSR0C; //read
	reg = (reg & ~(1 <<USBS0)) | (_stopbits<<USBS0);//modify --> primeiro zerei o registrador
	UCSR0C = reg //update*/

	UCSR0C = (UCSR0C & ~(1 << USBS0)) | (_stopbits << USBS0); // read, modify e update

	/* Set frame format: 8data, 2stop bit *///OLD
	//UCSR0C = (3<<UCSZ00);//= a setar: (1<<UCSZ01)|(1<<UCSZ00);

}

UART::~UART() {
	__singleton = 0;
}

void UART::put(unsigned char data){

	UCSR0B &= ~(1<<UDRIE0);
	_tx_fifo.push(data);
	UCSR0B |= (1<<UDRIE0);

}

unsigned char UART::get(){
	return _rx_fifo.pop();
}

void UART::puts(char* str){
	while(*str != '\0'){
		this->put(*str);
		str++;
	}
}

void UART::tx_handler() //interrupt service request handler
{
	UART * uart = self();
	if(uart->tx_has_data())
		UDR0 = uart->_tx_fifo.pop();
	else
		UCSR0B &= ~(1<<UDRIE0);

}

void UART::rx_handler() //interrupt service request handler
{
	UART * uart = self();
	uart->_rx_fifo.push(UDR0);

}

ISR(USART_UDRE_vect) {
	UART::tx_handler();
}

ISR(USART_RX_vect) {
	UART::rx_handler();
}

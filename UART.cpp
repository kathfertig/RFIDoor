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

	//set databits: read, modify e update
	if (_databits == DATABITS_9){
		UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (3 << UCSZ00);
		UCSR0B = (UCSR0B & ~(1 << UCSZ02)) | (1 << UCSZ02);
	}
	else
		UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (_databits << UCSZ00);

	//set parity: read, modify e update
	UCSR0C = (UCSR0C & ~(3 << UPM00)) | (_parity << UPM00);
	UCSR0C = (UCSR0C & ~(1 << USBS0)) | (_stopbits << USBS0);
}

UART::~UART() {
	__singleton = 0;
}

void UART::put(unsigned char data){
	UCSR0B &= ~(1<<UDRIE0); //desliga interrupção antes de colocar dado na fifo
	_tx_fifo.push(data);
	UCSR0B |= (1<<UDRIE0); //liga interrupção depois de colocar dado na fifo
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

#ifdef __AVR_ATmega2560__
ISR(USART0_RX_vect)
#else
ISR(USART_RX_vect)
#endif
{
	UART::rx_handler();
}

#ifdef __AVR_ATmega2560__
ISR(USART0_UDRE_vect)
#else
ISR(USART_UDRE_vect)
#endif
{
	UART::tx_handler();
}

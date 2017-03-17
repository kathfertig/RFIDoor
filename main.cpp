/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */


#include <util/delay.h>
#include <avr/io.h>
#include "UART.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

char pin_led = 3;
const unsigned char led_mask = (1<<pin_led);

char pin_bot = 4;
const unsigned char bot_mask = (1<<pin_bot);

unsigned long tempo = 1000;

UART uart(19200, UART::DATABITS_9, UART::PARITY_NONE, UART::STOPBITS_1); //chama o construtor automaticamente, antes mesmo de chegar na uart





void setup() {
	DDRB = (DDRB | led_mask) & ~bot_mask;
}

bool le_botao(){
	return (PINB & bot_mask);
}

void acende_led(){
	PORTB = PORTB | led_mask;
}
void apaga_led(){
	PORTB = PORTB & ~led_mask;
}

//loop botao-led
void loop() {
	uart.put(uart.get() + 1);
	if(le_botao()) {
		acende_led();
	}
	else apaga_led();
}


//loop pisca led
//void loop() {
//    acende_led();
//    _delay_ms (tempo);
//    apaga_led()printf("On\n");;
//    _delay_ms (tempo);
//}

int main(){

	setup();
	while(true)
		loop();
}




/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */


#include <util/delay.h>
#include <avr/io.h>
#include "UART.h"
#include "GPIO.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led = 11;
const int pin_bot = 12;

unsigned long tempo = 1000;

UART uart(//chama o construtor automaticamente, antes mesmo de chegar na uart
		19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot, GPIO::INPUT);


void setup() {}	//DDRB = (DDRB | led_mask) & ~bot_mask;

//loop botao-led
void loop() {
	led.set(botao.get());
}


int main(){
	setup();
	while(true)
		loop();
}

/*bool le_botao(){
	return botao.get();
	//return (PINB & bot_mask);
}

void acende_led(){
	led.set(1);
	//PORTB = PORTB | led_mask;
}
void apaga_led(){
	led.set(0);
	//PORTB = PORTB & ~led_mask;
}
*/


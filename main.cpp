/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */


#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led = 11;
const int pin_bot = 12;

unsigned long long tempo = 1000; //ms
unsigned long long fq = ((1/(tempo/1000))*1000);

UART uart(//chama o construtor automaticamente, antes mesmo de chegar na uart
		19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot, GPIO::INPUT);
Timer timer(fq);


void setup() {
	sei(); //inicializar/ativar as interrupções
};
	bool val_botao;
	char message[8];


//loop botao-led
void loop() {
	val_botao = botao.get();
	led.set(val_botao);
	//sprintf(message, "LED: %d\n", val_botao);
	//uart.puts(message);
	//_delay_ms(tempo);

	timer.delay(tempo);
	sprintf(message, "%d\n", timer.millis());
	uart.puts(message);

}


int main(){
	setup();
	while(true)
		loop();
}


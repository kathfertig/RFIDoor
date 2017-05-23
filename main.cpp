
 /*  * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 *      */


#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include "RFID.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led = 11;
const int pin_bot = 12;

unsigned long long tempo = 2000; //ms
unsigned long long fq = 1000000/tempo;


UART uart(//chama o construtor automaticamente, antes mesmo de chegar na uart
		19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot, GPIO::INPUT);
Timer timer(fq);
FIFO<8> fifo;
RFID ID_gen;

bool val_botao;
char message[8];
ID _id_teste;
unsigned long teste = 1210004925;


void setup() {
	sei(); //inicializar/ativar as interrupções
};

//loop botao-led
void loop() {
	val_botao = botao.get();
	led.set(val_botao);

	if(uart.rx_has_data()){
		uart.put(uart.get());
	}
}


int main(){
	setup();
	while(true)
		loop();
}

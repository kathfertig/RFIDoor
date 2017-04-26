
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


void setup() {
	sei(); //inicializar/ativar as interrupções
};
	bool val_botao;
	char message[8];
	char data = 'a';


//loop botao-led
void loop() {
	val_botao = botao.get();
	led.set(val_botao);
	//sprintf(message, "LED: %d\n", val_botao);
	//uart.put('a');
	if(uart.has_data())
		uart.put(uart.get() + 1);

	// TESTE DO TIMER = OK
	//timer.delay(tempo);
	//sprintf(message, "%lu\n", timer.millis());
	//uart.puts(message);

}


int main(){
	setup();
	while(true)
		loop();
}


// TESTE DA FIFO - OK
// * main.cpp
// *
// *  Created on: 15 de mar de 2017
// *      Author: arliones.hoeller

/*
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led = 11;
const int pin_bot = 12;


UART uart(19200, UART::DATABITS_8, UART::PARITY_NONE, UART::STOPBITS_1);
GPIO led(11, GPIO::OUTPUT);
GPIO botao(12, GPIO::INPUT);
Timer timer(1000);
bool val_botao;
char message[8];

void setup() {
	sei();
}

static const int MAX = 4;
typedef FIFO<MAX> MyFIFO;
MyFIFO fifo_test;

void loop() {
//	val_botao = botao.get();
//	led.set(val_botao);
//	timer.delay(1000);
//	sprintf(message, "%lu\n", timer.millis());
//	uart.puts(message);


	char x = 0, y = 0;

	uart.puts("Test 1: insert/remove 1.\r\n");
	fifo_test.clear();

	uart.puts("Push A. ");
	fifo_test.push('A');
	uart.puts(" => OK.\r\n");

	uart.puts("Pop: ");
	x = fifo_test.pop();
	uart.put(x);
	if(x == 'A') uart.puts(". => OK.\r\n");
	else uart.puts(". => NOK.\r\n");


	uart.puts("Test 2: insert/remove MAX.\r\n");
	fifo_test.clear();

	x = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("Push ");
		uart.put(x);
		uart.puts(". ");
		fifo_test.push(x);
		uart.puts(" => OK.\r\n");
		x++;
	}

	y = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("Pop: ");
		x = fifo_test.pop();
		uart.put(x);
		if(x == y) uart.puts(". => OK.\r\n");
		else uart.puts(". => NOK.\r\n");
		y++;
	}


	uart.puts("Test 3: remove from empty.\r\n");
	fifo_test.clear();

	for (int i = 0; i < MAX; i++) {
		uart.puts("Pop: ");
		fifo_test.pop();
		x = fifo_test.get_error();
		if(x == (char)MyFIFO::FIFO_ERROR_EMPTY) uart.puts(". => OK.\r\n");
		else uart.puts(". => NOK.\r\n");
	}

	uart.puts("Test 4: insert in full.\r\n");
	fifo_test.clear();

	x = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("Push ");
		uart.put(x);
		uart.puts(". ");
		fifo_test.push(x);
		uart.puts(" => OK.\r\n");
		x++;
	}

	uart.puts("Add extra item: ");
	fifo_test.push('X');
	x = fifo_test.get_error();
	if(x == (char)MyFIFO::FIFO_ERROR_FULL) uart.puts(". => OK.\r\n");
	else uart.puts(". => NOK.\r\n");

	y = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("Pop: ");
		x = fifo_test.pop();
		uart.put(x);
		if(x == y) uart.puts(". => OK.\r\n");
		else uart.puts(". => NOK.\r\n");
		y++;
	}

	_delay_ms(30000);
	//timer.delay(10000);
}

int main() {
	setup();
	while (true)
		loop();
}*/




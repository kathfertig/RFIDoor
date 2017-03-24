/*
 * Timer.cpp
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#include "Timer.h"
#include <avr/io.h>

Timer::Timer(Hertz freq) {

	TCCR0A = 0x00; //operação normal de contagem
	TCCR0B = 0x05; //dividindo o clock por 1024
	TIMSK0 = 0x01; //liga interrupção de overflow
	TCNT0 = 0xF0; //0xF0 - 16;
}

Timer::~Timer() {}

Milliseconds Timer::millis(){

	//versão básica(errada)
	return _ticks;
}
Microseconds Timer::micros(){
	return 1;
}

void Timer::delay(Milliseconds ms){

}
void Timer::udelay(Microseconds us){

}

void Timer::isr_handler(){
	TCNT0 = 0xF0;
	_ticks++;
}



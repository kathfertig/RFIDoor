/*
 * Timer.cpp
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long long Timer::_ticks = 0;
unsigned long long Timer::_us_ticks = 0;
unsigned long long Timer::_ms_ticks = 0;
unsigned int Timer::_count_timer=0;


Timer::Timer(Hertz freq) : _frequency(freq)
{

	TCCR0A = 0x00; //operação normal de contagem
	TIMSK0 = 0x01; //liga interrupção de overflow

	double f_timer;
	//lógica oara selecionar divisor
	if(freq <= 15000){
		TCCR0B = 0x05; //dividindo o clock por 1024
		f_timer = F_CPU/1024;
	}else if(freq <= 62000){
		TCCR0B = 0x04; //dividindo o clock por 256
		f_timer = F_CPU/256;
	}else if(freq <= 250000){
		TCCR0B = 0x03; //dividindo o clock por 64
		f_timer = F_CPU/64;
	}else if(freq <= 2000000){
		TCCR0B = 0x02; //dividindo o clock por 8
	}else{
		TCCR0B = 0x01;
	}
	//calcular ciclos de timer
	_count_timer = f_timer/freq;
	TCNT0 = 0xFF - _count_timer;
	//TCNT0 = 0xF0; //0xF0 - 16;
}

Timer::~Timer() {}

Milliseconds Timer::millis(){

	//versão básica(errada)
	return micros()/1000;
}
Microseconds Timer::micros(){
	return _us_ticks * _ticks;
}

void Timer::delay(Milliseconds ms){
	udelay(ms*1000);
}
void Timer::udelay(Microseconds us){
	while (micros() != us)
		micros();
}

void Timer::isr_handler() //interrupt service request handler
{
	TCNT0 = 0xFF-_count_timer;
	_ticks++;
}

ISR(TIMER0_OVF_vect) {
	Timer::isr_handler();
}



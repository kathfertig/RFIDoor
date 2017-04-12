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
unsigned long Timer::_count_timer;


Timer::Timer(Hertz freq) : _frequency(freq)
{

	TCCR0A = 0x00; //operação normal de contagem
	TIMSK0 = 0x01; //liga interrupção de overflow

	Hertz f_timer;
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
	//_count_timer = f_timer/freq;
	_count_timer = (f_timer*freq)/1000000;
	TCNT0 = 0xFF - _count_timer; //funciona
	//TCNT0 = 0xFF - 64; //funciona - old 0xF0;

	_us_ticks = (1000000*_count_timer)/f_timer;
}

Timer::~Timer() {}

Milliseconds Timer::millis(){
	return micros()/1000;
}
Microseconds Timer::micros(){
	//return _ticks; //funciona
	return _us_ticks * _ticks;
}

void Timer::delay(Milliseconds ms){
	udelay(ms*1000);
}
void Timer::udelay(Microseconds us){
	Microseconds start = micros();
	while (micros() - start <= us);

}

void Timer::isr_handler() //interrupt service request handler
{
	//TCNT0 = 0xF0; //funciona - old
	//TCNT0 = 0xFF - 64; //funciona - old
	TCNT0 = 0xFF -_count_timer; //funciona
	_ticks++;
}

ISR(TIMER0_OVF_vect) {
	Timer::isr_handler();
}



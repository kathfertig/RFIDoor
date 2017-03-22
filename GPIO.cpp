/*
 * GPIO.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: aluno
 */

#include "GPIO.h"

GPIO::GPIO(int pin, PortDirection_t dir) {
	//calcular a máscara
	// configurar DDR

	if (pin >= 8){
		_mask = (1<<(pin-8));
		_ddr = &DDRB;
		_pin = &PINB;
		_port = &PORTB;
	}
	else if ((pin<=7) && (pin>=0)){
		_mask = (1<<pin);
		_ddr = &DDRD;
		_pin = &PIND;
		_port = &PORTD;
	}
	if (dir == OUTPUT)
		*_ddr  = *_ddr | _mask;
	else // input
		*_ddr = *_ddr & ~_mask;
}

GPIO::~GPIO() {}

bool GPIO::get() {
	//ler do pin
	return (*_pin & _mask);
}

void GPIO::set(bool val){
	//escrever no port
	if (val == true) //PORTB = PORTB | led_mask;
	*_port  = *_port | _mask;
	else
	*_port  = *_port & ~_mask;
}

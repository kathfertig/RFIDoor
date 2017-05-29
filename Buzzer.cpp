/*
 * Buzzer.cpp
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#include "Buzzer.h"


Buzzer::Buzzer(int pin, Buzzer_t bz) : _buzzer_config(pin, GPIO::OUTPUT) {

	switch(bz){
	case _buzzer0:
		//configuração 0:
		_frequencia = 0;
		_tempo = 0;
		break;

	case _buzzer1:
		//configuração 1: 1 bip longo alto
		//_frequencia = 0;
		//_tempo = 0;
		break;

	case _buzzer2:
		//configuração 2: 1 bip longo baixo
		//_frequencia = 0;
		//_tempo = 0;
	break;

	case _buzzer3:
		//configuração 3: 3 bips curtos altos
		//_frequencia = 0;
		//_tempo = 0;
		break;

	case _buzzer4:
		//configuração 4: 3 bips curtos baixos
		//_frequencia = 0;
		//_tempo = 0;
	break;
	}
}

Buzzer::~Buzzer(){}

void Buzzer::aciona_config(){
	hertz val = (500000/(_frequencia));
	//long int t = _miliseconds*1000 / (1000/_frequencia);
	hertz t = (_tempo*50) / (val*2);

	for(long int i=0; i < t; i++){
		_buzzer_config.set(true);
		timer_aciona.udelay(val);
		_buzzer_config.set(false);
		timer_aciona.udelay(val);
	}
}


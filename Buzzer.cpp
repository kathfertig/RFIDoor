/*
 * Buzzer.cpp
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#include "Buzzer.h"


Buzzer::Buzzer(hertz frequencia, GPIO * buzzer, Timer * timer)
:_buzzer(buzzer), _frequencia(frequencia), _timer(timer), _tempo(0) {}

Buzzer::~Buzzer(){}

void Buzzer::aciona(hertz tempo){
	_tempo = tempo;
	hertz div = (500000/(_frequencia));
	hertz repete = (_tempo*50) / (div*2);

	for(long int i=0; i < repete; i++){
		_buzzer->set(true);
		_timer->udelay(div);
		_buzzer->set(false);
		_timer->udelay(div);
	}
}


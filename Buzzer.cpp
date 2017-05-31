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
	hertz val = (500000/(_frequencia));
	//long int t = _miliseconds*1000 / (1000/_frequencia);
	hertz t = (_tempo*50) / (val*2);

	for(long int i=0; i < t; i++){
		_buzzer->set(true);
		_timer->udelay(val);
		_buzzer->set(false);
		_timer->udelay(val);
	}
}


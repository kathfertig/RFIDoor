/*
 * Notify.h
 *
 *  Created on: 30 de mai de 2017
 *      Author: maedel
 */

#ifndef NOTIFY_H_
#define NOTIFY_H_

#include "Timer.h"
#include "GPIO.h"


class Notify {
public:
	Notify(Timer * timer):_timer(timer){}
	~Notify(){}

	void notify_acesso(GPIO * led/*, GPIO * buzzer, GPIO * rele_porta*/){
		//acender led verde, habilitar relé, 3 bips curtos do alta freq. buzzer
		int vezes = 3;
		for (int repete = 0; repete < vezes; repete++){
			//rele_porte->set(true);			//Ativa Rele
			//buzzer_acesso->set(true);
			led->set(true);
			_timer->delay(500);
			led->set(false);
			//buzzer_acesso->set(false);
			_timer->delay(500);
		}
	}

	void notify_sucesso(GPIO * led/*, GPIO * buzzer*/){
		//acender led verde, 1 bip longo alta freq. do buzzer
			//buzzer_sucesso->set(true);
			led->set(true);
			_timer->delay(1000);
	}

	void notify_warning(GPIO * led/*, GPIO * buzzer*/){
		//acender led vermelho, bip longo de baixa freq. do buzzer
		led->set(true);
		//buzzer_warning.set(true);
		_timer->delay(1000);
	}

private:
	Timer *_timer;
};

#endif /* NOTIFY_H_ */

/*
 * Notify.h
 *
 *  Created on: 30 de mai de 2017
 *      Author: maedel
 */

#ifndef NOTIFY_H_
#define NOTIFY_H_

#include "Timer.h"
#include "Buzzer.h"


class Notify {
public:
	Notify(Timer * timer):_timer(timer){}
	~Notify(){}

	void notify_acesso(GPIO * led, GPIO * rele_porta, Buzzer * buzzer_acesso){
		//acender led verde, habilitar relé, 1 bip longo do buzzer
		rele_porta->set(true);	//Ativa Rele
		led->set(true);
		buzzer_acesso->aciona(500);
		_timer->delay(500);

	}

	void notify_sucesso(GPIO * led, Buzzer * buzzer_sucesso){
		//acender led verde, 2 bips curtos do buzzer
		for (int repete = 0; repete < 2; repete++){
			led->set(true);
			buzzer_sucesso->aciona(200);
			led->set(false);
			_timer->delay(200);
		}
	}

	void notify_warning(GPIO * led, Buzzer * buzzer_warning){
		//acender led vermelho, 4 bips curtos e rápidos do buzzer
		for (int repete = 0; repete < 4; repete++){
			led->set(true);
			buzzer_warning->aciona(50);
			led->set(false);
			_timer->delay(50);
		}
	}

private:
	Timer *_timer;
};

#endif /* NOTIFY_H_ */

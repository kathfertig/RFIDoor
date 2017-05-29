/*
 * Buzzer.h
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "GPIO.h"
#include "Timer.h"

Timer timer_aciona(1000);
typedef long int hertz;

class Buzzer {
public:

	enum Buzzer_t{_buzzer0 = 0, _buzzer1 = 1, _buzzer2 = 2, _buzzer3 = 3, _buzzer4 = 4};

	Buzzer(int pin, Buzzer_t = _buzzer0);
	~Buzzer();

	//Buzzer(int pin,int freq, int miliseconds);
	void aciona_config();

private:
	GPIO _buzzer_config;
	hertz _frequencia;
	hertz _tempo;
};

#endif /* BUZZER_H_ */

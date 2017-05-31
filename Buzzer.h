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

typedef long int hertz;

class Buzzer {
public:
	static bool _play;
	Buzzer(hertz frequencia, GPIO * buzzer, Timer * timer);
	~Buzzer();

	void aciona(hertz tempo);

private:
	GPIO * _buzzer;
	Timer * _timer;
	hertz _frequencia;
	hertz _tempo;

};

#endif /* BUZZER_H_ */

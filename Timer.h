/*
 * Timer.h
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#ifndef TIMER_H_
#define TIMER_H_

	typedef unsigned long Hertz;
	typedef unsigned long long Microseconds;
	typedef unsigned long long Milliseconds;

class Timer {
public:

	Timer(Hertz freq);
	~Timer();

	Milliseconds millis();
	Microseconds micros();
	void delay(Milliseconds ms);
	void udelay(Microseconds us);

	static void isr_handler();


private:
	Hertz _frequency;
	static unsigned long _count_timer;
	static unsigned long long _ticks;
	static unsigned long long _us_ticks;
	static unsigned long long _ms_ticks;

};
#endif /* TIMER_H_ */

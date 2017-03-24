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
	typedef unsigned long long ulong64_t;
	static ulong64_t _ticks;

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


};
#endif /* TIMER_H_ */

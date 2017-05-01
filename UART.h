/*
 * UART.h
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#ifndef UART_H_
#define UART_H_
#include "FIFO.h"

class UART {
public:

	enum StopBits_t{ STOPBITS_1 = 0, STOPBITS_2 = 1};
	enum ParityBits_t{ PARITY_NONE = 0, PARITY_EVEN = 2, PARITY_ODD = 3};
	enum DataBits_t{
		DATABITS_5 = 0,
		DATABITS_6 = 1,
		DATABITS_7 = 2,
		DATABITS_8 = 3,
		DATABITS_9 = 7};

	UART(
		unsigned long br = 19200,
		DataBits_t db = DATABITS_8,
		ParityBits_t pr = PARITY_NONE,
		StopBits_t sb = STOPBITS_1);

	~UART();

	void put(unsigned char data);
	unsigned char get();
	void puts(char* str);
	bool rx_has_data() { return _rx_fifo.get_size() > 0; }
	bool tx_has_data() { return _tx_fifo.get_size() > 0; }
	static void tx_handler();
	static void rx_handler();

	static UART * self() { return __singleton; }
private:
	unsigned long _baudrate;
	DataBits_t _databits;
	ParityBits_t _parity;
	StopBits_t _stopbits;

	FIFO<4> _tx_fifo;
	FIFO<4> _rx_fifo;

	static UART * __singleton;
};

#endif /* UART_H_ */

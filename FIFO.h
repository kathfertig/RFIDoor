/*
 * FIFO.h
 *
 *  Created on: 31 de mar de 2017
 *      Author: aluno
 */

#ifndef FIFO_H_
#define FIFO_H_
//#include <iostream>
#include <string.h>

//using namespace std;

template <int Q_SIZE>
//#define Q_MAX (Q_SIZE-1)

class FIFO {
public:

	enum FIFO_ERROR_t{FIFO_ERROR_FULL = 1,
					  FIFO_ERROR_EMPTY = 2};

	FIFO() : _head(0), _tail(0), _size(0){}
	~FIFO(){}

	void push(char value){

		_tail++;
		if( _size == Q_SIZE) {
			_error_fifo = FIFO_ERROR_FULL;

		} else {
		_buffer[_tail-1] = value;
		/* update the tail */
			if (_tail == Q_SIZE){
				_tail = 0;
			}
			_size++;
			strcpy(_message, "PUSH OK!\n");
		}

	}
	char pop(){
		char returnval;
		_head++;
		if (_size == 0) {
			_error_fifo = FIFO_ERROR_EMPTY;

		} else {
			returnval = _buffer[_head-1];
			if (_head == Q_SIZE){
				_head = 0;
			}
			_size--;
			strcpy(_message, "POP OK!\n");

		}
		return  returnval;
	}

	int get_size(){
		return _size;
	}

	void clear() {//limpa FIFO
		_head = 0;
		_tail = 0;
		_size = 0;
	}

	/*char* get_message(){ //método para teste, indica sucesso de operação
		return _message;
	}*/

	/*int get_error(){ //método para teste, indica qualo erro gerado pela operação
		return _error_fifo;
	}*/

private:
	int _head, _tail, _size;
	char _buffer[Q_SIZE];
	char _message[16];
	FIFO_ERROR_t _error_fifo;
};

#endif /* FIFO_H_ */

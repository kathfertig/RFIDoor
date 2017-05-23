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
		//_tail = _tail % Q_SIZE;
		if( _size == Q_SIZE) {
			//_message = "FILA CHEIA!\n";
			_error_fifo = FIFO_ERROR_FULL;

		//if (((_tail+1) % Q_SIZE) == _head)	//perror("enqueue onto full queue",_tail);
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
			//_message = "FILA VAZIA!\n";
			_error_fifo = FIFO_ERROR_EMPTY;

		} else {
		//if (_head == _tail) //cout << "dequeue from empty queue"<< head << endl;//error("dequeue from empty queue",head);

			returnval = _buffer[_head-1];
			if (_head == Q_SIZE){
				_head = 0;
			}
			_size--;
			strcpy(_message, "POP OK!\n");

		}
		return  returnval;
	}

	char* get_message(){
		return _message;
	}

	int get_error(){
			return _error_fifo;
		}
	int get_size(){
			return _size;
		}

	void clear() {
		_head = 0;
		_tail = 0;
		_size = 0;
	}

private:
	int _head, _tail, _size;
	char _buffer[Q_SIZE];
	char _message[16];
	FIFO_ERROR_t _error_fifo;
};

#endif /* FIFO_H_ */

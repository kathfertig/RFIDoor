/*
 * FIFO.h
 *
 *  Created on: 31 de mar de 2017
 *      Author: aluno
 */

#ifndef FIFO_H_
#define FIFO_H_


template <int Q_SIZE>
#define Q_MAX (Q_SIZE-1)

class FIFO {
public:
	FIFO() : _head(0), _tail(0){

	}
	~FIFO(){}

	void push(char value){
		if (((_tail+1) % Q_SIZE) == _head){
			//perror("enqueue onto full queue",_tail);
			}
		_buffer[_tail] = value;
		/* update the tail */
		if (_tail == Q_MAX){
			_tail = 0;
		}else{
			_tail++;}

	}
	char pop(){
		char returnval;
		if (_head == _tail){ //error("dequeue from empty queue",head);

		}
		returnval = _buffer[_head];
		if (_head == Q_MAX)
			_head = 0;
		else
			_head++;
		return  returnval;
	}

private:
	int _head, _tail;
	char _buffer[Q_SIZE];

};

#endif /* FIFO_H_ */

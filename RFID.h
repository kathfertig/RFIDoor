/*
 * RFID.h
 *
 *  Created on: 10 de mai de 2017
 *      Author: maedel
 */

#ifndef RFID_H_
#define RFID_H_
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#if RAND_MAX/256 >= 0xFFFFFFFFFF //número máximo gerado com 40 bits
  #define LOOP_COUNT 1
#elif RAND_MAX/256 >= 0xFFFFFF
  #define LOOP_COUNT 2
#elif RAND_MAX/256 >= 0x3FFFF
  #define LOOP_COUNT 3
#elif RAND_MAX/256 >= 0x1FF
  #define LOOP_COUNT 4
#else
  #define LOOP_COUNT 5
#endif

typedef unsigned long long id_mat;

class RFID {
public:
	RFID();
	RFID(id_mat min, id_mat max);
	~RFID();

	id_mat random_id(){
		id_mat r = 0;
		for (int i=LOOP_COUNT; i > 0; i--){
			r = r*(RAND_MAX + (id_mat)1) + rand();
		}
		return r;
		//return ( rand() % ( _max - _min + 1 ) ) + _min;
	}

private:
	id_mat _min;
	id_mat _max;
};

#endif /* RFID_H_ */

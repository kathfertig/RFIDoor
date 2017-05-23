/*
 * RFID.cpp
 *
 *  Created on: 10 de mai de 2017
 *      Author: maedel
 */

#include "RFID.h"

RFID::RFID() {
	_min = 0;
	_max = 2^40;
}

RFID::RFID(ID min, ID max) {
	_min = min;
	_max = max;
}

RFID::~RFID() {}

ID RFID::random_id(){

	return ( rand() % ( _max - _min + 1 ) ) + _min;
}




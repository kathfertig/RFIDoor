/*
 * RFID.cpp
 *
 *  Created on: 10 de mai de 2017
 *      Author: maedel
 */

#include "RFID.h"

RFID::RFID() {//inicialização do construtor para geração de nº randômicos de 40 bits
	_min = 2^39;
	_max = 2^40;
}

RFID::RFID(id_mat min, id_mat max) {
	_min = min;
	_max = max;
}

RFID::~RFID() {}






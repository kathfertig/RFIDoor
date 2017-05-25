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

typedef uint64_t n_id;

class RFID {
public:
	RFID();
	RFID(n_id min, n_id max);
	~RFID();

	n_id random_id();

private:
	n_id _min;
	n_id _max;
};

#endif /* RFID_H_ */

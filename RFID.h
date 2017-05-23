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

typedef uint64_t ID;

class RFID {
public:
	RFID();
	RFID(ID min, ID max);
	~RFID();

	ID random_id();

private:
	ID _min;
	ID _max;
};

#endif /* RFID_H_ */

/*
 * LOG.h
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#ifndef LOG_H_
#define LOG_H_
#include <avr/io.h>
//#include <time.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//typedef char * _lista_logs;

class LOG {
public:
	LOG();
	~LOG();

	//bool insere_log(char * new_reg);
	//void limpa_logs();
	/*int get_tam_atual(){ //retorna o tam. atual da lista, ie, o nº de users cadastrados na lista
		//return _tamanho;
		return sizeof(lista);
	}*/
	//char * get_log(int p);


private:

	//_lista_logs lista[256];
	//int _tamanho;

};

#endif /* LOG_H_ */

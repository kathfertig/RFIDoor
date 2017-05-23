/*
 * ID.h
 *
 *  Created on: 10 de mai de 2017
 *      Author: maedel
 */

#ifndef ID_H_
#define ID_H_
#include <avr/io.h>
#include "FIFO.h"
#include <stdlib.h>
#include <stdio.h>

/*Classe teste responsável por fazer verificação de usuário,
fazer teste temporário de gerar ID de entrada do sistema enquanto não há a leitura do RFID,
liberar acesso se o valor já for cadastrado no sistema.*/

typedef uint64_t id;


class ID {
public:
	ID();
	~ID();

	int verifica(id id_in);
	bool cadastra(id id_in);
	bool remove(id id_in);
	int get_tam_lista(){
		return sizeof(_lista_IDs);
		}
	void limpa_lista();

	//ID random_id();


private:
	id _lista_IDs[10];

};
#endif /* ID_H_ */

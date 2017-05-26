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
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define T_MAX 10
/*Classe teste responsável por fazer verificação de usuário,
fazer teste temporário de gerar ID de entrada do sistema enquanto não há a leitura do RFID,
liberar acesso se o valor já for cadastrado no sistema.*/

//typedef uint64_t id_mat; //Definindo novo dado do tipo id de matrícula
typedef unsigned long long id_mat;
//uint64_t é equivalente a long long int. (%lld)


class ID {
public:
	ID();
	~ID();

	int verifica(id_mat  id_in);
	bool cadastra(id_mat  id_in);
	bool remove(id_mat  id_in);
	int get_tam_atual(){ //retorna o tam. atual da lista, ie, o nº de users cadastrados na lista
		return _n_users;
		}
	id_mat busca(int posicao){
		return _lista_IDs[posicao];
	}
	bool lista_cheia(){
		return (get_tam_atual() == T_MAX);
	}
	void limpa_lista();

	char* get_id64(id_mat & id, bool endline = false);


	//ID random_id();


private:
	id_mat _lista_IDs[T_MAX];
	int _n_users;

};
#endif /* ID_H_ */

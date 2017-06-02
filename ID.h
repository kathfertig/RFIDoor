/*
 * ID.h
 *
 *  Created on: 10 de mai de 2017
 *      Author: maedel
 */

#ifndef ID_H_
#define ID_H_
#include <avr/io.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define T_MAX 10

typedef unsigned long long id_mat;

class ID {
public:
	ID();
	~ID();

	int verifica(id_mat  id_in); //percorre lista de cadastros para verificar se ID de entrada já está cadastrado
	int cadastra(id_mat  id_in); //cadastra ID de entrada se ainda não cadastrado
	int get_tam_atual(){ //retorna o tam. atual da lista, ie, o nº de users cadastrados na lista
		return _n_users;
		}
	void limpa_lista();
	id_mat busca(int posicao){ //método para teste, busca determinado ID
		return _lista_IDs[posicao];
	}

	//int remove(id_mat  id_in); //remove único ID

	/*bool lista_cheia(){ //método para teste, vê se lista está cheia
			return (get_tam_atual() == T_MAX);
		}*/


private:
	id_mat _lista_IDs[T_MAX];
	int _n_users;

};
#endif /* ID_H_ */

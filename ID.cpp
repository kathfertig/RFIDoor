/*
 * ID.cpp
 *
 *  Created on: 10 de mai de 2017
 *      Author: maedel
 */

#include "ID.h"

ID::ID() {}

ID::~ID() {}

int ID::verifica(id id_in){
	// Busca um elemento num vetor
	// Devolve a posição do elemento encontrado, caso tenha sucesso na busca
	// Retorna -1, caso não encontre
	//int busca (int x, ficha lista[], int n){
    int indice=-1, i=0;
    int n = get_tam_lista();

    while(i<n){
       if(this->_lista_IDs[i] == id_in){
          indice = i;
          i = n;
       }
       else
         i++;
    }
    return indice;
}

bool ID::cadastra(id id_in){
	int n = get_tam_lista();
	if ( verifica(id_in) == -1 ){ // se sim, elemento não encontrado. Pode inserir
		this->_lista_IDs[n]=id_in;
		return true;
	}else
	    return false;
}
//https://www.vivaolinux.com.br/script/Busca-insercao-e-remocao-de-elementos-numa-lista





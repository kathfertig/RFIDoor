/*
 * ID.cpp
 *
 *  Created on: 10 de mai de 2017
 *      Author: maedel
 */

#include "ID.h"

ID::ID() : _n_users(0){}

ID::~ID(){}

int ID::verifica(id_mat id_in){
    int index=-1, i=0;
    //int n = T_MAX;

    while(i<T_MAX){
       if(this->_lista_IDs[i] == id_in){
          index = i;
          i = T_MAX;
       }
       else
         i++;
    }
    return index;
}

int ID::cadastra(id_mat id_in){
	//int n = T_MAX;
	bool ret;
	if (verifica(id_in) == (-1)){ // se sim, elemento não encontrado. Pode inserir
		this->_lista_IDs[_n_users]=id_in;
		_n_users++;
		ret = 1;
	}else {
	    ret = 0;
	}
	return ret;
}

int ID::remove(id_mat id_in){

     int index = verifica(id_in);
     int ret;
     if(index == (-1)){
    	 ret = 0;
     }else{
    	 for(int i=index;i<T_MAX-1;i++){
    	   	 _lista_IDs[i]=_lista_IDs[i+1];
    	 }
    	 _n_users--;
    	 ret = 1;
     }
    return ret;
}

void ID::limpa_lista(){
	for (int i=0; i< T_MAX; i++) {
		memset(&_lista_IDs[i], 0, 40);
	}
}





//https://www.vivaolinux.com.br/script/Busca-insercao-e-remocao-de-elementos-numa-lista





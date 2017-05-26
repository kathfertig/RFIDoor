/*
 * LOG.cpp
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#include "LOG.h"

LOG::LOG() /*: _tamanho(0)*/ {}

LOG::~LOG() {}




/*bool LOG::insere_log(char * new_reg) {

	int tam = get_tam_atual(); // pega tamanho antes da inserção

	for (int i=get_tam_atual(); i < tam; i++){
		lista[i] = new_reg;
		_tamanho++;
	}

	if(tam < get_tam_atual()) { // se tam < tam_atual, significa que inseriu
		return true;
	} else
		return false;
}*/


/*void LOG::limpa_logs() {

	if (get_tam_atual()==256) { //A lista de logs só será totalmente zerada depois da produção de mais de 1024 linhas de log
		for (int i=0; i< get_tam_atual(); i++) {
				memset(&lista[i], 0, 256);
		}
	}
}*/

/*char * LOG::get_log(int p) {
	char * buffer = lista[p];
	return &buffer[0];
}*/


/*
 * LOG.cpp
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#include "LOG.h"

LOG::LOG(UART *uart, Timer *pausa):_uart_log(uart),_pausa(pausa){
	//memset(&_message, '\0', 40);
}

LOG::~LOG() {}


void LOG::get_id64(id_mat & id, bool endline){
	    char buffer[32];
	    union {
	        unsigned long long ull;
	        unsigned long ul[2];
	        unsigned short us[4];
	        unsigned char uc[8];
	    } rfid64;
	    rfid64.ull = id;

	    if (endline)
	        sprintf(buffer, "%04x %04x %04x %04x\r\n", rfid64.us[3], rfid64.us[2],
	                rfid64.us[1], rfid64.us[0]);
	    else
	        sprintf(buffer, "%lu%lu", rfid64.ul[0], rfid64.ul[1]);
	    _uart_log->puts(buffer);
}

void LOG::print_N_users(int n_users){
	sprintf(_message, "No de usuarios cadastrados no sistema: %d\n",n_users); //n_users = _id_teste.get_tam_atual()
	_uart_log->puts(_message);
	_pausa->delay(500);
}

void LOG::print_cadastra(id_mat id){ //método que informa o cadastro de IDs
	sprintf(_message, "Cadastrando ID: ");
	_uart_log->puts(_message);
	get_id64(id);
	endline();
	_pausa->delay(500);
}

void LOG::print_verifica(id_mat id){ //método que informa a verificação de IDs
	sprintf(_message, "Verificando ID: ");
	_uart_log->puts(_message);
	get_id64(id);
	endline();
	_pausa->delay(500);
}

void LOG::print_remove(id_mat id){ //método que informa a verificação de IDs
	sprintf(_message, "Removendo ID: ");
	_uart_log->puts(_message);
	get_id64(id);
	endline();
	_pausa->delay(500);
}

void LOG::print_resultado(int retorno_operacao){
	if (retorno_operacao > 0){
		sprintf(_message, "Operacao realizada com sucesso. Retorna: %d.\n",retorno_operacao);
	}else{
		sprintf(_message, "Operacao nao pode ser finalizada com sucesso. Retorna: %d.\n",retorno_operacao);
	}
	_uart_log->puts(_message);
	_pausa->delay(500);
}

void LOG::print_IDs(ID lista_ids){
	id_mat retorno;
	for(int i=0; i<lista_ids.get_tam_atual(); i++) {
		sprintf(_message, "ID%d: ", i+1);
		_uart_log->puts(_message);
		retorno = lista_ids.busca(i);
		get_id64(retorno);
		endline();
		_uart_log->puts(_message);
		_pausa->delay(500);
	}
}

void LOG::print_limpa_lista(int tam_lista, ID lista_ids){
	if(tam_lista>0){
		sprintf(_message, "Limpando lista de IDs: ");
		_uart_log->puts(_message);
		print_IDs(lista_ids);
		_pausa->delay(500);
	}else{
		sprintf(_message, "Lista ja esta vazia.\n");
		_uart_log->puts(_message);
		_pausa->delay(500);
	}
}

void LOG::print_acesso(id_mat id){
	sprintf(_message, "Novo ID tentando acesso: ");
	_uart_log->puts(_message);
	get_id64(id);
	endline();
	_pausa->delay(500);
}

void LOG::print_libera(int retorno_operacao){
	if(retorno_operacao >= 0){
		sprintf(_message, "ID cadastrado. Liberando acesso.\n");
	}else
		sprintf(_message, "ID sem cadastro.\n");
	_uart_log->puts(_message);
	_pausa->delay(500);
}

void LOG::instrucoes(){
	sprintf(_message, "Insira o seu cartao e:\n");
	_uart_log->puts(_message);
	sprintf(_message, "1) Para abrir porta aperte o botao 1;\n");
	_uart_log->puts(_message);
	sprintf(_message, "2) Para cadastrar ID aperte o botao 2;\n");
	_uart_log->puts(_message);
	sprintf(_message, "3) Para remover ID aperte o botao 3;\n");
	_uart_log->puts(_message);
	_pausa->delay(500);
}

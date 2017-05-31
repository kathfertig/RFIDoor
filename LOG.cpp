/*
 * LOG.cpp
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#include "LOG.h"

LOG::LOG(UART *uart, Timer *timer):_uart_log(uart),_timer(timer), _tempo_decorr(0){
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
	    delay_padrao();
}

void LOG::print_N_users(int n_users){
	tempo_decorrido();
	sprintf(_message, "No de usuarios cadastrados no sistema: %d\n",n_users); //n_users = _id_teste.get_tam_atual()
	_uart_log->puts(_message);
	endline();
	delay_padrao();
}

void LOG::print_cadastra(id_mat id){ //método que informa o cadastro de IDs
	tempo_decorrido();
	sprintf(_message, "Cadastrando ID: ");
	_uart_log->puts(_message);
	get_id64(id,0);
	endline();
	delay_padrao();
}

void LOG::print_verifica(id_mat id){ //método que informa a verificação de IDs
	tempo_decorrido();
	sprintf(_message, "Verificando ID: ");
	_uart_log->puts(_message);
	get_id64(id,0);
	endline();
	delay_padrao();
}

void LOG::print_remove(id_mat id){ //método que informa a verificação de IDs
	tempo_decorrido();
	sprintf(_message, "Removendo ID: ");
	_uart_log->puts(_message);
	get_id64(id,0);
	endline();
	delay_padrao();
}

void LOG::print_sucesso(){
	tempo_decorrido();
	sprintf(_message, "Operacao realizada com sucesso.\n");
	_uart_log->puts(_message);
	delay_padrao();
}

void LOG::print_fracasso(){
	tempo_decorrido();
	sprintf(_message, "Falha na operacao.\n");
	_uart_log->puts(_message);
	delay_padrao();
}

void LOG::print_warning(){
	tempo_decorrido();
	sprintf(_message, "Operacao invalida.\n");
	_uart_log->puts(_message);
	delay_padrao();
}

void LOG::print_IDs(ID lista_ids){
	tempo_decorrido();
	id_mat retorno;
	for(int i=0; i<lista_ids.get_tam_atual(); i++) {
		sprintf(_message, "ID%d: ", i+1);
		_uart_log->puts(_message);
		retorno = lista_ids.busca(i);
		get_id64(retorno,0);
		endline();
		delay_padrao();
	}
}

void LOG::print_limpa_lista(int tam_lista, ID lista_ids){
	tempo_decorrido();
	if(tam_lista>0){
		sprintf(_message, "Limpando lista de IDs: ");
		_uart_log->puts(_message);
		print_IDs(lista_ids);
		delay_padrao();
	}else{
		sprintf(_message, "Lista ja esta vazia.\n");
		_uart_log->puts(_message);
		delay_padrao();
	}
}

void LOG::print_acesso(id_mat id){
	tempo_decorrido();
	sprintf(_message, "Novo ID tentando acesso: ");
	_uart_log->puts(_message);
	get_id64(id,0);
	endline();
	delay_padrao();
}

void LOG::print_libera(int retorno_operacao){
	tempo_decorrido();
	if(retorno_operacao >= 0){
		sprintf(_message, "ID cadastrado. Liberando acesso.\n");
	}else
		sprintf(_message, "ID sem cadastro.\n");
	_uart_log->puts(_message);
	delay_padrao();
}

void LOG::instrucoes(){
	tempo_decorrido();
	sprintf(_message, "Insira o seu cartao e:\n");
	_uart_log->puts(_message);
	sprintf(_message, "1) Para abrir porta aperte o botao 1;\n");
	_uart_log->puts(_message);
	sprintf(_message, "2) Para cadastrar ID aperte o botao 2;\n");
	_uart_log->puts(_message);
	sprintf(_message, "3) Para remover ID aperte o botao 3;\n");
	_uart_log->puts(_message);
	delay_padrao();
	delay_padrao();
}

void LOG::tempo_decorrido(){
	_tempo_decorr = _timer->millis();
	get_id64(_tempo_decorr,0);
	sprintf(_message, "ms: ");
	_uart_log->puts(_message);
	delay_padrao();
}

/*
 * LOG.h
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#ifndef LOG_H_
#define LOG_H_

#include <avr/io.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "ID.h"
#include "Timer.h"


class LOG {
public:

	LOG(UART *uart, Timer *timer);
	~LOG();


	void get_id64(id_mat & id, bool endline = false); //mostra um ID de tam. 64 bits

	void print_acesso(id_mat id); //mostra operação de tentativa de acesso
	void print_cadastra(id_mat id); //mostra operação de tentativa de cadastro
	void print_verifica(id_mat id); //mostra operação de verificação de ID no sistema
	void print_IDs(ID *lista_ids); //mostra todos os ID cadastrados
	void print_libera(int retorno_operacao); //indica liberação de acesso ou não
	void print_limpa_lista(int tam_lista, ID *lista_ids); //mostra operação de tentativa de limpeza de cadastros
	void print_sucesso(); //indica sucesso de operação
	void print_fracasso(); //indica fracasso de operação
	void print_warning();  //indica alerta de operação inválida
	void tempo_decorrido(); //mostra "Timestamp" do sistema e tempo decorrido desde inicialização do sistema para cada operação realizada

	void delay_padrao(){ //método de delay padrão para os logs
		_timer->delay(10);

	};
	void endline(){ //pula linha na serial para novo log
		sprintf(_message, ".\n");
		_uart_log->puts(_message);
	}

	//void print_remove(id_mat id); //mostra operação de tentativa de remoção de ID
	//void instrucoes();//para implementação futura com adição de display ao sistema
	//void print_N_users(int n_users); //mostra a quantidade de IDs cadastrado

private:
	char _message[40];
	UART * _uart_log;
	Timer * _timer;
	ID *_lista_IDs;
	unsigned long long _tempo_decorr;

};

#endif /* LOG_H_ */

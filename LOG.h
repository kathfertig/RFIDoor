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


	void get_id64(id_mat & id, bool endline = false); //método para mostrar ID de tam. 64 bits
	void instrucoes();
	void print_N_users(int n_users);
	void print_acesso(id_mat id);
	void print_cadastra(id_mat id);
	void print_verifica(id_mat id);
	void print_remove(id_mat id);
	void print_IDs(ID lista_ids);
	void print_libera(int retorno_operacao);
	void print_limpa_lista(int tam_lista, ID lista_ids);
	void print_sucesso();
	void print_fracasso();
	void print_warning();
	void tempo_decorrido();


	void delay_padrao(){
		_timer->delay(10);
			//método de delay padrão para os logs
	};
	void endline(){
		sprintf(_message, ".\n");
		_uart_log->puts(_message);
	}

private:
	char _message[40];
	UART * _uart_log;
	Timer * _timer;
	unsigned long long _tempo_decorr;

};

#endif /* LOG_H_ */

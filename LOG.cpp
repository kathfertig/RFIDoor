/*
 * LOG.cpp
 *
 *  Created on: 26 de mai de 2017
 *      Author: maedel
 */

#include "LOG.h"

LOG::LOG(){
	//_uart_log =_uart;
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
	    _uart_log.puts(_message);
}

void LOG::print_N_users(int n_users){
	sprintf(_message, "No de usuarios cadastrados no sistema: %d\n",n_users); //n_users = _id_teste.get_tam_atual()
	_uart_log.puts(_message);
	//pausa.delay(500);
}

void LOG::print_cadastra(id_mat id){ //método que informa o cadastro de IDs
	sprintf(_message, "Cadastrando ID: ");
	_uart_log.puts(_message);
	get_id64(id);
	endline();
	//pausa.delay(500);
}

void LOG::print_verifica(id_mat id){ //método que informa a verificação de IDs
	sprintf(_message, "Verificando ID: ");
	_uart_log.puts(_message);
	get_id64(id);
	endline();
	//pausa.delay(500);
}

void LOG::print_remove(id_mat id){ //método que informa a verificação de IDs
	sprintf(_message, "Removendo ID: ");
	_uart_log.puts(_message);
	get_id64(id);
	endline();
	//pausa.delay(500);
}

void LOG::print_resultado(int retorno_operacao){
	if (retorno_operacao > 0){
		sprintf(_message, "Operacao realizada com sucesso. Retorna: %d.\n",retorno_operacao);
	}else{
		sprintf(_message, "Operacao nao pode ser finalizada com sucesso. Retorna: %d.\n",retorno_operacao);
	}
	_uart_log.puts(_message);
	//pausa.delay(500);
}

void LOG::print_IDs(ID lista_ids){
	id_mat retorno;
	for(int i=0; i<lista_ids.get_tam_atual(); i++) {
		sprintf(_message, "ID%d: ", i+1);
		_uart_log.puts(_message);
		retorno = lista_ids.busca(i);
		get_id64(retorno);
		endline();
		_uart_log.puts(_message);
		//pausa.delay(500);
	}
}

void LOG::print_limpa_lista(int tam_lista, ID lista_ids){
	if(tam_lista>0){
		sprintf(_message, "Limpando lista de IDs: ");
		_uart_log.puts(_message);
		print_IDs(lista_ids);
		//pausa.delay(500);
	}else{
		sprintf(_message, "Lista ja esta vazia.\n");
		_uart_log.puts(_message);
		//pausa.delay(500);
	}
}

void LOG::print_acesso(id_mat id){
	sprintf(_message, "Novo ID tentando acesso: ");
	_uart_log.puts(_message);
	get_id64(id);
	endline();
	//pausa.delay(500);
}

void LOG::print_libera(int retorno_operacao){
	if(retorno_operacao >= 0){
		sprintf(_message, "ID cadastrado. Liberando acesso.\n");
	}else
		sprintf(_message, "ID sem cadastro.\n");
	_uart_log.puts(_message);
	//pausa.delay(500);
}

void LOG::instrucoes(){
	sprintf(_message, "Insira o seu cartao e:\n");
	_uart_log.puts(_message);
	sprintf(_message, "1) Para abrir porta aperte o botao 1;\n");
	_uart_log.puts(_message);
	sprintf(_message, "2) Para cadastrar ID aperte o botao 2;\n");
	_uart_log.puts(_message);
	sprintf(_message, "3) Para remover ID aperte o botao 3;\n");
	_uart_log.puts(_message);
	//pausa.delay(500);
}




/* //TESTE 1 -CADASTRAR ID PELA PRIMEIRA VEZ:


	sprintf(message, "Verifica teste: %d\n",_id_teste.verifica(teste));
	uart.puts(message);
	timer.delay(1000);

	sprintf(message, "Cadastra teste: %d\n",_id_teste.cadastra(teste));
	uart.puts(message);
	timer.delay(1000);

	sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
	uart.puts(message);
	timer.delay(1000);

	sprintf(message, "Verifica novamente teste: %d\n",_id_teste.verifica(teste));
	uart.puts(message);
	timer.delay(1000);
 */

/* //TESTE 2 - CADASTRAR DADOS EM TODA LISTA
id_mat teste = 1210000000;
	id_mat retorno;
	if (!_id_teste.lista_cheia()){
			for(int indice =_id_teste.get_tam_atual(); indice < T_MAX; teste = teste+5,indice =_id_teste.get_tam_atual())
			{
				_id_teste.cadastra(teste);
				se = _id_teste.verifica(teste);
				if (se >= 0){
					sprintf(message, "C%d: ", _id_teste.get_tam_atual());
					uart.puts(message);
					retorno = _id_teste.busca(_id_teste.get_tam_atual()-1);
					get_id64(retorno,0);
					sprintf(message, " -ACK\n");
					uart.puts(message);
				}else{
					sprintf(message, "NACK\n");
					uart.puts(message);
				}
				timer.delay(1000);
			}
		} else{
			sprintf(message, "Lista cheia.\n");
			uart.puts(message);
			timer.delay(1000);
		}
 */

/* //TESTE 3 - REMOVER 1 DETERMINADO CADASTRO
  id_mat teste = 1210000000;
		id_mat retorno;
		memset(&message, '\0', 40);
		sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
		uart.puts(message);
		timer.delay(1000);


		sprintf(message, "Verifica teste: %d\n",_id_teste.verifica(teste));
		uart.puts(message);
		timer.delay(1000);


		sprintf(message, "Cadastra teste: %d\n",_id_teste.cadastra(teste));
		uart.puts(message);
		timer.delay(1000);


		sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
		uart.puts(message);
		timer.delay(1000);


		n = _id_teste.verifica(teste);
		sprintf(message, "Verifica novamente teste: %d\n",n);
		uart.puts(message);
		timer.delay(1000);

		sprintf(message, "Remover ");
		uart.puts(message);
		retorno = _id_teste.busca(n);
		get_id64(retorno);
		sprintf(message, ". Retorno remocao: %d\n", _id_teste.remove(retorno));
		uart.puts(message);
		timer.delay(1000);


		if(_id_teste.verifica(teste) < 0){ // se não encontrou

			sprintf(message, "Cadastro removido.\n");
			uart.puts(message);
			timer.delay(1000);

			sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
			uart.puts(message);
			timer.delay(5000);
		}else{

			sprintf(message, "Cadastro nao removido.\n");
			uart.puts(message);
			timer.delay(5000);
		}
 */

/* //TESTE 4 - REMOVE CADASTRO DA POSICAO n *Restrição: lista já deve ter IDs cadastrados
		int n = 0;
			id_mat n_mat = _id_teste.busca(n);

			sprintf(message, "Remover cadastro ");
			uart.puts(message);
			get_id64(n_mat);
			sprintf(message, ".\n");
			uart.puts(message);
			timer.delay(1000);

			rmove = _id_teste.remove(n_mat);
			se = _id_teste.verifica(n_mat);
			if (rmove){
				if (se < 0){
					sprintf(message, "Removido: ");
					uart.puts(message);
					get_id64(n_mat);
					sprintf(message, ".\n");
					uart.puts(message);
				}
			}else
				sprintf(message, "Esse cadastro nao pode ser removido.\n");
			timer.delay(1000);

			sprintf(message, "N de usuarios: %d \n", _id_teste.get_tam_atual());
			uart.puts(message);
			timer.delay(1000);
		 */

/* // TESTE 5 - OBTER TODOS OS IDs DA LISTA *Restrição: lista já deve ter IDs cadastrados

	id_mat retorno;
	memset(&message, '\0', 40);
	for(int i=0; i<_id_teste.get_tam_atual(); i++) {
		sprintf(message, "C%d: ", i+1);
		uart.puts(message);
		retorno = _id_teste.busca(i);
		get_id64(retorno,0);
		sprintf(message, ".\n");
		uart.puts(message);
		timer.delay(1000);
	}
		*/

/* //TESTE 6 - LIMPAR TODA LISTA

	sprintf(message, "No de users cadastrados: %d.\n", _id_teste.get_tam_atual());
	uart.puts(message);
	timer.delay(1000);
	if (_id_teste.get_tam_atual()>0){
		_id_teste.limpa_lista();
		sprintf(message, "Limpando lista. \n");
	}else
		sprintf(message, "Lista ja esta vazia.\n");
	uart.puts(message);
	timer.delay(1000);
 */

/*//TESTE 7 - LOG MOSTRAR ID ESPECIFICO DA LISTA *Restrição: lista já deve ter IDs cadastrados
	sprintf(message, "Matricula: ");
	uart.puts(message);
	get_id64(teste);
	sprintf(message, ".\n");
	uart.puts(message);
	timer.delay(1000);
	*/

/* //TESTE 8 - GERAÇÃO DE ID RANDOMICO

	sprintf(message, "ID randomico: ");
	uart.puts(message);
	teste = ID_gen.random_id();
	get_id64(teste);
	sprintf(message, ".\n");
	uart.puts(message);
	timer.delay(1000);
 */


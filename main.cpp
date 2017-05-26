
 /*  * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 *      */


//#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include "RFID.h"
#include "ID.h"
#include "LOG.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led1 = 9;
const int pin_led2 = 8;
const int pin_bot1 = 12;
const int pin_bot2 = 13;

Hertz tempo = 2000; //ms
Hertz fq = 1000000/tempo;


UART uart(//chama o construtor automaticamente, antes mesmo de chegar na uart
		19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);

GPIO led1(pin_led1, GPIO::OUTPUT);
GPIO led2(pin_led2, GPIO::OUTPUT);
GPIO botao1(pin_bot1, GPIO::INPUT);
GPIO botao2(pin_bot2, GPIO::INPUT);
Timer timer(fq);
RFID ID_gen;
ID _id_teste;
ID ID_acesso;
LOG logger;

bool val_botao;
char data;
int se;
int n;
bool rmove;
char message[40];
//id_mat teste = 1210004800;
//id_mat teste;
//char matricula_in[40];
id_mat id_gen;
id_mat matricula_in;
id_mat buscas;

void get_id64(id_mat & id, bool endline = false){
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
	    uart.puts(buffer);
}

void setup() {
	sei(); //inicializar/ativar as interrupções
};

/*//FUNCIONAMENTO DO SISTEMA:
 * Insere matricula/cartao

 * botao 1:
	- id cadastrado: libera acesso
		1. led verde
		2. 1 bip alto
		3. abre porta
	- id nao cadastrado: tentar denovo para se cadastrar (botao 2)
		1. led vermelho
		2. 1 bip baixo

 * botao 2:
	- id cadastrado: nao fazer nada
	- id nao cadastrado: cadastrar ID inserido
		1. cadastrado:
			1.1 led verde
			1.2 3 bips altos
		2. nao cadastrado:
			2.1 led vermelho
			2.2 3 bips baixos
 * botao 3:
	- id cadastrado: remover seu cadastro
		1. removido:
			1.1 led verde
			 1.2 3 bips altos
		2. nao removido:
			2.1 led vermelho
			2.2 3 bips baixos
	- id nao cadastrado: nao fazer nada
 */

void loop() {
	val_botao = botao1.get();
	led1.set(val_botao);

	val_botao = botao2.get();
	led2.set(val_botao);

	//val_botao = botao3.get();

	//Simulando obtenção de ID por leitor
	id_gen = ID_gen.random_id();
	get_id64(id_gen);
	uart.put(uart.get());
	timer.delay(10000);
	//Começa a executar apenas se houver tentativa de acesso ao sistema


	//if(uart.tx_has_data()){
	//	matricula = (id_mat)uart.get();
	//}else matricula = 0;

	/*if(matricula != 0){
	//1)ver se botão 1 foi clicado (quer entrar)
		//switch (botao)
		//case 1:

		//Analisa acesso:
		sprintf(message, "Novo ID tentando acesso:");
		uart.puts(message);
		get_id64(matricula);
		sprintf(message, ".\n");
		uart.puts(message);

		if(ID_acesso.verifica(matricula) >= 0)
		{
			sprintf(message, "ID cadastrado. Liberando acesso");
			uart.puts(message);
			//acender led verde, habilitar relé, 3 bips curtos do alta freq. buzzer

		}else
		{
			sprintf(message, "ID sem cadastro.");
			uart.puts(message);
			//acender led vermelho, bip longo de baixa freq. do buzzer
			sprintf(message, "Para editar cadastros insira o cartao e aperte o botao 2.");
			uart.puts(message);
		}

	//2)ver se botão 2 foi clicado (quer editar cadastros)
		//case 2:

		if(ID_acesso.verifica(matricula) >= 0)
		{
			sprintf(message, "ID cadastrado. Para remover seu ID aperte o botão 2.\n");
			uart.puts(message);
			//if(botao = 2){
			sprintf(message, "Preparando para remover ID.");
			uart.puts(message);
			buscas = ID_acesso.busca(n);
			if(ID_acesso.remove(buscas)){
				sprintf(message, "ID removido com sucesso!\n");
				//acender led verde, 2 bip curtos alta freq. do buzzer
			}else {
				sprintf(message, "ID nao pode ser removido! Tente novamente ou entre em contato com um responsavel.\n");
				//acender led vermelho, 2 bip curtos baixa freq. do buzzer
			}uart.puts(message);
			//}else(botao = 1){
				//sprintf(message, "Operacao invalida!\n");
				//uart.puts(message);}
			    //acender led vermelho, bip longo de baixa freq. do buzzer
		}
		else
		{
			sprintf(message, "ID sem cadastro. Para cadastrar aperte o botão 1.\n");
			uart.puts(message);
			//if(botao = 1){
			sprintf(message, "Preparando para cadastrar ID.");
			uart.puts(message);
			bool ret = ID_acesso.cadastra(matricula);
			if(ret){
				sprintf(message, "ID cadastrado com sucesso!\n");
				//acender led verde, 2 bip curtos alta freq. do buzzer
			}else{
				sprintf(message, "ID nao pode ser cadastrado! Tente novamente ou entre em contato com um responsavel.\n");
				//acender led vermelho, 2 bip curtos baixa freq. do buzzer
			}uart.puts(message);
			//}else(botao = 2){
				//sprintf(message, "Operacao invalida!\n");
				//uart.puts(message);}
			   //acender led vermelho, bip longo de baixa freq. do buzzer

		}

	}*/


}


int main(){
	setup();
	while(true)
		loop();
}

/* //TESTE 1 -CADASTRAR ID PELA PRIMEIRA VEZ:
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

/* //TESTE 8 - INSERE ALGO NO LOG - não funcionando
	//bool reg_ok;
	/*int tam;
	tam = logger.get_tam_atual();

	sprintf(message, "Tamanho atual: %d \n", tam);
	uart.puts(message);
	timer.delay(2000);*/

	/*sprintf(message, "Log de teste \n");
	logger.insere_log(message);

	tam = logger.get_tam_atual();

	sprintf(message, "Tamanho atual: %d \n", tam);
	uart.puts(message);
	timer.delay(2000);

	//char * texto_log = logger.lista[tam];

	sprintf(message, "Inserido: %s \n", logger.get_log(tam));
	uart.puts(message);
	timer.delay(2000);

 */

/* //TESTE 9 - GERAÇÃO DE ID RANDOMICO
	sprintf(message, "ID randomico: ");
	uart.puts(message);
	teste = ID_gen.random_id();
	get_id64(teste);
	sprintf(message, ".\n");
	uart.puts(message);
	timer.delay(1000);
 */







 /*  * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 *      */


//#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include "RFID.h"
#include "ID.h"
#include "UART.h"
//#include "LOG.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led1 = 9;
const int pin_led2 = 8;
const int pin_bot1 = 12;
const int pin_bot2 = 13;

Hertz tempo = 2000; //ms
Hertz fq = 1000000/tempo;
UART uart(19200,
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
//LOG logger;

bool val_botao;
char data;
int retorno;
int n;
bool rmove;
char message[40];
id_mat id_gen;
id_mat matricula_in;
id_mat buscas;
int tipo_log;

void get_id64(id_mat & id, bool endline){
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
	//id_gen = ID_gen.random_id();
	//get_id64(id_gen);
	//uart.put(uart.get());
	//timer.delay(10000);
	//Começa a executar apenas se houver tentativa de acesso ao sistema

	matricula_in = ID_gen.random_id();
	get_id64(matricula_in,0);
	timer.delay(500);

	//if(uart.tx_has_data()){
	//	matricula = (id_mat)uart.get();
	//}else matricula = 0;

	//sprintf(message, "Insira o seu cartao e: 1) Para abrir porta aperte o botao 1;\n2) Para cadastrar ID aperte o botao 2;\n3) Para remover ID aperte o botao 3;\n");
	//uart.puts(message);


	/*switch(val_botao){
	case 1:
		//Analisa acesso:
		logger.print_acesso(matricula_in);
		logger.print_verifica(matricula_in);
		retorno = ID_acesso.verifica(matricula_in);
		logger.print_libera(retorno);
		//notifier.set(retorno)//acender led verde, habilitar relé, 3 bips curtos do alta freq. buzzer
		//acender led vermelho, bip longo de baixa freq. do buzzer
		break;
	case 2:
		//Cadastra ID:
		logger.print_cadastra(matricula_in);
		retorno = ID_acesso.cadastra(matricula_in);
		logger.print_resultado(retorno);
		//notifier.set(retorno)//acender led verde, 2 bip curtos alta freq. do buzzer
		//acender led vermelho, 2 bip curtos baixa freq. do buzzer
		break;
	case 3:
		//Remove ID:
		logger.print_remove(matricula_in);
		retorno = ID_acesso.remove(matricula_in);
		logger.print_resultado(retorno);
		//notifier.set(retorno)//acender led verde, 2 bip curtos alta freq. do buzzer
		//acender led vermelho, 2 bip curtos baixa freq. do buzzer
		break;

	}*/
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

};


int main(){
	setup();
	while(true){
		loop();
	}
}








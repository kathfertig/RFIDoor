
 /*  * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 *      */


//#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "RFID.h"
#include "ID.h"
#include "UART1.h"
#include "UART.h"
#include "Timer.h"
#include "RDM6300.h"
#include "LOG.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led1 = 8; //led vermelho
const int pin_led2 = 9; //led verde
const int pin_bot1 = 11;
const int pin_bot2 = 12;
const int pin_bot3 = 13;

//unsigned long tempo = 2000; //ms
//unsigned long fq = 1000000/tempo;

UART uart(19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);
UART1 uart1;

GPIO led_verde(pin_led2, GPIO::OUTPUT);
GPIO led_vermelho(pin_led1, GPIO::OUTPUT);
GPIO botao_acesso(pin_bot1, GPIO::INPUT);
GPIO botao_cadastro(pin_bot2, GPIO::INPUT);
GPIO botao_remove(pin_bot3, GPIO::INPUT);


RDM6300<UART1> leitor_rfid(&uart1);
RFID ID_gen;
ID ID_acesso;
Timer timer(1000);
LOG logger(&uart, &timer);

char message[40];
id_mat id_in;
int retorno;
int id_valido;
enum botao_t{ ZERO = 0,BOTAO_1 = 1, BOTAO_2 = 2, BOTAO_3 = 3};
botao_t valor;

void valor_botoes(){
	if(botao_acesso.get())
		valor = BOTAO_1;
	else if (botao_cadastro.get())
		valor = BOTAO_2;
	else if (botao_remove.get())
		valor = BOTAO_3;
	else valor = ZERO;
}


void setup() {
	sei(); //inicializar/ativar as interrupções
};

void zerar_pinos(){
	led_verde.set(false);
	led_vermelho.set(false);
	botao_acesso.set(false);
	botao_cadastro.set(false);
	botao_remove.set(false);
}

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

	//id_in = ID_gen.random_id();
	id_in = leitor_rfid.read();
	logger.get_id64(id_in,1);
	timer.delay(1000);



	/*id_in = ID_gen.random_id();
	if (valor > 0){
		//logger.print_acesso(matricula_in);
		sprintf(message, "Novo ID tentando acesso: ");
		uart.puts(message);
		logger.get_id64(id_in,0);
		endline();
		//timer.delay(2000);

		switch(valor){
		case 1:
			//Analisa acesso:

			//logger.print_verifica(matricula_in);
			sprintf(message, "Verificando ID.");
			uart.puts(message);
			endline();
			//timer.delay(2000);

			retorno = ID_acesso.verifica(id_in);
			//logger.print_libera(retorno);
			if(retorno >= 0){
				sprintf(message, "ID cadastrado. Liberando acesso.\n");
				uart.puts(message);
				//timer.delay(2000);


				//notifier.notify_acesso();
				//acender led verde, habilitar relé, 3 bips curtos do alta freq. buzzer
				int vezes = 3;
				for (int repete = 0; repete < vezes; repete++){
					//rele.set(true);			//Ativa Rele
					//buzzer_acesso.set(true);
					led_verde.set(true);
					timer.delay(500);
					led_verde.set(false);
					//buzzer_acesso.set(false);
					timer.delay(500);
				}
				zerar_pinos();
				//rele.set(false);		//Desativa Rele
				//timer.delay(2000);

			}else{
				sprintf(message, "ID sem cadastro.\n");
				uart.puts(message);
				//timer.delay(2000);

				//notifier.notify_warning();
				//acender led vermelho, bip longo de baixa freq. do buzzer
				led_vermelho.set(true);
				//buzzer_warning.set(true);
				timer.delay(1000);
				zerar_pinos();
				//buzzer_warning.set(false);
			}break;

		case 2:
			//Cadastra ID:
			//logger.print_cadastra(matricula_in);
			sprintf(message, "Cadastrando ID: ");
			uart.puts(message);
			logger.get_id64(id_in,0);
			endline();
			//timer.delay(2000);

			retorno = ID_acesso.cadastra(id_in);
			//logger.print_resultado(retorno);
			if (retorno > 0){
				sprintf(message, "Operacao realizada com sucesso. Retorna: %d.\n",retorno);
				uart.puts(message);
				//timer.delay(2000);

				//notifier.notify_sucesso();
				//acender led verde, 1 bip longo alta freq. do buzzer
				//buzzer_sucesso.set(true);
				led_verde.set(true);
				led_vermelho.set(false);
				timer.delay(1000);
				led_verde.set(false);
				//buzzer_sucesso.set(false);
			}else{
				sprintf(message, "Operacao nao pode ser finalizada com sucesso. Retorna: %d.\n",retorno);
				uart.puts(message);
				//timer.delay(2000);

				//notifier.notify_warning();
				//acender led vermelho, bip longo de baixa freq. do buzzer
				led_vermelho.set(true);
				//buzzer_warning.set(true);
				led_verde.set(false);
				timer.delay(1000);
				led_verde.set(false);
				//buzzer_warning.set(false);
			}
			break;

		case 3:
			//Remove ID:
			//logger.print_remove(matricula_in);
			sprintf(message, "Removendo ID: ");
			uart.puts(message);
			logger.get_id64(id_in,0);
			endline();
			//timer.delay(2000);


			retorno = ID_acesso.remove(id_in);

			//logger.print_resultado(retorno);
			if (retorno > 0){
				sprintf(message, "Operacao realizada com sucesso. Retorna: %d.\n",retorno);
				uart.puts(message);
				//timer.delay(2000);

				//notifier.notify_sucesso();
				//acender led verde, 1 bip longo alta freq. do buzzer
				//buzzer_sucesso.set(true);
				led_verde.set(true);
				led_vermelho.set(false);
				timer.delay(1000);
				led_verde.set(false);
				//buzzer_sucesso.set(false);
			}else{
				sprintf(message, "Operacao nao pode ser finalizada com sucesso. Retorna: %d.\n",retorno);
				uart.puts(message);
				//timer.delay(2000);

				//notifier.notify_warning();
				//acender led vermelho, bip longo de baixa freq. do buzzer
				led_vermelho.set(true);
				//buzzer_warning.set(true);
				led_verde.set(false);
				timer.delay(1000);
				led_verde.set(false);
				//buzzer_warning.set(false);
			}
			break;

	/*default:
		sprintf(message, "Aperte um botao! \n");
		uart.puts(message);
		break;*/
		/*memset(&message, '\0', 40);
		sprintf(message, "Insira o seu cartao: \n");
		uart.puts(message);
		memset(&message, '\0', 40);
		sprintf(message, "1) Para abrir porta aperte o botao 1;\n");
		uart.puts(message);
		memset(&message, '\0', 40);
		sprintf(message, "2) Para cadastrar ID aperte o botao 2;\n");
		uart.puts(message);
		memset(&message, '\0', 40);
		sprintf(message, "3) Para remover ID aperte o botao 3;\n");
		uart.puts(message);
		timer.delay(2000);*/

	//}
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
	//}
};


int main(){
	setup();
	while(true){
		valor_botoes();
		zerar_pinos();
		loop();
	}
}

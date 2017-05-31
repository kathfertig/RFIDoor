
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
#include "Notify.h"
#include "Buzzer.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led1 = 9; //led verde
const int pin_led2 = 11; //led vermelho
const int pin_bot1 = 12;
const int pin_bot2 = 13;
const int pin_bot3 = 7;
const int pin_porta = 10;
const int pin_buzzer = 8;

UART uart(19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);
UART1 uart1;

GPIO led_verde(pin_led1, GPIO::OUTPUT);
GPIO led_vermelho(pin_led2, GPIO::OUTPUT);
GPIO rele_porta(pin_porta, GPIO::OUTPUT);
GPIO buzzer(pin_buzzer, GPIO::OUTPUT);

GPIO botao_acesso(pin_bot1, GPIO::INPUT);
GPIO botao_cadastro(pin_bot2, GPIO::INPUT);
GPIO botao_remove(pin_bot3, GPIO::INPUT);

RDM6300<UART1> leitor_rfid(&uart1);
RFID ID_gen;
ID ID_acesso;
Timer timer(1000);
LOG logger(&uart, &timer);
Notify notifier(&timer);

Buzzer buzzer_acesso(10000,&buzzer, &timer);
Buzzer buzzer_sucesso(1000,&buzzer, &timer);
Buzzer buzzer_warning(10000,&buzzer, &timer);

char message[40];
id_mat id_in;
int int_ret;
bool bool_ret;
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

void zerar_pinos(){
	led_verde.set(false);
	led_vermelho.set(false);
	rele_porta.set(false);
	buzzer.set(false);

	botao_acesso.set(false);
	botao_cadastro.set(false);
	botao_remove.set(false);
}

void setup() {
	sei(); //inicializar/ativar as interrupções
	zerar_pinos();
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

	//id_in = ID_gen.random_id();
	while(id_in == 0)
		id_in = leitor_rfid.read();
		//logger.get_id64(id_in,1);
	while(valor == 0)
		valor_botoes();

	if (valor > 0){
		logger.print_acesso(id_in);

		switch(valor){
		case 1:
			//Analisa acesso:
			logger.print_verifica(id_in);
			int_ret = ID_acesso.verifica(id_in);
			logger.print_libera(int_ret);
			if(int_ret >= 0)
				notifier.notify_acesso(&led_verde, &rele_porta, &buzzer_acesso);
			else
				notifier.notify_warning(&led_vermelho, &buzzer_warning);
			zerar_pinos();
			break;


		case 2:
			//Cadastra ID:
			logger.print_cadastra(id_in);
			int_ret = ID_acesso.cadastra(id_in);
			if(int_ret == 1){
				logger.print_sucesso();
				notifier.notify_sucesso(&led_verde, &buzzer_sucesso);
			}else if(int_ret == 0){
				logger.print_fracasso();
				notifier.notify_warning(&led_vermelho, &buzzer_warning);
			}else
				logger.print_warning();
			zerar_pinos();
			break;

		case 3:
			//Remove ID:
			logger.print_remove(id_in);
			int_ret = ID_acesso.remove(id_in);
			if(int_ret == 1){
				logger.print_sucesso();
				notifier.notify_sucesso(&led_verde, &buzzer_sucesso);
			}else if(int_ret == 0){
				logger.print_fracasso();
				notifier.notify_warning(&led_vermelho, &buzzer_warning);
			}else
				logger.print_warning();
			zerar_pinos();
			break;

		default:
			logger.instrucoes();
		}
	}
	id_in = 0;
	valor = ZERO;
};


int main(){
	setup();
	while(true){
		valor_botoes();
		loop();
	}
}

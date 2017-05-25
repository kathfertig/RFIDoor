
 /*  * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 *      */


#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include "RFID.h"
#include "ID.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

//#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define bzero(b,len) memset(b, '\0', len)

const int pin_led = 11;
const int pin_bot = 12;

unsigned long long tempo = 2000; //ms
unsigned long long fq = 1000000/tempo;


UART uart(//chama o construtor automaticamente, antes mesmo de chegar na uart
		19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot, GPIO::INPUT);
Timer timer(fq);
RFID ID_gen;
ID _id_teste;

bool val_botao;
char message[40];
char data;
int se;
int n;
bool rmove;
id_mat teste = 1210000000;
//int teste = 100;


void setup() {
	sei(); //inicializar/ativar as interrupções
};

//loop botao-led
void loop() {
	val_botao = botao.get();
	led.set(val_botao);

	memset(&message, '\0', 40);

	sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
	uart.puts(message);
	timer.delay(2000);


	sprintf(message, "Verifica teste: %d\n",_id_teste.verifica(teste));
	uart.puts(message);
	timer.delay(2000);


	sprintf(message, "Cadastra teste: %d\n",_id_teste.cadastra(teste));
	uart.puts(message);
	timer.delay(2000);


	sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
	uart.puts(message);
	timer.delay(2000);


	n = _id_teste.verifica(teste);
	sprintf(message, "Verifica novamente teste: %d\n",n);
	uart.puts(message);
	timer.delay(2000);


	sprintf(message, "Remover %lu: %d\n", _id_teste.busca(n), _id_teste.remove(_id_teste.busca(n)));
	uart.puts(message);
	timer.delay(2000);

	if(_id_teste.verifica(teste) < 0){ // se não encontrou

		sprintf(message, "Cadastro removido.\n");
		uart.puts(message);
		timer.delay(2000);


		sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
		uart.puts(message);
		timer.delay(2000);
	}else{

		sprintf(message, "Cadastro nao removido.\n");
		uart.puts(message);
		timer.delay(2000);
	}

		/*n = 0;
		sprintf(message, "Remover cadastro %lu\n", _id_teste.busca(n));
		uart.puts(message);
		timer.delay(1000);


		if(teste == _id_teste.busca(n)){
			sprintf(message, "Cadastro confere.\n");
			uart.puts(message);
		}

		rmove = _id_teste.remove(teste);
		se = _id_teste.verifica(_id_teste.busca(n));
		if (rmove && (se<0)){
			sprintf(message, "Removido: %lu \n", _id_teste.busca(n));
		}else
			sprintf(message, "Esse cadastro nao pode ser removido.\n");
		uart.puts(message);
		timer.delay(1000);*/


}


int main(){
	setup();
	while(true)
		loop();
}

/*//TESTE PARA CADASTRAR ID PELA PRIMEIRA VEZ:
 * sprintf(message, "N de usuarios cadastrados: %d\n",_id_teste.get_tam_atual());
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

/*//TESTE PARA CADASTRAR DADOS EM TODA LISTA
  if (!_id_teste.lista_cheia()){
		for(int indice = 0; indice < T_MAX; teste = teste+5,indice =_id_teste.get_tam_atual())
		{
			_id_teste.cadastra(teste);
			se = _id_teste.verifica(teste);
			if (se >= 0){
				sprintf(message, "C%d: %d -ACK\n", _id_teste.get_tam_atual(),_id_teste.busca(indice));
			}else{
				sprintf(message, "NACK\n");
				//indice = T_MAX;
			}
			uart.puts(message);
			timer.delay(500);
		}
	} else{
		sprintf(message, "Lista cheia.\n");
		uart.puts(message);
		timer.delay(1000);
	}
 */

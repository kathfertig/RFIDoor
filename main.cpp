
 /*  * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 *      */


#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include "RFID.h"
#include "ID.h"

#define BAUD 9600
#define MYUBRR F_CPU/8/BAUD-1

const int pin_led1 = 9;
const int pin_led2 = 8;
const int pin_bot1 = 12;
const int pin_bot2 = 13;

unsigned long long tempo = 2000; //ms
unsigned long long fq = 1000000/tempo;


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

bool val_botao;
char message[40];
char data;
int se;
int n;
bool rmove;
//id_mat teste = 1210000000;
id_mat teste;


void setup() {
	sei(); //inicializar/ativar as interrupções
};

//loop botao-led
void loop() {
	val_botao = botao1.get();
	led1.set(val_botao);

	val_botao = botao2.get();
	led2.set(val_botao);


		if (!_id_teste.lista_cheia()){
			for(int indice =_id_teste.get_tam_atual(); indice < T_MAX; teste = teste+5,indice =_id_teste.get_tam_atual())
			{
				_id_teste.cadastra(teste);
				se = _id_teste.verifica(teste);
				if (se >= 0){
					sprintf(message, "C%d: %lu -ACK\n", _id_teste.get_tam_atual(),_id_teste.busca(_id_teste.get_tam_atual()-1));
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
	}
}


int main(){
	setup();
	while(true)
		loop();
}

/* //TESTE 1 -CADASTRAR ID PELA PRIMEIRA VEZ:
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

/* //TESTE 2 - CADASTRAR DADOS EM TODA LISTA
  if (!_id_teste.lista_cheia()){
		for(int indice =_id_teste.get_tam_atual(); indice < T_MAX; teste = teste+5,indice =_id_teste.get_tam_atual())
		{
			_id_teste.cadastra(teste);
			se = _id_teste.verifica(teste);
			if (se >= 0){
				sprintf(message, "C%d: %lu -ACK\n", _id_teste.get_tam_atual(),_id_teste.busca(_id_teste.get_tam_atual()-1));
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

/* //TESTE 3 - REMOVER 1 DETERMINADO CADASTRO
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
 */

/* //TESTE 4 - REMOVE CADASTRO DA POSICAO n
		int n = 0;
		id_mat n_mat = _id_teste.busca(n);
		sprintf(message, "Remover cadastro %lu\n", n_mat);
		uart.puts(message);
		timer.delay(1000);
		rmove = _id_teste.remove(n_mat);
		se = _id_teste.verifica(n_mat);
		if (rmove){
			if (se < 0)
			sprintf(message, "Removido: %lu \n", n_mat);
		}else
			sprintf(message, "Esse cadastro nao pode ser removido.\n");

		uart.puts(message);
		timer.delay(1000);

		sprintf(message, "N de usuarios: %d \n", _id_teste.get_tam_atual());
		uart.puts(message);
		timer.delay(1000);

		 */

/* // TESTE 5 - OBTER TODOS OS IDs DA LISTA

		for(int i=0; i<_id_teste.get_tam_atual(); i++) {
			sprintf(message, "C%d: %lu \n", i+1,_id_teste.busca(i));
			uart.puts(message);
			timer.delay(1000);
		}
		*/

/* //TESTE 6 - LIMPAR TODA LISTA
		_id_teste.limpa_lista();
		sprintf(message, "No de users cadastrados: %d.\n", _id_teste.get_tam_atual());
		uart.puts(message);
		timer.delay(1000);
 */

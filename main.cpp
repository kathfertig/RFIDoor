
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

bool val_botao;
char data;
int se;
int n;
bool rmove;
char message[40];

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

//loop botao-led
void loop() {
	val_botao = botao1.get();
	led1.set(val_botao);

	val_botao = botao2.get();
	led2.set(val_botao);






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

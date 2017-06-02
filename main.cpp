
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

//Definição dos pinos usados nos sistema:
const int pin_led1 = 9; //led verde
const int pin_led2 = 11; //led vermelho
const int pin_bot1 = 12;
const int pin_bot2 = 13;
const int pin_bot3 = 7;
const int pin_porta = 10;
const int pin_buzzer = 8;

//Instanciação das classes:
UART uart(19200,
		UART::DATABITS_8,
		UART::PARITY_NONE,
		UART::STOPBITS_1);
UART1 uart1;

GPIO led_verde(pin_led1, GPIO::OUTPUT);
GPIO led_vermelho(pin_led2, GPIO::OUTPUT);
GPIO rele_porta(pin_porta, GPIO::OUTPUT);
GPIO buzzer(pin_buzzer, GPIO::OUTPUT);

GPIO botao_acesso(pin_bot1, GPIO::INPUT);//botão 1
GPIO botao_cadastro(pin_bot2, GPIO::INPUT);//botão 2
GPIO botao_remove(pin_bot3, GPIO::INPUT);//botão 3

RDM6300<UART1> leitor_rfid(&uart1);
//RFID ID_gen;     //Classe apenas usada para teste de ID com valor randômico gerado por ela.
ID ID_acesso;
Timer timer(1000);
LOG logger(&uart, &timer);
Notify notifier(&timer);

//Instanciação de 3 configurações diferentes para o buzzer (3 sequências diferentes de sons)
Buzzer buzzer_acesso(10000,&buzzer, &timer);
Buzzer buzzer_sucesso(1000,&buzzer, &timer);
Buzzer buzzer_warning(10000,&buzzer, &timer);

id_mat id_in; //ID de entrada obtido do leitor RFID
int int_ret;  //variável de controle para tomada de decisões

//definição de tipos de botões(valores) que podem ser acionados:
enum botao_t{ ZERO = 0,BOTAO_1 = 1, BOTAO_2 = 2, BOTAO_3 = 3};
botao_t valor;  //variável para verificar os botões acionados

void valor_botoes(){//método para verificar qual botão foi apertado
	if(botao_acesso.get())
		valor = BOTAO_1;
	else if (botao_cadastro.get())
		valor = BOTAO_2;
	else if (botao_remove.get()){
		valor = BOTAO_3;
		//atraso_botao3 = true;
	}else
		valor = ZERO;
}

void zerar_pinos(){//método para zerar valores de pinos de entrada e saída
	led_verde.set(false);
	led_vermelho.set(false);
	rele_porta.set(false);
	buzzer.set(false);

	botao_acesso.set(false);
	botao_cadastro.set(false);
	botao_remove.set(false);
	valor = ZERO;

}

void setup() {
	sei(); //inicializar/ativar as interrupções
	zerar_pinos(); //zerar pinos
};

void limpa_cadastros(){//realiza todas as etapas do sistema ao acionar o botão 3

	int_ret = ID_acesso.verifica(id_in);
	if(int_ret >= 0){
		//se ID lido já cadastrado, ele pode realizar operação de limpar toda a lista de cadastros
		int_ret = ID_acesso.get_tam_atual();
		logger.print_limpa_lista(int_ret,&ID_acesso);
		ID_acesso.limpa_lista();
		int_ret = ID_acesso.get_tam_atual();

		if(int_ret == 0){//se lista vazia, indica que operação foi realizada com sucesso
			logger.print_sucesso();
			notifier.notify_sucesso(&led_verde, &buzzer_sucesso);
		}else if(int_ret != 0){//se a lista não está vazia, indica fracasso
			logger.print_fracasso();
			notifier.notify_warning(&led_vermelho, &buzzer_warning);
		}
	}
	else{//se ID não cadastrado, não pode realizar operação de limpeza
		logger.print_warning();
		notifier.notify_warning(&led_vermelho, &buzzer_warning);
	}
	zerar_pinos();

}

//método para implementação futura que realiza todas as etapas do sistema para remover ID
/*void remove_id(){
	logger.print_remove(id_in);
	int_ret = ID_acesso.remove(id_in);
	if(int_ret == 1){
		logger.print_sucesso();
		notifier.notify_sucesso(&led_verde, &buzzer_sucesso);
	}else if(int_ret == 0){
		logger.print_fracasso();
		notifier.notify_warning(&led_vermelho, &buzzer_warning);
	}else{
		logger.print_warning();
		notifier.notify_warning(&led_vermelho, &buzzer_warning);
	}zerar_pinos();
}*/

void cadastra_id(){//realiza todas as etapas do sistema ao acionar o botão 2
	logger.print_cadastra(id_in);
	int_ret = ID_acesso.cadastra(id_in);
	if(int_ret == 1){//se usuário ainda não cadastrado, sistema cadastra ID
		logger.print_sucesso();
		notifier.notify_sucesso(&led_verde, &buzzer_sucesso);
	}else if(int_ret == 0){//se ID já cadastrado, impede a operação
		logger.print_fracasso();
		notifier.notify_warning(&led_vermelho, &buzzer_warning);
	}
	zerar_pinos();
}

void analisa_acesso(){//realiza todas as etapas do sistema ao acionar o botão 1
	logger.print_verifica(id_in);
	int_ret = ID_acesso.verifica(id_in);
	logger.print_libera(int_ret);//método que libera de acordo com a verificação de usuário
	if(int_ret >= 0)//se ID já cadastrado, libera acesso
		notifier.notify_acesso(&led_verde, &rele_porta, &buzzer_acesso);
	else //se não, nega acesso
		notifier.notify_warning(&led_vermelho, &buzzer_warning);
	zerar_pinos();
}


void loop() {

	//id_in = ID_gen.random_id();	//chamada de geração de ID randômico

	while(id_in == 0)	//loop para ler qualquer valor do leitor
		id_in = leitor_rfid.read();

	while(valor == 0)	//loop para detectar qualquer acionamento de botões
		valor_botoes();

	if (valor > 0){		//Indica que um ID lido está tentando realizar alguma operação
		logger.print_acesso(id_in);

		switch(valor){	//executa operações de acordo com o botão acionado
		case 1:
			//Analisa acesso:
			analisa_acesso();
			break;

		case 2:
			//Cadastra ID:
			cadastra_id();
			break;

		case 3:
			//Limpa cadastros:
			limpa_cadastros();
			break;

		//default: //método para implementação futura com possíveis uso de displays para o log
		//	logger.instrucoes();
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

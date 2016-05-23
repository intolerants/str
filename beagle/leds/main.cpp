 /**
	Autor: Tiago Fernandes de Miranda
	Universidade Federal do Rio Grande do Norte
	
	compilar: g++ main.cpp -o main
 **/
 
 #include <iostream>
 #include <stdio.h>
 #include <unistd.h>
 using namespace std;
 
 // Fatores de conversao de tempo para o metodo usleep
 int FATOR_MILLI = 1000;
 int FATOR_SEG = 1000000;
 
 // Diretorios dos LEDS da BeagleBone Black [0 ... 3]
 FILE *LEDHandle = NULL;
 const char *LEDBrightness0="/sys/class/leds/beaglebone:green:usr0/brightness";
 const char *LEDBrightness1="/sys/class/leds/beaglebone:green:usr1/brightness";
 const char *LEDBrightness2="/sys/class/leds/beaglebone:green:usr2/brightness";
 const char *LEDBrightness3="/sys/class/leds/beaglebone:green:usr3/brightness";

 void acender(const char * target);
 void apagar(const char * target);
 const char * seleciona(int i);
 
 // A funcao main executa um loop N iteracoes, cada iteracao
 // o metodo utiliza o indice i para selecionar qual LED 
 // utilizar para acender e apagar fazendo i%4.
 // Entao para cada iteracao ele acende o LED, dorme por
 // 50 millisegundos, apaga o LED e dorme novamente pelo
 // mesmo tempo.
 int main(){
	cout << "LED Flash Start" << endl;
	for(int i=0; i<100; i++){
		acender(seleciona(i%4));
        usleep(50 * FATOR_MILLI);
		apagar(seleciona(i%4));       
        usleep(50 * FATOR_MILLI);
	}
	cout << "LED Flash End" << endl;
 }
 
 // Este metodo tem por funcao acender um LED passado
 // por parametro, o target eh o caminho do arquivo
 // a ser escrito valor "1" para acender o LED respectivo.
 void acender(const char * target){	 
	if((LEDHandle = fopen(target, "r+")) != NULL){
		fwrite("1", sizeof(char), 1, LEDHandle);
		fclose(LEDHandle);
	}
 }

// Este metodo tem por funcao apagar um LED passado
// por parametro, o target eh o caminho do arquivo
// a ser escrito valor "0" para apagar o LED respectivo.
 void apagar(const char * target){	 
	if((LEDHandle = fopen(target, "r+")) != NULL){
		fwrite("0", sizeof(char), 1, LEDHandle);
		fclose(LEDHandle);
    }
 }
 
 const char * seleciona(int i){
	const char* target;
	switch(i){
		case 0: return LEDBrightness0;
		case 1:	return LEDBrightness1;
		case 2:	return LEDBrightness2;
		case 3: return LEDBrightness3;
		default: return NULL;		
	}
 }

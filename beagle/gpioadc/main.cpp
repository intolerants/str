/**
 * Autor: Tiago Fernandes de Miranda
 * Universidade Federal do Rio Grande do Norte
 */

#include <iostream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

#define UNIT_MS 1000;
#define UNIT_SEC 1000000;

using namespace std;

int main(int argc, char * argv[])
{
    cout << "Example 2 - GPIO e ADC" << endl;
    ADC adc0(AINx::AIN0);
    BlackLib::BlackGPIO led(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
    long maxSegundos = 15*UNIT_MS;

    while(true){
    	float p = adc0.getPercentValue(); // 0 ~ 100
    	long tempo = round((p*maxSegundos)/100.0);
    	tempo += 10*UNIT_MS;
    	cout << "Tempo " << tempo << endl;
    	led.setValue(BlackLib::high);
    	usleep(tempo);
    	led.setValue(BlackLib::low);
    	usleep(tempo);
    }
    return 0;
}

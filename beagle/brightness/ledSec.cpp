#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 
#include <math.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

void *pwm_function(void *arg);
//int run_now = 1;
char message[] = "Hello World";
// clock_t clockStart, clockEnd, freq_time, duty_time;
time_t timeStart, timeEnd;
double freq_cycle, duty_cycle, freq_time, duty_time;

int main() {
    int res;
    pthread_t pwm_thread;
    void *thread_result;

    ADC freqPot(AINx::AIN0); 
    ADC dutyPot(AINx::AIN1);
    

    freq_time = 2;
    duty_time = 1/100;
    freq_cycle = 0.5;
    duty_cycle = 0.5;
       
    res = pthread_create(&pwm_thread, NULL, pwm_function, (void *)message);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    while(1){
        freq_cycle = freqPot.getPercentValue()/100;
        duty_cycle = dutyPot.getPercentValue()/100;
    }

    res = pthread_join(pwm_thread, &thread_result);
    if (res != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void *pwm_function(void *arg) {
    BlackLib::BlackGPIO led(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
    timeStart = time( (time_t *) 0);
    while(1) {
        timeEnd = time( (time_t *) 0);
        if(timeEnd - timeStart < freq_time*freq_cycle){

            led.setValue(BlackLib::high);
            usleep(duty_time*duty_cycle*100000);

            led.setValue(BlackLib::low);
            usleep(duty_time*(1 - duty_cycle)*100000);
        }
        else if(timeEnd - timeStart >= freq_time){
            timeStart = time( (time_t *) 0);
        }
    }
}




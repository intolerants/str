#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"


#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <sys/types.h>
#include <sched.h>
#include <pthread.h>
#include <errno.h>


void *pwm_function(void *arg);
//void *read_function(void *arg);
//int run_now = 1;
char message[] = "Hello World";
// clock_t clockStart, clockEnd, freq_time, duty_time;
double freq_cycle, duty_cycle;

#define UNIT_MS 1000
#define UNIT_SEC 1000000

using namespace std;

int main() {
    int res;
    pthread_t pwm_thread;
    
    void *thread_result;
    int cpu = 0, prio = 10;
    cpu_set_t set;
    pthread_attr_t *tattr;
    struct sched_param param;
    int error,policy;

    CPU_ZERO (&set);
    CPU_SET (cpu, &set);
    

    tattr = (pthread_attr_t *)malloc(sizeof(pthread_attr_t));
    error = pthread_attr_init(tattr);
    cout << "init: " << error << endl;

    error = pthread_attr_getschedparam(tattr,&param);
    cout << "getschedparam: " << error << endl;

    error = pthread_attr_setinheritsched(tattr, PTHREAD_EXPLICIT_SCHED);
    cout << "setinheritsched: " << error << endl;
    
    policy = SCHED_RR;
    error = pthread_attr_setschedpolicy(tattr, policy);
    cout << "setschedpolicy = " << policy << ": " << error << endl;

    param.sched_priority = prio;
    error = pthread_attr_setschedparam(tattr ,&param);
    cout << "setschedparam: " << error << endl;


    res = pthread_create(&pwm_thread, tattr, pwm_function, (void *)message);
    if (res != 0) {
        perror("PWM Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    pthread_getschedparam(pwm_thread,&policy,&param);
    printf("policy:: %d pri :: %d\n",policy,param.sched_priority);

    if(pthread_setaffinity_np(pwm_thread, sizeof(cpu_set_t), &set) != 0) {
      fprintf(stderr, "Error setting affinity\n");
      return 1;
    }

    res = pthread_join(pwm_thread, &thread_result);
    if (res != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void *pwm_function(void *arg) {
    printf("Start PWM read");
    double duty_time;

    duty_cycle = 0.1;
    //duty_time = 0.01;
    duty_time = 0.02;
    //duty_time = 1/100;

    BlackLib::BlackGPIO led(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
    //timeStart = time( (time_t *) 0);
    while(1) {          
        led.setValue(BlackLib::high);
        printf("sleepON:%.3f\n", duty_time*duty_cycle*(double)UNIT_SEC);
        usleep(duty_time*duty_cycle*(double)UNIT_SEC);

        led.setValue(BlackLib::low);
        printf("sleepOFF:%.3f\n", duty_time*(1.0 - duty_cycle)*(double)UNIT_SEC);
        usleep(duty_time*(1.0 - duty_cycle)*(double)UNIT_SEC);

    }
}

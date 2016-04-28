#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <chrono>

#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <sys/types.h>
#include <sched.h>
#include <pthread.h>
#include <errno.h>

void *pwm_function(void *arg);
void *read_function(void *arg);
//int run_now = 1;
char message[] = "Hello World";
// clock_t clockStart, clockEnd, freq_time, duty_time;
double freq_cycle, duty_cycle;

#define UNIT_MS 1000
#define UNIT_SEC 1000000

using namespace std::chrono;

int main() {
    int res;
    pthread_t pwm_thread, read_thread;
    
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

    freq_cycle = 0.5;
    duty_cycle = 0.5;

    res = pthread_create(&pwm_thread, NULL, pwm_function, (void *)message);
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

    res = pthread_create(&read_thread, NULL, read_function, (void *)message);
    if (res != 0) {
        perror("Read Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_join(pwm_thread, &thread_result);
    res = pthread_join(read_thread, &thread_result);
    if (res != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void *read_function(void *arg) {
    printf("Start ADC read");

    ADC freqPot(AINx::AIN0);
    ADC dutyPot(AINx::AIN1);

    while(1){
        freq_cycle = freqPot.getPercentValue()/100;
        duty_cycle = dutyPot.getPercentValue()/100;
        usleep(50*UNIT_MS);
        system("clear");
        printf("duty_c:%f freq_c:%f\n", duty_cycle, freq_cycle);
    }
}

void *pwm_function(void *arg) {
    printf("Start PWM read");
    
    high_resolution_clock::time_point timeStart, timeEnd;
    double freq_time, duty_time;
    
    freq_time = 2;
    duty_time = 0.02; //ms
    duty_cycle = 0.0;
    freq_cycle = 0.5;

    // double local_duty_cycle = duty_cycle, local_freq_cycle = freq_cycle;

    BlackLib::BlackGPIO led(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
    timeStart = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(timeEnd - timeStart);
    while(1) {
        time_span = duration_cast<duration<double>>(timeEnd - timeStart);
        timeEnd = high_resolution_clock::now();
        // printf("timeEnd:%ld\n", timeEnd);
        if(time_span.count() < freq_time*freq_cycle){
            // std::cout << time_span.count() << endl;
            
            led.setValue(BlackLib::high);
            usleep(duty_time*duty_cycle*(double)UNIT_SEC);
            led.setValue(BlackLib::low);
            usleep(duty_time*(1.0 - duty_cycle)*(double)UNIT_SEC);
        }
        else if(time_span.count() >= freq_time){
           timeStart = high_resolution_clock::now();
        }
    }
}

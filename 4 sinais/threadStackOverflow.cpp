#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <sys/types.h>
#include <signal.h>
#include <sched.h>
#include <pthread.h>
#include <errno.h>

#define handle_error_en(en, msg) \
       do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)


//using std::cout;
using namespace std;


// function to load the CPU
void carga(int k)
{
    float f = 0.999999;
    for (int i = 0; i < k; i++)
    {
        f = f * f * f * f * f;
        f = 1.56;
        for (int j = 0; j < k; j++)
        {
            f = sin(f) * sin(f) * f * f * f;

        }
    }

}

void *threadFunc(void *k){
    int numOfExecutions = *((int*)k);
    clock_t time_1, time_2;
    time_t  real_time_1, real_time_2, delta_real_time[1000];

    int out;
    double out2[1000], mean = 0, stdev = 0, mean2 = 0, stdev2 = 0;

    // ---------------------------------------------------------------------------------
    //
    //  Parte do código associada com uso intenso de CPU : início
    //
    //  --------------------------------------------------------------------------------
    for (int i = 0; i < numOfExecutions; ++i)
    {
        time_1 = clock();
        real_time_1 = time(0);
        carga(10000);       // funcão de uso intenso de CPU
        real_time_2 = time(0);
        time_2 = clock();

        out = (int) (time_2) - (time_1);  // tempo de CPU
        out2[i] = (double) ((out) / (double) CLOCKS_PER_SEC);
        delta_real_time[i] = (real_time_2) - (real_time_1);

        mean += (double)delta_real_time[i];
        mean2 += (double)out2[i];
        printf(" Time of CPU use: %.2f \n", out2[i]);
        printf(" Real time: %.2f \n\n", (double) delta_real_time[i]);
    }
    mean /= (double)numOfExecutions;
    mean2 /= (double)numOfExecutions;
    double aux;
    for (int i = 0; i < numOfExecutions; ++i)
    {
        aux = (double)delta_real_time[i] - (double)mean;
        aux *= aux;
        stdev += aux;
        aux = (double)out2[i] - (double)mean2;
        aux *= aux;
        stdev2 += aux;

    }
    stdev = sqrt(stdev / (numOfExecutions));
    stdev2 = sqrt(stdev2 / (numOfExecutions));

    printf("MEAN_CPU: %.2f\n", (double)mean2);
    printf("STDEV_CPU: %.2f\n", (double)stdev2);
    printf("MEAN: %.2f\n", (double)mean);
    printf("STDEV: %.2f\n\n", (double)stdev);


    // ---------------------------------------------------------------------------------
    //
    //  Parte do código associada com uso intenso de CPU : fim
    //
    //  --------------------------------------------------------------------------------
    pthread_exit(NULL);

}


int main( ) {

    int cpu, prio, numOfExecutions;
    cpu_set_t set;
    void *thread_result;

    // cpu = 0;
    // prio = 10;
    // numOfExecutions = 50;

    while (cpu < 0 || cpu > 7) {
        printf("CPU: ");
        scanf("%d", &cpu);
    }

    while (prio < 0 || prio > 40) {
        printf("Prioridade: ");
        scanf("%d", &prio);
    }

    printf("Numero de Execucoes: ");
    scanf("%d", &numOfExecutions);

    CPU_ZERO (&set);
    CPU_SET (cpu, &set);

    printf("Pid: %d\n", getpid());
    
    pthread_t oliver;
    pthread_attr_t *tattr;
    struct sched_param param;
    int error,policy;

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

    error = pthread_create(&oliver,tattr,threadFunc,&numOfExecutions);
    cout << "create: " << error << endl;

    pthread_getschedparam(oliver,&policy,&param);
    printf("policy:: %d pri :: %d\n",policy,param.sched_priority);

    if(pthread_setaffinity_np(oliver, sizeof(cpu_set_t), &set) != 0) {
      fprintf(stderr, "Error setting affinity\n");
      return 1;
    }

    error = pthread_join(oliver, &thread_result);
    if (error != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
    exit(1);
}

#include <time.h>
#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <errno.h>

#define handle_error_en(en, msg) \
       do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)


//using std::cout;
using namespace std;


// função para simular carregamento da CPU
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

    int saida;
    double saida2[1000], mean = 0, stdev = 0, mean2 = 0, stdev2 = 0;

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
        // sleep(6);
        real_time_2 = time(0);
        time_2 = clock();

        saida = (int) (time_2) - (time_1);  // tempo de CPU
        saida2[i] = (double) ((saida) / (double) CLOCKS_PER_SEC);
        delta_real_time[i] = (real_time_2) - (real_time_1);

        mean += (double)delta_real_time[i];
        mean2 += (double)saida2[i];
        // printf("\n Tempo de uso da CPU em microsegundos: %d \n", saida);
        printf(" Tempo de uso da CPU em segundos: %.2f \n", saida2[i]);
        printf(" Tempo Real decorrido em segundos: %.2f \n\n", (double) delta_real_time[i]);
    }
    mean /= (double)numOfExecutions;
    mean2 /= (double)numOfExecutions;
    double aux;
    for (int i = 0; i < numOfExecutions; ++i)
    {
        aux = (double)delta_real_time[i] - (double)mean;
        // cout << delta_real_time[i] << "|";
        // cout << aux << "|";
        aux *= aux;
        // cout << aux << "|";
        stdev += aux;
        // cout << aux << "\n";
        aux = (double)saida2[i] - (double)mean2;
        aux *= aux;
        stdev2 += aux;

    }
    // cout << stdev << "|";
    stdev = sqrt(stdev / (numOfExecutions));
    // cout << stdev << "\n";
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

    int cpu = -1, prio = -1, s;
    cpu_set_t set;
    bool flagwhile;
    int numOfExecutions = 5;
    pthread_t oliver;
    void *thread_result;

    //pthread_attr_t attr;
    //struct sched_param param;
    //char *attr_sched_str;

    while (cpu < 0 || cpu > 7) {
        printf("CPU: ");
        scanf("%d", &cpu);
    }

    while (prio < 0 || prio > 19) {
        printf("Prioridade: ");
        scanf("%d", &prio);
    }

    printf("Numero de Execucoes: ");
    scanf("%d", &numOfExecutions);
    
    CPU_ZERO (&set);
    CPU_SET (cpu, &set);

    printf("Pid: %d\n", getpid());

    if(pthread_create(&oliver, NULL, threadFunc, &numOfExecutions)) {
      fprintf(stderr, "Error creating thread\n");
      return 1;
    }

    if(pthread_setaffinity_np(oliver, sizeof(cpu_set_t), &set) != 0) {
      fprintf(stderr, "Error setting affinity\n");
      return 1;
    }

    /*param.sched_priority = strtol(&attr_sched_str[1], NULL, 0);

    s = pthread_attr_setschedparam(&attr, &param);
       if (s != 0)
           handle_error_en(s, "pthread_attr_setschedparam");*/

    s = pthread_join(oliver, &thread_result);
    if (s != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }

    //setpriority(PRIO_PROCESS, 0, prio);

    exit(1);

}

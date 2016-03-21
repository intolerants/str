#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;          /* See feature_test_macros(7) */

int main () {

  int cpu = -1, prio = -1;
  cpu_set_t set;

  while(cpu < 0 || cpu > 7){
    printf("CPU: ");    
    scanf("%d", &cpu);
  }

  while(prio < 0 || prio > 19){
    printf("Prioridade: ");
    scanf("%d", &prio);
  }

  CPU_ZERO (&set);
  CPU_SET (cpu, &set);

  sched_setaffinity(0, 8, &set);

  setpriority(PRIO_PROCESS, 0, prio);

  printf("Pid: %d\n", getpid());
  while(1);

  exit (0);

}
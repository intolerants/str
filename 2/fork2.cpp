// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa: fork2.c
// Objetivo: utilizar as funções getpid() e getppid()

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <iostream>

using namespace std;


int main ()
{

// declaração de variáveis
  pid_t pid;          // definindo um identificador de processo - inteiro longo
   
  printf("Começando o programa fork2 ... \n");
  //system("ps");  // tente ps -aux, ps -auf
  //sleep(3); 
  printf( "\n\nEu sou o Pai %d e vou criar um Filho\n", getpid() );
  pid = fork();   // dividindo o processo em dois

  cout << PRIO_PROCESS << PRIO_PGRP << PRIO_USER;
  switch(pid)
    {
    case -1:       // erro na abertura do processo filho
      exit(1);  
    case 0:        // execução do processo Filho
      for(int i=0; i<5; i++) {
        sleep(1);  // dormir por 2 segundos   
        printf( "\t Eu sou o processo %d, filho de %d \n", getpid(), getppid());
        printf( "\t Vou dormir um pouco - %d\n", getpriority(PRIO_PROCESS, 0 ) );
        nice(10);
        printf( "\t Vou dormir um pouco - %d\n", getpriority(PRIO_PROCESS, 0 ) );
      }
    break;
    default:      // excução do processo Pai    
      sleep(3);   
      printf( "\t Eu sou o processo Pai = %d, filho de %d \n", getpid(), getppid()); 
      printf(" Fim do Processo Pai\n");
      printf( "\t Prioridade - %d\n", getpriority(PRIO_PROCESS, 0 ) );
      nice(10);
      printf( "\t Prioridade - %d\n", getpriority(PRIO_PROCESS, 0 ) );
      
    break;
    }
    // execução de ambos os processos
    /*system("ps -f");
    if(pid > 0) {
      sleep(10);
      system("ps -aufx | grep fork2");
    }*/
    printf("Terminando o programa fork2 ... \n");
    exit (0);

}

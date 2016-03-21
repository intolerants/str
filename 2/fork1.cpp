// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa: fork1

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{

  // declarações de variáveis
  int i, j, k;
  pid_t pid = -2, pid2 = -2, pidn1 = -2, pidn2 = -2;          // definindo um identificador de processo - inteiro longo
  
  printf("Comecando o programa fork1 ... \n");
  sleep(1);
  printf("0 - Pai \n");
  // system("ps");
  
  pid = fork();   // dividindo o processo em dois
  if (pid == -1)       // erro na abertura do processo filho
    exit(1); 
  else if (pid == 0){        // Parte a ser executada pelo processo Filho1
    for(i=1;i<10;i++) {
      sleep(1);
      printf("--%d) Filho1 \n", i);
      system("pstree -p | grep fork1");
      if (i == 8){
        pidn1 = fork();
        if (pidn1 == 0) {
          for(j=1;j<10;j++) {
            sleep(1);
            printf("----%d) Neto1 \n", j);
            system("pstree -p | grep fork1");
          }
          printf("----KILL - Neto1\n");
          return 0;
        } 
      }
    }
    printf("--KILL - Filho1\n");
    return 0;
  } 
  else {       // parte a ser executada pelo processo Pai
    for(i=1;i<5;i++) {
       sleep(1);
       if (i == 2)
       {
          pid2 = fork();   // Cria Filho 2
          if (pid2 == 0) {
            for(j=1;j<10;j++) {
              sleep(1);
              printf("--%d) Filho2 \n", j);
              system("pstree -p | grep fork1");
              if (j == 8)
              {
                pidn2 = fork(); // Cria Neto 2
                if (pidn2 == 0)
                {
                  for(k=1;k<10;k++) {
                    sleep(1);
                    printf("----%d) Neto2 \n", k);
                    system("pstree -p | grep fork1");
                  }
                  printf("----KILL - Neto2\n");
                  return 0;
                }
              }
            }
            printf("--KILL - Filho2\n");
            return 0;
          }      
       }
       printf("%d) Pai \n", i);
       // system("ps -f | grep fork1");
    }
    printf("KILL - Pai\n");
  }
  // espera todas os processos terminarem evita impressao do fim do programa
  // sleep(17);
  exit (0);
}

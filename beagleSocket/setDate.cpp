#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define YEAR_DEPRECATED 2015

void manual(void){
  char date[30] /*= "1 May 2016 19:30:00"*/, cmd[40], c;
  while((c = getchar()) != '\n' && c != EOF); // clear buffer
  printf("Entre com a hora atual no formato (1 May 2016 19:30:00): \n");
  scanf ("%[^\n]%*c", date); // get string with spaces
  sprintf(cmd, "date --set \"%s\"", date);
  // printf("%s\n",cmd);
  system(cmd);
}

void automatic(void){
  printf("Aguardando servidor...\n");
  system("ntpdate-debian");
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
int currentYear(void) {
    time_t     now = time(0);
    struct tm  tstruct;
    tstruct = *localtime(&now);
    return (int)tstruct.tm_year+1900;
}

void checkDate(void){
  system("clear");
  if (currentYear() < YEAR_DEPRECATED)
  {
    char op = '\0';
    printf("Atualizar hora do sistema.\nEscolha uma opcao:\n(a)utomatico\n(m)anual\n(n)ao atualizar\n");
    while(op == '\0'){
      scanf("%c", &op);
      system("clear");
      switch(op){
        case 'a':
          automatic();
          break;
        case 'm':
          manual();
          break;
        case 'n':
          break;
        default:
          op = '\0';
      }
    }
  } else {
    printf("System date:\n");
    system("date");
    printf("\n");
  }
}

int main(int argc, char const *argv[])
{
  checkDate();
  return 0;
}
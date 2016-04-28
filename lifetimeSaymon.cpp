#include <iostream>
#include <time.h>

int main()
{
    //Tempo inicial e final
    time_t tempo_inicial, tempo_final, data_hora_segundos;
    tempo_inicial=0;
    tempo_final=0;
    data_hora_segundos=0;
    //Seta o tempo inicial para 01/01/1970 00:00:00
    time(&data_hora_segundos); // preenche a variável data_hora_segundos
    tm *tempo_inicial_info=localtime(&data_hora_segundos);

    tempo_inicial=mktime(tempo_inicial_info);

  //Seta o tempo final
    int x[3];
  
  std::cout << "ano aniversario: "; 
  std::cin >> x[0];

  std::cout << "mes aniversario: "; 
  std::cin >> x[1];
  
  std::cout << "dia aniversario: "; 
  std::cin >> x[2];
    
  tm* tempo_final_info=localtime(&tempo_final);

  tempo_final_info->tm_year=x[0]-1900; //ano (� necess�rio subtrair 1900, pois os anos iniciam em 1900)
  tempo_final_info->tm_mon=x[1]-1;  //m�s (� necess�rio subtrair 1, pois os meses iniciam no zero)
  tempo_final_info->tm_mday=x[2]; //dia
    tempo_final_info->tm_hour=0; //hora=00
    tempo_final_info->tm_min=0; //minuto=00
    tempo_final_info->tm_sec=0; //segundo=00

    tempo_final=mktime(tempo_final_info);

    std::cout << "Diferenca em segundos: " << tempo_inicial - tempo_final << std::endl;

    return 0;
}
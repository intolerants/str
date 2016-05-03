//  UFRN - ENG. COMP. - STR 2016.1
//  servidor.cpp
//  
//  by Hanoch, Saymon, Taynara
//  reference client5.cpp from Affonso on 25/04/16.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

typedef struct{
    int day;
    int month;
    int year;
}date;

typedef struct{
    int time;
    char description[34];
}details;

int calcTime(date birthday);


int main( )
{

    int server_sockfd, client_sockfd;
    size_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    date birthday;
    details feedback;
    int porta = 9738;

    unlink("server_socket");  // remocao de socket antigo
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);  // cria um novo socket
    
    server_address.sin_family = AF_INET;
    //server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // s� clientes locais
    server_address.sin_addr.s_addr  = INADDR_ANY;  // qualquer cliente
    server_address.sin_port = htons(porta);
    
    //strcpy(server_address.sun_path, "server_socket");
    
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
    
    listen(server_sockfd, 5);
    // system("clear");
    while(1) {
        printf("Servidor esperando na porta %d ...\n", porta);
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t *) &client_len);
        
        recv(client_sockfd, &birthday,sizeof(birthday),0);
        cout <<"\t\tRecebido " << birthday.day << "/" << birthday.month << "/" << birthday.year << endl;

        feedback.time = calcTime(birthday);      
        if (feedback.time < 748918912)
        {
            strcpy(feedback.description, "Novinh@ emmmmmm!");
        } else {
            strcpy(feedback.description, "Ta velh@ emmmmmm!");
        }
        send(client_sockfd, &feedback, sizeof(feedback),0);

        close(client_sockfd);
    }
}

int calcTime(date birthday){
    time_t tempo_inicial, tempo_final, data_hora_segundos;
    tempo_inicial=0;
    tempo_final=0;
    data_hora_segundos=0;
    //Seta o tempo inicial para 01/01/1970 00:00:00
    time(&data_hora_segundos); // preenche a variável data_hora_segundos
    tm *tempo_inicial_info=localtime(&data_hora_segundos);

    int time_diff;

    tempo_inicial=mktime(tempo_inicial_info);

    tm* tempo_final_info=localtime(&tempo_final);

    tempo_final_info->tm_year=birthday.year-1900; //ano (� necess�rio subtrair 1900, pois os anos iniciam em 1900)
    tempo_final_info->tm_mon=birthday.month-1;  //m�s (� necess�rio subtrair 1, pois os meses iniciam no zero)
    tempo_final_info->tm_mday=birthday.day; //dia
    tempo_final_info->tm_hour=0; //hora=00
    tempo_final_info->tm_min=0; //minuto=00
    tempo_final_info->tm_sec=0; //segundo=00

    tempo_final=mktime(tempo_final_info);

    //cout << "Tempo: " << tempo_inicial << " " <<  tempo_final << endl;
    time_diff = tempo_inicial - tempo_final;

    cout << "\t\tDiferenca em segundos: " << time_diff << endl;

    return time_diff;
}

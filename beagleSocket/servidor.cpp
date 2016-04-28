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

struct date {
    int day;
    int month;
    int year;
};

struct details
{
    int time;
    char description[34];
};


int main( )
{

    int server_sockfd, client_sockfd;
    size_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    date birthday;
    details feedback;
    int porta = 9733;


    char cmd = 'a';

    feedback.time = 100;
    strcpy(feedback.description, "Taynara ta velha");


    unlink("server_socket");  // remocao de socket antigo
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);  // cria um novo socket
    
    server_address.sin_family = AF_INET;
    //server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // s� clientes locais
    server_address.sin_addr.s_addr  = INADDR_ANY;  // qualquer cliente
    server_address.sin_port = porta;
    
    //strcpy(server_address.sun_path, "server_socket");
    
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
    
    listen(server_sockfd, 5);
    system("clear");
    while(1) {
        printf("Servidor esperando na porta %d ...\n", porta);
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t *) &client_len);
        
        read(client_sockfd, &birthday,sizeof(birthday));
        cout <<"\t\tRecebido " << birthday.day << "/" << birthday.month << "/" << birthday.year << endl;
        
        write(client_sockfd, &feedback, sizeof(feedback));

        close(client_sockfd);
        // cin >> cmd;
        // if(cmd == 'e')
        //     break;
    }
}
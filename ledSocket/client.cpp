//  UFRN - ENG. COMP. - STR 2016.1
//  client.cpp
//  
//  by Hanoch, Saymon, Taynara
//  reference client5.cpp from Affonso on 25/04/16.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <netdb.h>

using std::cout;
using std::cin;
using std::endl;

int main( )
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    unsigned short porta;

    int leds[4] = {1,1,1,1};

    struct hostent *nome_da_maquina;

    system("clear");

    char hostname[256] = "xuxu.local";
    // char hostname[256];
    porta = 8080;  // numero da porta

    // cout << "\tHostname: ";
    // cin >> hostname;
    // cout << "\tPort: ";
    // cin >> porta;
    
    cout <<"\t\tConectando ao " << hostname << ":" << porta << endl;

    // cout << "\tValores dos leds: ";
    // for (int i = 0; i < 4; i++)
    //     cin >> leds[i];

    cout <<"\t\tEnviando ";
    for (int i = 0; i < 4; i++)
        cout << leds[i] << " ";

    nome_da_maquina = gethostbyname(hostname);  // pegando a maquina a ser conectado
    if (nome_da_maquina == (struct hostent *) 0)
    {
        fprintf(stderr, "Gethostbyname falhou\n");
        exit(1);
    }

    // cout <<"\t\tConectando ao " << nome_da_maquina->h_addr << ":" << porta << endl;

    if( (sockfd  = socket(AF_INET, SOCK_STREAM,0) ) < 0)   // criacao do socket
    {
        perror(" Houve erro na abertura do socket ");
        exit (1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = *((unsigned long int *)nome_da_maquina->h_addr);
    address.sin_port = htons(porta);
    
    len = sizeof(address);
    
    result = connect(sockfd, (struct sockaddr *) &address, len);
    
    if (result == -1)
    {
        perror ("Houve erro no cliente");
        exit(1);
    }
    
    write(sockfd, leds, sizeof(int)*4);
    
    close(sockfd);
    exit(0);
}
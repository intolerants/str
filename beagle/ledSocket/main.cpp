#include <iostream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char * argv[])
{
    BlackLib::BlackGPIO led0(BlackLib::GPIO_67,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO led1(BlackLib::GPIO_68,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO led2(BlackLib::GPIO_44,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO led3(BlackLib::GPIO_26,BlackLib::output, BlackLib::SecureMode);

    int server_sockfd, client_sockfd;
    size_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    int size = 4, leds[size] = {0};
    int porta = 9739;

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
    while(true) {
        printf("Servidor esperando na porta %d ...\n", porta);
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t *) &client_len);
        
        recv(client_sockfd,leds,size*sizeof(int),0);
        printf("\t\tRecebido: %d %d %d %d\n", leds[0], leds[1], leds[2], leds[3]);
     
        leds[0] == 0 ? led0.setValue(BlackLib::low) : led0.setValue(BlackLib::high);
        leds[1] == 0 ? led1.setValue(BlackLib::low) : led1.setValue(BlackLib::high);
        leds[2] == 0 ? led2.setValue(BlackLib::low) : led2.setValue(BlackLib::high);
        leds[3] == 0 ? led3.setValue(BlackLib::low) : led3.setValue(BlackLib::high);

        close(client_sockfd);
    }

    return 0;
}

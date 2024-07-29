#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>


int main (){

    int client_socket;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1){

        perror("socket creation failed");

        exit(EXIT_FAILURE);
    
    }


    struct sockaddr_in serv = {0};

    serv.sin_family = AF_INET;

    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr.s_addr);

    serv.sin_port = htons(2048);

    

    int connected = connect ( client_socket, (const struct sockaddr*)&serv, sizeof(serv) );

    if (connected == -1) {

        perror("failed to connect");

        close(client_socket);

        exit(EXIT_FAILURE);


    }

    char * hello = "a big step for humanity";

    
    int sending = send(client_socket, hello, strlen(hello), 0 );

    char recv_buf[1024];

    int receiving = recv(client_socket, recv_buf, 1024, 0);

    recv_buf[receiving] = '\0';

    printf("Server: %s \n", recv_buf);

}
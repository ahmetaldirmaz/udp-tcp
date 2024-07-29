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

    int socketfd;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd == -1){

        perror("socket creation failed");

        exit(EXIT_FAILURE);
    
    }

    struct sockaddr_in serv_addr = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(2048);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int bind_check = bind(socketfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr) );

    if (bind_check == -1){

        perror("binding failed");

        close(socketfd);

        exit(EXIT_FAILURE);

    }
    
    // int listen(int sockfd, int backlog)
    int listen_check = listen(socketfd, 5);

    if (listen_check == -1){

        perror("listen failed");

        close(socketfd);

        exit(EXIT_FAILURE);

    }

    struct sockaddr_in client_addr = {0};

    socklen_t len = sizeof(client_addr);



    //int accept(int sockfd, struct sockaddr * addr, socklen_t * addrlen)

    int sockfd2 = accept (socketfd, (struct sockaddr *) &client_addr, &len );

    if (sockfd2 == -1 ) {

        perror("accepting failed. Terminating like schwarzenegger");

        close(socketfd);

        exit(EXIT_FAILURE);
    }
    else{

        printf("connected/n");
    }


    // recv from client

    char buf[1024];

    int recved = recv(sockfd2, buf, 1024, 0);

    if (recved == -1){

        perror("received? doesnt look like that");

        close(socketfd);
        close(sockfd2);

        exit(EXIT_FAILURE);

    }

    buf[recved] = '\0';
    printf("client: %s\n", buf);


    char * hi = "here to serve you";

    int sent = send(sockfd2, hi, strlen(hi), 0);

    if (sent == -1){

        perror("not sent. don't use aras kargo next time");

        close(socketfd);
        close(sockfd2);

        exit(EXIT_FAILURE);

    }

    close(sockfd2);
    close(socketfd);
    
    return 0;

}
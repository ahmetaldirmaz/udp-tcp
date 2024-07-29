#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main (){


    int socketfd;

    socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketfd == -1){

        perror("socket creation failed miserably, save us the lord..");

        exit(EXIT_FAILURE);

    }

    struct sockaddr_in client_addr = {0};

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(2050);
  

    int binding = bind(socketfd, (const struct sockaddr *) &client_addr, sizeof(client_addr));

    if (binding == -1 ){

        perror("binding failed, terminating");

        close(socketfd);
        
        exit(EXIT_FAILURE);

    }

    struct sockaddr_in serv_addr = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(2048);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);


    const char * text = "i am the client";

    //       ssize_t sendto(int sockfd, const void buf[.len], size_t len, int flags,
    //                 const struct sockaddr *dest_addr, socklen_t addrlen);
    
    
    int s = sendto( socketfd, text, strlen(text), 0, (const struct sockaddr *)&serv_addr,  sizeof(serv_addr) );

    if (s == -1)
    {

        perror("sending failed");

        close(socketfd);

        exit(EXIT_FAILURE);

    }

    char msge [80] = {0};

    socklen_t source_len = sizeof(serv_addr);


    int n = recvfrom(socketfd, msge, 80, MSG_WAITALL, NULL, 0);


    if (n == -1) {
        
        perror("recvfrom error");
 
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    
    msge[n] = '\0';
    printf("Server : %s\n", msge);

    close(socketfd);

    return 0;

    
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main (){


    int sockfd;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); //three parameters, domain - type - protocol
    
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(2048);

    int bind_rc = bind(sockfd, (const struct sockaddr * ) &serv_addr, sizeof(serv_addr));

    if (bind_rc == -1){

        perror("binding failed");
        close(sockfd);
        exit(EXIT_FAILURE);

    }


    char msge[80] = {0};
    // the buff for the message

    // *** recvfrom func ***
    //ssize_t recvfrom(int sockfd, void buf[restrict .len], size_t len, int flags,
    //  struct sockaddr * src_addr, socklen_t * addrlen);
    
    // returns number of bytes received or -1

    //source address
    struct sockaddr_in source_addr = {0};

    // addrlen - source addr len - is a value-result argument.
    // Before the call, it should be initialized
    // to the size of the buffer.  Upon return,
    // addrlen is updated to contain the actual size of the source address.

    socklen_t source_len = sizeof(source_addr);



    //MSG_WAITALL flag
    //This flag requests that the operation block until the full
    //request is satisfied.

    int n = recvfrom(sockfd, msge, 80, MSG_WAITALL, (struct sockaddr *) &source_addr, &source_len );


    if (n == -1) {
        
        perror("recvfrom error");
 
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    msge[n] = '\0';
    printf("Client : %s\n", msge);

    // Send response
    
    const char *response = "Hello from server";
    sendto(sockfd, response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &source_addr, source_len);
    printf("Response sent.\n");

    // Close socket
    close(sockfd);

    
    return 0;

}

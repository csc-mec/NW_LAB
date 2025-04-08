#include <netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFFER_SIZE 1024

int main(){
    char buffer[BUFFER_SIZE];
    int sockfd;
    socklen_t len;
    struct sockaddr_in server,client;
    char answer[BUFFER_SIZE];
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        perror("Failed Socket Creation\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);
    len=sizeof(server);
    printf("Enter the number:");
    fgets(buffer,BUFFER_SIZE,stdin);
    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&server,sizeof(server));
    printf("Sent to Client\n");
    recvfrom(sockfd,answer,BUFFER_SIZE,0,(struct sockaddr*)&server,&len);
    printf("Server:%s\n",answer);
    close(sockfd);
}

/* output
./cli
Enter the number:24
Sent to Client
Server:Two Four
*/

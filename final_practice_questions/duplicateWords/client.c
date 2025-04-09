#include <netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024

int main(){

    int sockfd,newfd;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char buffer[BUFFER_SIZE];

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));

    printf("Enter the String:");
    fgets(buffer,BUFFER_SIZE,stdin);
    send(sockfd,buffer,BUFFER_SIZE,0);
    memset(buffer,0,BUFFER_SIZE);
    printf("Formatting...\n");
    recv(sockfd,buffer,BUFFER_SIZE,0);
    printf("%s",buffer);
    close(sockfd);
}

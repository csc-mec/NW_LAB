#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFFER_SIZE 1024

int main(){
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server,client;
    int sockfd,newfd;
    socklen_t len;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    if((connect(sockfd,(struct sockaddr*)&server,sizeof(server)))){
        perror("No connection done\n");
        exit(0);
    }
    read(sockfd,buffer,BUFFER_SIZE);
    printf("Server:%s\n",buffer);
    memset(buffer,0,BUFFER_SIZE);
    printf("Enter the string:");
    fgets(buffer,BUFFER_SIZE,stdin);
    send(sockfd,buffer,strlen(buffer),0);

    close(sockfd);
}

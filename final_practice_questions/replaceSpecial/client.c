#include <ctype.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024

int main(){
    struct sockaddr_in server,client;
    int sendfd,newfd;
    socklen_t len=sizeof(server);
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    char special;

    sendfd=socket(AF_INET,SOCK_STREAM,0);
    if(sendfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sendfd,(struct sockaddr*)&server,len);
    printf("Enter string:");
    fgets(buffer,BUFFER_SIZE,stdin);
    send(sendfd,buffer,strlen(buffer),0);
    printf("Sent the sentence\n");

    printf("Enter the special character:");
    scanf("%s",&special);
    send(sendfd,&special,sizeof(char),0);
    printf("Character sent\n");

    recv(sendfd,response,BUFFER_SIZE,0);
    printf("%s\n",response);
    close(sendfd);
}

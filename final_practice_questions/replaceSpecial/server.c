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
    socklen_t len=sizeof(client);
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    char special;

    sendfd=socket(AF_INET,SOCK_STREAM,0);
    if(sendfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    if((bind(sendfd,(struct sockaddr*)&server,sizeof(server))<0)){
        perror("Binding Failed\n");
        exit(0);
    }

    if(listen(sendfd,5)<0){
        perror("No one to listen to\n");
        exit(0);
    }

    newfd=accept(sendfd,(struct sockaddr*)&client,&len);
    if(newfd<0){
        perror("Error creating the receiver socket\n");
        exit(0);
    }

    if(recv(newfd,buffer,BUFFER_SIZE,0)<0){
        perror("Failed to receive input\n");
        exit(0);
    }
    if(recv(newfd,&special,sizeof(char),0)<0){
        perror("Failed to receive special character\n");
        exit(0);
    }
    for(int i=0;buffer[i]!='\0';i++){
        if(isspace(buffer[i])){
            buffer[i]=special;
        }
    }
    printf("%s\n",buffer);
    sprintf(response,"Formatted String:%s\n",buffer);
    send(newfd,response,strlen(response),0);
    close(sendfd);
    close(newfd);
}

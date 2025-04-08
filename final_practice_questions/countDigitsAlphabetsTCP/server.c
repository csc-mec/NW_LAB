#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<ctype.h>

#define BUFFER_SIZE 1024

int main(){
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server,client;
    int sockfd,newfd;
    socklen_t len;
    int num=0,alp=0;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    if((bind(sockfd,(struct sockaddr*)&server,sizeof(server)))<0){
        perror("Binding Failed\n");
        exit(0);
    }

    if((listen(sockfd,5))<0){
        perror("Listening Failed\n");
        exit(0);
    }
    len=sizeof(client);
    newfd=accept(sockfd,(struct sockaddr*)&client,&len);

    // printf("Enter message:");
    // fgets(buffer,BUFFER_SIZE,stdin);

    memset(buffer,0,BUFFER_SIZE);
    read(newfd,buffer,BUFFER_SIZE);
    for(int i=0;buffer[i]!='\0';i++){
        if(isalpha(buffer[i])){
            alp++;
        }
        else if(isdigit(buffer[i])){
            num++;
        }
    }
    sprintf(buffer,"Output Obtained\n%d - Numbers\n%d - Alphabets",num,alp);
    send(newfd,buffer,BUFFER_SIZE,0);
    printf("Client:%s\n",buffer);
    printf("Numbers:%d\n",num);
    printf("Alphabets:%d\n",alp);
    close(newfd);
    close(sockfd);
}

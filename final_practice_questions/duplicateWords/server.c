#include <netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024
#define WORD_LIMIT 20
#define WORD_SIZE 20

int main(){

    int sockfd,newfd;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char buffer[BUFFER_SIZE],response[BUFFER_SIZE];

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

    if(listen(sockfd,5)<0){
        perror("Listening Failed\n");
        exit(0);
    }

    newfd=accept(sockfd,(struct sockaddr*)&client,&len);
    if(newfd<0){
        perror("Socket for Sender Failed\n");
        exit(0);
    }

    char* words[BUFFER_SIZE];
    recv(newfd,buffer,BUFFER_SIZE,0);
    printf("Received String:%s\n",buffer);
    int ind=0;
    int wordCount=0;
    char* token=strtok(buffer," \t\n");
    while(token!=NULL){
        int isDuplicate=0;
        for(int i=0;i<wordCount;i++){
            if(strcmp(words[i],token)==0){
                isDuplicate=1;
                break;
            }
        }
        if(!isDuplicate){
            words[wordCount++]=token;
        }
        //printf("Infinityy\n");
        token=strtok(NULL," \t\n");
    }
    printf("Sending the Formatted Sentence\n");
    for(int i=0;i<wordCount;i++){

        strcat(response,words[i]);
        strcat(response," ");
        printf("%s",words[i]);
    }
    send(newfd,response,sizeof(response),0);
    close(sockfd);
    close(newfd);
}

#include <netinet/in.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 1024
#define MAX 20

int main(){

    int sockfd,clientfd;
    struct sockaddr_in server,client;
    socklen_t len;
    int rows,columns;
    char buffer[BUFFER_SIZE];
    int matrix1[MAX][MAX],matrix2[MAX][MAX];

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    printf("Enter no. of rows:");
    scanf("%d",&rows);
    printf("Enter no. of columns:");
    scanf("%d",&columns);

    printf("Enter Matrix :\n");
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            scanf("%d",&matrix1[i][j]);
        }
    }
    // printf("Enter Matrix 2:\n");
    // for(int i=0;i<rows;i++){
    //     for(int j=0;j<columns;j++){
    //         scanf("%d",&matrix2[i][j]);
    //     }
    // }

    len=sizeof(server);
    connect(sockfd,(struct sockaddr*)&server,len);

    send(sockfd,&rows,sizeof(int),0);
    send(sockfd,&columns,sizeof(int),0);

    printf("Sending Matrix \n");
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            send(sockfd,&matrix1[i][j],sizeof(int),0);
        }
    }
    // printf("Sending Matrix 2\n");
    // for(int i=0;i<rows;i++){
    //     for(int j=0;j<columns;j++){
    //         send(sockfd,&matrix2[i][j],sizeof(int),0);
    //     }
    // }

    recv(sockfd,buffer,BUFFER_SIZE,0);
    printf("Result:%s\n",buffer);

    close(sockfd);
}

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
    const char* words[10]={"Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        perror("Failed Socket Creation\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);
    len=sizeof(client);
    if((bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)){
        perror("Binding Failed\n");
        exit(0);
    }
    int bytesReceived;
    //char wordsResponse[BUFFER_SIZE];
    bytesReceived=recvfrom(sockfd,buffer,BUFFER_SIZE-1,0,(struct sockaddr*)&client,&len);
    if(bytesReceived>0){
        buffer[bytesReceived]='\0';
        printf("Client:%s\n",buffer);
        char wordsResponse[BUFFER_SIZE]="";

        for(int i=0;buffer[i]!='\0';i++){
            if(buffer[i]>='0'&& buffer[i]<='9'){
                if(strlen(wordsResponse)>0){
                    strcat(wordsResponse," ");
                }
                int index=buffer[i]-'0';
                strcat(wordsResponse,words[index]);
           }
        }
        sendto(sockfd,wordsResponse,strlen(wordsResponse),0,(struct sockaddr*)&client,len);
    }
    close(sockfd);
}
/* output
./ser
Client:24
*/

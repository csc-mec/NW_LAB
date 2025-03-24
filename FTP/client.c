#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
  int client;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE] = {0};
  char filename[BUFFER_SIZE] = {0};

  client = socket(AF_INET,SOCK_STREAM,0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(client,(struct sockaddr *)&server_addr,sizeof(server_addr));

  printf("Filename : ");
  scanf("%s",filename);

  send(client,filename,strlen(filename),0);

  while(recv(client,buffer,BUFFER_SIZE,0)>0){
    printf("%s",buffer);
    memset(buffer,0,BUFFER_SIZE);
  }

  close(client);
  return 0;
}

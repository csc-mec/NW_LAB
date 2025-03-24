#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(){
  int server;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in server_addr;
  int size = sizeof(server_addr);
  struct sockaddr_storage store;

  server = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(5556);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  strcpy(buffer,"UDP CLIENT ECHO\n\0");
  sendto(server,buffer,16,0,(struct sockaddr *)&server_addr,size);

  recvfrom(server,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_addr,&size);
  printf("Recieved : %s\n",buffer);

  close(server);
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(){
  int server;
  char buffer[BUFFER_SIZE];

  struct sockaddr_in server_addr,client_addr;
  int size = sizeof(server_addr);
  struct sockaddr_storage store;
  socklen_t addr_size;

  server = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(5556);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(server , (struct sockaddr *)&server_addr , sizeof(server_addr));

  recvfrom(server,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_addr,&size);
  printf("Recieved : %s\n",buffer);

  strcpy(buffer,"UDP SERVER ECHO\n\0");
  sendto(server,buffer,17,0,(struct sockaddr *)&server_addr,size);

  close(server);

  return 0;
}

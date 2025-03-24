#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void main(){
  int client;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in server_addr;
  struct sockaddr_storage store;

  socklen_t addr_size;

  client = socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5555);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(client , (struct sockaddr *)&server_addr , sizeof(server_addr));

  strcpy(buffer, "Hi Server !\n");
  send(client,buffer,11,0);
  recv(client,buffer,BUFFER_SIZE,0);
  printf("Recieved : %s \n",buffer);
  close(client);
}

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void main(){
  int server, client;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in server_addr;
  struct sockaddr_storage store;
  socklen_t addr_size;

  server = socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5555);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(server,(struct sockaddr *)&server_addr,sizeof(server_addr));

  int listen_status = listen(server,5);

  if(!listen_status){
    printf("Listening....\n");
  }else{
    printf("Unable to listen Exiting ....\n");
    return;
  }

  client = accept(server , (struct sockaddr *)&store , &addr_size);

  recv(client,buffer,BUFFER_SIZE,0);
  printf("Recieved : %s \n",buffer);
  
  strcpy(buffer,"Hi,Client this is server\n\0");
  printf("Sending Data to Client\n");

  send(client,buffer,25,0);

  close(client);
  close(server);

  return;
}


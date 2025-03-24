#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handleClient(int client_socket){
  char buffer[BUFFER_SIZE] = {0};
  char filename[BUFFER_SIZE] = {0};

  int recv_size = recv(client_socket,filename,BUFFER_SIZE,0);
  
  if(recv_size < 0){
    printf("Cannot recieve filename \n");
    return;
  }

  FILE *file = fopen(filename,"r");
  if(file == NULL ){
    strcpy(buffer,"404");
    send(client_socket,buffer,3,0);
    return;
  }
  else{
    while(fgets(buffer,BUFFER_SIZE,file) != NULL){
      send(client_socket,buffer,strlen(buffer),0);
      memset(buffer,0,BUFFER_SIZE);
    }
  }

  fclose(file);
  close(client_socket);
}

int main(){
  int server,client;
  struct sockaddr_in server_addr,client_addr;
  socklen_t addr_len = sizeof(client_addr);

  server = socket(AF_INET,SOCK_STREAM,0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(server,(struct sockaddr *)&server_addr,sizeof(server_addr));
  listen(server,5);

  while(1){
    client = accept(server,(struct sockaddr *)&client_addr,&addr_len);
    handleClient(client);
  }

  close(server);
  return 0;
}

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(){
  int client;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in server_addr;

  socklen_t addr_size;

  client = socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5555);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(client , (struct sockaddr *)&server_addr , sizeof(server_addr));
  printf("Connected to server\n");



  printf("client : ");
  fgets(buffer, BUFFER_SIZE, stdin);
  // Instead of next two lines it is also possible to use `scanf("%s", buffer)` , the program will not be able to take white spaces in inputs with scanf
  buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
  send(client,buffer,strlen(buffer),0);


  while(1){
      memset(buffer, 0, BUFFER_SIZE); //memset clears the buffer
      recv(client, buffer, BUFFER_SIZE, 0);
      printf("server : %s\n",buffer);
      if(strcmp("bye", buffer) == 0){
          send(client, buffer, strlen(buffer), 0);
          printf("Closing Connection\n");
          break;
      }
      memset(buffer, 0, BUFFER_SIZE);
      printf("client : ");
      fgets(buffer, BUFFER_SIZE, stdin);
      buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
      send(client, buffer, strlen(buffer), 0);
  }

  close(client);
  printf("Chat ended, Exiting... \n");
  return 0;
}

#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main(){
    int server,client;
    char buffer[BUFFER_SIZE];

    struct sockaddr_in server_addr;
    struct sockaddr_storage store;

    socklen_t addr_size;

    server = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5555);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server,(struct sockaddr *)&server_addr , sizeof(server_addr));
    listen(server, 10);
    client = accept(server, (struct sockaddr *)&store, &addr_size);
    printf("Connected to client !\n");
    recv(client, buffer, BUFFER_SIZE, 0);
    printf("client : %s\n",buffer);
    // Above Part is same as TCP and this program


    while(1){
        if(strcmp("bye", buffer) == 0){
            send(client, buffer, strlen(buffer), 0);
            printf("Closing Connection\n");
            break;
        }
        memset(buffer, 0, BUFFER_SIZE); //memset clears the buffer
        printf("server : ");
        scanf("%s",buffer);
        send(client, buffer, strlen(buffer), 0);
        memset(buffer, 0, BUFFER_SIZE);
        recv(client, buffer, BUFFER_SIZE, 0);
        printf("client : %s\n",buffer);
    }
    close(client);
    close(server);
    printf("Chat ended, Exiting... \n");
    return 0;
}

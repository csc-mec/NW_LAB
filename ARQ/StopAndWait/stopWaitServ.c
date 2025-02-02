#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
int main(){
	int socket_desc,new_sock;
	char buffer[1024],msg[10],rec[10];
	struct sockaddr_in server_addr;
	struct sockaddr_storage store;
	socklen_t sock_size = sizeof(store);
	
	if((socket_desc = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		printf("Error in socket creation \n");
		return 0;
		}
	printf("Socket successfully created\n");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(6400);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(server_addr.sin_zero,'\0',sizeof(server_addr.sin_zero));
	
	if((bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr)))!=0){
		printf("Error while binding \n");
		return 0;
		}
	printf("Socket succcessfully binded\n");
	if(listen(socket_desc,5)==0){
		printf("Listening ... \n");
		}
	else{
		printf("Error\n");
		return 0;
		}
	if((new_sock = accept(socket_desc,(struct sockaddr*)&store,&sock_size))<0){
		printf("Accept failed\n");
		return 0;
		}
	printf("Successfully accepted connection\n");
	
	int k=5,m=1;
	
	while(k>0){
		int i=2,stat=-1;
		while(i>0){
			if((stat=recv(new_sock,buffer,sizeof(buffer),0))<0){
				sleep(1);
				i--;
			}
			else{break;}
		}
		if(stat<=0){
			printf("Failed to receive msg, sending ack for it again\n ");
			rec[0]=(char)(m+48);
			rec[1]='\0';
			strcpy(msg,rec);
			send(new_sock,msg,strlen(msg),0);
			continue;
		}
		if(strncmp(buffer,"frame",5)!=0){
			printf("invalid msg receieved : %s\n",buffer);
			close(new_sock);
			close(socket_desc);
			exit(0);
		}
		printf("Receieved msg is : %s\n",buffer);
		m++;
		rec[0]=(char)(m+48);
		//printf("%c\n",rec[0]);
		rec[1]='\0';
		strcpy(msg,rec);
		send(new_sock,msg,strlen(msg),0);
		k--;
		strcpy(buffer,"");
	}
	close(socket_desc);
	close(new_sock);
}

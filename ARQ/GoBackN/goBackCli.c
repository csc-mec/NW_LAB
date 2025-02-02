#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){
	int socket_desc;
	char buffer[1024],msg[10],rec[10];
	struct sockaddr_in server_addr;
	socklen_t sock_size = sizeof(server_addr);
	
	if((socket_desc = socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Error in socket creation \n");
		return 0;
		}
	printf("Socket successfully created\n");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(6500);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(server_addr.sin_zero,'\0',sizeof(server_addr.sin_zero));
	
	if((connect(socket_desc,(struct sockaddr*)&server_addr,sock_size))<0){
		printf("Error in connecting\n");
		return 0;
		}
	printf("Connection requested\n");
	int k=9,m=1,w=0;
	while(m<=k){
		printf("Enter msg to be send to server : ");
		char input[50];
		scanf("%s",input);
		buffer[0]=((char)(m+48));
		buffer[1]='\0';
		strcat(buffer,input);
		send(socket_desc,buffer,strlen(buffer),0);
		if(w<2){w=w+1;m++;continue;}
		w=0;
		int i=2,stat=-1;
		while(i>0){
			if((stat=recv(socket_desc,msg,sizeof(msg),0))<0){
				sleep(1);
				i--;
			}
			else{break;}
		}
		if(stat<=0){
			printf("Ack not receieved properly, sending msg again\n");
			m=m-2;
			continue;
		}
		else if(atoi(msg)<m){
			printf("msg not receieved, sending it again\n");
			m=m-2;
			continue;
		}
		else if(atoi(msg)==m){
			if(m==9){break;}
			printf("Acknoledgment receieved properly,  send next msg \n");
			m++;
		}
		else{
			printf("invalid ack receieved %d\n",atoi(msg));
			close(socket_desc);
			exit(0);
		}
		
	}
	
	close(socket_desc);
}

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdbool.h>
int main(){
	int socket_desc,new_sock;
	bool err=false,check;
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
	server_addr.sin_port=htons(6500);
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
	int k=9,m=1,w=0;
	int arr[3];
	char buff2 [3][1024];
	memset(buff2,'\0',sizeof(buff2));
	memset(buffer,'\0',sizeof(buffer));
	memset(arr,-1,sizeof(arr));
	while(m<=k){
		err=false;
		check=false;
		int i=2,stat=-1;
		while(i>0){
			if((stat=recv(new_sock,buffer,sizeof(buffer),0))<0){
				sleep(1);
				i--;
			}
			else{break;}
		}
		if(stat<=0 || buffer[0]!=((char)(m+48))){
			arr[w]=m;
			err=true;
		}
		else{
			strcpy(buff2[w],buffer);
		}
		if(w==2){
			for(int i=0;i<3;i++){
				if(arr[i]!=-1){
					rec[0]=(char)(m+48);
					rec[1]='\0';
					strcpy(msg,rec);
					send(new_sock,msg,strlen(msg),0);
					check=true;
					m=m-3;
					memset(arr,-1,sizeof(arr));	
					memset(buff2,'\0',sizeof(buff2));
					break;
				}
				else{
					printf("frame %d : %s\n",(m-2+i),buff2[i]);
				}
				if(!check && i==2){
					rec[0]=(char)(m+48);
					rec[1]='\0';
					strcpy(msg,rec);
					memset(arr,-1,sizeof(arr));
					memset(buff2,'\0',sizeof(buff2));
					send(new_sock,msg,strlen(msg),0);
				}
			}
		}
		w=(w+1)%3;
		m++;
		memset(buffer,'\0',sizeof(buffer));
	}

	close(socket_desc);
	close(new_sock);
}

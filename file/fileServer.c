#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
int main(void){
	int listenfd = 0;
	int connfd = 0;
	struct sockaddr_in serv_addr;
	char receivedBuff[256];
	int numrv;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket retrieve success\n");
	memset(&serv_addr, '0', sizeof(serv_addr));
	//memset(receivedBuff, '0', sizeof(receivedBuff));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);
	bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(listen(listenfd, 10) == -1) {
		printf("Failed to listen\n");
		return -1;
	}
	while(1) {
		connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
		/* Open the file that we wish to transfer */
		FILE *fp = fopen("server.txt","rb");
		if(fp==NULL) {
			printf("File opern error");
			return 1;
		}
		
		int nread = fread(receivedBuff,1,256,fp);
		printf("Bytes read %d \n", nread); 
		/* Read data from file and send it */
	
			send(connfd,receivedBuff, nread,0);
				//printf("%s \n", recvBuff);
		
			
		
	}
	close(connfd);
	sleep(1);
	
	return 0;
}


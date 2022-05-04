#include<stdio.h> //udps.c
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define BUFLEN 255
#define PORT 8885
void die(char *s) {
perror(s);
exit(1);
}
int main(void) {
	struct sockaddr_in si_me, si_other;
	int s, slen = sizeof(si_other) , recv_len=0;
	unsigned long flen=0;
	char buf[BUFLEN], fname[20];
	FILE *fp;
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		("socket");
	}
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
		die("bind");
	}
	// receive fileName
	recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen);
	printf("%s\n",buf);
	strcpy(fname,"a.txt");
	fp=fopen(fname,"wb");
	memset(buf,0,BUFLEN);
	// receive bytes
	recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen);
	flen = atoi(buf);
	printf("%ld\n",flen);
	
	for(int i = 0 ; i < (flen/256)+1 ; i++){
		memset(buf,0,BUFLEN);
		if ((recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
				die("recvfrom()");
		}
		printf("%s",buf);
		
		fseek( fp, 0, SEEK_END);
		fputs(buf,fp);
		//fwrite(buf,flen, 1, fp);
	}
	//printf("%s==%ld\n",buf, flen);
	fclose(fp); close(s); return 0;
}
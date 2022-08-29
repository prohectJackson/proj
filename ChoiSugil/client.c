#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

void *sendMsg(void *arg)
{
	int dataSocket = *(int *)arg;
	char bufs[1024];
	int len;
	for (;;){
		fgets(bufs, 1024, stdin);
		if (strcmp(bufs, "/q\n")== 0 )
			break;
		for(int i=0;i<strlen(bufs);i++){
			if(bufs[i] == '\n')
				// len = i+1;
				bufs[i] = '\0';

		}

		write(dataSocket, bufs, strlen(bufs));
		printf("sending message buf: %s\t nread:  strlen(buf): %ld\n", bufs, strlen(bufs));
	}
	
	close(dataSocket);
	exit(0);

	return NULL;
}

void *recvMsg(void *arg)
{
	int dataSocket = *(int *)arg;
	char buf[1024];
	for (;;){
		int nread = read(dataSocket, buf, 1024);
		if (nread == -1){
			// error
		}
		buf[nread] = '\0';
		printf("receiving message buf: %s\t nread: %d strlen(buf): %ld\n", buf,nread, strlen(buf));
	}
}

int main(void)
{
	int dataSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(dataSocket == -1){
		fprintf(stderr, "can't creat socket()\n");
		exit(1);
	}

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("192.168.35.155");
	serverAddr.sin_port = htons(7000);

	int re;
	re = connect(dataSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
	if (re == -1){
		fprintf(stderr, "can't connect socket()\n");
		exit(2);
	}

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, sendMsg, (void *)&dataSocket);
	pthread_create(&tid2, NULL, recvMsg, (void *)&dataSocket);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);


	return 0;
}
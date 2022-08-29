#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int dataSockets[1000];
int count;

pthread_mutex_t mutex;

void *threadProc(void *arg)
{
	int dataSocket = *(int *)arg;

	char buf[1024];
	int nread;
	int cnt =0;
	while ((nread = read(dataSocket, buf, 1024))> 0){
		printf("%d",++cnt);
		if (nread == -1){
			fprintf(stderr, "read() error\n");
			exit(5);
		}
		buf[nread]='\0';
		printf("buf: %s\n", buf);
		// atonic 하게 만들어야 할 부분. 
pthread_mutex_lock(&mutex);
		for (int i=0;i<count;++i){
			write(dataSockets[i], buf, nread);// nread
			printf("writing: datasocket Number %d\n", dataSockets[i]);
		}
pthread_mutex_unlock(&mutex);
	}
	// EOF
	// 아토믹. 전역데이타에 접근 
pthread_mutex_lock(&mutex);
	printf("client disconneted!! %d\n",  dataSocket);
	for (int i =0; i<count;++i){
		if(dataSocket == dataSockets[i]){
			for(int j =i; j< count-1;++j){
				dataSockets[j] = dataSockets[j+1];
			}
		}
	}
	--count;
pthread_mutex_unlock(&mutex);

	close(dataSocket);

	return NULL;
}


int main(void)
{
	pthread_mutex_init(&mutex, NULL);


	int serverSocket; 		// file descriptor 파일 기술자.
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1){
		fprintf(stderr, "can't open socket()");
		exit(1); 
	}

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(7000);
	int re;
	re = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
	if( re == -1){
		fprintf(stderr, "bind() error\n");
		exit(2);
	}
	// printf("%d", INADDR_ANY);
	re = listen(serverSocket, 5);
	if( re == -1){
		fprintf(stderr, "listen() error\n");
		exit(3);
	}
	for (;;) {
		//accept(serverSocket, NULL, NULL ); 클라이언트 주소에 관심 없음. 
		struct sockaddr_in clientAddr;
		int addrLen = sizeof(struct sockaddr_in);
		
		int dataSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
		if (dataSocket == -1){
			fprintf(stderr, "accept() error\n");
			exit(4);
		}

		fprintf(stdout, "client ip: %s\n", inet_ntoa(clientAddr.sin_addr));

		// 아토믹. 
pthread_mutex_lock(&mutex);
		dataSockets[count] = dataSocket;
		++count;
pthread_mutex_unlock(&mutex);

		pthread_t tid;
		pthread_create(&tid, NULL, threadProc, (void *)&dataSocket);
		pthread_detach(tid);	// 좀비 쓰레드 없애기.

	}
	

	close(serverSocket);
	return 0;

}
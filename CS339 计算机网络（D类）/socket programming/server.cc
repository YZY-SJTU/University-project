#include <stdio.h> // standard input and output library
#include <stdlib.h> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <errno.h> //It defines macros for reporting and retrieving error conditions through error codes
#include <time.h> //contains various functions for manipulating date and time
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 2017
#define QUEUE_SIZE 20
#define BUFFER_SIZE 1024

void *handle_client(void *arg)
{
	char begintime[BUFFER_SIZE];
	char dataSending[BUFFER_SIZE]; // Actually this is called packet in Network Communication, which contain data and send through.	
	int writelen;
	int clintConnt = *(int *) arg;
	time_t clock;
	int handle = open("file.txt", O_RDONLY);	
	int res;

	//send begin time message to client
	memset(begintime, '0', sizeof(begintime));
	clock = time(NULL);
	snprintf(begintime, sizeof(begintime), "%.24s\r\n", ctime(&clock)); // Printing successful message
	res = write(clintConnt, begintime, strlen(begintime));
	//printf("server subthread write test res:%d\n", res);

	//handle all the packets of the file and transfer
	while(1){
		memset(dataSending, '0', sizeof(dataSending));
		//need to connect the target file and use send() to clients
		writelen = read(handle, dataSending, strlen(dataSending));
		if(writelen < 0){
			printf("write failed\n");
			//printf("%d",clintConnt);
			break;
		}
		else if(writelen == 0){
			printf("write exit\n");
			break;		
		}
		else{
			//printf("server transfer: %s", dataSending);
			res = write(clintConnt, dataSending, writelen);//unsuccess in sub thread
			if(res < 0){
				printf("write to client failed\n");				
				break;			
			}
			//printf("server write test res:%d, writelen:%d\n", res, writelen);
		}
	}
	close(handle);
	close(clintConnt);

	/* the function must return something - NULL will do */
	return NULL;

}
 
int main()
{	
	time_t clock;	
	int clintListn = 0, clintConnt = 0, ret = 0;
	pthread_t pid;
	struct sockaddr_in ipOfServer;
	clintListn = socket(AF_INET, SOCK_STREAM, 0); // creating socket
	memset(&ipOfServer, '0', sizeof(ipOfServer)); //define socketaddr_in
	
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer.sin_port = htons(PORT); 		// this is the port number of running server
	ret = bind(clintListn, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer)); //bind
	if(ret < 0){
		perror("bind failed");
		return -1;
	}
	ret = listen(clintListn , QUEUE_SIZE); //listen
	if(ret < 0){
		perror("listen failed");
		return -1;
	} 	
	
	while(1)
	{
		//process block in accept func
		clintConnt = accept(clintListn, (struct sockaddr*)NULL, NULL);
		if(clintConnt < 0){
			perror("connect failed");
			return -1;
		}
		/*char dataSending[BUFFER_SIZE];
 		clock = time(NULL);
		snprintf(dataSending, sizeof(dataSending), "%.24s\r\n", ctime(&clock)); // Printing successful message
		write(clintConnt, dataSending, strlen(dataSending));*/
		printf("\n\nHi,Iam running server.Some Client hit me\n"); // whenever a request from client came. It will be processed here.
		
		ret = pthread_create(&pid, NULL, handle_client, (void *)&clintConnt);
		if(ret < 0){
			perror("create thread failed");
			return -1;
		}
		pthread_detach(pid); 
	}
 
     	return 0;
}

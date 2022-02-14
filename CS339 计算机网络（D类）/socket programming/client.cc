#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
 
#define PORT 2017
#define SERVE_RADDR "10.0.0.1"
#define BUFFER_SIZE 1024

int main()
{
	time_t clock;    	
	int CreateSocket = 0,n = 0;
    	char dataReceived[BUFFER_SIZE];
	char endtime[BUFFER_SIZE];
    	struct sockaddr_in ipOfServer;
	int readlen;
 	bool flag = true;
	int res;	
	
	FILE *fp=NULL;  
    	char buff[10]={0};
   	memset(buff,0,sizeof(buff)); 
   	fp=popen("ifconfig","r");
   	fread(buff,1,9,fp);
	pclose(fp);

	char client_file[128];
	client_file[0] = 'h'; 
	int i = 1;
	while(buff[i]>='0' && buff[i]<='9')
	{
		client_file[i] = buff[i];
		i++;
	}
	client_file[i] = '.';
	client_file[i+1] = 't';
	client_file[i+2] = 'x'; 
    	client_file[i+3] = 't'; 
	client_file[i+4] = '\0';
       	int writefile = open(client_file, O_WRONLY|O_CREAT);

    	if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    	{
    	    printf("Socket not created \n");
    	    return 1;
    	}
    	memset(&ipOfServer, '0', sizeof(ipOfServer));	
    	ipOfServer.sin_family = AF_INET;
    	ipOfServer.sin_port = htons(PORT);
    	ipOfServer.sin_addr.s_addr = inet_addr(SERVE_RADDR);
 
    	if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
    	{
        	printf("Connection failed due to port and ip problems\n");
        	return 1;
    	}
	
	memset(dataReceived, '0' ,sizeof(dataReceived));
	printf("begintime:");
	//receive the begin message from server and output time
	while((n = read(CreateSocket, dataReceived, sizeof(dataReceived))) > 0)
    	{        	
		if(flag)
		{	
			for(int i=0; i<24; ++i)
				printf("%c", dataReceived[i]);
			printf("\n");
			res = write(writefile, dataReceived+26, n-26);//unsuccess in sub thread
			if(res < 0){
				printf("client write to file failed\n");				
				break;			
			}
			flag =false;
		}
		else
		{
			res = write(writefile, dataReceived, n);//unsuccess in sub thread
			if(res < 0){
				printf("client write to file failed\n");				
				break;			
			}
		}			
    	}
	if(n == 0)
	{
		memset(endtime, '0' ,sizeof(endtime));
		clock = time(NULL);
		snprintf(endtime, sizeof(endtime), "%.24s\r\n", ctime(&clock)); // Printing successful message
		printf("endtime:%s\n", endtime);
		close(writefile);
	}
	
    	if(n < 0)
    	{
    	    printf("Standard input error \n");
   	}

    	close(CreateSocket);
 
    	return 0;
}

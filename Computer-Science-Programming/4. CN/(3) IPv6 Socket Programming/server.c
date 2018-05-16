#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, len ;
    struct sockaddr_in s_addr, c_addr; 

    char sendBuff[100];

    int sockfd = 0, n = 0;
    struct sockaddr_in serv_addr; 

    char recvBuff[100];


    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&s_addr, '0', sizeof(s_addr));
    memset(sendBuff, '\0', sizeof(sendBuff)); 

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr("192.168.56.101");
    s_addr.sin_port = htons(40801); 

    if(bind(listenfd, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1){
    	printf("Can not Bind\n");
    	return -1;
    } 

    if(listen(listenfd, 10) == -1){
    	printf("listen Fail\n");
    	return -1;
    } 

    len = sizeof(c_addr);
    connfd = accept(listenfd, (struct sockaddr*)&c_addr, &len); 
       
	read(connfd,sendBuff,sizeof(sendBuff));
	sendBuff[strlen(sendBuff)-1] = '\0';
	printf("%s",sendBuff);

	close(connfd);
	close(listenfd);



	memset(recvBuff, '\0',sizeof(recvBuff));

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(40830); 

    inet_pton(AF_INET, "192.168.56.101", &serv_addr.sin_addr);

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

    write(sockfd,sendBuff,strlen(sendBuff));

    close(sockfd);

    return 0;
}

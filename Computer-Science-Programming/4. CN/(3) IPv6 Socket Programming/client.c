#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{
    int sockfd = 0;
    struct sockaddr_in6 svrsin6;

    char ipv6_addr[16], buf[1024];


    int listenfd = 0, connfd = 0, len;
    struct sockaddr_in s_addr, c_addr; 

    char sendBuff[1025];
    char token[100];

    pid_t pid;


    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("socket create error:");
        exit(0);
    }

    svrsin6.sin6_family   = AF_INET6;
    svrsin6.sin6_flowinfo = 0;
    svrsin6.sin6_port     = htons(38492);

    inet_pton(AF_INET6, "2001:0:53aa:64c:289f:12c9:8c6e:5546", (void *)&ipv6_addr);
    memcpy((void *)&svrsin6.sin6_addr, (void *)&ipv6_addr, 16);

    if(connect(sockfd, (struct sockaddr *)&svrsin6, sizeof(svrsin6)) < 0){
        perror("connect error:");
        exit(0);
    }
    
    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(0,buf,sizeof(buf));
    write(sockfd,buf,strlen(buf)); // 2013312343




    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(0,buf,sizeof(buf));
    write(sockfd,buf,strlen(buf)); // IP




    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(0,buf,sizeof(buf));
    write(sockfd,buf,strlen(buf)); // PORT




    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(0,buf,sizeof(buf));
    write(sockfd,buf,strlen(buf)); // Y,N




    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(sockfd,buf,sizeof(buf));
    printf("%s",buf);

    memset(buf,0x00,sizeof(buf));

    read(0,buf,sizeof(buf));
    write(sockfd,buf,strlen(buf)); // OK



    pid = fork();

    if(pid == 0){

        sleep(3);

    }



    else if(pid>0){

        printf("Connect Success\n");
        close(sockfd);    

        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&s_addr, '0', sizeof(s_addr));
        memset(sendBuff, '\0', sizeof(sendBuff)); 

        s_addr.sin_family = AF_INET;
        s_addr.sin_addr.s_addr = inet_addr("192.168.56.101");
        s_addr.sin_port = htons(40830); 

        if(bind(listenfd, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1){
            printf("Can not Bind\n");
            return -1;
        } 

        if(listen(listenfd, 10) == -1){
            printf("listen Fail\n");
            return -1;
        } 

        while(1){
            len = sizeof(c_addr);
            connfd = accept(listenfd, (struct sockaddr*)&c_addr, &len); 

            memset(token,0x00,sizeof(token));
            read(connfd,token,sizeof(token));
            printf("[System] Starting server by client");
            printf("\n\n");
            printf("RECEIVED ( %d ) :  %s ",strlen(token)-1,token);

            close(connfd);
        }

        close(listenfd);

    }

    write(sockfd,token,strlen(token));
    close(sockfd);
    exit(0);

    return 0;


}   

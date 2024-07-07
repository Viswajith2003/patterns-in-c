#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>

void main()
{
    int socketId,contionId;
    struct sockaddr_in serverAddress,clientAddress;

    socketId = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socketId == -1)
    {
        printf("socket creation failed");
        return;
    }
    printf("Socket created sucessfully");
    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddress.sin_port=htons(8080);
    
    if(bind (socketId,(struct sockaddr *)&serverAddress,sizeof(serverAddress))!=0)
    {
        printf("bind unsucessfull");
        close(socketId);
        return;
    }
    printf("bind sucessfull");
}
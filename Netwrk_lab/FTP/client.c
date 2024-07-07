#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>

void main()
{
    int socketId;
    struct sockaddr_in serverAddress;
    socketId=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socketId ==-1)
    {
        printf("socket creation failed");
        return;
    }
    printf("socket created sucessfully");

    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(8080);

    


}


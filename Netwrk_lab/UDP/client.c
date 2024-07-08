#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

void main()
{
    int socketId;
    struct sockaddr_in serverAddress;
    socketId=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(socketId==-1)
    {
        printf("socket creation failed");
        return 1;
    }
    printf("socket created sucessfully \n");
    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddress.sin_port=htons(8080);

    char buffer[100];
    while(1)
    {
        printf("To server :");
        fgets(buffer,sizeof(buffer),stdin);
        sendto(buffer,strlen(buffer),0,(struct sockaddr *))
    }

}
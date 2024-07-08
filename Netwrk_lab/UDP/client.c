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
        sendto(socketId,buffer,strlen(buffer),0,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
        buffer[strcspn(buffer,"\n")]="\0";
        if(strcmp(buffer,"exit")==0)
        {
            printf("client is exiting");
            break;
        }

        ssize_t Received=recvfrom(socketId,buffer,sizeof(buffer),0,NULL,NULL);
        if(Received == -1)
        {
            printf("Receved failed");
            close(socketId);
            return 1;
        }
        printf("from server :%s\n",buffer);
        if(strcmp(buffer,"exit")==0)
        {
            printf("exit cmd received,closing connection");
            break;
        }

    
    }
    close(socketId);

}
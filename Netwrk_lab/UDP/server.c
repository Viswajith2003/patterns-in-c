#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

void main()
{
    int socketId;
    struct sockaddr_in serverAddress,clientAddress;
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

    if(bind(socketId,(struct sockaddr *)&serverAddress,sizeof(serverAddress))!=0)
    {
        printf("bind failed ");
        close(socketId);
        return 1;
    }
    printf("Binded sucessfully\n");

    char buffer[100];
    while (1)
    {
        socklen_t len=sizeof(clientAddress);
        ssize_t Recevied=recvfrom(socketId,buffer,sizeof(buffer),0,(struct sockaddr *)&clientAddress,&len);
        if(Recevied==-1)
        {
            printf("received failed ");
            close(socketId);
            return 1;
        }
        printf("from client :%s\n",buffer);

        if(strcmp(buffer,"exit")==0)
        {
            printf("Exit cmd received,closing connection \n");
            break;
        }

        printf("To client :");
        fgets(buffer,sizeof(buffer),stdin);
        sendto(socketId,buffer,strlen(buffer)+1,0,(struct sockaddr *)&clientAddress,len);
        buffer[strcspn(buffer,"\n")]="\0";
        if(strcmp(buffer,"exit") == 0)
        {
            printf("server exiting");
            break;
        }
    }
    close(socketId);
}
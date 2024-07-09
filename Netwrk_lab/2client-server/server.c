#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

void main()
{
    int socketId,connId;
    struct sockaddr_in serverAddress,clientAddress;
    socketId=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socketId == -1)
    {
        printf("socket creation failed");
        return;
    }
    printf("socket creation successfull\n");
    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddress.sin_port=htons(8080);
    if(bind(socketId,(struct sockaddr *)&serverAddress,sizeof(serverAddress))!=0)
    {
        printf("bind unsuccessfull");
        close(socketId);
        return;
    }
    printf("successfully bounded\n");
    if(listen(socketId,5)==-1)
    {
        printf("Listen failed");
        close(socketId);
        return;
    }
    printf("Listening...\n");

    socklen_t len=sizeof(clientAddress);
    connId=accept(socketId,(struct sockaddr *)&clientAddress,&len);
    if(connId==-1)
    {
        printf("client accept failed");
        close(socketId);
        close(connId);
        return;
    }
    printf("client accepted\n");

    char buffer[100];
    while(1)
    {
        ssize_t Received=recv(connId,buffer,sizeof(buffer),0);
        if(Received==-1)
        {
            printf("Received failed");
            close(socketId);
            close(connId);
            return;
        }
        else if (Received==0)
        {
            printf("client disconnected");
            break;
        }
        printf("\nfrom client %s:",buffer);
        if(strcmp(buffer,"exit")==0)
        {
            printf("exit cmd received, close the connection");
            break;
        }

        printf("\nTo client :");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]!="\0";
        if(send(connId,buffer,strlen(buffer)+1,0)==-1)
        {
            printf("send failed");
            close(socketId);
            close(connId);
            return;
        }
        if(strcmp(buffer,"exit")==0)
        {
            printf("server exit");
            break;
        }
    }
    close(connId);
    close(socketId);
}
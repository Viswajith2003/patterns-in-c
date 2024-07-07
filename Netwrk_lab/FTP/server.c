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

    if(listen (socketId,5)==-1)
    {
        printf("listen failed");
        close(socketId);
        return;
    }
    printf("Sucessfully listened");

    socklen_t len=sizeof(clientAddress);
    contionId=accept(socketId,(struct sockaddr *)&clientAddress,&len);
    if(contionId == -1)
    {
        printf("Connection accept failed");
        close(socketId);
        close(contionId);
        return;
    }
    printf("Connection accepted sucessfully from client");

    char filename[100];
    ssize_t received=recv(contionId,filename,sizeof(filename),0);
    if(received ==-1)
    {
        printf("Receve failed");
        close(socketId);
        close(contionId);
        return;
    }
    printf("Filename is:%s\n",filename);

    FILE *file=fopen(filename,"r");
    char filecontent[1024];
    memset(filecontent,0,sizeof(filecontent));

    if(file)
    {
        int c;
        while((c=fgetc(file)!=EOF))
        sprintf(filecontent,"%s%c",filecontent,c);
        fclose(file);
        send(contionId,filecontent,sizeof(filecontent),0);
    }
    else{
        printf("something went wrong");
    }
    close(socketId);
    close(contionId);
}
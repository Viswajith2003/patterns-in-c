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
    printf("socket created sucessfully \n");

    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(8080);

    if(connect (socketId,(struct sockaddr *)&serverAddress,sizeof(serverAddress))!=0)
    {
        printf("Connection failed");
        close(socketId);
        return;
    }
    printf("Successfully connected \n");

    char filename[100];
    printf("Enter the filename: ");
    scanf("%s",filename);

    if(send(socketId,filename,sizeof(filename),0)==-1)
    {
        printf("sending failed \n");
        close(socketId);
        return;
    }
    printf("Sucessfully sented \n");

    char filecontent[1024];
    ssize_t Received=recv(socketId,filecontent,sizeof(filecontent),0);
    if(Received == -1)
    {
        printf("receving failed");
        close(socketId);
        return;
    }
    printf("The file content is: %s \n",filecontent);
    close(socketId);
}


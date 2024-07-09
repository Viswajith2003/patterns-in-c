#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
void main()
{
    int socketfd, connectionfd;
    struct sockaddr_in serverAddress, clientAddress;
    socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketfd == -1)
    {
        printf("Socket creation failed \n");
        return;
    }
    printf("Socket created successfully \n");
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(8080);
    if (bind(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) !=
        0)
    {
        printf("Bind unsuccessfull \n");
        close(socketfd);
        return;
    }
    printf("Bind successfull \n");
    if (listen(socketfd, 5) == -1)
    {
        printf("Listen failed \n");
        close(socketfd);
        return;
    }
    printf("Listen successful \n");
    socklen_t len = sizeof(clientAddress);
    connectionfd = accept(socketfd, (struct sockaddr *)&clientAddress, &len);
    if (connectionfd == -1)
    {
        printf("Client accept failed \n");
        close(socketfd);
        return;
    }
    printf("Client accept successfull \n");
    char buffer[100];
    ssize_t recieved = recv(connectionfd, buffer, sizeof(buffer), 0);
    if (recieved == -1)
    {
        printf("Receive failed \n");
        close(socketfd);
        close(connectionfd);
        return;
    }
    printf("Filename : %s\n", buffer);
    FILE *file = fopen(buffer, "r");
    memset(buffer, 0, sizeof(buffer));
    if (file)
    {
        int c;
        while ((c = fgetc(file)) != EOF)
            sprintf(buffer, "%s%c", buffer, c);
        fclose(file);
        send(connectionfd, buffer, sizeof(buffer), 0);
    }
    else
        printf("Something went wrong\n");
    close(socketfd);
    close(connectionfd);
}











// #include<stdio.h>
// #include<arpa/inet.h>
// #include<unistd.h>
// #include<sys/types.h>
// #include<sys/socket.h>
// #include<string.h>

// void main()
// {
//     int socketId,contionId;
//     struct sockaddr_in serverAddress,clientAddress;

//     socketId = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//     if(socketId == -1)
//     {
//         printf("socket creation failed");
//         return;
//     }
//     printf("Socket created sucessfully \n");
//     memset(&serverAddress,0,sizeof(serverAddress));
//     serverAddress.sin_family=AF_INET;
//     serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
//     serverAddress.sin_port=htons(8080);

//     if(bind (socketId,(struct sockaddr *)&serverAddress,sizeof(serverAddress))!=0)
//     {
//         printf("bind unsucessfull");
//         close(socketId);
//         return;
//     }
//     printf("bind sucessfull \n");

//     if(listen (socketId,5)==-1)
//     {
//         printf("listen failed");
//         close(socketId);
//         return;
//     }
//     printf("Sucessfully listened \n");

//     socklen_t len=sizeof(clientAddress);
//     contionId=accept(socketId,(struct sockaddr *)&clientAddress,&len);
//     if(contionId == -1)
//     {
//         printf("Connection accept failed");
//         close(socketId);
//         close(contionId);
//         return;
//     }
//     printf("Connection accepted sucessfully from client \n");

//     char filename[100];
//     ssize_t received=recv(contionId,filename,sizeof(filename),0);
//     if(received ==-1)
//     {
//         printf("Receve failed");
//         close(socketId);
//         close(contionId);
//         return;
//     }
//     printf("Filename is:%s\n",filename);

//     FILE *file=fopen(filename,"r");
//     char filecontent[2048];
//     memset(filecontent,0,sizeof(filecontent));

//     if(file)
//     {
//         int c;
//         size_t len = 0;
//         while ((c = fgetc(file)) != EOF && len < sizeof(filecontent) - 1) {
//             filecontent[len++] = (char)c;
//         }
//         filecontent[len] = '\0';  // Null-terminate the string
//         fclose(file);
//         send(contionId,filecontent,sizeof(filecontent),0);
//     }
//     else{
//         printf("something went wrong");
//     }
//     close(socketId);
//     close(contionId);
// }
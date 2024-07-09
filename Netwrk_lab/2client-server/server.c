
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
    printf("client1 accepted\n");


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
        // if(strcmp(buffer,"exit")==0)
        // {
        //     printf("exit cmd received, close the connection");
        //     break;
        // }

        printf("\nTo client2 :");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]!="\0";
        if(send(connId,buffer,strlen(buffer)+1,0)==-1)
        {
            printf("send failed");
            close(socketId);
            close(connId);
            return;
        }
        // if(strcmp(buffer,"exit")==0)
        // {
        //     printf("server exit");
        //     break;
        // }
    }
    close(connId);
    close(socketId);
}


// #include <sys/types.h>
// #include <sys/socket.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <string.h>

// void main() {
//     int socketId, connId1, connId2;
//     struct sockaddr_in serverAddress, clientAddress;
//     socketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (socketId == -1) {
//         printf("socket creation failed\n");
//         return;
//     }
//     printf("socket creation successful\n");
    
//     memset(&serverAddress, 0, sizeof(serverAddress));
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
//     serverAddress.sin_port = htons(8080);
    
//     if (bind(socketId, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0) {
//         printf("bind unsuccessful\n");
//         close(socketId);
//         return;
//     }
//     printf("successfully bound\n");
    
//     if (listen(socketId, 5) == -1) {
//         printf("Listen failed\n");
//         close(socketId);
//         return;
//     }
//     printf("Listening...\n");
    
//     socklen_t len = sizeof(clientAddress);
//     connId1 = accept(socketId, (struct sockaddr *)&clientAddress, &len);
//     if (connId1 == -1) {
//         printf("client 1 accept failed\n");
//         close(socketId);
//         return;
//     }
//     printf("client 1 accepted\n");

//     connId2 = accept(socketId, (struct sockaddr *)&clientAddress, &len);
//     if (connId2 == -1) {
//         printf("client 2 accept failed\n");
//         close(socketId);
//         close(connId1);
//         return;
//     }
//     printf("client 2 accepted\n");

//     char buffer[100];
//     while (1) {
//         ssize_t Received = recv(connId1, buffer, sizeof(buffer), 0);
//         if (Received == -1) {
//             printf("Receive from client 1 failed\n");
//             close(socketId);
//             close(connId1);
//             close(connId2);
//             return;
//         } else if (Received == 0) {
//             printf("client 1 disconnected\n");
//             break;
//         }
//         buffer[Received] = '\0';
//         printf("\nfrom client 1: %s\n", buffer);

//         if (send(connId2, buffer, strlen(buffer) + 1, 0) == -1) {
//             printf("send to client 2 failed\n");
//             close(socketId);
//             close(connId1);
//             close(connId2);
//             return;
//         }
//         printf("message sent to client 2\n");
//     }
    
//     close(connId1);
//     close(connId2);
//     close(socketId);
// }
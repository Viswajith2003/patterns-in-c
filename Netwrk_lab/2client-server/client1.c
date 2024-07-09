
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
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(8080);
    if(connect(socketId,(struct sockaddr *)&serverAddress,sizeof(serverAddress))!=0)
    {
        printf("connectin failed");
        close(socketId);
        return;
    }
    printf("successfully connected\n");

    char buffer[100];
    while(1)
    {
        printf("\nTo server:");
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\n")]!="\0";
        if(send(socketId,buffer,strlen(buffer)+1,0)==-1)
        {
            printf("send failed");
            close(socketId);
            return;
        }
        // if(strcmp(buffer,"exit")==0)
        // {
        //     printf("client exiting");
        //     break;
        // }


        ssize_t Received=recv(socketId,buffer,sizeof(buffer),0);
        if(Received==-1)
        {
            printf("Received failed");
            close(socketId);
            close(connId);
            return;
        }
        else if (Received==0)
        {
            printf("server disconnected");
            break;
        }
        buffer[Received]="\0";
        printf("\nfrom server %s:",buffer);
        // if(strcmp(buffer,"exit")==0)
        // {
        //     printf("exit cmd received, close the connection");
        //     break;
        // }
    }
    close(socketId);
}



// #include <sys/types.h>
// #include <sys/socket.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <string.h>

// void main() {
//     int socketId;
//     struct sockaddr_in serverAddress;
//     socketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (socketId == -1) {
//         printf("socket creation failed\n");
//         return;
//     }
//     printf("socket creation successful\n");
    
//     memset(&serverAddress, 0, sizeof(serverAddress));
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // assuming server is on localhost
//     serverAddress.sin_port = htons(8080);
    
//     if (connect(socketId, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0) {
//         printf("connection failed\n");
//         close(socketId);
//         return;
//     }
//     printf("successfully connected\n");
    
//     char buffer[100];
//     while (1) {
//         printf("\nTo server: ");
//         fgets(buffer, sizeof(buffer), stdin);
//         buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character
        
//         if (send(socketId, buffer, strlen(buffer) + 1, 0) == -1) {
//             printf("send failed\n");
//             close(socketId);
//             return;
//         }
        
//         ssize_t Received = recv(socketId, buffer, sizeof(buffer), 0);
//         if (Received == -1) {
//             printf("Receive failed\n");
//             close(socketId);
//             return;
//         } else if (Received == 0) {
//             printf("server disconnected\n");
//             break;
//         }
//         buffer[Received] = '\0';
//         printf("from server: %s\n", buffer);
//     }
    
//     close(socketId);
// }







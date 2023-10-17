#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <pthread.h>

#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>

int main() {

    WSADATA wsaData;
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    WSAStartup(MAKEWORD(2,2), &wsaData);
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4444);
    serverAddr.sin_addr.s_addr = inet_addr("10.40.216.60");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    while(1) {
        printf("Enter a message : ");
        fgets(buffer, 1024, stdin);
        send(clientSocket, buffer, strlen(buffer), 0);

        recv(clientSocket,buffer,1024,0);
        printf("Message from server : %s\n",buffer);
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
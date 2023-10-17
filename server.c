#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    int sockfd, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    int addr_size;

    WSAStartup(MAKEWORD(2,2), &wsaData);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4444);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(sockfd, 5);
    addr_size = sizeof(clientAddr);
    newSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &addr_size);

    while(1) {
        recv(newSocket, buffer, 1024, 0);
        printf("Message received: %s\n", buffer);

        fgets(buffer, 1024, stdin);
        send(newSocket, buffer, strlen(buffer), 0);
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
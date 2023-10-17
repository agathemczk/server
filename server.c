#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    int clientAddrLen;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4444);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    printf("Server is listening on port 4444...\n");

    while (1) {
        clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

        printf("Client connected from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        while (1) {
            memset(buffer, 0, sizeof(buffer));
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) {
                printf("Client %s:%d disconnected.\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                closesocket(clientSocket);
                break;
            }

            printf("Received from %s:%d: %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buffer);

            // Envoyer le message à tous les clients connectés (y compris l'expéditeur)
            SOCKET tempSocket = serverSocket;
            while (tempSocket != INVALID_SOCKET) {
                if (tempSocket != clientSocket) {
                    send(tempSocket, buffer, bytesReceived, 0);
                }
                tempSocket = accept(serverSocket, NULL, NULL);
            }
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
// msg.c
#include <stdio.h>
#include <winsock2.h>
#include "msg.h"

SOCKET create_socket() {
    return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

int connect_to_server(SOCKET sock, const char* server_ip, int port) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(port);

    return connect(sock, (SOCKADDR*)&server_addr, sizeof(server_addr));
}

void send_message(SOCKET sock, const char* msg) {
    send(sock, msg, strlen(msg), 0);
}

void receive_message(SOCKET sock) {
    char recvbuf[1024];
    int recvbuflen = 1024;
    int bytes_received = recv(sock, recvbuf, recvbuflen, 0);
    if (bytes_received > 0) {
        recvbuf[bytes_received] = '\0'; // Null-terminate the received data
        printf("Received: %s\n", recvbuf);
    }
}

void initialize_winsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        exit(1);
    }
}

void cleanup_winsock() {
    WSACleanup();
}

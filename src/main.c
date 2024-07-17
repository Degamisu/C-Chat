//`main.c` defines the basic functions for CHAT.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>
#include "msg.h"

#define PORT 9800

void initialize_winsock();
void cleanup_winsock();

char* getname(){ // get name of user
    static char name[20];
    printf("Please enter your name: ");
    scanf("%19s", name);
    return name;
}

int main() { // main program
    initialize_winsock();

    char* name = getname();
    bool running = true;

    SOCKET sock = create_socket();
    if (connect_to_server(sock, "127.0.0.1", PORT) == SOCKET_ERROR) {
        printf("Failed to connect to server\n");
        closesocket(sock);
        cleanup_winsock();
        return 1;
    }

    printf("Connected to server. Type 'exit' to quit.\n");

    while (running) {
        char input[1024];
        if (fgets(input, sizeof(input), stdin)) { // check for user input
            input[strcspn(input, "\n")] = 0;

            if (strcmp(input, "exit") == 0) {
                running = false;
                printf("Exiting...\n");
            } else {
                send_message(sock, input);
            }
        }
        receive_message(sock);
    }

    closesocket(sock);
    cleanup_winsock();

    return 0;
}

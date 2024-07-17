//`main.c` defines the basic functions for CHAT.

#include <stdio.h>
#include <string.h>
#include "msg.h"
#include <stdbool.h>

char* getname(){ // get name of user

    static char name[20];
    printf("Please enter your name:");
    scanf("%19s", name);
    return name;

}

int main() { // main program

    char* name = getname();
    bool running = true;

    while (running) {
        // Check for user input
        char input[1024];
        if (fgets(input, sizeof(input), stdin)) {
            input[strcspn(input, "\n")] = 0;

            if (strcmp(input, "exit") == 0) {
                running = false;
                printf("Exiting...\n");
            } else {
                send_message(input, 9800); // FIXME
            }
        }
        receive_message();
    }

    return 1;
}
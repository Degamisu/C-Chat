#include <string.h>
#include <stdio.h>
#include "src/msg.c"

int test(){
    connect(9800, 'test', 4);
    printf("Connected");
}

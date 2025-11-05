#include<stdlib.h>
#include<string.h>

void fatal(char *msg) {
    char err_msg[100];

    strcpy(err_msg, "[!!] Fatal Error ");
    strncat(err_msg, msg, 83);
    perror(err_msg);
    exit(-1);
}

void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}
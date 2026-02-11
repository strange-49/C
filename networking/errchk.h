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

void dump(const unsigned char *data_buffer, const unsigned int length) {
    unsigned char byte;
    unsigned int i,j;
    for(i = 0; i<length; i++) {
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]);
        if(((i%16)==15) || (i ==length-1)) {
            for(j=0; j<15-(i%16); j++) {
                byte = data_buffer[j];
                if((byte > 31) && (byte < 127))
                    printf("%c", byte);
                else   
                    printf(".");
            }
            printf("\n");
        }
    }
}
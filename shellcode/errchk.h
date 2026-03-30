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
    unsigned int i, j;

    for(i = 0; i < length; i++) {

        printf("%02x ", data_buffer[i]);

        // End of 16-byte line OR end of buffer
        if((i % 16 == 15) || (i == length - 1)) {

            // Fill spacing if line not complete
            if(i % 16 != 15) {
                for(j = 0; j < 15 - (i % 16); j++)
                    printf("   ");
            }

            printf("  ");

            // Print ASCII section
            unsigned int line_start = i - (i % 16);
            unsigned int line_end = i;

            for(j = line_start; j <= line_end; j++) {
                if(data_buffer[j] >= 32 && data_buffer[j] <= 126)
                    printf("%c", data_buffer[j]);
                else
                    printf(".");
            }

            printf("\n");
        }
    }
}


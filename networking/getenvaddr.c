#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(char argc, char *argv[]) {
    char *ptr;

    if(argc < 3) {
        printf("Usage wrong");
        exit(0);
    }

    ptr = getenv(argv[1]);
    ptr+= (strlen(argv[0]) - strlen(argv[2]))*2;
    printf("%s will be at %p\n", argv[1], ptr);
}
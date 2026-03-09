#include<stdio.h>
#include"errchk.h"
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

void usuage(char *pg_name, char *filename) {
    printf("Usuage: %s <data to add to %s>\n", pg_name, filename);
    exit(0);
}

void fatal(char *);
void *ec_malloc(unsigned int);

int main(int argc, char *argv[]) {
    int userid, fd;
    char *buffer, *datafile;

    buffer = (char *)ec_malloc(100);
    datafile = (char *)ec_malloc(20);
    strcpy(datafile, "/var/notes%d");

    if(argc < 2)
        usuage(argv[0], datafile);

    strcpy(buffer, argv[1]);

    printf("\n buffer: @%p: \'%s\'\n datafile: @%p: \'%s\'\n",buffer,buffer, datafile,datafile);

    fd = open(datafile,O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if(fd==-1)
        fatal("in main while opening file ");
    printf("file descriptor is: %d \n",fd);

    userid = getuid();

    if(write(fd,&userid,4)==-1)
        fatal("in main while writing userid file ");
    write(fd,"\n",1);

    if(write(fd, buffer, strlen(buffer)) == -1)
        fatal("in main while writing buffer to file");
    write(fd,"\n",1);

    if(close(fd)==-1)
        fatal("in main while closing file ");
    printf("Note has been saved.\n");
    free(buffer);
    free(datafile);
}
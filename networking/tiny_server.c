#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include "errchk.h"
#include "network.h"

#define PORT 80
#define webroot "./webroot"

void handle_connection(int , struct sockaddr_in *);
int get_file_size(int);

int main(void) {
    int sockfd, new_sockfd, yes=1;
    struct sockaddr_in hostaddr, clientaddr;
    socklen_t sin_size;

    printf("Accepting web requests on port %d \n", PORT);

    if((sockfd = socket(PF_INET,  SOCK_STREAM, 0))== -1)
        fatal("in socket ");

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        fatal("setting socket option ");

    hostaddr.sin_family = AF_INET;
    hostaddr.sin_port = htons(PORT);
    hostaddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(hostaddr.sin_zero), '\0', 8);

    if(bind(sockfd, (struct sockaddr *)&hostaddr, sizeof(struct sockaddr)) == -1)
        fatal("binding socket error ");

    if(listen(sockfd, 20)== -1)
        fatal("listening on socket error ");

    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        new_sockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &sin_size);
        if(new_sockfd == -1)
            fatal("Accepting connection error ");

        handle_connection(new_sockfd, &clientaddr);
    }
    return 0;
}

void handle_connection(int sockfd, struct sockaddr_in *client_addr_ptr) {
    unsigned char *ptr, request[500], resource[500];
    int fd, length;

    length = recv_line(sockfd, request);

    printf("Got request from %s: %d \"%s\" \n", inet_ntoa(client_addr_ptr->sin_addr),
    ntohs(client_addr_ptr->sin_port), request);

    ptr = strstr(request, "HTTP/");
    if(ptr==NULL) {
        printf("Not HTTP! \n");
    }
    else {
        *ptr=0;
        ptr = NULL;
        if(strncmp(request, "GET ",4)==0)
            ptr = request+4;
        if(strncmp(request, "HEAD ", 5)==0)
            ptr = request+5;

        if(ptr == NULL) {
            printf("UNKNOWN REQUEST \n");
        }
        else {
            if(ptr[strlen(ptr)-1] == '/')
                strcat(ptr, "index.html");
            strcpy(resource, webroot);
            strcat(resource, ptr);
            fd = open(resource, O_RDONLY, 0);
            printf("\t Opening \'%s\'\t", resource);
            if(fd == -1) {
                printf("404 Not found \n");
                send_string(sockfd, "HTTP/1.0 404 NOT FOUND \r\n");
                send_string(sockfd, "Server: Tiny web server \r\n\r\n");
                send_string(sockfd, "<html><head><title> 404 not found </title></head></html>\r\n");
            } else {
                printf(" 20 OK \n");
                send_string(sockfd, "HTTP/1.0 200 OK \r\n");
                send_string(sockfd, "Server: Tiny webserver \r\n\r\n");
                if(ptr == request+4) {
                    if((length = get_file_size(fd))==-1)
                        fatal("getting resource file size ");
                    if((ptr= (unsigned char *)malloc(length))==NULL)
                        fatal("allocating memory for reading resource ");
                    read(fd, ptr, length);
                    send(sockfd, ptr, length, 0);
                    free(ptr);
                }
                close(fd);
            }
        }
    }
    shutdown(sockfd, SHUT_RDWR);
}

int get_file_size(int fd) {
    struct stat stat_struct;

    if(fstat(fd, &stat_struct)==-1)
        return -1;
    return (int) stat_struct.st_size;
}
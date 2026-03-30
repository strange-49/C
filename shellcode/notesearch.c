#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include"errchk.h"
#include<unistd.h>
#include<fcntl.h>

#define FILENAME "/var/notes"

int print_notes(int, int, char *);
int find_user_note(int, int);
int search_note(char *, char *);
void fatal(char *);

int main(int argc, char *argv[]) {
    int fd, userid, printing = 1;
    char searchstr[100];

    if(argc > 1)
        strcpy(searchstr, argv[1]);
    else
        searchstr[0] = 0;

    userid = getuid();
    fd = open(FILENAME, O_RDONLY);
    if(fd == -1)
        fatal("in main() opening file. \n");    
    while(printing)
        printing = print_notes(fd, userid, searchstr);
    printf("--------END OF NOTE DATA-----------\n");
    close(fd);
}

int print_notes(int fd, int uid, char *searchstr)
{
    int note_len;
    char byte = 0, note_buffer[100];

    note_len = find_user_note(fd, uid);
    if(note_len==-1)
        return 0;

    read(fd, note_buffer, note_len);
    note_buffer[note_len]=0;

    if(search_note(note_buffer, searchstr))
        printf(note_buffer);
    return 1;
}

int find_user_note(int fd, int user_id)
{
    int note_uid = -1;
    unsigned char byte;
    int length;

    while(note_uid != user_id) {
        if(read(fd, &note_uid, 4) != 4)
            return -1;
        if(read(fd, &byte, 1) != 1)
            return -1;

        byte = length = 0;
        while(byte != '\n') {
            if(read(fd, &byte, 1) != 1)
                return -1;
            length++;
        }
    }
    lseek(fd, length * -1, SEEK_CUR);
    printf("[DEBUG] found a %d byte note for usesr id %d\n", length, note_uid);
    return length;
}

int search_note(char *note, char *keyword)
{
    int i, keyword_len, match = 0;
    keyword_len = strlen(keyword);
    if(keyword_len==0)
        return 1;

    for(i=0; i<strlen(note); i++) {
        if(note[i]==keyword[match])
            match++;
        else {
            if(note[i] == keyword[0])
                match=1;
            else
                match=0;
        }
        if(match == keyword_len)
            return 1;
    }
    return 0;
}
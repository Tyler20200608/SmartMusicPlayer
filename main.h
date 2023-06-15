


#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <dirent.h>

#define SUCCESS 1000
#define FAILURE 1001
#define SERVER_PORT 8000
#define SERVER_IP "127.0.0.1"
#define MUSICPATH "/root/home/tyler/code_C_CPP/music_player"

extern int g_buttonfd;
extern int g_ledfd;
extern int g_mixerfd;
extern int g_socketfd;
extern Node *head;
int InitDriver();
int InitSocket();
int led_on(int which);
int led_off(int which);


typedef struct Node
{
    char music_name[64];
    struct Node *next;
}Node;


#endif











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

#define SUCCESS 1000
#define FAILURE 1001
#define SERVER_PORT 8000
#define SERVER_IP "127.0.0.1"

extern int g_buttonfd;
extern int g_ledfd;
extern int g_mixerfd;
extern int g_socketfd;

int InitDriver();
int InitSocket();
int led_on(int which);
int led_off(int which);

#endif








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
#include <sys/syscall.h> 
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SUCCESS 1000
#define FAILURE 1001
#define SERVER_PORT 8000
#define SERVER_IP "127.0.0.1"
#define MUSICPATH "/home/tyler/code_C_CPP/music_player"
#define SHMKEY 1234
#define SHMSIZE 4096

typedef struct Node
{
    char music_name[64];
    struct Node *next;
}Node;


extern int g_buttonfd;
extern int g_ledfd;
extern int g_mixerfd;
extern int g_socketfd;
extern Node *head;
extern void *g_addr;
int InitDriver();
int InitSocket();
void *connect_cb(void *arg);
int led_on(int which);
int led_off(int which);
void show();
void m_select();
int m_mp3_end(const char *name);
void GetMusic();
int InitLink();
int InsertLink(Node *head,const char *name);
int InitShm();
void start_play();

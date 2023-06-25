#include "main.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>

int g_buttonfd=0;
int g_ledfd=0;
int g_mixerfd;
int g_socketfd=0;
int g_start_flag = 0;//表示没有开始播放音乐
int g_suspend_flag = 0;//表示没有暂停播放音乐
int g_mode=1;//播放模式
struct Node *head;
void *g_addr = NULL;
int main(){
    int ret;
    // ret = InitDriver();//打开设备文件
    // if(ret==FAILURE){
    //     printf("device init failure\n");
    //     exit(1);
    // }

    // ret = InitSocket();//初始化网络
    // if(ret==FAILURE){
    //     printf("socket init failure\n");
    //     led_on(0);
    //     led_on(1);//初始化失败，点亮两个led
    // }

    //初始化链表
    ret=InitLink();
    if(ret==FAILURE){
        printf("链表初始化失败");
        exit(1);
    }
// printf("1\n");
    //初始化共享内存
    ret = InitShm();
    if(ret==FAILURE){
        printf("共享内存初始化失败");
        exit(1);
    }
    
    //读取音乐
    GetMusic();
    // char cur_name[64];
    // FindNextMusic("1.mp3",SEQUENCEMODE,cur_name);
    // printf("1mp3:%s",cur_name);

    // FindNextMusic("2.mp3",SEQUENCEMODE,cur_name);
    // printf("2mp3:%s",cur_name);

    // FindNextMusic("3.mp3",SEQUENCEMODE,cur_name);
    // printf("3mp3:%s",cur_name);
    start_play();
    //m_select();

    
    return 0;
}
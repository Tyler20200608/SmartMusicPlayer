#include "main.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>

int g_buttonfd;
int g_ledfd;
int g_mixerfd;
int g_socketfd;
int g_start_flag = 0;//表示没有开始播放音乐
int g_suspend_flag = 0;//表示没有暂停播放音乐
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
    start_play();
    return 0;
}
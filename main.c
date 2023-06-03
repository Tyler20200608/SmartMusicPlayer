#include "main.h"

int g_buttonfd;
int g_ledfd;
int g_mixerfd;
int g_socketfd;

int main(){
    int ret;
    // ret = InitDriver();//打开设备文件
    // if(ret==FAILURE){
    //     printf("device init failure\n");
    //     exit(1);
    // }

    ret = InitSocket();//初始化网络
    if(ret==FAILURE){
        printf("socket init failure\n");
        led_on(0);
        led_on(1);//初始化失败，点亮两个led
    }
    return 0;
}
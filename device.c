//用于操作硬件设备
#include "main.h"
int InitDriver(){
    //打开按键设备
    g_buttonfd = open("/dev/buttons", O_RDONLY);
    if(g_buttonfd==-1){
        return FAILURE;
    }
    //打开led设备文件
    g_ledfd = open("/dev/leds", O_WRONLY);
    if(g_ledfd==-1){
        return FAILURE;
    }

    //所有LED灭
    for (int i = 0; i < 4;i++){
        ioctl(g_ledfd, 0, i);
    }
        // 打开mixer设备文件
        g_mixerfd = open("/dev/mixer", O_WRONLY);
    if(g_mixerfd==-1){
        return FAILURE;
    }

    return SUCCESS;
}

int led_on(int which){
    ioctl(g_ledfd, 1, which);
}

int led_off(int which){
    ioctl(g_ledfd, 0, which);
}
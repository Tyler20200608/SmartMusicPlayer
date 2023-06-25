#include "main.h"

void show(){
    for (int i = 1; i < 9;i++){
        printf("%d\n", i);
    }
}


void m_select(){
    show();
    fd_set readfd, tmpfd;
    int maxfd = (g_buttonfd > g_socketfd) ? g_buttonfd : g_socketfd;
    int ret;
    FD_ZERO(&readfd);
    FD_ZERO(&tmpfd);

    //FD_SET(g_buttonfd, &readfd);
    //FD_SET(g_socketfd, &readfd);
    FD_SET(0, &readfd);
    printf("111\n");
    while(1){
        tmpfd = readfd;
        ret = select(maxfd + 1, &readfd, NULL, NULL, NULL);
        if(ret==-1){
            perror("select");
            
        }

        if(FD_ISSET(0,&readfd)){//测试标准输入有数据可读
            //printf("222\n");
            int in;
            scanf("%d",&in);
            switch (in)
            {
            case 1: start_play();
                break;
            case 2: pause_play();
                break;
            case 3: unpause_play();
                break;
            default:
                break;
            }
            
        }
        // if(FD_ISSET(g_socketfd,&readfd)){//TCP有数据可读

        // }else if(FD_ISSET(g_buttonfd,&readfd)){//按键有数据可读

        // }else if(FD_ISSET(0,&readfd)){//测试标准输入有数据可读
        //     printf("222\n");
        //     int in;
        //     scanf("%d",&in);
        //     start_play();
        // }
    }
}
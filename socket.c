#include "main.h"

void *connect_cb(void *arg){//connect！！！
    int count = 5;
    int ret;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = SERVER_PORT;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    while(count--){
        //向服务器发起连接，第一个灯亮
        led_on(0);
        ret = connect(g_socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if(ret==-1){
            sleep(5);
            continue;
        } 
            
        else{//连接成功，点亮四个led
            // led_on(0);
            // led_on(1);
            // led_on(2);
            // led_on(3);
            // led_on(4);

            printf("connect success\n");
            break;
        }
    }
    return NULL;
}

int InitSocket(){
    g_socketfd = socket(PF_INET,SOCK_STREAM,0);
    if(g_socketfd==-1){
        return FAILURE;
    }
    //启动线程，向服务器发起连接
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, connect_cb, NULL);
    if(ret!=0){
        return FAILURE;
    }
    
    return SUCCESS;
}

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
 
 
#define PORT 8080
#define SIZE 1024
 

struct hash{//存储device socket的哈希表
	int id;
	int listen_socket;
	struct hash *next;
};
struct hash *table[128];


 

//接收name
//匹配
//客户端：读id，找socket，发送指令
//设备：存socket


void *hanld_client(void *arg)    //信息处理函数,功能是将客户端传过来的小写字母转化为大写字母
{
    int count = *(int *)arg;
    if(count==2){//接受终端的指令,向音箱发送命令
		
	int id = 123;
	int index = id % 128;
	struct hash *head = table[index];
	while(head!=NULL&&head->id!=id){
		head = head->next;
	}
	if(head==NULL){
		head=(struct hash *)malloc(sizeof(struct hash));
		head->id = id;
		head->listen_socket = listen_socket;
		head->next = NULL;
	}else{
		head->listen_socket = listen_socket;
	}

	printf("id:%d,socket:%d", head->id, head->listen_socket);
    return NULL;
    }else if(count==1){//将设备id以及其socket存储在hash_table中
        int index = 123 % 128;
		struct hash *head = table[index];
		while(head!=NULL&&head->id!=id){
			head = head->next;
		}
		if(head==NULL){
			//write(client_socket, "not exist", 9);
			printf("该id不存在对应socket\n");
			break;
		}else{
			//write(client_socket, "exist", 5);
			int listen = head->listen_socket;
            printf("cunzai\n");
        }	
		return NULL;
	}else{
		return NULL;
	}
	
}

int main()
{
	// int listen_socket = 11;
	
	for (int i = 0; i < 128;i++){
		table[i] = NULL;
	}

	// int id = 156;
	// int index = id % 128;
	// struct hash *head = table[index];
	// while(head!=NULL&&head->id!=id){
	// 	head = head->next;
	// }
	// if(head==NULL){
	// 	head=(struct hash *)malloc(sizeof(struct hash));
	// 	head->id = id;
	// 	head->listen_socket = listen_socket;
	// 	head->next = NULL;
	// }else{
	// 	head->listen_socket = listen_socket;
	// }

	// printf("id:%d,socket:%d", head->id, head->listen_socket);

	int listen_socket = Creat_socket();
	int count=2
	while(count--)
	{
		//int client_socket = wait_client(listen_socket);
		
		pthread_t id;
		pthread_create(&id, NULL, hanld_client, (void *)&count);  //创建一个线程，来处理客户端。
		
		pthread_detach(id);   //把线程分离出去。
	}

    sleep(5);

    //close(listen_socket);
	
	return 0;
}
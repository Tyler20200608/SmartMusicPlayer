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

int Creat_socket()         //创建套接字和初始化以及监听函数
{
	int listen_socket = socket(AF_INET, SOCK_STREAM, 0);      //创建一个负责监听的套接字  
	if(listen_socket == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;  /* Internet地址族 */
    addr.sin_port = htons(PORT);  /* 端口号 */
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* IP地址 */
	
	int ret = bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));    //连接
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	
	ret = listen(listen_socket, 5);   //监听
	if(ret == -1)
	{
		perror("listen");
		return -1;
	}
	return listen_socket;
}
 
int wait_client(int listen_socket)
{
	struct sockaddr_in cliaddr;
	int addrlen = sizeof(cliaddr);
	printf("等待客户端连接。。。。\n");
	int client_socket = accept(listen_socket, (struct sockaddr *)&cliaddr, &addrlen);     //创建一个和客户端交流的套接字
	if(client_socket == -1)
	{
		perror("accept");
		return -1;
	}
	
	printf("成功接收到一个客户端：%s\n", inet_ntoa(cliaddr.sin_addr));
	
	return client_socket;
}
 

//接收name
//匹配
//客户端：读id，找socket，发送指令
//设备：存socket


void *hanld_client(void *arg)    //信息处理函数,功能是将客户端传过来的小写字母转化为大写字母
{
	int client_socket = *(int *)(arg);
	char buf[SIZE];
	int ret = read(client_socket, buf, SIZE-1);
	if(ret == -1)
	{
		perror("read");
		return NULL;
	}
	if(ret == 0)
	{
		return NULL;
	}
	buf[ret] = '\0';
	printf("buf:%s\n",buf);
	if(strcmp(buf,"client")==0){//接受终端的指令,向音箱发送命令
		//printf("buf:%s",buf);
		memset((void *)buf, 0, strlen(buf));
		char id_buf[10] = {0};
		while(1)
		
		{
			printf("?????\n");
			int listen_socket;
			ret = read(client_socket, id_buf, 10);
			printf("ret2:%d\n", ret);
			if(ret == -1)
			{
				perror("read");
				break;
			}
			if(ret == 0)
			{
				break;
			}
			id_buf[ret] = '\0';
			printf("buf:%s\n", id_buf);
			int id = 0;//寻找音箱id对应的socket
			for (int i = 0; i < ret;i++){
				id = id * 10 + id_buf[i] - '0';
			}
			printf("id:%d", id);
			int index = id % 128;
			struct hash *head = table[index];
			while(head!=NULL&&head->id!=id){
			//	printf("1\n");
				head = head->next;
			}
			if(head==NULL){
			int ret_write=write(client_socket, "not exist", 9);
			printf("ret_write:%d\n",ret_write);
				printf("该id不存在对应socket\n");
				break;
			}else{
				write(client_socket, "exist", 5);
				listen_socket = head->listen_socket;
			}			



			memset((void *)buf, 0, strlen(buf));

			ret = read(client_socket, buf, SIZE-1);
			if(ret == -1)
			{
				perror("read");
				break;
			}
			if(ret == 0)
			{
				break;
			}
			buf[ret] = '\0';
			if(strncmp(buf, "7", 1) == 0)     //播放指定歌曲
			{
				//break;
				
			}else if(strncmp(buf, "8", 1) == 0){//上传歌曲
				//
			}else if(strncmp(buf, "9", 1) == 0){//单曲循环
				//
			}else if(strncmp(buf, "0", 1) == 0){//随机播放
				//
			}else if(strncmp(buf, "end", 3) == 0){//结束
				memset((void *)buf, 0, strlen(buf));
				break;
			}else{//1~6
				//
				write(listen_socket, buf, strlen(buf));//直接将指令编号发送给device
			}
			memset((void *)buf, 0, strlen(buf));
		}
		close(client_socket);
	}else if(strcmp(buf,"device")==0){//将设备id以及其socket存储在hash_table中
		memset((void *)buf, 0, strlen(buf));
		ret = read(client_socket, buf, SIZE-1);
		//将字符数组转换为整数
		if(ret == -1)
		{
			perror("read");
			return NULL;
		}
		if(ret == 0)
		{
			return NULL;
		}
		buf[ret] = '\0';
		int id = 0;
		for (int i = 0; i < ret;i++){
			id = id * 10 + buf[i] - '0';
		}
		printf("id:%d\n",id);
		int index = id % 128;
		struct hash *head = table[index];
		while(head!=NULL&&head->id!=id){
			head = head->next;
		}
		if(head==NULL){
		//	printf("id2:%d\n",id);
			head=(struct hash *)malloc(sizeof(struct hash));

			head->id = id;
			head->listen_socket = client_socket;
			head->next = NULL;
			table[index]=head;
			// printf("id2:%d\n",head->id);

		}else{
			head->listen_socket = client_socket;
		}
		memset((void *)buf, 0, strlen(buf));
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
	
	while(1)
	{
		int client_socket = wait_client(listen_socket);
		
		pthread_t id;
		pthread_create(&id, NULL, hanld_client, (void *)&client_socket);  //创建一个线程，来处理客户端。
		
		pthread_detach(id);   //把线程分离出去。
	}
	
	close(listen_socket);
	
	return 0;
}

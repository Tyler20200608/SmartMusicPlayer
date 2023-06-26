
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
 
 
#define PORT 9990
#define SIZE 1024
 
int main()
{
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);   //创建和服务器连接套接字
	if(client_socket == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;  /* Internet地址族 */
    addr.sin_port = htons(PORT);  /* 端口号 */
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* IP地址 */
	inet_aton("39.105.7.127", &(addr.sin_addr));
 
	int addrlen = sizeof(addr);
	int listen_socket =  connect(client_socket,  (struct sockaddr *)&addr, addrlen);  //连接服务器
	if(listen_socket == -1)
	{
		perror("connect");
		return -1;
	}
	
	printf("成功连接到一个服务器\n");
	
	char buf[SIZE] = {0};
    char name[] = "client";
    while(1)        //向服务器发送指令
	{
        printf("1.开始播放；2.暂停播放；3.上一首；4.下一首；5.音量增加；6.音量减小；7.播放指定歌曲；8.上传歌曲；9.单曲循环；0.随机播放")
		printf("请输入你相输入的指令编号：");
		scanf("%s", buf);
        write(client_socket, name, strlen(name));
		write(client_socket, buf, strlen(buf));
		
		int ret = read(client_socket, buf, strlen(buf));
		
		//printf("buf = %s", buf);
		//printf("\n");
		if(strncmp(buf, "7", 1) == 0)     //播放指定歌曲
		{
			//break;
		}else if(strncmp(buf, "8", 1) == 0){//上传歌曲
			//
		}else if(strncmp(buf, "9", 1) == 0){//单曲循环
			//
			continue;
		}else if(strncmp(buf, "0", 1) == 0){//随机播放
			//
			continue;
		}else if(strncmp(buf, "end", 3) == 0){//结束
			break;
		}
	}
	close(listen_socket);
	
	return 0;
}

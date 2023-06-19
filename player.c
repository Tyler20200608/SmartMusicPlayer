#include "main.h"

int m_mp3_end(const char *name){
    const char *ptr = name;
    while(*ptr!='\0'){
        ptr++;
    }    
    for (int i = 0; i < 4;i++){
        ptr--;
    }
    if(ptr<name){
        return 0;
    }
    //printf("%s\n", name);//test
    return !(strcmp(ptr, ".mp3"));
}

void GetMusic(){
    //打开目录
    DIR *dir = opendir(MUSICPATH);
    if(dir==NULL){
        perror("opendir");
        exit(1);
    }



    // 读取目录
    struct dirent *file=NULL; 
//printf("???1\n");
    while ((file= readdir(dir)) != NULL)
    {
        //printf("???2\n");
        if (file->d_type != 8)
        {
            //printf("1%s\n", file->d_name);//test
            continue; // 不是普通文件
        }
        else
        {
            //printf("？？？？：%s\n", file->d_name);//test
            if (!m_mp3_end(file->d_name))//不是mp3文件
            {
                //printf("%s\n", file->d_name);//test
                continue;
            }
        }

        printf("%s\n", file->d_name);//test

        int ret= InsertLink(head, file->d_name);
        if(ret==FAILURE){
            printf("insertFailed");
            exit(1);
        }
    }
}

int InitShm(){
    void *addr2=NULL;
    //printf("1\n");
    int shmid = shmget(SHMKEY,SHMSIZE,0644 | IPC_CREAT);//创建共享内存
    if(shmid==-1){
        return FAILURE;
    }

    addr2 = shmat(shmid, NULL, 0);
    if(addr2==NULL){
        return FAILURE;
    }
    
    struct shm s;
    s.play_mode = SEQUENCEMODE;
    s.parent_pid = getpid();
    printf("111\n");
    memcpy((char *)addr2, &s,sizeof(s));
    printf("2\n");
    return SUCCESS;
}

void play_music(const char *name){
    pid_t child_pid = fork();
    if(child_pid==-1){
        perror("child fork failed");
        exit(1);
    }else if(child_pid==0){//子进程
        pid_t grand_pid = -1;
        while(grand_pid!=0){
            grand_pid=vfork();
            if(grand_pid==-1){
                perror("grand fork failed");
                exit(1);
            }else if(grand_pid==0){//孙进程
                char cur_name[64] = {0};
                //获取共享内存
                int shmid = shmget(SHMKEY, SHMSIZE, 0);
                if(shmid==-1){
                    perror("shmget failed");
                    exit(1);
                }
                //映射
                struct shm s;
                void *addr = shmat(shmid, NULL, 0);
                if(addr==NULL){
                    perror("shmat failed");
                    exit(1);
                }
                if(strlen(name)!=0){//直接开始播放
                    strcpy(cur_name, name);

                    //execl(MADPLAYPATH,"madplay -o wav:- ",music_path," | aplay");
                }else{//遍历链表，找到下一首歌
                    //判断播放模式，找到下一首歌曲
                    memcpy(&s, addr, sizeof(s));
                    FindNextMusic(s.cur_name,s.play_mode,cur_name);

                }

                //把信息写入共享内存(父子孙进程号、当前歌曲名)
                struct shm s2;
                strcpy(s2.cur_name, name);
                s2.child_pid = getppid();
                s2.grand_pid = getpid();
                memcpy(addr,&s2,sizeof(s2));
                shmdt(addr);//解除映射

                char music_path[128] = {0};//包含路径的歌曲名称
                strcpy(music_path, MUSICPATH);
                strcat(music_path, cur_name);
                char command[64] = {0};
                strcpy(command, COMMAND1);
                strcat(command,music_path);
                strcat(command, COMMAND2);
                system(command);



            }else{//子进程
                memset((void *)name, 0, strlen(name));//歌曲长度变为0，方便下次操作
                

                int status;
                waitpid(grand_pid, &status, 0); // 回收孙进程
            }
        }

    }else{
        return;
    }
}

void start_play(){
    if(g_start_flag==1){//已经开始播放
        return;
    }
    //获取歌曲名称
    if(head->next==NULL){//链表为空
        return;
    }
    char name[64];
    strcpy(name, head->next->music_name);
    play_music(name);//开始播放音乐
    g_start_flag = 1;
}
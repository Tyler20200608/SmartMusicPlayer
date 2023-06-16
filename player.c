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
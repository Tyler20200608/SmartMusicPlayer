#include "main.h"

//初始化双向循环链表
int InitLink(){
    head = (Node *)malloc(sizeof(Node));
    if(head==NULL){
        return FAILURE;
    }
    head->next = head;
    head->prior = head;
    return SUCCESS;
}

int InsertLink(Node *head,const char *name){
    if(head==NULL||name==NULL){
        return FAILURE;
    }
    Node *end = head->prior;
    // while(temp->next!=NULL){
    //     temp = temp->next;
    // }

    Node *n = (Node *)malloc(sizeof(Node));
    if(n==NULL){
        return FAILURE;
    }
    n->next = head;
    head->prior = n;
    n->prior = end;
    end->next = n;
    strcpy(n->music_name, name);
    //temp->next = n;
    return SUCCESS;
}

//cur当前 next下一首 mode模式
void FindNextMusic(const char *cur,int mode,char *next){//根据当前歌曲和播放模式找到下一首歌
    if (mode==CIRCLEMODE){//单曲循环
        strcpy(next, cur);
        return;
    }else if(mode==SEQUENCEMODE){//顺序播放
        Node *p = head->next;
        while(strcmp(p->music_name,cur)!=0){
            p = p->next;
        }
        if(p->next!=head){//跳过头结点，插入时头结点没有插入数据
            strcpy(next, p->next->music_name);
        }else{
            p = p->next;
            strcpy(next, p->next->music_name);
        }
        return;
    }else if(mode==RANDOMNMODE){//随机播放
        Node *p = head->next;
        srand(time(NULL));
        int num = rand() % 100;
        for (int i = 0; i < num;i++){
            p = p->next;
        }
        if(p==head){//跳过头结点
            p = p->next;
        }
        strcpy(next, p->music_name);
        return;
    }

    
}
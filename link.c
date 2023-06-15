#include "main.h"

//初始化链表
int InitLink(){
    head = (Node *)malloc(sizeof(Node));
    if(head==NULL){
        return FALLURE;
    }
    head->next = NULL;
    return SUCCESS;
}

int InsertLink(Node *head,const char *name){
    if(head==NULL||n==NULL){
        return FAILURE;
    }
    Node *temp = h;
    while(temp->next!=NULL){
        temp = temp->next;
    }

    Node *n = (Node *)malloc(sizeof(Node));
    if(n==NULL){
        return FAILURE;
    }
    n->next = NULL;
    strcpy(n->music_name, name);
    temp->next = n;
    return SUCCESS;
}
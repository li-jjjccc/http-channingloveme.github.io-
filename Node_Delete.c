#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define arrNum 10   // 数组大小
#define TargetNum 4 // 需要找到的数字，找到后删除该节点
typedef struct node {
    struct node* next;
    int val;
} node;


typedef bool(*remove_fn)(node*);

bool rm(node* curr)
{
    if(curr==NULL || curr->val!=TargetNum)
    {
        return false;
    }
    return true;
}
void remove_if(node ** head, remove_fn rm_fn)
{
    for(node** curr=head;*curr!=NULL;)
    {
        node* entry=*curr;
        if(rm_fn(entry)==true)
        {
            *curr=entry->next;
            free(entry);
            entry=NULL;
        }
        else{
            curr=&entry->next;
        }
    }
}
void remove_f(node** head, remove_fn rm_fn)
{
    node* phead;
    phead->next=*head;

    
    for(node*curr=phead->next,*prev=phead;curr!=NULL;)
    {
        if(rm_fn(curr)==true)
        {
            prev->next=curr->next;
            curr=curr->next;
        }
        else{
            prev=curr;
            curr=curr->next;
        }
        
        
    }


    *head=phead->next;
}
void nodePrint(node**nodeArr)
{   // 打印数组数据
    for(int i=0;i<arrNum&&nodeArr[i]!=NULL;i++)
    {
        printf("%d-",nodeArr[i]->val);
    }
    printf("\n");
}
void nodePrint_new(node**nodeArr)
{   // 打印链表数据
    node* head=*nodeArr;
    while(head)
    {
        printf("%d-",head->val);
        head=head->next;
    }
    printf("\n");
}

//
int main() {
    node**nodeArr=(node**)malloc(arrNum*sizeof(node*));
    for(int i=0;i<arrNum;i++)
    {
        nodeArr[i]=(node*)malloc(sizeof(node));
    }
    for(int i=0;i<arrNum;i++)
    {
        nodeArr[i]->val=i;
        if(i!=9)
        {
            nodeArr[i]->next=nodeArr[i+1];
        }
        else
        {
            nodeArr[i]->next=NULL;
        }
    }


    nodePrint(nodeArr);
    remove_if(&nodeArr[0],rm);
    nodePrint_new(nodeArr);
    
    return 0;
}

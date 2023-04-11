#include <iostream>
#include <stdio.h>

// 循环队列缓冲区模块  https://mp.weixin.qq.com/s/XMy8ZhHAxXzx2Xk4rcX54A
// 基本宏定义
#define qdata_t uint8_t
#define FIFO_SIZE 6
typedef enum{
    QUEUE_OK,
    QUEUE_FULL,
    QUEUE_EMPTY
}qstatus_t;
typedef struct{
    uint16_t addr_wr;
    uint16_t addr_rd;
    uint16_t length;
    qdata_t fifo[FIFO_SIZE];
}queue_t;



// 函数声明
int queue_cnt(queue_t* q);
bool queue_isEmpty(queue_t* q);
bool queue_isFull(queue_t* q);
qstatus_t queue_print(queue_t* q);
qstatus_t queue_reset(queue_t* q);
qstatus_t queue_write(queue_t* q,qdata_t data);
qstatus_t queue_read(queue_t* q,qdata_t* pdata);

// 函数定义
qstatus_t queue_reset(queue_t* q)
{
    int i=0;
    q->addr_rd=0;
    q->addr_wr=0;
    q->length=FIFO_SIZE;
    for(i=0;i<q->length;i++)
    {
        q->fifo[i]=0;
    }
    return QUEUE_OK;
}
qstatus_t queue_write(queue_t* q,qdata_t data)
{
    if(queue_isFull(q))
    {
        printf("queue is full!\n");
        return QUEUE_FULL;
    }

    q->fifo[q->addr_wr]=data;
    q->addr_wr=(q->addr_wr+1)%q->length;
    printf("queue write success!\n");
    queue_print(q);
    return QUEUE_OK;
}
qstatus_t queue_read(queue_t* q,qdata_t* pdata)
{
    if(queue_isEmpty(q))
    {
        printf("queue is empty!\n");
        return QUEUE_EMPTY;
    }

    *pdata=q->fifo[q->addr_rd];
    q->addr_rd=(q->addr_rd+1)%q->length;
    printf("queue read success!  :%02d\n",*pdata);
    queue_print(q);
    return QUEUE_OK;
}
int queue_cnt(queue_t* q)
{
    if(q->addr_rd<=q->addr_wr)
    {
        return q->addr_wr-q->addr_rd;
    }
    return q->length-q->addr_rd+q->addr_wr;
}
qstatus_t queue_print(queue_t* q)
{
    int i,j;

    for(i=0;i<q->addr_rd;i++)
    {
        printf("    ");
    }
    printf("rd=%d\n",q->addr_rd);

    for(i=0;i<q->length;i++)
    {
        if(q->addr_wr>q->addr_rd)
        {
            if(i>=q->addr_rd && i<q->addr_wr)
            {
                printf("[%02d]",q->fifo[i]);
            }
            else{
                printf("[ ]");
            }
        }
        else
        {
            if(i>=q->addr_rd || i<q->addr_wr)
            {
                printf("[%02d]",q->fifo[i]);
            }
            else{
                printf("[ ]");
            }
        }
    }

    printf("-----------cnt = %d\n",queue_cnt(q));

    for(i=0;i<q->addr_wr;i++)
    {
        printf("    ");
    }
    printf("wr=%d\n",q->addr_wr);

    return QUEUE_OK;
}
bool queue_isEmpty(queue_t* q)
{
    return (q->addr_rd==q->addr_wr);
}
bool queue_isFull(queue_t* q)
{
    return (q->addr_wr+1)%q->length==q->addr_rd;
}

// 
int main() 
{
    queue_t q;
    qdata_t data;

    queue_reset(&q);

    queue_write(&q,1);
    queue_write(&q,11);
    queue_write(&q,111);
    queue_read(&q,&data);
    queue_read(&q,&data);

    queue_write(&q,2);
    queue_write(&q,22);
    queue_write(&q,222);
    queue_read(&q,&data);
    queue_read(&q,&data);

    queue_write(&q,3);
    queue_write(&q,33);
    queue_write(&q,133);
    queue_read(&q,&data);
    queue_read(&q,&data);

    system("pause");
    return 0;
}

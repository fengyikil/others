#ifndef _HOT_H
#define _HOT_H
//温度队列相关
typedef struct _tem_queue
{
    short* data;
    short size;
    int front;
    int rear;
    int count;
    short max;
    short min;
    short avera;
}*ptem_queue,tem_queue;

extern void init_que(ptem_queue tq,short num);
extern char is_empty(ptem_queue tq);
extern char is_full(ptem_queue tq);
extern short de_que(ptem_queue tq);
extern void en_que(ptem_queue tq,short elem);
extern void max_min_avera(ptem_queue tq,unsigned short n,unsigned short m);
#endif

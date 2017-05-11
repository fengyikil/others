#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "../include/mtable.h"
#include <sys/mman.h>
#include <semaphore.h>
#include <mqueue.h>
#include "../include/map.h"
#include"hot.h"

void init_que(ptem_queue tq,short num)
{
	tq->data = (short*)malloc(sizeof(short)*num);
	tq->size = num;
	tq->max=tq->min=tq->avera=tq->front=tq->rear=tq->count=0;
	memset(tq->data,0,sizeof(short)*num);
}
char is_empty(ptem_queue tq)
{
	return (tq->count==0);
}
char is_full(ptem_queue tq)
{
	return (tq->count==tq->size);
}
short de_que(ptem_queue tq)
{
	short temp=0;
	if(!is_empty(tq))
	{
		temp=tq->data[tq->front];
		tq->count--;
		tq->front = (tq->front+1)%(tq->size);
	}
	else
	{
		printf("que is empty\n");
	}    
	return temp;
}
void en_que(ptem_queue tq,short elem)
{
	if(is_full(tq))
	    de_que(tq);
	tq->count++;
	tq->data[tq->rear]=elem;
	tq->rear = (tq->rear+1)%(tq->size);
}
void max_min_avera(ptem_queue tq,unsigned short n,unsigned short m)
{
	int num;
	int sum=0;
	int i;
	short temp;
	num = (tq->count>m)?(m-n+1):(tq->count-n+1);
	if(num>=1)
	{
		tq->min=tq->max=tq->data[((tq->rear-n)+(tq->size))%(tq->size)];
		for(i=0;i<num;i++)
		{
            temp = 	tq->data[((tq->rear-n-i)+(tq->size))%(tq->size)];
			if(tq->min > temp)
			    tq->min = temp;
			if(tq->max < temp)
			    tq->max = temp;
		    sum+=temp;	
		}
		tq->avera = sum/num;
	}
}



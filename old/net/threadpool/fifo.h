#ifndef __FIFO_H__
#define __FIFO_H__
#include<pthread.h>
struct fifo
{
    unsigned char  *buffer;
    unsigned int size;
    unsigned int in;
    unsigned int out;
    pthread_mutex_t *mtx;
    pthread_cond_t *cond;
};

extern struct fifo* fifo_init(unsigned int size);
extern void fifo_free(struct fifo* f);
extern void __fifo_reset(struct fifo *f);
extern unsigned int __fifo_get(struct fifo* f,void *buf,unsigned int len);
extern unsigned int __fifo_put(struct fifo* f,void *buf,unsigned int len);
extern unsigned int fifo_len(struct fifo *f);
extern void fifo_reset(struct fifo *f);
extern unsigned int fifo_get(struct fifo *f,void *buffer,unsigned int len);
extern unsigned int fifo_put(struct fifo *f,void *buffer,unsigned int len);
extern void block_fifo_put(struct fifo *f,void *buffer,unsigned int len);
#endif

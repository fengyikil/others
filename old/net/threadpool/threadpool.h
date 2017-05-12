#ifndef THREAD_POOL
#define THREAD_POLL
#include "fifo.h"
typedef void(*user_fun)(void*arg_buf);
struct thread_pool
{
    struct fifo*  tp_fifo;
    pthread_t* pool;
    user_fun ufun;
    int pool_size;
    int elem_size;
};
struct thread_pool* thread_pool_init(int pool_size,int fifo_size ,int elem_size, user_fun ufun);
 void thread_pool_add(struct thread_pool* tp ,void* arg_buf);
 void thread_pool_add_block(struct thread_pool* tp ,void* arg_buf);
#endif

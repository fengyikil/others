#include <threadpool.h>

void* thread_pool_fun(void* arg)
{
    struct thread_pool* tp = arg;
    char* buf = (char*)malloc(tp->elem_size);
    for(;;)
    {
        fifo_get(tp->tp_fifo,(void*)buf,tp->elem_size);
        (*tp->ufun)(buf);
    }
}
struct thread_pool* thread_pool_init(int pool_size,int fifo_size ,int elem_size, user_fun ufun)
{
    int i;
    struct thread_pool* tp = NULL;
    tp = (struct thread_pool*)malloc(sizeof(struct thread_pool));
    if(!tp)
    {
        goto Lerr;
    }
    memset(tp,0,sizeof(struct thread_pool));
    //初始化队列元素大小
    tp->elem_size = elem_size;
    //初始化用户执行函数
    tp->ufun = ufun;
    //初始化队列
    tp->tp_fifo = fifo_init(fifo_size);
    //初始化线程池
    tp->pool = (pthread_t* )malloc(sizeof(pthread_t)*pool_size);
    if(!tp->pool)
    {
        goto Lerr;
    }
    pthread_t* tmp_pool = tp->pool;
    for(i=0;i<pool_size;i++,tmp_pool++)
    {
        if( pthread_create(tmp_pool,NULL,thread_pool_fun,(void*)tp)!=0)
        {
            goto Lerr;
        }
    }
    return tp;

Lerr:
    if(tp)
    {
        if(tp->tp_fifo)
            free(tp->tp_fifo);
        free(tp);
    }
    return NULL;
}

void thread_pool_add(struct thread_pool* tp ,void* buf)
{
    if(fifo_put(tp->tp_fifo,buf,tp->elem_size) <  tp->elem_size)
        printf("no space for elem!\n");
}
void thread_pool_add_block(struct thread_pool* tp ,void* buf)
{
    block_fifo_put(tp->tp_fifo,buf,tp->elem_size);
}

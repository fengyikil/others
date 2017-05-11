#include <stdio.h>
#include<pthread.h>
//#include <fifo.h>
#include<threadpool.h>
struct tdelem
{
    int fd;
    int state;
};
void test_fun(void*arg_buf)
{
   printf("child thread tid = %u\n", pthread_self());
   sleep(1);
}
int main(int argc, char *argv[])
{
    struct tdelem myelem;
    struct thread_pool* tp;
    tp=thread_pool_init(2,10,sizeof(struct tdelem),test_fun);
    for(int i=0;i<100;i++)
    thread_pool_add_block(tp,&myelem);
        printf("hello\n");
//    sleep(15);

    pthread_join(*(tp->pool),NULL);

}

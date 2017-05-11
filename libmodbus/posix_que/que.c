#include <mqueue.h>
#include <pthread.h>

int mq_data[128];

struct tq
{
	int a;
	int b;
};
void* re_thread()
{
 	int mq_data[2];
	int b;
	b = 9;
	mqd_t re_mq;
	struct tq* mtq;
	mtq = (struct tq*)mq_data;
	re_mq = mq_open("/test_que",O_RDWR,0666,NULL);
	while(1)
	{
	mq_receive(re_mq,(char*)mq_data,128,0);
	printf("mtq->a is %d\n",mtq->a);
	printf("mtq->b is %d\n",mtq->b);
	printf("b is %d\n",b);
	}
}
void main()
{
	struct tq mtq;
	mqd_t main_mq;
	mtq.a=0;
	mtq.b=3;
	main_mq = mq_open("/test_que",O_RDWR|O_CREAT,0666,NULL);
	pthread_t re_t;
	pthread_create(&re_t,NULL,re_thread,NULL);
	while(1)
	{
	mtq.a++;
	mq_send(main_mq,(char*)&mtq,sizeof(struct tq),0);
	sleep(1);
	}
}

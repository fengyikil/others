#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<QDebug>
#include <sys/epoll.h>

#define PORT 6666
#define MAX_EVENTS 1000
void do_use_fd(struct epoll_event event)
{
    char buf[20];
    memset(buf,0,20);
    int size;
    printf("event is %d\n",event.events);
    printf("fd is %d\n",event.data.fd);
        size = read(event.data.fd,buf,3);
    printf("size is %d : %s\n",size,buf);
}
void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}
int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    struct epoll_event ev, events[MAX_EVENTS];
    int listen_sock, conn_sock, nfds, epollfd;
    int err,n;
    socklen_t addrlen = sizeof(struct sockaddr);
    //创建epoll
    epollfd =  epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(1);
    }

    //创建套接字
    listen_sock=socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock ==-1)
    {
        perror("can not create socket");
        exit(1);
    }
    //填充服务器端sockaddr地址结构
    //    bzero(&server_addr,sizeof(struct sockaddr_in));
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;           //协议族
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   //本地地址
    server_addr.sin_port = htons(PORT);
    //绑定地址结构
    err = bind(listen_sock,(struct sockaddr *)&server_addr,addrlen);
    if(err<0)
    {
        perror("server : bind error");
        exit(1);
    }
    //设置监听地址结构对应的端口
    err = listen(listen_sock,10);
    if(err ==-1)
    {
        perror("server : listen error\n");
        exit(1);
    }
    //添加listen_sock到epollfd
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(1);
    }
    //
    for (;;) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listen_sock)
            {
                conn_sock = accept(listen_sock,
                                   (struct sockaddr *) &client_addr, &addrlen);
                if (conn_sock == -1)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                printf("new sock com\n");
                setnonblocking(conn_sock);
//                ev.events = EPOLLIN | EPOLLET;
                ev.events = EPOLLIN |EPOLLET;

                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
                              &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                do_use_fd(events[n]);
            }
        }
    }
    return 0;
}

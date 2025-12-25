#include "EPoll.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <errno.h>
#include <fcntl.h>


#define EPOLL_SIZE 1024
#define BUFFER_SIZE 1024

EPoll::EPoll(/* args */)
{
    m_ePoll_fd = create_event1(EPOLL_CLOEXEC);
    if (m_ePoll_fd == -1)
    {
        printf("create_event1 failed\n");
    }
}

EPoll::~EPoll()
{
}
int startEpoll()
{
    int server_fd, epoll_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    struct epoll_event ev, events[MAX_EVENTS];
    char buffer[BUFFER_SIZE];

    // 1. 创建服务器 socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置 SO_REUSEADDR 选项，方便重启
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    return 0;
}
int set_nonblocking(int sockfd) {
    // 获取文件描述符的状态标志
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return -1;
    }
    // 设置文件描述符为非阻塞模式
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        return -1;
    }
    return 0;
}

int EPoll::addEvent(int fd, int event)
{
    struct epoll_event ev = {0};
    ev.events = toEpoll(event) ;
    ev.data.fd = fd;
    int ret = epoll_ctl(_event_fd, EPOLL_CTL_ADD, fd, &ev);
    if (ret != -1) {
       printf("epoll_ctl add fd %d event %d", fd, event);
    }
    return ret;
}

int EPoll::modifyEvent(int fd, int event)
{
    struct epoll_event ev = { 0 };
    ev.events = toEpoll(event);
    ev.data.fd = fd;
    auto ret = epoll_ctl(_event_fd, EPOLL_CTL_MOD, fd, &ev);
    cb(ret != -1);
    return ret;
}

int EPoll::delEvent(int fd,int event)
{
    int ret = -1;
    if (_event_map.erase(fd)) {
        _event_cache_expired.emplace(fd);
        ret = epoll_ctl(_event_fd, EPOLL_CTL_DEL, fd, nullptr);
    }
    return ret;
}

int EPoll::runLoop(bool blocked,bool ref_self)
{
    int ret = 0;
    char buffer[BUFFER_SIZE];
    struct epoll_event events[EPOLL_SIZE];
    while (!m_exit_flag)
    {
        ret = epoll_wait(m_ePoll_fd, events, EPOLL_SIZE, -1);
        if (ret <= 0)
        {
            continue;
        }

        for (size_t i = 0; i < ret; i++)
        {
            struct epoll_event &ev = events[i];
            int fd = ev.data.fd;
            if (events[i].events & EPOLLIN)
            {
                // 清空缓冲区
                memset(buffer, 0, BUFFER_SIZE);
                int valread = read(current_fd, buffer, BUFFER_SIZE - 1);

                if (valread > 0) {
                    // 成功读取数据
                    printf("Received from fd %d: %s", current_fd, buffer);
                    // 回显数据：将收到的数据原样发回给客户端
                    send(current_fd, buffer, valread, 0);
                } else if (valread == 0 || (valread == -1 && errno != EAGAIN && errno != EWOULDBLOCK)) {
                    // 客户端关闭连接或读取出错
                    // valread == 0 表示客户端优雅关闭 (EOF)
                    // valread == -1 且 errno 不是 EAGAIN/EWOULDBLOCK 表示真正的错误
                    printf("Client fd %d disconnected.\n", current_fd);
                    close(current_fd); // 关闭客户端 socket
                    // 注意：从 epoll 实例中删除 fd 是自动的（当 fd 被关闭时），但显式删除是更好的实践。
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, current_fd, NULL);
                }
            }
        }  
    }
    return 0;
    
}
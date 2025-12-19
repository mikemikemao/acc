#include "EPoll.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <errno.h>
#include <fcntl.h>
EPoll::EPoll(/* args */)
{

}

EPoll::~EPoll()
{
}

int EPoll::addEvent(int fd, int event)
{
    struct epoll_event ev = {0};
    
    return 0;
}

int EPoll::modifyEvent(int fd, int event)
{
    return 0;
}

int EPoll::delEvent(int fd,int event)
{
    return 0;
}
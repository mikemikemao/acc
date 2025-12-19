#include "EventPoller.h"

class EPoll : public EventPoller
{
private:
    /* data */
public:
    EPoll(/* args */);
    ~EPoll();
    /**
     * 添加事件
     * @param fd 监听的文件描述符
     * @param event 事件类型，例如 Event_Read | Event_Write
     */
    virtual int addEvent(int fd, int event);

    /**
     * 删除事件
     * @param fd 监听的文件描述符
     * @param event 事件类型，例如 Event_Read | Event_Write
     */
    virtual int delEvent(int fd, int event);

    /**
     * 修改事件
     * @param fd 监听的文件描述符
     * @param event 事件类型，例如 Event_Read | Event_Write
     */
    virtual int modifyEvent(int fd, int event);
};



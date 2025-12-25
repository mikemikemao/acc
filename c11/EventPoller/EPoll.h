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

    /**
     * 执行事件轮询
     * @param blocked 是否用执行该接口的线程执行轮询
     * @param ref_self 是记录本对象到thread local变量
     */
    virtual int runLoop(bool blocked,bool ref_self);
private:
    int m_ePoll_fd = -1;
    bool m_exit_flag = false;
    std::unordered_map<int, Poll_Record::Ptr> _event_map;
};



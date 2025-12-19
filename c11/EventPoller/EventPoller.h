class EventPoller
{
private:
    /* data */
public:
    typedef enum {
        Event_Read = 1 << 0, //读事件
        Event_Write = 1 << 1, //写事件
        Event_Error = 1 << 2, //错误事件
        Event_LT = 1 << 3,//水平触发
    } Poll_Event;
    EventPoller(/* args */){}
    virtual ~EventPoller(){}
    /**
     * 添加事件
     * @param fd 监听的文件描述符
     * @param event 事件类型，例如 Event_Read | Event_Write
     */
    virtual int addEvent(int fd, int event) = 0;

    /**
     * 删除事件
     * @param fd 监听的文件描述符
     * @param event 事件类型，例如 Event_Read | Event_Write
     */
    virtual int delEvent(int fd, int event) = 0;

    /**
     * 修改事件
     * @param fd 监听的文件描述符
     * @param event 事件类型，例如 Event_Read | Event_Write
     */
    virtual int modifyEvent(int fd, int event) = 0;
};



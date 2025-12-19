#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_EVENTS 10
#define PORT 8080
#define BUFFER_SIZE 1024

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

int main() {
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

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 2. 绑定 socket 到端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. 开始监听
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 4. 创建 epoll 实例
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 5. 将服务器 socket 添加到 epoll 监控列表中，监听读事件（新连接）
    ev.events = EPOLLIN; // 监听可读事件
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
        perror("epoll_ctl: server_fd");
        close(server_fd);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }

    // 主事件循环
    while (1) {
        // 6. 等待事件发生。返回值 nfds 是就绪事件的个数。
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1); // -1 表示无限期阻塞
        if (nfds == -1) {
            perror("epoll_wait");
            break;
        }

        // 7. 处理所有就绪的事件
        for (int i = 0; i < nfds; i++) {
            int current_fd = events[i].data.fd;

            // 情况 A：服务器 socket 可读，表示有新的客户端连接
            if (current_fd == server_fd) {
                int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
                if (client_fd == -1) {
                    perror("accept");
                    continue;
                }

                // 将新的客户端 socket 设置为非阻塞模式（Edge Triggered 模式下必须）
                set_nonblocking(client_fd);

                printf("New connection accepted, client_fd: %d\n", client_fd);

                // 设置监听客户端 socket 的读事件
                // 注意：这里使用了 EPOLLET（边缘触发）模式，性能更高，但编程更复杂。
                // 为了简单演示，我们先使用 Level Triggered（水平触发，默认）模式。
                // 将下一行改为 `ev.events = EPOLLIN | EPOLLET;` 即可启用 ET 模式。
                ev.events = EPOLLIN;
                ev.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                    perror("epoll_ctl: client_fd");
                    close(client_fd);
                }
            }
            // 情况 B：客户端 socket 可读，表示有数据到来
            else if (events[i].events & EPOLLIN) {
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
                // 如果 valread == -1 且 errno 是 EAGAIN/EWOULDBLOCK，在非阻塞模式下是正常的，表示数据已读完，无需处理。
            }
            // 可以在这里添加 EPOLLOUT（可写事件）的处理逻辑
            // else if (events[i].events & EPOLLOUT) { ... }
        }
    }

    // 清理资源（虽然上面的循环是无限的）
    close(server_fd);
    close(epoll_fd);
    return 0;
}
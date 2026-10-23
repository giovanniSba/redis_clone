#include "event_loop.h"
#include <sys/epoll.h>
#include <optional>
#include <utility>

EventLoop::EventLoop(uint16_t port, uint16_t connection_number): 
    tcp_server(port, connection_number)
{}


std::optional<string> EventLoop::init_epoll(){
    // init tcp server
    
    if(std::optional<string> error = tcp_server.init_server()){
        return *error;
    }

    int fd = epoll_create1(0);
    if(fd < 0){
        return "Error creating the epoll.";
    }

    this->epoll_fd = FileDescriptor(fd);

    // set event struct
    epoll_event event{
        .events = EPOLLIN,
        .data.fd = tcp_server.get_fd()
    };

    // bind all together
    int epoll_result = epoll_ctl(fd, EPOLL_CTL_ADD, tcp_server.get_fd(), &event);
    if(epoll_result < 0){
        return "Error in epoll binding.";
    }
    
    return std::nullopt;
}
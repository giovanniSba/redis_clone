#include "event_loop.h"
#include <sys/epoll.h>
#include <optional>
#include <utility>

EventLoop::EventLoop(uint16_t port = 6379, uint16_t connection_number = 128): 
    tcp_server(port, connection_number)
{}


std::optional<string> EventLoop::init_epoll(){
    // init tcp server
    FileDescriptor server_fd; // PROBLEM: now this is a local variable in this method. This should be moved to TcpServer property.
    auto result = tcp_server.init_server();
    
    if(std::holds_alternative<FileDescriptor>(result)){
        //correct 
        server_fd = std::move(std::get<FileDescriptor>(result));
    }else if(std::holds_alternative<string>(result)){
        //not correct
        return std::get<string>(result);
    }

    int fd = epoll_create1(0);
    if(fd < 0){
        return "Error creating the epoll.";
    }

    this->epoll_fd = FileDescriptor(fd);

    // set event struct
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = server_fd.get_fd();

    // bind all together
    int epoll_result = epoll_ctl(fd, EPOLL_CTL_ADD, server_fd.get_fd(), &event);
    if(epoll_result < 0){
        return "Error in epoll binding.";
    }
    
    return std::nullopt;
}
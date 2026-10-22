#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H
#include "file_descriptor.h"
#include "tcp_server.h"
#include "client_connection.h"
#include <unordered_map>

class EventLoop{
    private: 
        FileDescriptor epoll_fd; 
        TcpServer tcp_server; 
        std::unordered_map<int, ClientConnection> client_map; 
    public: 
        EventLoop(uint16_t port = 6379, uint16_t connection_number = 128); 
        
        // If it fails returns a string describing the error, null otherwise. 
        std::optional<string> init_epoll();     
        
};

#endif
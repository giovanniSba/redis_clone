#include "server.h"
#include <stdint.h>
#include <cstdio>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>

// TCP connection handling idea: set every socket to not blocking and monitor them with epoll.
class EventLoop{
    private: 
        sock_t server_fd; 
        sockaddr_in sock;
    public:

}

// Init a server connections. Return the socket associated to the server if the connection goes well, -1 otherwise.
std::unique_ptr<int> init_server_sock(in_port_t port){
    
}
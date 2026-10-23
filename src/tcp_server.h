#ifndef TCP_SERVER
#define TCP_SERVER
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <file_descriptor.h>
#include <sys/socket.h>
#include <optional>

using std::string;

class TcpServer{ 
    private: 
        uint16_t port;
        uint16_t connection_number;
        FileDescriptor fd;
    public: 
        explicit TcpServer(uint16_t port = 6379, uint16_t connection_number = 128);
        
        // init server sock, returns a string describing the error if it occurs, nullopt otherwise. 
        std::optional<string> init_server();

        int get_fd(){ return this->fd.get_fd();}
};

#endif
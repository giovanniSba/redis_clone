#ifndef TCP_SERVER
#define TCP_SERVER
#include <stdint.h>
#include <stdlib.h>
#include <variant>
#include <string>
#include <file_descriptor.h>
#include <sys/socket.h>
#include <netinet/in.h>

using std::string;

class TcpServer{ 
    private: 
        uint16_t port;
        uint16_t connection_number;
    public: 
        explicit TcpServer(uint16_t port = 6379, uint16_t connection_number = 128);
        std::variant<FileDescriptor, string> init_server();
};

#endif
#include <tcp_server.h>
#include <netinet/in.h>
#include <fcntl.h>

// constructor that only init server port
TcpServer::TcpServer(uint16_t port, uint16_t connection_number): 
port(port), connection_number(connection_number){};

// init server sock 
std::variant<FileDescriptor, string> TcpServer::init_server(){
    // create a TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0); 
    if(sock < 0){ 
        return "Socket creation failed";
    }

    // init server addr struct
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(this->port);

    // set sockopt to reuse addr
    int optval = 1; 
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0){
        return "Error when settings sock options.";
    }

    int result = bind(sock, (sockaddr *)&addr, sizeof(addr));
    if(result < 0){
        return "Socket binding went wrong.";
    }

    result = listen(sock, this->connection_number);
    if(result < 0){
        return "Listen phase went wrong.";
    }

    // setting the sock to NONBLOCK so we can create the epoll
    int current_flags = fcntl(sock, F_GETFL);
    if(current_flags < 0){
        return "Error when setting the sock to non-blocking mode";
    }

    result = fcntl(sock, F_SETFL, current_flags | O_NONBLOCK);
    if(result < 0){
        return "Error when setting the sock to non-blocking mode";
    }

    return FileDescriptor(sock); 
}
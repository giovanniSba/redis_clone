#include "client_connection.h"
#include <cerrno>


// Init ClientConnection with a file descriptor and empty buffers
ClientConnection::ClientConnection(int file_descriptor): fd(file_descriptor){
    this->input_buffer = "";
    this->output_buffer = "";
}

bool ClientConnection::is_input_empty(){
    return this->input_buffer.empty();
}

bool ClientConnection::is_output_empty(){
    return this->output_buffer.empty();
}

void ClientConnection::append_output(const string& buffer){
    this->output_buffer.append(buffer);
}

void ClientConnection::append_input(const string& buffer){
    this->input_buffer.append(buffer);
}

ssize_t ClientConnection::flush_output(){
    // prevent useless system calls
    if(this->output_buffer.empty()) return 0;

    ssize_t written_bytes = write(this->fd.get_fd(), this->output_buffer.data(), this->output_buffer.size());
    if(written_bytes < 0){
        // some errors occurs only because we are calling write with non blocking sockets, so we can ignore them
        if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR){
            return 0;
        }
        return -1;
    }

    this->output_buffer.erase(0, written_bytes);
    return written_bytes;
}

std::optional<string> ClientConnection::extract_command(){
    //TODO REDS logic for getting tha last command.
    return "command";
}

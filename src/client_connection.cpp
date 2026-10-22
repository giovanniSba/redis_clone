#include "client_connection.h"



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

void ClientConnection::flush_output(){
    //TODO
}

std::optional<string> ClientConnection::extract_command(){
    //TODO
    return "command";
}

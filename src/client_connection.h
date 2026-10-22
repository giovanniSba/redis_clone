#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H
#include "file_descriptor.h"
#include <string>
#include <optional>

using std::string;

// This class encapsulate:
// - The socket file descriptor (accept output)
// - Read buffer
// - Write buffer

class ClientConnection{
    private:
        FileDescriptor fd;
        string input_buffer;
        string output_buffer;
    public: 
        ClientConnection(int file_descriptor);
        bool is_input_empty();
        bool is_output_empty();

        void append_output(const string& buff);
        void append_input(const string& buff);

        // extract the last command
        std::optional<string> extract_command();

        // send data stored in the output buffer
        void flush_output();

      
};

#endif
#include <file_descriptor.h>
#include <unistd.h>

FileDescriptor::FileDescriptor(int descriptor) : fd(descriptor){} 

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept{
    if(this != &other){
        if(this->fd != -1){
            close(fd);
        }

        fd = other.fd;
        other.fd = -1;
    }

    return *this;
}
FileDescriptor::FileDescriptor(FileDescriptor &&other) noexcept: fd(other.fd){
    other.fd = -1;
}
FileDescriptor::~FileDescriptor(){
    if(this->fd != -1)
        close(this->fd);
}

int FileDescriptor::get_fd(){
    return this->fd;
}
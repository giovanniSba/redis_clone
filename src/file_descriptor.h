#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

class FileDescriptor{
    private: 
        int fd;
    public: 
        explicit FileDescriptor(int descriptor = -1);
        // move constructor
        FileDescriptor(FileDescriptor &&other) noexcept;
        //move assignment operator
        FileDescriptor& operator=(FileDescriptor&& other) noexcept;

        // deactivate copy and copy assignment
        FileDescriptor(const FileDescriptor&) = delete;
        FileDescriptor& operator=(const FileDescriptor&) = delete;

        ~FileDescriptor();
};

#endif
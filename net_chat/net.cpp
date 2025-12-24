#include "net.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

int create_server_socket(int port){
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) throw std::runtime_error("socket failed");

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if(bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("bind failed");

    if(listen(fd, 16) < 0)
        throw std::runtime_error("listen failed");

    return fd;
}

int connect_to_server(const std::string& host, int port){
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) throw std::runtime_error("socket failed");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0)
        throw std::runtime_error("bad ip");

    if(connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("connect failed");
    return fd;
}

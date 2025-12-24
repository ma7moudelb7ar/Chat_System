#include <iostream>
#include <thread>
#include <atomic>
#include <sys/socket.h>
#include <unistd.h>

#include "../common/protocol.h"
#include "../common/utils.h"
#include "net.h"

std::atomic<bool> running{true};

// استفبال رسائل 
void recv_loop(int fd){
    while(running){
        Message msg{};
        ssize_t n = recv(fd, &msg, sizeof(msg), 0);
        if(n <= 0){ running=false; break; }
        std::cout << format_message(msg) << std::endl;
    }
}
// argument vector   __  argument count
int main(int argc, char** argv){
    if(argc < 4){
        std::cerr << "Usage: client <server_ip> <port> <username>\n";
        return 1;
    }
    std::string host = argv[1];
    int port = std::stoi(argv[2]);
    std::string username = argv[3];

    try{
        //file description
        int fd = connect_to_server(host, port);

        // Send join message
        Message join{};
        join.sender_id = -1;
        copy_cstr(join.sender, MAX_NAME, username);
        copy_cstr(join.text, MAX_TEXT, "__join__");
        join.timestamp_ms = now_ms();
        send(fd, &join, sizeof(join), 0);

        std::thread t(recv_loop, fd);

        std::cout << "Connected. Type messages, /quit to exit.\n";
        while(running){
            std::string line;
            if(!std::getline(std::cin, line)) break;
            if(line == "/quit"){ running=false; break; }

            Message msg{};
            msg.sender_id = 1; // server may overwrite/ignore; kept for uniformity
            copy_cstr(msg.sender, MAX_NAME, username);
            copy_cstr(msg.text, MAX_TEXT, line);
            msg.timestamp_ms = now_ms();
            send(fd, &msg, sizeof(msg), 0);
        }

        shutdown(fd, SHUT_RDWR);
        close(fd);
        if(t.joinable()) t.join();
    }catch(const std::exception& e){
        std::cerr << "Client error: " << e.what() << "\n";
        return 1;
    }
}

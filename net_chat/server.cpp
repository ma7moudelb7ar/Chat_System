#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>

#include "../common/protocol.h"
#include "../common/utils.h"
#include "net.h"

struct ClientInfo {
    int fd;
    int id;
    std::string name;
};

std::mutex g_clients_mtx;
std::unordered_map<int,int> g_fd_to_id;
std::vector<ClientInfo> g_clients;
std::atomic<int> g_next_id{1};

void broadcast(const Message& msg, int except_fd=-1){
    std::lock_guard<std::mutex> lock(g_clients_mtx);
    for(const auto& c : g_clients){
        if(c.fd == except_fd) continue;
        ::send(c.fd, &msg, sizeof(msg), 0);
    }
}

void handle_client(int client_fd){
    // First message from client is a "join" with sender name set.
   
    Message join{};
    ssize_t n = recv(client_fd, &join, sizeof(join), 0);
    if(n <= 0){ close(client_fd); return; }

    int id = g_next_id++;
    std::string name = join.sender;
    std::cout << "[LOG] " << name << " connected with id " << id << std::endl; // Log connection
    {
        std::lock_guard<std::mutex> lock(g_clients_mtx);
        g_clients.push_back({client_fd, id, name});
        g_fd_to_id[client_fd] = id;
    }

    Message sys{};
    sys.sender_id = 0;
    copy_cstr(sys.sender, MAX_NAME, "SERVER");
    copy_cstr(sys.text, MAX_TEXT, name + " joined the chat");
    sys.timestamp_ms = now_ms();
    broadcast(sys);

    // Receive loop
    while(true){
        Message msg{};
        ssize_t r = recv(client_fd, &msg, sizeof(msg), 0);
        if(r <= 0) break;
        std::cout << "[MSG] from " << name
			<< ": " << msg.text << std::endl;  // Log message
		msg.sender_id = id;
        msg.timestamp_ms = now_ms();
        broadcast(msg, client_fd);
    }

    // Remove client
    {
        std::lock_guard<std::mutex> lock(g_clients_mtx);
        g_clients.erase(
            std::remove_if(g_clients.begin(), g_clients.end(),
                           [&](const ClientInfo& c){ return c.fd == client_fd; }),
            g_clients.end()
        );
        g_fd_to_id.erase(client_fd);
    }
    close(client_fd);
    std::cout << "[LOG] " << name << " disconnected" << std::endl;

    Message left{};
    left.sender_id = 0;
    copy_cstr(left.sender, MAX_NAME, "SERVER");
    copy_cstr(left.text, MAX_TEXT, name + " left the chat");
    left.timestamp_ms = now_ms();
    broadcast(left);
}

int main(int argc, char** argv){
    setvbuf(stdout, NULL, _IONBF, 0);
    int port = 5050;
    if(argc >= 2) port = std::stoi(argv[1]);

    try{
        int server_fd = create_server_socket(port);
        std::cout << "Server listening on port " << port << std::endl;

        while(true){
            sockaddr_in caddr{};
            socklen_t clen = sizeof(caddr);
            int cfd = accept(server_fd, (sockaddr*)&caddr, &clen);
            if(cfd < 0) continue;

            std::thread(handle_client, cfd).detach();
        }
        close(server_fd);
    }catch(const std::exception& e){
        std::cerr << "Server error: " << e.what() << "\n";
        return 1;
    }
}

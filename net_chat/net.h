#pragma once
#include <string>
#include <netinet/in.h>

int create_server_socket(int port);
int connect_to_server(const std::string& host, int port);

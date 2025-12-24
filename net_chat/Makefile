CXX=g++
CXXFLAGS=-std=c++17 -pthread -I../common

all: server client

server: server.cpp net.cpp ../common/utils.cpp
	$(CXX) $(CXXFLAGS) server.cpp net.cpp ../common/utils.cpp -o server

client: client.cpp net.cpp ../common/utils.cpp
	$(CXX) $(CXXFLAGS) client.cpp net.cpp ../common/utils.cpp -o client

clean:
	rm -f server client

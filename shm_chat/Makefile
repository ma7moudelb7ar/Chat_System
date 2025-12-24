CXX=g++
CXXFLAGS=-std=c++17 -I../common

all: shm_chat

shm_chat: shm_chat.cpp ipc.cpp ../common/utils.cpp
	$(CXX) $(CXXFLAGS) shm_chat.cpp ipc.cpp ../common/utils.cpp -o shm_chat

clean:
	rm -f shm_chat

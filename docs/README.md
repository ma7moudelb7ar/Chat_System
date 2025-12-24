# 🚀 Real-Time Chat System
### **Operating Systems Project — Team eLb7ar**

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Qt](https://img.shields.io/badge/Qt-5-green.svg)
![License](https://img.shields.io/badge/license-Apache%202.0-orange.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)

*A complete real-time chat system demonstrating advanced IPC mechanisms and network programming*

[Features](#-features) • [Architecture](#-architecture) • [Installation](#-installation) • [Usage](#-usage) • [Documentation](#-documentation)

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Architecture](#-architecture)
- [System Requirements](#-system-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
  - [Network Chat (Sockets)](#1️⃣-network-chat-tcp-sockets)
  - [Shared Memory Chat](#2️⃣-shared-memory-chat-ipc)
- [Project Structure](#-project-structure)
- [Technical Implementation](#-technical-implementation)
- [API Reference](#-api-reference)
- [Contributing](#-contributing)
- [Team](#-team)
- [License](#-license)

---

## 🎯 Overview

This project implements **two complete chat systems** demonstrating different Inter-Process Communication (IPC) mechanisms as part of an Operating Systems course project. The systems showcase practical implementations of:

- **Network Programming** using TCP sockets
- **Concurrent Programming** with multithreading
- **Shared Memory** communication
- **Synchronization** using semaphores
- **Modern GUI Development** with Qt5

Both systems feature a custom binary protocol, thread-safe operations, and professional-grade error handling.

---

## ✨ Features

### 🌐 Network Chat (TCP/IP)
- ✅ Multithreaded TCP server supporting multiple concurrent clients
- ✅ Real-time message broadcasting to all connected users
- ✅ System notifications (user join/leave events)
- ✅ Cross-machine communication over network
- ✅ Graceful connection handling and cleanup
- ✅ Thread-safe client management with mutex protection

### 💾 Shared Memory Chat (IPC)
- ✅ High-performance local communication using System V IPC
- ✅ Circular buffer implementation for efficient message queuing
- ✅ Semaphore-based synchronization for thread safety
- ✅ Per-client read indices for independent message consumption
- ✅ Safe initialization with race condition prevention
- ✅ Support for up to 10 concurrent users

### 🎨 GUI Features
- ✅ Modern dark-themed Qt5 interface
- ✅ Separate server and client windows
- ✅ Real-time message display with formatted timestamps
- ✅ TCP stream framing for reliable message delivery
- ✅ Connection status indicators
- ✅ Intuitive user experience with visual feedback

### 🔧 Technical Features
- ✅ Custom binary message protocol (fixed-size structs)
- ✅ Safe string handling utilities (buffer overflow prevention)
- ✅ Millisecond-precision timestamps
- ✅ Modular architecture with reusable components
- ✅ RAII patterns for resource management
- ✅ Comprehensive error handling

---

## 🏗️ Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Chat System Architecture                  │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│  ┌─────────────┐      ┌──────────────┐      ┌────────────┐ │
│  │   Common    │      │  Network     │      │  Shared    │ │
│  │   Layer     │◄─────┤  Chat        │      │  Memory    │ │
│  │             │      │  (Sockets)   │      │  Chat      │ │
│  │ • Protocol  │      │              │      │  (IPC)     │ │
│  │ • Utils     │◄─────┤ • Server     │      │            │ │
│  │ • Message   │      │ • Client     │      │ • SHM      │ │
│  └─────────────┘      │ • Threading  │      │ • Semaphore│ │
│         ▲             └──────────────┘      └────────────┘ │
│         │                     ▲                     ▲       │
│         │                     │                     │       │
│         └─────────────────────┴─────────────────────┘       │
│                               │                             │
│                      ┌────────▼────────┐                    │
│                      │   Qt5 GUI       │                    │
│                      │                 │                    │
│                      │ • Main Menu     │                    │
│                      │ • Server Window │                    │
│                      │ • Chat Window   │                    │
│                      └─────────────────┘                    │
└─────────────────────────────────────────────────────────────┘
```

### Message Flow Diagram

#### Network Chat:
```
Client A                Server                 Client B
   │                      │                       │
   ├─────[Connect]───────►│                       │
   │◄────[Join Ack]───────┤                       │
   │                      ├─────[A Joined]───────►│
   │                      │                       │
   ├─────[Message]───────►│                       │
   │                      ├─────[Message]────────►│
   │◄─────[Message]───────┤◄─────[Message]───────┤
   │                      │                       │
```

#### Shared Memory Chat:
```
Process A                Shared Memory          Process B
   │                          │                     │
   ├──[sem_p]────────────────►│                     │
   ├──[write msg]────────────►│                     │
   ├──[sem_v]────────────────►│                     │
   │                          │◄────[sem_p]─────────┤
   │                          │◄────[read msg]──────┤
   │                          │◄────[sem_v]─────────┤
```

---

## 💻 System Requirements

### Operating System
- Linux (Ubuntu 20.04+, Fedora, Arch, etc.)
- macOS (with minor modifications)

### Development Tools
```bash
# Compiler
g++ 9.0+ (with C++17 support)

# Build Tools
make

# GUI Framework
Qt5 (qtbase5-dev, qt5-default)
```

### Libraries
```bash
# System Libraries
- pthread (POSIX threads)
- sys/socket.h (Network programming)
- sys/shm.h, sys/sem.h (System V IPC)

# Qt Libraries
- Qt5::Core
- Qt5::Widgets
- Qt5::Network
```

---

## 🔧 Installation

### 1. Clone the Repository
```bash
git clone https://github.com/ma7moudelb7ar/chat-system.git
cd chat-system
```

### 2. Install Dependencies

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential qt5-default qtbase5-dev g++ make
```

#### Fedora:
```bash
sudo dnf install gcc-c++ make qt5-qtbase-devel
```

#### Arch Linux:
```bash
sudo pacman -S base-devel qt5-base
```

### 3. Build the Projects

#### Network Chat (Console):
```bash
cd net_chat
make
```

#### Shared Memory Chat (Console):
```bash
cd shm_chat
make
```

#### GUI Applications:

**Network Chat GUI:**
```bash
cd gui/gui_net_chat
qmake gui.pro
make
```

**Shared Memory Chat GUI:**
```bash
cd gui/gui_shm_chat
qmake gui.pro
make
```

### 4. Quick Build (All Projects)
```bash
# From project root
./scripts/run_net.sh   # Build network chat
./scripts/run_shm.sh   # Build shared memory chat
```

---

## 🚀 Usage

### 1️⃣ Network Chat (TCP Sockets)

#### Console Mode

**Terminal 1 - Start Server:**
```bash
cd net_chat
./server 5050
# Output: Server listening on port 5050
```

**Terminal 2 - Client 1:**
```bash
./client 127.0.0.1 5050 Alice
# Output: Connected. Type messages, /quit to exit.
```

**Terminal 3 - Client 2:**
```bash
./client 127.0.0.1 5050 Bob
```

**Commands:**
- Type any message and press Enter to send
- `/quit` - Exit the chat

#### GUI Mode

```bash
cd gui/gui_net_chat
./gui
```

**Steps:**
1. Click **"Start Server"** to launch the server window
2. Set port (default: 5050) and click **"Start Server"**
3. Click **"Start Client"** to open client windows
4. Enter username, host (127.0.0.1), and port (5050)
5. Click **"Connect"** and start chatting!

**Network Configuration:**
- For LAN chat: Use server's local IP (e.g., 192.168.1.100)
- For same machine: Use 127.0.0.1 or localhost

---

### 2️⃣ Shared Memory Chat (IPC)

#### Console Mode

**Terminal 1 - User 1:**
```bash
cd shm_chat
./shm_chat 0 Alice
# Client ID: 0-9, Username: any string
```

**Terminal 2 - User 2:**
```bash
./shm_chat 1 Bob
```

**Terminal 3 - User 3:**
```bash
./shm_chat 2 Charlie
```

**Important Notes:**
- Each client must have a **unique ID** (0-9)
- All clients must run on the **same machine**
- Messages are stored in shared memory segment
- Use `/quit` to exit

#### GUI Mode

```bash
cd gui/gui_shm_chat
./gui_shm_chat
```

**Steps:**
1. Enter your name (e.g., "Alice")
2. Enter a unique Client ID (0-9)
3. Click **"Start Chat"**
4. Repeat in other terminals with different IDs

---

## 📁 Project Structure

```
chat-system/
│
├── 📂 common/                    # Shared components
│   ├── protocol.h                # Message structure definition
│   ├── utils.h                   # Utility functions (header)
│   └── utils.cpp                 # Timestamp, formatting, string utils
│
├── 📂 net_chat/                  # Network chat (TCP/IP)
│   ├── server.cpp                # Multithreaded TCP server
│   ├── client.cpp                # Console TCP client
│   ├── net.h/cpp                 # Socket utilities
│   └── Makefile                  # Build configuration
│
├── 📂 shm_chat/                  # Shared memory chat (IPC)
│   ├── shm_chat.cpp              # Main program (console)
│   ├── ipc.h/cpp                 # IPC wrapper functions
│   └── Makefile                  # Build configuration
│
├── 📂 gui/                       # Qt5 GUI applications
│   ├── 📂 gui_net_chat/          # Network chat GUI
│   │   ├── main.cpp              # Entry point
│   │   ├── mainmenuwindow.h/cpp  # Launcher window
│   │   ├── serverwindow.h/cpp    # Server GUI
│   │   ├── netchatwindow.h/cpp   # Client chat window
│   │   └── gui.pro               # Qt project file
│   │
│   └── 📂 gui_shm_chat/          # Shared memory GUI
│       ├── main.cpp              # Entry point
│       ├── startwindow.h/cpp     # Login window
│       ├── chatwindow.h/cpp      # Chat interface
│       └── gui.pro               # Qt project file
│
├── 📂 scripts/                   # Build automation
│   ├── run_net.sh                # Build & run network chat
│   └── run_shm.sh                # Build & run SHM chat
│
├── 📂 docs/                      # Documentation
│   └── README.md                 # Original documentation
```

---

## 🔬 Technical Implementation

### Message Protocol

All communication uses a fixed-size binary structure:

```cpp
struct Message {
    int32_t sender_id;        // Unique client identifier
    char sender[32];          // Username (null-terminated)
    char text[256];           // Message content
    int64_t timestamp_ms;     // Unix timestamp in milliseconds
};
```

**Advantages:**
- Fixed size enables efficient binary transmission
- No parsing overhead (direct memory copy)
- Predictable buffer requirements
- Cross-platform compatible (with endianness consideration)

### Thread Safety Mechanisms

#### Network Chat:
```cpp
std::mutex g_clients_mtx;  // Protects shared client list

void broadcast(const Message& msg, int except_fd) {
    std::lock_guard<std::mutex> lock(g_clients_mtx);
    // Safe iteration and sending
}
```

#### Shared Memory Chat:
```cpp
// Semaphore-based mutual exclusion
sem_p(semid, 0);  // Lock (P operation)
// Critical section: read/write shared memory
sem_v(semid, 0);  // Unlock (V operation)
```

### TCP Stream Framing

The GUI handles TCP's stream nature correctly:

```cpp
void NetChatWindow::onReadyRead() {
    recvBuffer.append(socket->readAll());
    
    // Extract complete messages
    while (recvBuffer.size() >= sizeof(Message)) {
        Message m;
        memcpy(&m, recvBuffer.constData(), sizeof(Message));
        recvBuffer.remove(0, sizeof(Message));
        displayMessage(m);
    }
}
```

### Circular Buffer Implementation

```cpp
struct SharedRegion {
    int write_idx;                  // Write position
    int read_idx[MAX_CLIENTS];      // Per-client read position
    Message buf[SHM_CAPACITY];      // Ring buffer
    
    // Writing:
    buf[write_idx] = msg;
    write_idx = (write_idx + 1) % SHM_CAPACITY;
    
    // Reading:
    msg = buf[read_idx[client_id]];
    read_idx[client_id] = (read_idx[client_id] + 1) % SHM_CAPACITY;
};
```

**Benefits:**
- O(1) insertion and removal
- Fixed memory footprint
- Each client reads at own pace
- No dynamic allocation

---

## 📚 API Reference

### Common Utilities

```cpp
// Get current timestamp in milliseconds
int64_t now_ms();

// Safe string copy (prevents buffer overflow)
void copy_cstr(char* dst, size_t cap, const std::string& src);

// Format message for display: "[username] message text"
std::string format_message(const Message& m);
```

### Network Functions

```cpp
// Create and bind TCP server socket
int create_server_socket(int port);

// Connect to TCP server
int connect_to_server(const std::string& host, int port);
```

### IPC Functions

```cpp
// Create or get shared memory segment
int create_or_get_shm(key_t key, size_t size);

// Attach to shared memory
void* attach_shm(int shmid);

// Detach from shared memory
void detach_shm(void* addr);

// Create or get semaphore set
int create_or_get_sem(key_t key, int nsems);

// Semaphore operations
void sem_p(int semid, int idx);  // Wait/Down/Lock
void sem_v(int semid, int idx);  // Signal/Up/Unlock
```

---

## 🧪 Testing

### Manual Testing Checklist

#### Network Chat:
- [ ] Server starts successfully
- [ ] Multiple clients can connect
- [ ] Messages broadcast to all clients
- [ ] Join/leave notifications work
- [ ] Clients can disconnect cleanly
- [ ] Server handles client crashes
- [ ] GUI connects/disconnects properly
- [ ] Message framing works (no corruption)

#### Shared Memory Chat:
- [ ] Multiple processes can attach
- [ ] Messages appear in all clients
- [ ] No race conditions (stress test)
- [ ] Circular buffer wraps correctly
- [ ] Semaphore prevents data corruption
- [ ] Clean shutdown releases resources

### Stress Testing

```bash
# Network Chat - 10 concurrent clients
for i in {1..10}; do
    ./client 127.0.0.1 5050 "User$i" &
done

# Shared Memory Chat - Max clients
for i in {0..9}; do
    ./shm_chat $i "User$i" &
done
```

---

## 🐛 Troubleshooting

### Common Issues

#### Issue: "Address already in use"
```bash
# Solution: Kill process using the port
sudo lsof -ti:5050 | xargs kill -9

# Or wait ~60 seconds for TIME_WAIT to expire
```

#### Issue: "Shared memory segment not found"
```bash
# List IPC resources
ipcs -m  # Shared memory
ipcs -s  # Semaphores

# Remove stale resources
ipcrm -m <shmid>
ipcrm -s <semid>

# Or remove all (careful!)
ipcs -m | awk '{print $2}' | xargs -n1 ipcrm -m
```

#### Issue: "Qt: Cannot find -lQt5Widgets"
```bash
# Install Qt development packages
sudo apt install qtbase5-dev qt5-qmake
```

#### Issue: GUI doesn't compile
```bash
# Regenerate Makefile
qmake gui.pro
make clean
make
```

---

## 🔮 Future Enhancements

### Planned Features
- [ ] 🔐 User authentication system
- [ ] 🔒 End-to-end encryption (TLS/SSL)
- [ ] 💬 Private messaging (/pm command)
- [ ] 📜 Chat history and logging
- [ ] 👥 Online users list display
- [ ] 🎨 Colored usernames
- [ ] 📁 File transfer support
- [ ] 🔔 Desktop notifications
- [ ] 💾 Message persistence (database)
- [ ] 🌐 IPv6 support

### Architecture Improvements
- [ ] Replace thread-per-client with epoll/io_uring
- [ ] Implement message queue for reliability
- [ ] Add heartbeat mechanism
- [ ] Graceful shutdown handling
- [ ] Configuration file support
- [ ] Logging framework integration

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### Getting Started
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request to [ma7moudelb7ar/chat-system](https://github.com/ma7moudelb7ar/chat-system)

### Coding Standards
- Follow existing code style (K&R with 4-space indentation)
- Add comments for complex logic
- Write meaningful commit messages
- Test thoroughly before submitting

### Bug Reports
Please include:
- Operating system and version
- Steps to reproduce
- Expected vs actual behavior
- Relevant logs or screenshots

**Contact**: For major changes, please open an issue first or email ma7moudelb7ar@gmail.com

---

## 👥 Team

**Team eLb7ar** - Operating Systems Course Project 2025

### 👨‍💻 Team Leader
**Mahmoud Elb7ar** - *Project Lead & Main Developer*
- 📧 Email: ma7moudelb7ar@gmail.com
- 🔗 GitHub: [@ma7moudelb7ar](https://github.com/ma7moudelb7ar)

### Team Members & Contributions

| Team Member | Technical Implementation | GUI Development |
|-------------|--------------------------|-----------------|
| **Person 1** | • Implemented TCP server with multithreading<br>• Developed socket utilities and connection handling<br>• Built message broadcasting system | • Designed Qt5 Network Chat server window<br>• Implemented connection status indicators<br>• Created server logging interface |
| **Person 2** | • Implemented shared memory communication system<br>• Designed circular buffer with semaphore synchronization<br>• Developed IPC wrapper functions and safety mechanisms | • Built Qt5 Shared Memory Chat interface<br>• Created start window with user authentication<br>• Implemented real-time message display |
| **Person 3** | • Developed console client with async message reception<br>• Implemented message protocol handling<br>• Built thread-safe message queuing | • Designed main menu launcher window<br>• Created dark-themed modern UI/UX<br>• Implemented TCP framing for GUI client |
| **Person 4** | • Implemented timestamp utilities and formatting<br>• Developed safe string handling functions<br>• Built error handling and validation layers | • Created chat message display widgets<br>• Designed input/send message interface<br>• Implemented GUI notifications and alerts |
| **Person 5** | • Conducted system testing and stress testing<br>• Created build scripts and Makefiles<br>• Wrote technical documentation | • Performed GUI testing and UX improvements<br>• Fixed UI bugs and responsiveness issues<br>• Integrated GUI with backend systems |

**Collaborative Efforts**: All team members participated in code reviews, debugging sessions, architectural decisions, and cross-component integration testing.

---

## 📄 License

This project is licensed under the **Apache License 2.0** - see below for details:

```
Copyright 2025 Team eLb7ar

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

### Educational Use
This project is developed for educational purposes as part of an Operating Systems course. Feel free to use it for learning, but please cite appropriately.

---

## 📞 Support

### Get Help
- **GitHub Issues**: [Report a Bug](https://github.com/ma7moudelb7ar/chat-system/issues)
- **GitHub Discussions**: [Ask Questions](https://github.com/ma7moudelb7ar/chat-system/discussions)
- **Email**: ma7moudelb7ar@gmail.com

### Quick Links
- 🏠 [Project Repository](https://github.com/ma7moudelb7ar/chat-system)
- 📖 [Documentation](https://github.com/ma7moudelb7ar/chat-system/wiki)
- 🐛 [Bug Reports](https://github.com/ma7moudelb7ar/chat-system/issues/new?template=bug_report.md)
- 💡 [Feature Requests](https://github.com/ma7moudelb7ar/chat-system/issues/new?template=feature_request.md)

### Response Time
We aim to respond to issues and questions within **48 hours**. For urgent matters, please email directly.

---

## 🙏 Acknowledgments

- Operating Systems course instructors and TAs
- Qt Framework documentation and community
- POSIX and System V IPC specifications
- Open source community for inspiration

---

## 📊 Project Statistics


- **Files**: 25+
- **Languages**: C++17, Qt/QML
- **Development Time**: 4 weeks
- **Team Size**: 5 members

---

<div align="center">

### ⭐ Star this repo if you found it helpful!

**by Team eLb7ar**

[⬆ Back to Top](#-real-time-chat-system)

</div>
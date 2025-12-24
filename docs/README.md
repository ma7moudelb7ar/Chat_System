# 🖧 Network Chat System  
### **Operating Systems Project — Team eLb7ar**  
A complete real-time chat system built using **TCP sockets**, **multithreading**, and a **Qt5 GUI client**.

---

## 🚀 Project Overview

This project implements a full network-based chat system that allows multiple clients to connect and exchange messages in real time.

It includes:

- ✔ **Multithreaded TCP Server** (C++)  
- ✔ **Console Client** (C++)  
- ✔ **Modern GUI Client (Qt5)**  
- ✔ **Custom Message Protocol**  
- ✔ **Safe utilities for string handling & timestamps**  
- ✔ **TCP Framing Support** to correctly handle stream-based message boundaries

The design is modular, clean, and close to production-grade networking code.

---

## 🏗 Folder Structure

```
project/
│
├── common/
│   ├── protocol.h
│   ├── utils.h
│   └── utils.cpp
│
├── net_chat/
│   ├── client.cpp
│   ├── server.cpp
│   ├── net.cpp
│   └── net.h
│
└── gui_chat/
    ├── netchatwindow.h
    ├── netchatwindow.cpp
    └── main.cpp
```

---

## 📡 How the System Works

### **🟦 Server**
- Creates a TCP listening socket.
- Accepts multiple clients (each in a separate thread).
- Broadcasts messages to all other connected clients.
- Sends system messages when users join or leave.
- Cleans up disconnected clients safely.

### **🟩 Console Client**
- Connects to the server via IP + Port.
- Spawns a thread for receiving messages.
- Sends user input messages.
- Gracefully exits using `/quit`.

### **🟧 GUI Client (Qt5)**
- Nice dark-themed UI.
- Connects using QTcpSocket.
- Shows chat messages in real-time.
- Handles TCP stream framing using an internal buffer.
- Clean user interface with connect/disconnect / send message handling.

---

## 📜 Message Protocol

All communication uses a fixed-size C++ struct:

```cpp
struct Message {
    int32_t sender_id;
    char sender[32];
    char text[256];
    int64_t timestamp_ms;
};
```

This ensures safe, predictable transfer across sockets.

---

## ⚙️ Building Instructions

### ✔ Build on Linux (Server + Console Client)

```bash
g++ server.cpp net.cpp ../common/utils.cpp -o server -std=c++17 -pthread
g++ client.cpp net.cpp ../common/utils.cpp -o client -std=c++17 -pthread
```

### ✔ Build GUI Client (Qt)

Inside `gui_chat/`:

```bash
qmake gui_chat.pro
make
./gui_chat
```

---

## ▶️ Running

### 1️⃣ Start Server
```bash
./server 5050
```

### 2️⃣ Run Console Clients
```bash
./client 127.0.0.1 5050 username
```

### 3️⃣ Run GUI Client
- Enter Username  
- Enter Host (ex: 127.0.0.1)  
- Enter Port (ex: 5050)  
- Click **Connect**  
- Start chatting 🎉

---

## 🧠 Technical Features

- 🚀 Multithreaded TCP server  
- 🧵 Each client handled in a separate thread  
- 🧱 Mutex-protected shared structures  
- 🛡 Safe string copying (`copy_cstr`)  
- ⏱ Timestamp support  
- 📢 System join/leave messages  
- 📦 GUI handles TCP framing correctly  
- 💬 Clean readable message formatting  

---

## 🔒 Thread Safety

The server protects shared resources with a mutex:

```cpp
std::mutex g_clients_mtx;
```

This ensures:

- Safe insertion/removal of clients  
- Safe broadcasting  
- No race conditions during disconnect  

---

## 🏁 Future Improvements

- 🔸 Private messaging (/pm)  
- 🔸 Display online user list  
- 🔸 Colored usernames  
- 🔸 Chat history / logging  
- 🔸 Better timestamp formatting  

---

## ✨ Developed By  
### **Team: eLb7ar**  
Operating Systems Course Project — 2025

---

## 📄 License  
This project is released for educational use under Apache License 2.0.


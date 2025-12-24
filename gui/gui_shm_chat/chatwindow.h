#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

#include <thread>
#include <atomic>

// IPC
#include "../../shm_chat/ipc.h"
#include "../../common/protocol.h"

// Forward declaration
struct SharedRegion;

class ChatWindow : public QWidget {
    Q_OBJECT

public:
    ChatWindow(int clientId, const QString& username);
    ~ChatWindow();

private slots:
    void sendMessage();

private:
    void receiverLoop();

    // ===== User Info =====
    int clientId;
    QString username;

    // ===== UI =====
    QTextEdit* chatBox;
    QLineEdit* input;
    QPushButton* sendBtn;

    // ===== Shared Memory =====
    int shmid;
    int semid;
    SharedRegion* region;

    // ===== Thread Control =====
    std::atomic<bool> running;
    std::thread recvThread;
};

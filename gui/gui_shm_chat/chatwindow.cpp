#include "chatwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <sys/sem.h>
#include <chrono>
#include <thread>

#include "../../common/utils.h"

#define MAX_CLIENTS 10

// Shared memory layout
struct SharedRegion {
    int initialized;
    int write_idx;
    int read_idx[MAX_CLIENTS];
    Message buf[SHM_CAPACITY];
};

ChatWindow::ChatWindow(int id, const QString& user)
    : clientId(id), username(user), running(true)
{
    setWindowTitle("Shared Memory Chat - Team elb7ar");
    resize(520, 620);

    // ===== Window Style =====
    setStyleSheet("background:#121212; color:white;");

    // ===== Chat Box =====
    chatBox = new QTextEdit(this);
    chatBox->setReadOnly(true);
    chatBox->setStyleSheet(
        "background:#1e1e1e;"
        "border:none;"
        "padding:10px;"
        "font-size:14px;"
    );

    // ===== Input =====
    input = new QLineEdit(this);
    input->setPlaceholderText("Type a message...");
    input->setStyleSheet(
        "background:#2a2a2a;"
        "color:white;"
        "padding:8px;"
        "border-radius:6px;"
    );

    // ===== Send Button =====
    sendBtn = new QPushButton("Send", this);
    sendBtn->setFixedWidth(80);
    sendBtn->setStyleSheet(
        "QPushButton{"
        "background:#2e7d32;"
        "color:white;"
        "font-size:14px;"
        "border-radius:8px;"
        "}"
        "QPushButton:hover{"
        "background:#388e3c;"
        "}"
    );

    auto* bottom = new QHBoxLayout();
    bottom->addWidget(input);
    bottom->addWidget(sendBtn);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(chatBox);
    layout->addLayout(bottom);

    connect(sendBtn, &QPushButton::clicked,
        this, &ChatWindow::sendMessage);
    connect(input, &QLineEdit::returnPressed,
        this, &ChatWindow::sendMessage);

    // ===== Shared Memory & Semaphore =====
    key_t shm_key = 0x1111;
    key_t sem_key = 0x2222;

    shmid = create_or_get_shm(shm_key, sizeof(SharedRegion));
    region = static_cast<SharedRegion*>(attach_shm(shmid));

    semid = create_or_get_sem(sem_key, 1);
    semctl(semid, 0, SETVAL, 1); // mutex

    // ===== Receiver Thread =====
    recvThread = std::thread(&ChatWindow::receiverLoop, this);
}

ChatWindow::~ChatWindow()
{
    running = false;
    if (recvThread.joinable())
        recvThread.join();

    detach_shm(region);
}

// ===== Send Message =====
void ChatWindow::sendMessage()
{
    QString text = input->text().trimmed();
    if (text.isEmpty())
        return;

    Message msg{};
    msg.sender_id = clientId;
    copy_cstr(msg.sender, MAX_NAME, username.toStdString());
    copy_cstr(msg.text, MAX_TEXT, text.toStdString());
    msg.timestamp_ms = now_ms();

    sem_p(semid, 0);
    region->buf[region->write_idx] = msg;
    region->write_idx =
        (region->write_idx + 1) % SHM_CAPACITY;
    sem_v(semid, 0);

    input->clear();
}

// ===== Receive Messages =====
void ChatWindow::receiverLoop()
{
    while (running) {
        sem_p(semid, 0);

        while (region->read_idx[clientId] != region->write_idx) {
            Message msg = region->buf[region->read_idx[clientId]];
            region->read_idx[clientId] =
                (region->read_idx[clientId] + 1) % SHM_CAPACITY;

            // عرض كل الرسائل (حتى رسالتي)
            chatBox->append(
                QString::fromUtf8(
                    format_message(msg).c_str()
                )
            );
        }

        sem_v(semid, 0);
        std::this_thread::sleep_for(
            std::chrono::milliseconds(5)
        );
    }
}

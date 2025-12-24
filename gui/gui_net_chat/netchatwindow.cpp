#include "netchatwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "../common/utils.h"

NetChatWindow::NetChatWindow(QWidget *parent)
    : QWidget(parent), socket(new QTcpSocket(this))
{
    setWindowTitle("Network Chat - Project OS");
    resize(650, 480);

    auto *title = new QLabel("Network Chat (Sockets) - Project OS - Team eLb7ar");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 8px;");

    nameEdit = new QLineEdit("eLb7ar");
    hostEdit = new QLineEdit("127.0.0.1");
    portEdit = new QLineEdit("5050");

    nameEdit->setPlaceholderText("Username");
    hostEdit->setPlaceholderText("Server IP");
    portEdit->setPlaceholderText("Port");

    auto *form = new QHBoxLayout();
    form->addWidget(new QLabel("Name:"));
    form->addWidget(nameEdit);
    form->addWidget(new QLabel("Host:"));
    form->addWidget(hostEdit);
    form->addWidget(new QLabel("Port:"));
    form->addWidget(portEdit);

    connectBtn = new QPushButton("Connect");
    statusLabel = new QLabel("Not connected");
    statusLabel->setStyleSheet("color: #ffcc80;");

    auto *top = new QHBoxLayout();
    top->addWidget(connectBtn);
    top->addWidget(statusLabel);

    chatBox = new QTextEdit();
    chatBox->setReadOnly(true);

    inputEdit = new QLineEdit();
    inputEdit->setPlaceholderText("Type message + Enter...");

    sendBtn = new QPushButton("Send");
    sendBtn->setEnabled(false);

    auto *bottom = new QHBoxLayout();
    bottom->addWidget(inputEdit);
    bottom->addWidget(sendBtn);

    auto *main = new QVBoxLayout();
    main->addWidget(title);
    main->addLayout(form);
    main->addLayout(top);
    main->addWidget(chatBox);
    main->addLayout(bottom);

    setLayout(main);

    setStyleSheet(
        "QWidget { background-color: #121212; color: #f0f0f0; }"
        "QTextEdit { background-color: #1e1e1e; border-radius: 8px; padding: 6px; }"
        "QLineEdit { background-color: #1e1e1e; border-radius: 6px; padding: 4px 6px; }"
        "QPushButton { background-color: #26a69a; color: white; border-radius: 8px; padding: 6px 12px; }"
        "QPushButton:disabled { background-color: #555555; }"
        "QPushButton:hover:!disabled { background-color: #2bbbad; }"
        "QPushButton:pressed:!disabled { background-color: #00897b; }"
    );

    connect(connectBtn, &QPushButton::clicked, this, &NetChatWindow::onConnectClicked);
    connect(sendBtn, &QPushButton::clicked, this, &NetChatWindow::onSendClicked);
    connect(inputEdit, &QLineEdit::returnPressed, this, &NetChatWindow::onSendClicked);
    connect(socket, &QTcpSocket::readyRead, this, &NetChatWindow::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &NetChatWindow::onDisconnected);
}

void NetChatWindow::appendLine(const QString &line){
    chatBox->append(line);
}

void NetChatWindow::onConnectClicked(){
    if (connected){
        socket->disconnectFromHost();
        return;
    }

    username = nameEdit->text().trimmed();
    if (username.isEmpty()){
        statusLabel->setText("Enter username first");
        return;
    }

    QString host = hostEdit->text();
    bool ok;
    int port = portEdit->text().toInt(&ok);

    if (!ok){
        statusLabel->setText("Invalid port");
        return;
    }

    statusLabel->setText("Connecting...");
    socket->connectToHost(host, port);

    if(!socket->waitForConnected(3000)){
        statusLabel->setText("Connect failed");
        return;
    }

    connected = true;
    sendBtn->setEnabled(true);
    connectBtn->setText("Disconnect");
    statusLabel->setText("Connected as " + username);

    sendJoin();
}

void NetChatWindow::sendJoin(){
    if (!connected) return;

    Message m{};
    m.sender_id = -1;
    copy_cstr(m.sender, MAX_NAME, username.toStdString());
    copy_cstr(m.text, MAX_TEXT, "__join__");
    m.timestamp_ms = now_ms();

    socket->write(reinterpret_cast<char*>(&m), sizeof(m));
}

void NetChatWindow::onSendClicked(){
    if (!connected) return;

    QString text = inputEdit->text().trimmed();
    if (text.isEmpty()) return;

    Message m{};
    m.sender_id = 1;
    copy_cstr(m.sender, MAX_NAME, username.toStdString());
    copy_cstr(m.text, MAX_TEXT, text.toStdString());
    m.timestamp_ms = now_ms();

    socket->write(reinterpret_cast<char*>(&m), sizeof(m));
    inputEdit->clear();
}

void NetChatWindow::onReadyRead(){
    recvBuffer.append(socket->readAll());

    while (recvBuffer.size() >= (int)sizeof(Message)) {
        Message m{};
        memcpy(&m, recvBuffer.constData(), sizeof(Message));
        recvBuffer.remove(0, sizeof(Message));

        appendLine(QString::fromStdString(format_message(m)));
    }
}

void NetChatWindow::onDisconnected(){
    connected = false;
    sendBtn->setEnabled(false);
    connectBtn->setText("Connect");
    statusLabel->setText("Disconnected");
}

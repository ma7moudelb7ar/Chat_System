#include "serverwindow.h"
#include "../common/utils.h"
#include "../common/protocol.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ServerWindow::ServerWindow(QWidget* parent)
    : QWidget(parent), server(new QTcpServer(this))
{
    setWindowTitle("Chat Server - Project OS");
    resize(650, 480);

    auto* title = new QLabel("Network Chat (Server) - Project OS - Team eLb7ar");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 8px;");

    portEdit = new QLineEdit("5050");
    portEdit->setPlaceholderText("Port");

    startBtn = new QPushButton("Start Server");
    statusLabel = new QLabel("Not running");
    statusLabel->setStyleSheet("color: #ffcc80; font-weight: bold;");

    auto* form = new QHBoxLayout();
    form->addWidget(new QLabel("Port:"));
    form->addWidget(portEdit);
    form->addWidget(startBtn);
    form->addWidget(statusLabel);

    logBox = new QTextEdit();
    logBox->setReadOnly(true);

    auto* main = new QVBoxLayout();
    main->addWidget(title);
    main->addLayout(form);
    main->addWidget(logBox);
    setLayout(main);

    setStyleSheet(
        "QWidget { background-color: #121212; color: #f0f0f0; }"
        "QTextEdit { background-color: #1e1e1e; border-radius: 8px; padding: 6px; }"
        "QLineEdit { background-color: #1e1e1e; border-radius: 6px; padding: 4px 6px; }"
        "QPushButton { background-color: #26a69a; color: white; border-radius: 8px; padding: 6px 12px; }"
        "QPushButton:hover:!disabled { background-color: #2bbbad; }"
        "QPushButton:pressed:!disabled { background-color: #00897b; }"
        "QPushButton:disabled { background-color: #555555; }"
    );

    connect(startBtn, &QPushButton::clicked, this, &ServerWindow::startOrStopServer);
}


// ====================================================================
// Start OR Stop server (fixed version)
// ====================================================================
void ServerWindow::startOrStopServer() {

    // ---------- STOP ----------
    if (serverRunning) {
        serverRunning = false;

        // stop listening
        if (server) {
            server->close();
            server->deleteLater();
            server = nullptr;
        }

        // disconnect all clients
        for (QTcpSocket* c : clients) {
            c->disconnectFromHost();
            c->close();
        }
        clients.clear();

        statusLabel->setText("Stopped");
        statusLabel->setStyleSheet("color: #ffcc80; font-weight: bold;");
        startBtn->setText("Start Server");
        logBox->append("🛑 Server stopped.");
        return;
    }

    // ---------- START ----------
    int port = portEdit->text().toInt();

    // create fresh server instance
    server = new QTcpServer(this);

    if (!server->listen(QHostAddress::Any, port)) {
        logBox->append("❌ Failed to start server!");
        return;
    }

    serverRunning = true;

    startBtn->setText("Stop Server");
    statusLabel->setText("Running");
    statusLabel->setStyleSheet("color: #80ff80; font-weight: bold;");
    logBox->append("✅ Server started on port " + QString::number(port));

    connect(server, &QTcpServer::newConnection, this, &ServerWindow::onNewConnection);
}


// ====================================================================
void ServerWindow::onNewConnection() {
    QTcpSocket* client = server->nextPendingConnection();
    clients.append(client);

    logBox->append("🔵 Client connected!");

    connect(client, &QTcpSocket::readyRead, this, &ServerWindow::onClientMessage);
    connect(client, &QTcpSocket::disconnected, this, &ServerWindow::onClientDisconnected);
}


// ====================================================================
void ServerWindow::onClientMessage() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();

    if (data.size() < (int)sizeof(Message))
        return;

    Message m{};
    memcpy(&m, data.data(), sizeof(Message));

    logBox->append(QString::fromStdString(format_message(m)));

    // broadcast to all
    for (QTcpSocket* c : clients)
        if (c != client)
            c->write(data);
}


// ====================================================================
void ServerWindow::onClientDisconnected() {
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    clients.removeAll(client);

    logBox->append("🔴 Client disconnected!");
}

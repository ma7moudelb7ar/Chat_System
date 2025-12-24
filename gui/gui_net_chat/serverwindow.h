#pragma once
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class ServerWindow : public QWidget {
    Q_OBJECT

public:
    explicit ServerWindow(QWidget* parent = nullptr);

private slots:
    void startOrStopServer();   // ← مهم جداً! اسم الدالة الصحيح
    void onNewConnection();
    void onClientMessage();
    void onClientDisconnected();

private:
    QTcpServer* server;
    QList<QTcpSocket*> clients;

    QLineEdit* portEdit;
    QPushButton* startBtn;
    QLabel* statusLabel;
    QTextEdit* logBox;

    bool serverRunning = false;
};

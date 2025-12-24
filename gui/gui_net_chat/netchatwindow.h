#pragma once
#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>        // ← IMPORTANT (هذا هو الذي كان ناقص)
#include <QString>

#include "../common/protocol.h"

class NetChatWindow : public QWidget {
    Q_OBJECT

public:
    explicit NetChatWindow(QWidget* parent = nullptr);

private slots:
    void onConnectClicked();
    void onSendClicked();
    void onReadyRead();
    void onDisconnected();

private:
    void appendLine(const QString& line);
    void sendJoin();

    QTcpSocket* socket;
    bool connected = false;

    QLineEdit* nameEdit;
    QLineEdit* hostEdit;
    QLineEdit* portEdit;

    QPushButton* connectBtn;
    QPushButton* sendBtn;

    QLabel* statusLabel;     // ← الآن QLabel معروف

    QTextEdit* chatBox;
    QLineEdit* inputEdit;

    QString username;
    QByteArray recvBuffer;
};

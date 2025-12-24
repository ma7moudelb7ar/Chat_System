#include "startwindow.h"
#include "chatwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

StartWindow::StartWindow(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Chat System Launcher");
    resize(600, 320);

    // ===== Background =====
    setStyleSheet("background:#0f0f0f; color:white;");

    // ===== Title =====
    auto* title = new QLabel(
        "Shared Memory System By Team elb7ar",
        this
    );
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "margin-bottom:30px;"
    );

    // ===== Username =====
    nameEdit = new QLineEdit(this);
    nameEdit->setText("elb7ar");   // default
    nameEdit->setPlaceholderText("Enter your name");
    nameEdit->setStyleSheet(
        "background:#1e1e1e;"
        "color:white;"
        "padding:10px;"
        "border-radius:8px;"
        "font-size:14px;"
    );

    // ===== Client ID =====
    idEdit = new QLineEdit(this);
    idEdit->setPlaceholderText("Client ID (0 - 9)");
    idEdit->setStyleSheet(
        "background:#1e1e1e;"
        "color:white;"
        "padding:10px;"
        "border-radius:8px;"
        "font-size:14px;"
    );

    // ===== Start Button =====
    startBtn = new QPushButton("Start Chat", this);
    startBtn->setFixedHeight(55);
    startBtn->setStyleSheet(
        "QPushButton{"
        "background:#2e7d32;"
        "color:white;"
        "font-size:18px;"
        "border-radius:10px;"
        "}"
        "QPushButton:hover{"
        "background:#388e3c;"
        "}"
    );

    // ===== Layout =====
    auto* layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(nameEdit);
    layout->addWidget(idEdit);
    layout->addWidget(startBtn);
    layout->addStretch();

    connect(startBtn, &QPushButton::clicked,
        this, &StartWindow::onStart);
}

void StartWindow::onStart()
{
    QString name = nameEdit->text().trimmed();
    int id = idEdit->text().toInt();

    if (name.isEmpty())
        return;

    if (id < 0 || id > 9)
        return;

    ChatWindow* chat = new ChatWindow(id, name);
    chat->show();
    close();
}

#include "mainmenuwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MainMenuWindow::MainMenuWindow(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Chat System Launcher");
    resize(400, 250);

    // ----------- Title -----------
    auto* title = new QLabel("Network Chat System By Team eLb7ar");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 15px;");

    // ----------- Buttons -----------
    QPushButton* serverBtn = new QPushButton("Start Server");
    QPushButton* clientBtn = new QPushButton("Start Client");

    serverBtn->setFixedHeight(40);
    clientBtn->setFixedHeight(40);

    // Hand cursor for better UX
    serverBtn->setCursor(Qt::PointingHandCursor);
    clientBtn->setCursor(Qt::PointingHandCursor);

    // Button styles
    serverBtn->setStyleSheet(
        "background:#2e7d32; color:white; border-radius:10px; font-weight:bold;"
    );
    clientBtn->setStyleSheet(
        "background:#0277bd; color:white; border-radius:10px; font-weight:bold;"
    );

    // ----------- Layout -----------
    auto* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addSpacing(10);
    layout->addWidget(serverBtn);
    layout->addWidget(clientBtn);

    setLayout(layout);

    // ----------- Connect Buttons -----------
    connect(serverBtn, &QPushButton::clicked, this, &MainMenuWindow::openServer);
    connect(clientBtn, &QPushButton::clicked, this, &MainMenuWindow::openClient);

    // ----------- Background + hover style -----------
    setStyleSheet(
        "QWidget { background:#121212; color:#f0f0f0; }"
        "QPushButton:hover { background-color: #2bbbad; }"
    );
}

#include <QApplication>
#include "mainmenuwindow.h"
#include "serverwindow.h"
#include "netchatwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Main menu window
    MainMenuWindow menu;
    menu.show();

    // Single server instance
    ServerWindow* server = new ServerWindow();

    // --- Connections ---
    QObject::connect(&menu, &MainMenuWindow::openServer, [&]() {
        server->show();
        });

    QObject::connect(&menu, &MainMenuWindow::openClient, [&]() {
        // Create a new client window for every press
        NetChatWindow* client = new NetChatWindow();
        client->show();
        });

    return app.exec();
}

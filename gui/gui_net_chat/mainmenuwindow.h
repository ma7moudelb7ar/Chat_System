#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MainMenuWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainMenuWindow(QWidget* parent = nullptr);

signals:
    void openServer();
    void openClient();
};

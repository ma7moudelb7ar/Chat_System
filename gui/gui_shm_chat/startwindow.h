#pragma once
#include <QWidget>

class QPushButton;
class QLineEdit;

class StartWindow : public QWidget {
    Q_OBJECT
public:
    explicit StartWindow(QWidget* parent = nullptr);

private slots:
    void onStart();

private:
    QLineEdit* nameEdit;
    QLineEdit* idEdit;
    QPushButton* startBtn;
};

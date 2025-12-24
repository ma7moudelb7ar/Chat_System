#include <QApplication>
#include "startwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StartWindow w;
    w.show();
    return app.exec();
}

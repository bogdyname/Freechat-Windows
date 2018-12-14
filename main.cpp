#include "mainwindow.h"
#include <QApplication>

using namespace Qt;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}

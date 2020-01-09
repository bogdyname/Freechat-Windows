#include "Bin/freechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ui
    Freechat window;
    window.show();

    return a.exec();
}

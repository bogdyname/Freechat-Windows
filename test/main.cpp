#include "Bin/freechat.h"
#include "Network/connectionf2f.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // network
    ConnectionF2F networkTest;
    networkTest.NetworkInfo();

    // ui
    Freechat window;
    window.show();

    return a.exec();
}

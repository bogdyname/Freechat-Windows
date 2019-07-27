#include "peerout.h"
#include "freechat.h"
#include "connectionf2f.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Freechat w;
    w.show();

    ConnectionF2F testOnIP; //do not show WAN IP

    Peerout testOnConnecting;
    testOnConnecting.DoConnect();

    return a.exec();
}

#include "peerout.h"
#include "freechat.h"
#include "connectionf2f.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Freechat w;
    w.show();



    return a.exec();
}

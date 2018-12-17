#include "mainwindow.h"
#include <QApplication>
#include <QWidget>

using namespace Qt;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget wgt;
    QPixmap pix("D:/Freechat/Freechat/Freechat/unnamed.png");
    QCursor cur(pix);

    wgt.setCursor(cur);
    wgt.resize(750, 550);
    wgt.show();

    return app.exec();
}

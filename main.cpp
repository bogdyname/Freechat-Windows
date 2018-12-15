#include "mainwindow.h"
#include <QApplication>
#include <QWidget>

using namespace Qt;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget wgt;
        QPixmap pix("/freechat.jpg");
        QCursor cur(pix);

        wgt.setCursor(cur);
        wgt.resize(25, 25);
        wgt.show();

    return app.exec();
}

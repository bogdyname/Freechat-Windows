#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QFont>
#include <QPushButton>
#include "imageviewer.h"

using namespace Qt;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget Freechat;
    QPixmap pix("D:/Freechat/Freechat/Freechat/unnamed.png");
    QCursor cur(pix);

    QPushButton quit("Quit", &Freechat);
    quit.setFont(QFont("Segoe Print", 14, QFont::Bold));
    quit.setGeometry(660, 510, 90, 40);
    QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));

    //ImageViewer imageViewer;
    //imageViewer.show();

    Freechat.setCursor(cur);
    Freechat.resize(750, 550);
    Freechat.show();

    return app.exec();
}

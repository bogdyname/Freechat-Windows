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
    quit.setGeometry(700, 525, 50, 25);
    QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));

    QPushButton call("Call request", &Freechat);
    call.setFont(QFont("Segoe Print", 14, QFont::Bold));
    call.setGeometry(620, 0, 130, 25);
    QObject::connect(&call, SIGNAL(clicked()), &app, SLOT(call));

    //ImageViewer imageViewer;
    //imageViewer.show();

    Freechat.setCursor(cur);
    Freechat.resize(750, 550);
    Freechat.show();

    return app.exec();
}

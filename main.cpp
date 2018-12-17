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
    quit.setFont(QFont("Segoe Print", 12, QFont::Bold));
    quit.setGeometry(700, 525, 50, 25);
    QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));

    QPushButton call("Call request", &Freechat);
    call.setFont(QFont("Segoe Print", 12, QFont::Bold));
    call.setGeometry(640, 0, 110, 30);
    QObject::connect(&call, SIGNAL(clicked()), &app, SLOT(call));

    QPushButton friendList("Show friend list", &Freechat);
    friendList.setFont(QFont("Segoe Print", 12, QFont::Bold));
    friendList.setGeometry(0, 0, 140, 35);
    QObject::connect(&friendList, SIGNAL(clicked()), &app, SLOT(call));

    //ImageViewer imageViewer;
    //imageViewer.show();

    Freechat.setCursor(cur);
    Freechat.resize(750, 550);
    Freechat.show();

    return app.exec();
}

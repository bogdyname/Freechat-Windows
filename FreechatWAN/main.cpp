/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow Freechat;
    Freechat.setWindowTitle("TTS Version for WAN");
    Freechat.show();



    return a.exec();
}
/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "freechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Freechat w;
    w.show();

    return app.exec();
}

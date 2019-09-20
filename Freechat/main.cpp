/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"
#include "Data/datasave.h"
#include <QtGui>
#include <QApplication>
#include <QtCore/QSettings>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QNetworkConfigurationManager>

using namespace Qt;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QNetworkConfigurationManager manager;

    Freechat freechat;
    freechat.show();
    return app.exec();
}

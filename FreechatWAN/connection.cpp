/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "connection.h"

Connection::Connection(QObject *parent)

{
    QSctpSocket(QObject *parent = nullptr);
    QSctpSocket *socket = new QSctpSocket(this);

    socket->setMaxChannelCount(1);
    socket->connectionToHost(QHostAddress::LocalHost, 4433);

    if(socket->waitForConnection(1000))
    {
        int inputChannels = socket->readChannelCout();
        int outputChannels = socket->writeChannelCout();
    }
}

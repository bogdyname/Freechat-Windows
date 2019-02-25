/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QHostAddress>
#include <QTcpSocket>
#include <QSctpSocket>

class Connection : public QSctpSocket
{
    Q_OBJECT

public:
    enum ConnectionData
    {
        WaintinForConnection,
        WritingForConnection,
        ReadyForConnection
    };

    enum MetaData
    {
        Ping,
        AlreadyConnection,
        NameOfUser,
    };

    QSctpSocket *socket = new QSctpSocket(this);

    socket->setMaxChannelCount(1);
    socket->connectionToHost(QHostAddress::LocalHost, 4433);

    if(socket->waitForConnection(1000))
    {
        int inputChannels = socket->readChannelCout();
        int outputChannels = socket->writeChannelCout();
    }
}


#endif // CONNECTION_H

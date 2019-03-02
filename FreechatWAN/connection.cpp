/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "connection.h"

Connection::Connection(QObject *parent)
    : QTcpSocket(parent), writer(this)
{
    username = tr("unknown");
    state = WaintinForConnection;
    currentDataType = Undefined;
    transferTimerId = -1;
    isCheckConnection = false;
    pingTimer.setInterval(PingInterval);


    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::connect(this, SIGNAL(disconnected()), &pingTimer, SLOT(stop()));
    QObject::connect(&pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
    QObject::connect(this, SIGNAL(connected()),this, SLOT(sendGreetingMessage()));
}

Connection::Connection(qintptr socketDescriptor, QObject *parent)
    : Connection(parent)
{
    setSocketDescriptor(socketDescriptor);
    reader.setDevice(this);
}

QString Connection::name() const
{
    return username;
}

bool Connection::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return false;

    writer.startMap(1);
    writer.append(PlainText);
    writer.append(message);
    writer.endMap();
    return true;
}

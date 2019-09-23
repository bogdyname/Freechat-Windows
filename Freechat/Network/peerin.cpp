/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"

Peerin::Peerin(QObject *parent)
    : QTcpServer(parent)
{
    CheckPortForConnection();

}

void Peerin::CheckPortForConnection()
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

        if(listen(QHostAddress::Any, 1234))
        {
           #ifndef Q_DEBUG
           qDebug() << "Server: started";
           #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Server: not started: " << errorString();
            #endif
        }

    return;
}

void Peerin::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnecting()));

    return;
}

void Peerin::ReadData()
{

    return;
}

void Peerin::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();

    QByteArray outBuf;
    QDataStream outStream(&outBuf, QIODevice::WriteOnly);
    outStream.setVersion(QDataStream::Qt_4_6);
    outStream<<QString(ConnectionF2F::globalNetworkBuffer);
    socket->write(outBuf);
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();

    ConnectionF2F::globalNetworkBuffer.clear();
}

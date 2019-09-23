/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerout.h"

Peerout::Peerout()
{
    socket = new QTcpSocket(this);

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

Peerout::~Peerout()
{
    if(socket != nullptr)
    {
        delete socket;
    }
    else
    {
        /*clear code*/
    }
}

void Peerout::WriteIpAddressFromPeer()
{
    ip += ConnectionF2F::globalNetworkBuffer;
    ConnectionF2F::globalNetworkBuffer.clear();

    return;
}

void Peerout::DoConnect()
{
    socket->connectToHost(ip, 1234);

        if(socket->waitForConnected(3000))
        {
            #ifndef Q_DEBUG
            qDebug() << "Connecting,..";
            #endif

            Connected();

            QByteArray outBuf;
            QDataStream outStream(&outBuf, QIODevice::WriteOnly);
            outStream.setVersion(QDataStream::Qt_4_6);
            outStream<<QString(ConnectionF2F::globalNetworkBuffer);
            socket->write(outBuf);
            socket->waitForBytesWritten(1000);
            socket->waitForReadyRead(3000);

            ReadyRead();

            socket->close();
            socket->flush();
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Not connected!";
            qDebug() << "Error: " << socket->errorString();
            #endif
        }

        return;
}

void Peerout::Connected()
{
    #ifndef Q_DEBUG
    qDebug() << "Connected!";
    #endif

    return;
}

void Peerout::Disconnected()
{
    #ifndef Q_DEBUG
    qDebug() << "Disconnected!";
    #endif

    return;
}

void Peerout::ReadyRead()
{
    #ifndef Q_DEBUG
    qDebug() << "reading...";
    qDebug() << "Reading: " << socket->bytesAvailable();
    qDebug() << socket->readAll();
    #endif

    return;
}

/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerout.h"
#include "Bin/freechat.h"

Peerout::Peerout()
    : nextBlockSize(0)
{
    socket = new QTcpSocket(this);

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    connect(socket, SIGNAL(connected()), this, SLOT(SlotConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(SlotReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(SlotError(QAbstractSocket::SocketError)));
}

Peerout::~Peerout()
{
    delete socket;
}

void Peerout::SlotReadyRead()
{
    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_4_2);
    QTime time = QTime::currentTime();
    QString buffer;

    #ifndef Q_DEBUG
    qDebug() << "Read data from server";
    #endif

    forever
    {
        if(nextBlockSize == 0)
        {
            if(socket->bytesAvailable() < sizeof(932838457459459))
                break;

            stream >> nextBlockSize;
        }

        if(socket->bytesAvailable() < nextBlockSize)
            break;

        stream >> buffer;

        #ifndef Q_DEBUG
        qDebug() << "Data from server: " << buffer;
        #endif

        if(!buffer.isEmpty())
        {
            Freechat::viewField->setAlignment(Qt::AlignRight);
            Freechat::viewField->insertPlainText(time.toString() + "\n" + buffer + " :Peer\n");
        }

        nextBlockSize = 0;
    }

    return;
}

void Peerout::SlotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found.\n" :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed.\n" :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused.\n" :
                         QString(socket->errorString()));

    // show error in view field
    Freechat::viewField->setAlignment(Qt::AlignCenter);
    Freechat::viewField->insertPlainText(strError);

    return;
}

void Peerout::SlotSendToServer()
{
    #ifndef Q_DEBUG
    qDebug() << "Sending data to server from peerout.cpp: " << Freechat::bufferOfMessages;
    #endif

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.setVersion(QDataStream::Qt_4_2);
    sendStream << qint64(0) << Freechat::bufferOfMessages;

    sendStream.device()->seek(0);
    sendStream << (qint64)(block.size() - sizeof(932838457459459));
    socket->write(block);
    socket->flush();

    Freechat::bufferOfMessages.clear();

    return;
}

void Peerout::SlotLanConnecting()
{
    #ifndef Q_DEBUG
    qDebug() << "Connecting to " << Freechat::lanIpOfPeer;
    #endif

    QHostAddress hostAddress(Freechat::lanIpOfPeer);
    socket->connectToHost(hostAddress, 6000);

    if(socket->waitForConnected(2000))
    {
        #ifndef Q_DEBUG
        qDebug() << "Connected.";
        #endif
    }
    else
    {
        #ifndef Q_DEBUG
        qDebug() << "Error connection.";
        #endif
    }

    Freechat::lanIpOfPeer.clear();

    return;
}

void Peerout::SlotWanConnecting()
{
    /*
    Need to make Wan connection
    */

    return;
}

void Peerout::SlotConnected()
{
    Freechat::viewField->insertPlainText("Connected to peerin\n");

    #ifndef Q_DEBUG
    qDebug() << "Connected.";
    #endif

    return;
}

/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"
#include "Bin/freechat.h"

Peerin::Peerin(QObject *parent)
    : QTcpServer(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));

    if (server->listen(QHostAddress::Any, 6000))
    {
        #ifndef Q_DEBUG
        qDebug() << "Server started!";
        #endif

    }
    else
    {
        #ifndef Q_DEBUG
        qDebug() << "Server not started: " << errorString();
        #endif

        server->close();
    }
}

Peerin::~Peerin()
{
    delete server;
}

void Peerin::clearValue()
{
    #ifndef Q_DEBUG
    qDebug() << "Value was cleared!";
    #endif

    Freechat::value = 0;

    return;
}

void Peerin::SlotNewConnection()
{
    server->setMaxPendingConnections(1);
    socket = server->nextPendingConnection();
    Freechat::value = 1;
    Freechat::viewField->insertPlainText("Peerout connected\n");

    connect(socket, SIGNAL(disconnected()), this, SLOT(clearValue()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(SlotReadClient()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    #ifndef Q_DEBUG
    qDebug() << "Value already: " << Freechat::value;
    #endif

    return;
}

void Peerin::SlotReadClient()
{
    socket = (QTcpSocket*)sender();
    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_4_2);
    QTime time = QTime::currentTime();
    QString buffer;
    nextBlockSize = 0;

    #ifndef Q_DEBUG
    qDebug() << "Read data from client";
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
        qDebug() << "Data from client: " << buffer;
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

void Peerin::SendResponseToClient()
{
    #ifndef Q_DEBUG
    qDebug() << "Sending data to client from peerin.cpp: " << Freechat::bufferOfMessages;
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

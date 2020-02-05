/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"

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
    QTcpSocket* сlientSocket = (QTcpSocket*)sender();
    QDataStream in(сlientSocket);
    in.setVersion(QDataStream::Qt_4_2);

    #ifndef Q_DEBUG
    qDebug() << "Read data from client";
    #endif

    for(;;)
    {
        if(!nextBlockSize)
        {
            if(сlientSocket->bytesAvailable() < sizeof (quint16))
            {
                break;
            }
            in >> nextBlockSize;
        }

        if(сlientSocket->bytesAvailable() < nextBlockSize)
        {
            break;
        }

        QTime time;
        QString str;
        in >> time >> str;

        #ifndef Q_DEBUG
        qDebug() << "Data from server: " << str;
        #endif

        QString message = time.toString() + ": " + str + "\n";
        Freechat::viewField->append(message);
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
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << Freechat::bufferOfMessages;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof (quint16));
    socket->write(block);

    Freechat::bufferOfMessages.clear();

    return;
}

void Peerin::SendToClientFlush()
{
    SendResponseToClient();
    Freechat::bufferOfMessages.clear();

    return;
}

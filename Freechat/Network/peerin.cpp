/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"
#include "Bin/freechat.h"

Peerin::Peerin(QObject *parent)
    : QTcpServer(parent)
{
    try
    {
        Peerin::server = new QTcpServer(this);
    }
    catch(std::bad_alloc &exp)
    {
        #ifndef Q_DEBUG
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qCritical() << "Some exception caught";
        #endif
        abort();
    }

    QObject::connect(Peerin::server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));

    if (Peerin::server->QTcpServer::listen(QHostAddress::Any, 6000))
    {
        #ifndef Q_DEBUG
        qDebug() << "Server started!";
        #endif

    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "Server not started: " << QTcpServer::errorString();
        #endif

        Peerin::server->QTcpServer::close();
    }

    Peerin::server->setMaxPendingConnections(1);

    return;
}

Peerin::~Peerin()
{
    delete Peerin::server;
}

void Peerin::DisconnectPeer()
{
    Peerin::socket->QAbstractSocket::abort();

    const QColor color(255, 153, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText("Peerout disconnected\n");

    return;
}

void Peerin::SendMessages()
{
    Peerin::SendResponseToClient(Freechat::bufferOfMessages);

    #ifndef Q_DEBUG
    qDebug() << "Sending data!";
    #endif

    return;
}

void Peerin::SlotNewConnection()
{
    Peerin::socket = Peerin::server->QTcpServer::nextPendingConnection();
    Freechat::value = 1;

    const QColor color(255, 153, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText("Peerout connected\n");

    QObject::connect(Peerin::socket, SIGNAL(disconnected()), this, SLOT(clearValue()));
    QObject::connect(Peerin::socket, SIGNAL(readyRead()), this, SLOT(SlotReadClient()));
    QObject::connect(Peerin::socket, SIGNAL(disconnected()), Peerin::socket, SLOT(deleteLater()));

    #ifndef Q_DEBUG
    qDebug() << "Value already: " << Freechat::value;
    #endif

    return;
}

void Peerin::SendResponseToClient(QString &message)
{
    #ifndef Q_DEBUG
    qDebug() << "Sending data to client from peerin.cpp: " << message;
    #endif

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.QDataStream::setVersion(QDataStream::Qt_4_2);
    sendStream << qint64(0) << message;

    sendStream.QDataStream::device()->QIODevice::seek(0);
    sendStream << (qint64)(block.size() - sizeof(932838457459459));
    Peerin::socket->QIODevice::write(block);
    Peerin::socket->QAbstractSocket::flush();

    message.QString::clear();

    return;
}

void Peerin::SlotReadClient()
{
    Peerin::socket = (QTcpSocket*)sender();
    QDataStream stream(Peerin::socket);
    stream.QDataStream::setVersion(QDataStream::Qt_4_2);
    const QTime time = QTime::currentTime();
    const QColor color(0, 255, 255); //234, 0, 217
    QString buffer;
    nextBlockSize = 0;

    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignRight);

    #ifndef Q_DEBUG
    qDebug() << "Read data from client";
    #endif

    forever
    {
        if(nextBlockSize == 0)
        {
            if(Peerin::socket->bytesAvailable() < sizeof(932838457459459))
                break;

            stream >> nextBlockSize;
        }

        if(Peerin::socket->bytesAvailable() < nextBlockSize)
            break;

        stream >> buffer;

        #ifndef Q_DEBUG
        qDebug() << "Data from client: " << buffer;
        #endif

        if(!buffer.isEmpty())
            Freechat::viewField->QTextEdit::insertPlainText(time.toString() + "\n" + "Peer:\n" + buffer + "\n");

        nextBlockSize = 0;
    }

    return;
}

void Peerin::clearValue()
{
    #ifndef Q_DEBUG
    qDebug() << "Value was cleared!";
    #endif

    Freechat::value = 0;

    return;
}

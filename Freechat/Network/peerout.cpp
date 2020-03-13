/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerout.h"
#include "Bin/freechat.h"

Peerout::Peerout()
    : nextBlockSize(0)
{
    try
    {
        Peerout::socket = new QTcpSocket(this);
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

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    QObject::connect(Peerout::socket, SIGNAL(connected()), this, SLOT(SlotConnected()));
    QObject::connect(Peerout::socket, SIGNAL(readyRead()), this, SLOT(SlotReadyRead()));
    QObject::connect(Peerout::socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(SlotError(QAbstractSocket::SocketError)));
}

Peerout::~Peerout()
{
    delete Peerout::socket;
}

void Peerout::SlotReadyRead()
{
    QDataStream stream(Peerout::socket);
    stream.QDataStream::setVersion(QDataStream::Qt_4_2);
    QTime time = QTime::currentTime();
    QColor color(0, 255, 255);
    QString buffer;

    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignRight);

    #ifndef Q_DEBUG
    qDebug() << "Read data from server";
    #endif

    forever
    {
        if(nextBlockSize == 0)
        {
            if(Peerout::socket->bytesAvailable() < sizeof(932838457459459))
                break;

            stream >> nextBlockSize;
        }

        if(Peerout::socket->bytesAvailable() < nextBlockSize)
            break;

        stream >> buffer;

        #ifndef Q_DEBUG
        qDebug() << "Data from server: " << buffer;
        #endif

        if(!buffer.isEmpty())
            Freechat::viewField->QTextEdit::insertPlainText(time.QTime::toString() + "\n" + "Peer:\n" + buffer + "\n");

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
                         QString(socket->QIODevice::errorString() + "\n"));

    // show error in view field
    QColor color(156, 0, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText(strError);

    return;
}

void Peerout::SlotSendToServer()
{
    #ifndef Q_DEBUG
    qDebug() << "Sending data to server from peerout.cpp: " << Freechat::bufferOfMessages;
    #endif

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.QDataStream::setVersion(QDataStream::Qt_4_2);
    sendStream << qint64(0) << Freechat::bufferOfMessages;

    sendStream.QDataStream::device()->QIODevice::seek(0);
    sendStream << (qint64)(block.size() - sizeof(932838457459459));
    Peerout::socket->QIODevice::write(block);
    Peerout::socket->QAbstractSocket::flush();

    Freechat::bufferOfMessages.QString::clear();

    return;
}

void Peerout::SlotLanConnecting()
{
    #ifndef Q_DEBUG
    qDebug() << "Connecting to " << Freechat::lanIpOfPeer;
    #endif

    QHostAddress hostAddress(Freechat::lanIpOfPeer);
    Peerout::socket->QAbstractSocket::connectToHost(hostAddress, 6000);

    if(Peerout::socket->QAbstractSocket::waitForConnected(2000))
    {
        #ifndef Q_DEBUG
        qDebug() << "Connected.";
        #endif
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "Error connection.";
        #endif

        // show error in view field
        QColor color(156, 0, 0);
        Freechat::viewField->QTextEdit::setTextColor(color);
        Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
        Freechat::viewField->QTextEdit::insertPlainText("Error: can not connecting to peer, check IP.\n");
    }

    Freechat::lanIpOfPeer.QString::clear();

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
    QColor color(255, 153, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText("Connected to peerin\n");

    #ifndef Q_DEBUG
    qDebug() << "Connected.";
    #endif

    return;
}

void Peerout::SlotDisconnectPeer()
{
    Peerout::socket->QAbstractSocket::disconnectFromHost();

    QColor color(255, 153, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText("Disconnected from peerin\n");

    return;
}

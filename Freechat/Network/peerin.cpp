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

    Peerin::server->QTcpServer::setMaxPendingConnections(1);

    const quint64 keyin = Q_UINT64_C(0x0c3ad5a4acb1f021);
    const quint64 keyout = Q_UINT64_C(0x0c2ad2a2acb1f012);
    Peerin::cryptomanagerOfPeerout.setKey(keyout);
    Peerin::cryptomanagerOfPeerin.setKey(keyin);;

    Peerin::cryptomanagerOfPeerin.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    Peerin::cryptomanagerOfPeerin.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);
    Peerin::cryptomanagerOfPeerout.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    Peerin::cryptomanagerOfPeerout.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

    return;
}

Peerin::~Peerin()
{
    delete Peerin::server;
}

void Peerin::DisconnectPeer()
{
    Peerin::socket->QTcpSocket::disconnectFromHost();
    Freechat::value = 2; //2 = default

    #ifndef Q_DEBUG
    qDebug() << "Value already: " << Freechat::value;
    #endif

    QTextCursor tc = Freechat::viewField->QTextEdit::textCursor();
    bool visualNavigation = tc.QTextCursor::visualNavigation();
    tc.QTextCursor::setVisualNavigation(true);
    tc.QTextCursor::movePosition(QTextCursor::End);
    tc.QTextCursor::setVisualNavigation(visualNavigation);

    if(Freechat::viewField->QTextEdit::textCursor() != tc)
        Freechat::viewField->QTextEdit::setTextCursor(tc);

    const QColor color(255, 153, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText("Peerout disconnected\n");

    return;
}

void Peerin::SendMessages()
{
    Peerin::SendResponseToClient(Freechat::bufferOfMessages);
    Freechat::bufferOfMessages.QString::clear();

    #ifndef Q_DEBUG
    qDebug() << "Sending data!";
    #endif

    return;
}

void Peerin::CloseOwnServerSlot()
{
    Peerin::server->QTcpServer::close();

    #ifndef Q_DEBUG
    qDebug() << "Server is close!";
    #endif

    return;
}

void Peerin::ResumeServerSlot()
{
    qDebug() << "1";

    Peerin::server->QTcpServer::listen(QHostAddress::Any, 6000);

    #ifndef Q_DEBUG
    qDebug() << "Server is resume!";
    #endif

    return;
}

void Peerin::SlotNewConnection()
{
    Peerin::socket = Peerin::server->QTcpServer::nextPendingConnection();
    Freechat::value = 1; //1 = server is action

    QTextCursor tc = Freechat::viewField->QTextEdit::textCursor();
    bool visualNavigation = tc.QTextCursor::visualNavigation();
    tc.QTextCursor::setVisualNavigation(true);
    tc.QTextCursor::movePosition(QTextCursor::End);
    tc.QTextCursor::setVisualNavigation(visualNavigation);

    if(Freechat::viewField->QTextEdit::textCursor() != tc)
        Freechat::viewField->QTextEdit::setTextCursor(tc);

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

void Peerin::SendResponseToClient(const QString &message)
{
    #ifndef Q_DEBUG
    qDebug() << "Sending data to client from peerin.cpp: " << message;
    #endif

    const QString cryptmessage = Peerin::cryptomanagerOfPeerin.Cryptography::encryptToString(message);
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.QDataStream::setVersion(QDataStream::Qt_4_2);
    sendStream << qint64(0) << cryptmessage;

    sendStream.QDataStream::device()->QIODevice::seek(0);
    sendStream << (qint64)(block.QByteArray::size() - sizeof(932838457459459));
    Peerin::socket->QIODevice::write(block);
    Peerin::socket->QAbstractSocket::flush();

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
    Peerin::nextBlockSize = 0;

    QTextCursor tc = Freechat::viewField->QTextEdit::textCursor();
    bool visualNavigation = tc.QTextCursor::visualNavigation();
    tc.QTextCursor::setVisualNavigation(true);
    tc.QTextCursor::movePosition(QTextCursor::End);
    tc.QTextCursor::setVisualNavigation(visualNavigation);

    if(Freechat::viewField->QTextEdit::textCursor() != tc)
        Freechat::viewField->QTextEdit::setTextCursor(tc);

    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignRight);

    #ifndef Q_DEBUG
    qDebug() << "Read data from client";
    #endif

    forever
    {
        if(Peerin::nextBlockSize == 0)
        {
            if(Peerin::socket->QAbstractSocket::bytesAvailable() < sizeof(932838457459459))
                break;

            stream >> Peerin::nextBlockSize;
        }

        if(Peerin::socket->QAbstractSocket::bytesAvailable() < Peerin::nextBlockSize)
            break;

        stream >> buffer;

        #ifndef Q_DEBUG
        qDebug() << "Data from client: " << buffer;
        #endif

        const QString dechyphermessage = Peerin::cryptomanagerOfPeerout.Cryptography::decryptToString(buffer);

        if (!(Peerin::cryptomanagerOfPeerout.Cryptography::lastError() == Cryptography::ErrorNoError))
        {
            #ifndef Q_DEBUG
            qCritical() << "error decrypt message from peerout";
            #endif

            return;
        }

        if(!dechyphermessage.QString::isEmpty())
            Freechat::viewField->QTextEdit::insertPlainText(time.QTime::toString() + "\n" + "Peer:\n" + dechyphermessage + "\n");

        Peerin::nextBlockSize = 0;
    }

    return;
}

void Peerin::clearValue()
{
    #ifndef Q_DEBUG
    qDebug() << "Value was cleared!";
    #endif

    Freechat::value = 2; //2 = default

    return;
}

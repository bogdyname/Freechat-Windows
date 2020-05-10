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

    const quint64 keyin = Q_UINT64_C(0x0c3ad5a4acb1f021);
    const quint64 keyout = Q_UINT64_C(0x0c2ad2a2acb1f012);
    Peerout::cryptomanagerOfPeerout.setKey(keyout);
    Peerout::cryptomanagerOfPeerin.setKey(keyin);;

    Peerout::cryptomanagerOfPeerin.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    Peerout::cryptomanagerOfPeerin.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);
    Peerout::cryptomanagerOfPeerout.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    Peerout::cryptomanagerOfPeerout.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);
}

Peerout::~Peerout()
{
    delete Peerout::socket;
}

void Peerout::SlotSendToServer()
{
    Peerout::SendToServer(Freechat::bufferOfMessages);
    Freechat::bufferOfMessages.QString::clear();

    #ifndef Q_DEBUG
    qDebug() << "Send data to server: " << Freechat::bufferOfMessages;
    #endif

    return;
}

void Peerout::SlotReadyRead()
{
    QDataStream stream(Peerout::socket);
    stream.QDataStream::setVersion(QDataStream::Qt_4_2);
    const QTime time = QTime::currentTime();
    const QColor color(0, 255, 255);
    QString buffer;
    Peerout::nextBlockSize = 0;

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
    qDebug() << "Read data from server";
    #endif

    forever
    {
        if(Peerout::nextBlockSize == 0)
        {
            if(Peerout::socket->QAbstractSocket::bytesAvailable() < sizeof(932838457459459))
                break;

            stream >> Peerout::nextBlockSize;
        }

        if(Peerout::socket->QAbstractSocket::bytesAvailable() < Peerout::nextBlockSize)
            break;

        stream >> buffer;

        #ifndef Q_DEBUG
        qDebug() << "Data from server: " << buffer;
        #endif

        const QString dechyphermessage = Peerout::cryptomanagerOfPeerin.Cryptography::decryptToString(buffer);

        if (!(Peerout::cryptomanagerOfPeerin.Cryptography::lastError() == Cryptography::ErrorNoError))
        {
            #ifndef Q_DEBUG
            qCritical() << "error decrypt message from peerin";
            #endif

            return;
        }

        if(!dechyphermessage.QString::isEmpty())
            Freechat::viewField->QTextEdit::insertPlainText(time.QTime::toString() + "\n" + "Peer:\n" + dechyphermessage + "\n");

        Peerout::nextBlockSize = 0;
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
    QTextCursor tc = Freechat::viewField->QTextEdit::textCursor();
    bool visualNavigation = tc.QTextCursor::visualNavigation();
    tc.QTextCursor::setVisualNavigation(true);
    tc.QTextCursor::movePosition(QTextCursor::End);
    tc.QTextCursor::setVisualNavigation(visualNavigation);

    if(Freechat::viewField->QTextEdit::textCursor() != tc)
        Freechat::viewField->QTextEdit::setTextCursor(tc);

    const QColor color(156, 0, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText(strError);

    return;
}

void Peerout::SendToServer(const QString &message)
{
    #ifndef Q_DEBUG
    qDebug() << "Sending data to server from peerout.cpp: " << message;
    #endif

    const QString cryptmessage = Peerout::cryptomanagerOfPeerout.Cryptography::encryptToString(Freechat::bufferOfMessages);
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.QDataStream::setVersion(QDataStream::Qt_4_2);
    sendStream << qint64(0) << cryptmessage;

    sendStream.QDataStream::device()->QIODevice::seek(0);
    sendStream << (qint64)(block.QByteArray::size() - sizeof(932838457459459));
    Peerout::socket->QIODevice::write(block);
    Peerout::socket->QAbstractSocket::flush();

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

        Freechat::value = 0;
        emit Peerout::CloseOwnServerSignal();

        #ifndef Q_DEBUG
        qDebug() << "Value already: " << Freechat::value;
        #endif
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "Error connection.";
        #endif

        // show error in view field
        QTextCursor tc = Freechat::viewField->QTextEdit::textCursor();
        bool visualNavigation = tc.QTextCursor::visualNavigation();
        tc.QTextCursor::setVisualNavigation(true);
        tc.QTextCursor::movePosition(QTextCursor::End);
        tc.QTextCursor::setVisualNavigation(visualNavigation);

        if(Freechat::viewField->QTextEdit::textCursor() != tc)
            Freechat::viewField->QTextEdit::setTextCursor(tc);

        QColor color(156, 0, 0);
        Freechat::viewField->QTextEdit::setTextColor(color);
        Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
        Freechat::viewField->QTextEdit::insertPlainText("Error: can not connecting to peer, check IP.\n");
    }

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
    Freechat::viewField->QTextEdit::insertPlainText("Connected to peerin\n");

    Freechat::value = 0;

    #ifndef Q_DEBUG
    qDebug() << "Value already: " << Freechat::value;
    #endif

    #ifndef Q_DEBUG
    qDebug() << "Connected.";
    #endif

    return;
}

void Peerout::SlotDisconnectPeer()
{
    Peerout::socket->QTcpSocket::abort();
    Freechat::value = 3;
    emit Peerout::ResumeServerSignal();

    #ifndef Q_DEBUG
    qDebug() << "Value was cleared!";
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
    Freechat::viewField->QTextEdit::insertPlainText("Disconnected from peerin\n");

    return;
}

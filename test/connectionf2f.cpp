/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"
#include "connectionf2f.h"

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{
    socket = new QTcpSocket(this);

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    connect(socket, SIGNAL(Connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(DoConnect()), this, SLOT(DoConnect()));
    connect(socket, SIGNAL(ReadyRead()), this, SLOT(ReadyRead()));
    connect(socket, SIGNAL(BytesWrittenOfData(qint64)), this, SLOT(BytesWrittenOfData(qint64)));
}

ConnectionF2F::~ConnectionF2F()
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

void ConnectionF2F::WriteIpAddressFromPeer()
{

    auto list = QHostInfo::fromName(QHostInfo::localHostName()).addresses();

    #ifndef Q_DEBUG
    qDebug() << "Addresses: " << list << endl;
    #endif

    return;
}

void ConnectionF2F::DoConnect()
{
    ipAddress = QHostAddress("92.243.182.174").toIPv4Address();

    socket->connectToHost("192.168.1.28", 80);

        if(socket->waitForConnected(3000))
        {
            Connected();

            socket->write("DATA OF TEXT");
            socket->waitForBytesWritten(1000);
            socket->waitForReadyRead(3000);
            #ifndef Q_DEBUG
            qDebug() << "Reading: " << socket->bytesAvailable();
            qDebug() << socket->readAll();
            #endif

            socket->close();
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Not connected!";
            #endif
        }

        return;
}

void ConnectionF2F::BytesWrittenOfData(qint64 bytes)
{
    #ifndef Q_DEBUG
    qDebug() << bytes << " bytes written...";
    #endif

    return;
}

void ConnectionF2F::Connected()
{
    #ifndef Q_DEBUG
    qDebug() << "Connected!";
    #endif

    return;
}

void ConnectionF2F::Disconnected()
{
    #ifndef Q_DEBUG
    qDebug() << "Disconnected!";
    #endif

    return;
}

void ConnectionF2F::ReadyRead()
{
    #ifndef Q_DEBUG
    qDebug() << "reading...";
    qDebug() << socket->readAll();
    #endif

    return;
}

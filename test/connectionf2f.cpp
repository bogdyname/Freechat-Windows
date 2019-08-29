/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

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
    /*
       If I write DNS or default gateway
       It is work, but another IP addresses not at all
    */
    ipAddress = QHostAddress("92.243.182.174").toIPv4Address();

    socket->connectToHost(ipAddress, 80);

        if(socket->waitForConnected(3000))
        {
            #ifndef Q_DEBUG
            qDebug() << "Connected!";
            #endif

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

    return;
}

void ConnectionF2F::Disconnected()
{

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

void ConnectionF2F::TaskResult(unsigned int &Number)
{
    Number = 0;

    return;
}




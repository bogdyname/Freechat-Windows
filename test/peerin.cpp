/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"

Peerin::Peerin(QObject *parent)
    : QTcpServer(parent)
{
    socketserv = new QTcpServer(this);
    connect(socketserv,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(listen(QHostAddress::Any, 1234))
        {
            #ifndef Q_DEBUG
            qDebug() << "Server: started";
            #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Server: not started!";
            #endif
        }
}

void Peerin::Connection()
{
    QTcpSocket *socket = socketserv->nextPendingConnection();
    socket->write("hello client\r\n");
    socket->flush(); // check this out

    socket->waitForBytesWritten(3000);
    socket->close();

    return;
}

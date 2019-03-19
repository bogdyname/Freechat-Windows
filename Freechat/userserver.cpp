/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include <QtNetwork>
#include <QHostAddress>
#include "userserver.h"
#include "connection.h"

Server::Userserver(QObject *parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void Server::InComingConnection(qintptr socketDescription)
{
    Connection *connection = new Connection(socketDescription, this);
    emit NewConnection(connection);
}

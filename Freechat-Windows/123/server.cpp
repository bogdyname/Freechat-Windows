/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/
#include <QtNetwork>
#include "server.h"
#include "connection.h"

Server::Server(QObject *parent):QSctpServer(parent)
{
    listen(QHostAddress::Any);
}

void Server::InComingConnection(qintptr socketDescription)
{
    Connection *connection = new Connection(socketDescription, this);
    emit NewConnection(connection);
}

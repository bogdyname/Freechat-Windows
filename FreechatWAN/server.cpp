/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "server.h"
#include "connection.h"

server::server(QObject *parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
    /*
     * * DOCS QHostAddress class
     * The dual stack any-address.
     * A socket bound with this address will listen on both IPv4 and IPv6 interfaces.
    */
}

void server::incomingConnection(qintptr socketDescriptor)
{
    Connection *connection = new Connection(socketDescriptor, this); //ERROR
    emit newConnection(connection);
}

/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QHostAddress>
#include <QtNetwork>

class Connection;

class server : public QTcpServer
{
    Q_OBJECT

public:
    server(QObject *parent = nullptr);

signals:
    void newConnection(Connection *connection);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H

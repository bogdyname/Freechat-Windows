/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QSctpServer>

class Connection;

class Server : public QSctpServer
{
    Q_OBJECT

public:
        QSctpServer(QObject *parent = nullptr);

signals:
        void NewConnection(Connection *connection);

protected:
        void InComingConnection(qintptr socketDescription) override;
};

#endif // SERVER_H

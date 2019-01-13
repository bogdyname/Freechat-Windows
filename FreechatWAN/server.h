#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Connection : public QTcpServer
{
    Q_OBJECT


};

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(QObject *parent = nullptr);
};

#endif // SERVER_H

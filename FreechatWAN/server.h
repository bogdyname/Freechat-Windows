#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

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

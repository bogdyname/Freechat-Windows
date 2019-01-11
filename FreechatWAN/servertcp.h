#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QTcpServer>

class Connection : public QTcpServer
{
    Q_OBJECT


};

class servertcp : public QTcpServer
{
    Q_OBJECT
public:
    servertcp(QObject *parent = nullptr);
};

#endif // SERVERTCP_H

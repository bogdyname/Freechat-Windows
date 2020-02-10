/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include "Bin/freechat.h"
#include <QTcpServer>
#include <QTcpSocket>

class Freechat;
class QTcpSocket;
class QTcpServer;

class Peerin : public QTcpServer
{
    Q_OBJECT

private:
    QTcpServer *server = nullptr;
    qint64 nextBlockSize;
    QTcpSocket *socket = nullptr;

public:
    explicit Peerin(QObject *parent = nullptr);
    ~Peerin();

public slots:
    virtual void SlotNewConnection();
    void SendResponseToClient();
    void SlotReadClient();
    void clearValue();

};
#endif

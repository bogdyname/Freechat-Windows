/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include "Network/connectionf2f.h"
#include "Network/peerout.h"

class Peerout;
class QTcpSpcket;
class ConnectionF2F;

class Peerin : public QTcpServer
{
    Q_OBJECT

private:
    QTcpServer *server = nullptr;
    quint16 nextBlockSize = 0;

private:
    explicit Peerin(QObject *parent = nullptr);
    ~Peerin();

private:
    void SendResponseToClient(QTcpSocket *socket, const QString &str);

public slots:
    virtual void SlotNewConnection();
    void SlotReadClient ();

};
#endif

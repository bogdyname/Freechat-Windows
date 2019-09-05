/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include "Network/connectionf2f.h"
#include "Network/peerout.h"

class Peerin : public ConnectionF2F, public QTcpServer
{
    Q_OBJECT

    Peerin(ConnectionF2F *parent = nullptr);
    ~Peerin();

private:
    void CheckPortsForConnection();
    void Connection();

private:
    QTcpSocket *socket = nullptr;
};
#endif

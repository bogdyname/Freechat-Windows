/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEEROUT
#define PEEROUT

#include "Network/connectionf2f.h"
#include "Bin/freechat.h"

class Peerin;
class Freechat;
class ConnectionF2F;

class Peerout : public ConnectionF2F
{
    Q_OBJECT

public:
    Peerout(const QString &ipHost);
    ~Peerout();

public slots:
    void SlotReadyRead();
    void SlotConnected();
    void SlotSendToServer();
    void SlotError(QAbstractSocket::SocketError);

private:
    QTcpSocket *socket = nullptr;
    quint16 nextBlockSize = 0;
};
#endif

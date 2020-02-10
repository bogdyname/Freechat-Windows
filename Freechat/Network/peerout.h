/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEEROUT
#define PEEROUT

#include "Bin/freechat.h"
#include <QHostAddress>
#include <QTcpSocket>


class Freechat;
class QTcpSocket;
class ConnectionF2F;

class Peerout : public QTcpSocket
{
    Q_OBJECT

public:
    explicit Peerout();
    ~Peerout();

public slots:
    void SlotReadyRead();
    void SlotConnected();
    void SlotConnecting();
    void SlotSendToServer();
    void SlotError(QAbstractSocket::SocketError);

private:
    QTcpSocket *socket;
    qint64 nextBlockSize;
};
#endif

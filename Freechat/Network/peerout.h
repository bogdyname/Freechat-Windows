/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEEROUT
#define PEEROUT

#include "Data/cryptography.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QSslSocket>

class Freechat;
class QTcpSocket;
class Cryptography;
class ConnectionF2F;

class Peerout : public QTcpSocket
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

public:
    explicit Peerout();
    ~Peerout();

public slots:
    void SlotDisconnectPeer();
    void SlotLanConnecting();
    void SlotWanConnecting();
    void SlotSendToServer();

private:
    void SendToServer(const QString &message);

private slots:
    void SlotReadyRead();
    void SlotConnected();
    void SlotError(QAbstractSocket::SocketError);

private:
    QTcpSocket *socket;
    qint64 nextBlockSize;
    Cryptography cryptomanagerOfPeerout;
    Cryptography cryptomanagerOfPeerin;
};
#endif

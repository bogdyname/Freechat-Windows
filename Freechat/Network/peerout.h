/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEEROUT
#define PEEROUT

#include <QHostAddress>
#include <QTcpSocket>

class Freechat;
class QTcpSocket;
class ConnectionF2F;

class Peerout : public QTcpSocket
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

public:
    explicit Peerout();
    ~Peerout();

public slots:
    void SlotReadyRead();
    void SlotConnected();
    void SlotLanConnecting();
    void SlotWanConnecting();
    void SlotSendToServer();
    void SlotError(QAbstractSocket::SocketError);

private:
    QTcpSocket *socket;
    qint64 nextBlockSize;
};
#endif

/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QNetworkSession>
#include <QHostAddress>
#include <QHostAddress>
#include <QTimerEvent>
#include <QTcpSocket>
#include <QHostInfo>
#include <QtNetwork>
#include <QSsl>

using namespace QSsl;
using namespace QPasswordDigestor;

class ConnectionF2F : public QTcpSocket
{
    Q_OBJECT

    ConnectionF2F(QObject *parent = nullptr);
    ~ConnectionF2F();

private slots:
    void DigitalSignature();
    void ConnectingToPeer();
    void SocketConnected();
    void SocketDisconnected();
    void ReadyReadOfData();
    void ListenPort();

public:
    void GetSocketFromClient();
    void getSocketFromHost();

private:
    void MakeSocketByClient();
    void MakeSocketByHost();
    void SockedErroe();

private:
    quint16 GetPeerPort();
    QHostAddress GetPeerAddress();

private:
    QTimerEvent TimerForWaitingConnection();

};

#endif // CONNECTION_H

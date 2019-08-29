/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTIONF2F_H
#define CONNECTIONF2F_H

#define WIN32_LEAN_AND_MEAN

#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QNetworkSession>
#include <QHostAddress>
#include <QHostAddress>
#include <QTimerEvent>
#include <QTcpSocket>
#include <QHostInfo>
#include <QtNetwork>

class ConnectionF2F : public QTcpSocket
{
    Q_OBJECT

public:
    ConnectionF2F(QObject *parent = nullptr);

    void ConnectingToPeer();
    void ReadyReadOfData();

    void AskForConnectingToPortPeer();
    void AskForDisconnectingFromPortPeer();

public:
    void PassOnWANIp(QString &buffer);

public:
    void GetIpAddressFromWAN(QString &textWithIPAddres);

private:
    QTcpSocket *socket = nullptr;
};
#endif

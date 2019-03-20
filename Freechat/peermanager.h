/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QList>
#include <QTimer>
#include <QObject>
#include <QByteArray>
#include <QUdpSocket>

class Client;
class Connection;

class PeerManager : public QObject
{
    Q_OBJECT

public:
    PeerManager(Client *client);

    QString userName() const;
    void startBroadcasting();
    void setServerPort(int port);
    //bool isLocalHostAddress(const QHostAddress &address); Need to connection via WLAN (not only LAN)

signals:
    void newConnection(Connection *connection);

private slots:
    void sendBroadcastDatagram();
    void readBroadcastDatagram();

private:
    void updateAddresses();

    Client *client;
    QList<QHostAddress> broadcastAddresses;
    QList<QHostAddress> ipAddresses;
    QUdpSocket broadcastSocket;
    QTimer broadcastTimer;
    QString username;
    int serverPort;
};

#endif // PEERMANAGER_H

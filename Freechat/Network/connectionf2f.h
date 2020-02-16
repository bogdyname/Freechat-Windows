/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTIONF2F_H
#define CONNECTIONF2F_H

#include <QNetworkInterface>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QHostAddress>
#include <QJsonObject>
#include <QTcpSocket>
#include <QtNetwork>

class QTcpSocket;
class Freechat;
class Peerout;
class Peerin;

class ConnectionF2F : public QTcpSocket
{
    Q_OBJECT

public:
    explicit ConnectionF2F(QObject *parent = nullptr);
    ~ConnectionF2F();

public:
    void LanNetwork(QString &ip, QString &mac, QString &netmask, QString &hostname);
    static int CheckNetworkAccess();
};
#endif

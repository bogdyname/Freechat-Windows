/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTIONF2F_H
#define CONNECTIONF2F_H

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
    ~ConnectionF2F();

    void ConnectingToPeer();
    void ReadyReadOfData();

public slots:
    void WriteIpAddressFromPeer();

signals:

public slots:
    void ReadyRead();
    void DoConnect();
    void Connected();
    void Disconnected();
    void BytesWrittenOfData(qint64 bytes);

private:
    QTcpSocket *socket = nullptr;
    QChar ipAddress;
    QString strWANip;
};
#endif

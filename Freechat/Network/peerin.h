/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include "Data/cryptography.h"
#include <QTcpServer>
#include <QSslSocket>
#include <QTcpSocket>
#include <QList>

class Freechat;
class QTcpSocket;
class QTcpServer;
class Cryptography;

class Peerin : public QTcpServer
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0")

private:
    QTcpServer *server = nullptr;
    qint64 nextBlockSize;
    QTcpSocket *socket = nullptr;
    Cryptography cryptomanagerOfPeerout;
    Cryptography cryptomanagerOfPeerin;

public:
    explicit Peerin(QObject *parent = nullptr);
    ~Peerin();

public slots:
    void DisconnectPeer();
    void SendMessages();
    void CloseOwnServerSlot();
    void ResumeServerSlot();

private slots:
    virtual void SlotNewConnection();
    void SendResponseToClient(const QString &message);
    void SlotReadClient();
    void clearValue();

};
#endif

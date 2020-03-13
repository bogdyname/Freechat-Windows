/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include <QTcpServer>
#include <QSslSocket>
#include <QTcpSocket>
#include <QList>

class Freechat;
class QTcpSocket;
class QTcpServer;

class Peerin : public QTcpServer
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

private:
    QTcpServer *server = nullptr;
    qint64 nextBlockSize;
    QTcpSocket *socket = nullptr;

public:
    explicit Peerin(QObject *parent = nullptr);
    ~Peerin();

public:
    void SetMaxConnection(unsigned short int &value);

public slots:
    virtual void SlotNewConnection();
    void SendResponseToClient();
    void DisconnectPeer();
    void SlotReadClient();
    void clearValue();

};
#endif

/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QHostAddress>
#include <QTimerEvent>
#include <QTcpSocket>
#include <QtNetwork>

class ConnectionF2F : public QTcpSocket
{
    Q_OBJECT

public:
    void DigitalSignature();
    void ConnectingToPeer();
    void MakeSocket();

private:
    QTimerEvent TimerForWaitingConnection();

};

#endif // CONNECTION_H

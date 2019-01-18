/*
***Copyright (C) 2019 Freechat Company
***Contact: bogdyname@gmail.com
*/

#include "connection.h"
#include <QtNetwork>

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout = 60 * 1000;
static const int PingInterval = 5 * 1000;

Connection::Connection(QObject *parent)
    : QTcpSocket(parent), writer(this)
{
    greetingMessage = tr("undefined");
    username = tr("unknown");
    state = WaitingForGreeting;
    currentDataType = Undefined;
    transferTimerId = -1;
    isGreetingMessageSent = false;
    pingTimer.setInterval(PingInterval);

    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::connect(this, SIGNAL(disconnected()), &pingTimer, SLOT(stop()));
    QObject::connect(&pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
    QObject::connect(this, SIGNAL(connected()),
                     this, SLOT(sendGreetingMessage()));
}

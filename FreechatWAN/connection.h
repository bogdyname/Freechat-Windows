/*
***Copyright (C) 2019 Freechat Company
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QElapsedTimer>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QTimer>

class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    enum ConnectionState
    {
        WaitingForGreeting,
        ReadingGreeting,
        ReadyForUse
    };
    enum DataType
    {
        PlainText,
        Ping,
        Pong,
        Greeting,
        Undefined
    };
};

#endif // CONNECTION_H

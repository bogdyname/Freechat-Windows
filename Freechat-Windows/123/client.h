/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include <QAbstractSocket>
#include <QHostAddress>
#include <QHash>

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

    void sendMessage(const QString &message);
    QString nickName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

signals:
    void newMessage(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

};

#endif // CLIENT_H

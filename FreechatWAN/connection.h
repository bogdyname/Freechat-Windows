/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QElapsedTimer>
#include <QHostAddress>
#include <QSctpSocket>
#include <QByteArray>
#include <QString>
#include <QTimer>

class Connection : public QSctpSocket
{
    Q_OBJECT

public:
    enum ConnectionData
    {
        WaintinForConnection,
        WritingForConnection,
        ReadyForConnection
    };

    enum MetaData
    {
        Ping,
        AlreadyConnection,
        NameOfUser,
    };

    Connection(QObject *parent = nullptr);
    Connection(qintptr socketDescriptor, QObject *parent = nullptr);
    ~Connection();

    QString name() const;
    void testMessage(const QString &message);
    bool sendMessage(const QString &message);

signals:
    void readyForUse();
    void newMessage(const QString &from, const QString &message);

protected:
    void timerEvent(QTimerEvent *timerEvent) override;//CHECK THIS OUT!!!!!!!!!!!!!!!!
};


#endif // CONNECTION_H

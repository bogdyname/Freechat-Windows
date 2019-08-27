/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "connectionf2f.h"

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{
    QString ip;
    PassOnWANIp(ip);
}

void ConnectionF2F::PassOnWANIp(QString &buffer)
{
    GetIpAddressFromWAN(buffer);

    #ifndef Q_DEBUG
    qDebug() << "Your IP address: " << buffer;
    #endif

    return;
}

void ConnectionF2F::GetIpAddressFromWAN(QString &textWithIPAddres)
{
        QNetworkAccessManager networkManager;
        QHostAddress IP;

        QUrl url("https://api.ipify.org");
        QUrlQuery query;
        query.addQueryItem("format", "json");
        url.setQuery(query);

        QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

        connect(reply, &QNetworkReply::finished, [&]()
        {
            if(reply->error() != QNetworkReply::NoError)
            {
                #ifndef Q_DEBUG
                qDebug() << "error: " << reply->error();
                #endif
            }
            else
            {
                QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
                QHostAddress ip(jsonObject["ip"].toString());

                IP = ip;
            }
            reply->deleteLater();
        });

        textWithIPAddres = IP.toString();

        return;
}

void ConnectionF2F::DoConnect()
{
    socket = new QTcpSocket(this);

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    //QString str("92.243.182.174");

    socket->connectToHost("192.168.1.1", 80);

        if(socket->waitForConnected(3000))
        {
            #ifndef Q_DEBUG
            qDebug() << "Connected!";
            #endif

            socket->write("DATA OF TEXT");
            socket->waitForBytesWritten(1000);
            socket->waitForReadyRead(3000);
            #ifndef Q_DEBUG
            qDebug() << "Reading: " << socket->bytesAvailable();
            qDebug() << socket->readAll();
            #endif

            socket->close();
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Not connected!";
            #endif
        }

        return;
}

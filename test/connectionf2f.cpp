/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "connectionf2f.h"

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{
    QString tts;
    GetIpAddressFromWAN(tts);
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

                qDebug() << "external ip: " << ip;
                IP = ip;
            }
            reply->deleteLater();
        });

        textWithIPAddres = IP.toString();

        return;
}


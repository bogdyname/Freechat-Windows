/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Data/datasave.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

Bin::Bin(QWidget *parent)
    : QFile(parent)
{
    MakeFileWithIp();
    MakeFileWithMac();
}

Bin::~Bin()
{
    delete buffer;
}

inline void Bin::ReadingIpAddress(QFile &fileWithIP)
{
    if ((fileWithIP.exists()) && (fileWithIP.open(ReadOnly)))
    {
        fileWithIP.readAll();
        fileWithIP.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

inline void Bin::ReadingMACAddress(QFile &fileWithMac)
{
    if ((fileWithMac.exists()) && (fileWithMac.open(ReadOnly)))
    {
        fileWithMac.readAll();
        fileWithMac.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

inline void Bin::MakeFileWithIp()
{
    QString ipOfUser;
    GetIpAddressFromWAN(ipOfUser);

    QString fname = "ipadd" +
            QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
    QFile file(fname);

    if((file.exists()) && (file.isOpen()))
    {
         if(file.open(WriteOnly))
         {
             QTextStream writeStream(&file);
             writeStream << ipOfUser;
             file.flush();
         }
         else
         {
             file.close();
         }
    }
}

inline void Bin::MakeFileWithMac()
{
    QString macOfUser;
    GetMacAddress(macOfUser);

    QString fnamem = "macadd" +
            QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";

    QFile filem(fnamem);

    if((filem.exists()) && (filem.isOpen()))
    {
         if(filem.open(WriteOnly))
         {
             QTextStream writeStream(&filem);
             writeStream << macOfUser;
             filem.flush();
         }
         else
         {
             filem.close();
         }
    }
}

inline void Bin::GetMacAddress(QString &textWithMacAddresOfUser)
{
            foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
            {
                textWithMacAddresOfUser += interface.hardwareAddress();
            }

    return;
}

void Bin::GetIpAddressFromWAN(QString &textWithIPAddres)
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
                qDebug() << "error: " << reply->error();
            }
            else
            {
                QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
                QHostAddress ip(jsonObject["ip"].toString());

                IP = ip;
            }
            reply->deleteLater();
        }
        );

        textWithIPAddres = IP.toString();

        return;
}

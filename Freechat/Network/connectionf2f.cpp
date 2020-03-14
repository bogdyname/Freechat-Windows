/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Network/connectionf2f.h"
#include "Network/peerout.h"
#include "Network/peerin.h"
#include "Bin/freechat.h"

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{

    return;
}

ConnectionF2F::~ConnectionF2F()
{

    return;
}

void ConnectionF2F::LanNetwork(QString &ip, QString &mac, QString &netmask, QString &hostname)
{
       QString localhostIP;
       QString localhostname =  QHostInfo::localHostName();
       QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).QHostInfo::addresses();

       foreach (const QHostAddress& address, hostList)
       {
           if (address.QHostAddress::protocol() == QAbstractSocket::IPv4Protocol && address.QHostAddress::isLoopback() == false)
                localhostIP = address.QHostAddress::toString();
       }

       QString localMacAddress;
       QString localNetmask;

       foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces())
       {
           foreach (const QNetworkAddressEntry& entry, networkInterface.QNetworkInterface::addressEntries())
           {
               if (entry.QNetworkAddressEntry::ip().QHostAddress::toString() == localhostIP)
               {
                   localMacAddress = networkInterface.QNetworkInterface::hardwareAddress();
                   localNetmask = entry.QNetworkAddressEntry::netmask().QHostAddress::toString();
                   break;
               }
           }
       }

       #ifndef Q_DEBUG
       qDebug() << "Localhost name: " << localhostname;
       qDebug() << "IP = " << localhostIP;
       qDebug() << "MAC = " << localMacAddress;
       qDebug() << "Netmask = " << localNetmask;
       #endif

       ip += localhostIP;
       mac += localMacAddress;
       netmask += localNetmask;
       hostname += localhostname;

       return;
}

unsigned short int ConnectionF2F::CheckNetworkAccess()
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.QNetworkAccessManager::get(req);
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.QEventLoop::exec();

    if(reply->bytesAvailable())
    {
        return 101;
    }
    else
    {
        return 404;
    }
}

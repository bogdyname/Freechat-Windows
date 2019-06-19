/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "username.h"
#include "datasave.h"
#include "freechat.h"
#include "connectionf2f.h"

Username::Username(QObject *parent)
    : QFile(parent)
{

}

void Username::ReadingIpAddress(QFile &fileWithIP)
{
    if ((fileWithIP.exists()) && (fileWithIP.open(ReadOnly)))
    {
        ui->textBrowser->setTextWithNetworkData(fileWithIP.readAll());
        fileWithIP.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

void Username::ReadingMACAddress(QFile &fileWithMac)
{
    if ((fileWithMac.exists()) && (fileWithMac.open(ReadOnly)))
    {
        ui->listViewWithNetworkData->setText(fileWithMac.readAll());
        fileWithMac.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

Usernametable::Usernametable(QObject *parent)
    : QFile(parent)
{
          foreach (const QHostAddress &addr, addresses)
          {
              switch (addr.protocol())
              {
                  case QAbstractSocket::IPv4Protocol:
                      protocol = "IPv4";
                  break;
                  case QAbstractSocket::IPv6Protocol:
                      protocol = "IPv6";
                  break;
              }
              qDebug() << addr.toString() << "(" << protocol << ")";
          }

          QString macOfUser;
          GetMacAddresses(macOfUser);

          QString fname = "macadd" +
                  QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
          QFile file(fname);

          if((file.exists()) && (file.isOpen()))
          {
               if(file.open(WriteOnly))
               {
                   QTextStream writeStream(&file);
                   writeStream << macOfUser;
                   file.flush();
               }
               else
               {
                   file.close();
               }
          }
}

inline QString Usernametable::GetIpV4AndV6Protocol()
    {
        if((list[nIter].protocol() == QAbstractSocket::IPv4Protocol) &&
                (list[nIter].protocol() == QAbstractSocket::IPv6Protocol))
        {
            list[nIter].toString();
        }
        else
        {
            /*clear code*/
        }

        return list[nIter].toString();
}

inline void Usernametable::GetIpAddresses()
{
    for(nInter < list.count();; nInter++)
    {
        if(!list[nInter].isLoopback())
        {
            GetIpV4AndV6Protocol();
        }
        else
        {
            /*clear code*/
        }
    }

    return;
}

inline void Usernametable::GetMacAddresses(QString &textWithMacAddresOfUser)
{
            foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
            {
                textWithMacAddresOfUser += interface.hardwareAddress();
            }

    return;
}

void Usernametable::TranslationName(QFile &fileWithMAC, QString &translator)
{
    fileWithMAC = ReadingMACAddress(fileWithMAC);

    return;
}

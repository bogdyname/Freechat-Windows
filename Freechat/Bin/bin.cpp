/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Data/datasave.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

Bin::Bin(QObject *parent)
    : QObject(parent)
{

}

Bin::~Bin()
{

}

template <typename Wcontainer>
Wcontainer Bin::WriteElementsInList(Wcontainer &list, const QString &element)
{
    list << element;

    return;
}

template <typename Gcontainer>
Gcontainer Bin::GetElementsFromList(Gcontainer &list)
{
    QList<QString>::const_iterator it = list.constBegin();

    for(; it != list.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from list: " << *it << endl;
        #endif
    }

    return;
}

template <typename Rcontainer>
Rcontainer Bin::RemoveElementsFromList(Rcontainer &list)
{
    QList<QString>::iterator it = list.begin();

    for(; it != list.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from list: " << *it << endl;
        #endif

        //list.erase(*it);
    }

    return;
}

void Bin::WriteInNickNameListOfPeers(const QString &nickname)
{
    listWithNickName << nickname;

    return;
}

void Bin::WriteInIpListOfPeers(const QString &lanIP, const QString &wanIP)
{
    listWithLANIpAddress << lanIP;
    listWithWANIpAddress << wanIP;

    return;
}

void Bin::GetElementFromIpList()
{
    /*wan ip list*/

    QList<QString>::const_iterator itWAN = listWithWANIpAddress.constBegin();

    for(; itWAN != listWithWANIpAddress.end(); ++itWAN)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from WAN IP list: " << *itWAN << endl;
        #endif
    }

    /*lan ip list*/

    QList<QString>::const_iterator itLAN = listWithLANIpAddress.constBegin();

    for(; itLAN != listWithWANIpAddress.end(); ++itLAN)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from LAN IP list: " << *itLAN << endl;
        #endif
    }

    return;
}

void Bin::GetElementFromNickNameList()
{
    QList<QString>::const_iterator it = listWithNickName.constBegin();

    for(; it != listWithNickName.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from Nickname list: " << *it << endl;
        #endif
    }

    return;
}

void Bin::RemoveFromIpList()
{
    /*wan ip list*/

    QList<QString>::const_iterator itWAN = listWithWANIpAddress.constBegin();

    for(; itWAN != listWithWANIpAddress.end(); ++itWAN)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from WAN IP list: " << *itWAN << endl;
        #endif

        //listWithWANIpAddress.erase(*it);
    }

    /*lan ip list*/

    QList<QString>::const_iterator itLAN = listWithLANIpAddress.constBegin();

    for(; itLAN != listWithWANIpAddress.end(); ++itLAN)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from LAN IP list: " << *itWAN << endl;
        #endif

        //listWithLANIpAddress.erase(*it);
    }


    return;
}

void Bin::RemoveFromNickNameList()
{
    QList<QString>::iterator it = listWithNickName.begin();

    for(; it != listWithNickName.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from Nickname list: " << *it << endl;
        #endif

        //listWithNickName.erase(*it);
    }

    return;
}

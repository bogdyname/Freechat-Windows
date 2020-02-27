/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

using namespace std;

Bin::Bin(QObject *parent)
    : QObject(parent)
{
    Bin::fileForSavingNick.QFile::link("nicks");
    Bin::fileForSavingWANip.QFile::link("wi");
    Bin::fileForSavingLANip.QFile::link("li");

    return;
}

Bin::~Bin()
{

    return;
}

inline bool Bin::CheckMaxLengthOfString(const QString &string)
{
    if(string.QString::length() == 15)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Bin::AddPeerLan()
{
    if(Bin::CheckMaxLengthOfString(Freechat::lanIpOfPeer) == true)
        return;

    Bin::WriteElementsInList(Bin::listWithWANIpAddress, Freechat::lanIpOfPeer);

    return;
}

void Bin::AddPeerWan()
{
    if(Bin::CheckMaxLengthOfString(Freechat::wanIpOfPeer) == true)
        return;

    Bin::WriteElementsInList(Bin::listWithLANIpAddress, Freechat::wanIpOfPeer);

    return;
}

void Bin::AddPeerNick()
{
    if(Freechat::nickNameOfPeer == "")
        return;

    Bin::WriteElementsInList(Bin::listWithNickName, Freechat::nickNameOfPeer);
    Freechat::nickNameOfPeer.QString::clear();

    return;
}

void Bin::DeleteAllPeer()
{
    Bin::RemoveElementsFromList(Bin::listWithNickName);
    Bin::RemoveElementsFromList(Bin::listWithWANIpAddress);
    Bin::RemoveElementsFromList(Bin::listWithLANIpAddress);

    qDeleteAll(Freechat::listWithNickName->QListWidget::selectedItems());
    Freechat::listWithNickName->QListWidget::clear();

    return;
}

void Bin::SavingDataAboutPeer(QList<QString> &list)
{
    if ((Bin::fileForSavingNick.QFile::exists()) &&
       (Bin::fileForSavingNick.QIODevice::open(QIODevice::ReadOnly)))
    {
        while(!Bin::fileForSavingNick.QFileDevice::atEnd())
        {
            Bin::fileForSavingNick.QIODevice::write("");
        }
    }

    return;
}

void Bin::ReadDataAboutPeer()
{
    if ((Bin::fileForSavingNick.QFile::exists()) && (Bin::fileForSavingNick.QIODevice::open(QIODevice::ReadOnly)))
    {
        QString str = "";

        while(!Bin::fileForSavingNick.QFileDevice::atEnd())
        {
            str += Bin::fileForSavingNick.QIODevice::readLine();
        }

        Freechat::listWithNickName->QListWidget::addItem(str);
        Bin::fileForSavingNick.QFileDevice::close();
    }

    return;
}

void Bin::DeleteSelectedPeer()
{
    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem * item, items)
    {
        delete Freechat::listWithNickName->QListWidget::takeItem(Freechat::listWithNickName->QListWidget::row(item));
    }

    return;
}

void Bin::GetNickname(QList<QString> &nick)
{
    nick = Bin::GetElementsFromList(Bin::listWithNickName);

    return;
}

template <typename Wcontainer>
Wcontainer Bin::WriteElementsInList(Wcontainer &list, const QString &element)
{
    return list << element;
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

    return list;
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

        list.erase(it);
    }

    return list;
}

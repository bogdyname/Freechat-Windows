/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

using namespace std;
using namespace Qt;

Bin::Bin(QObject *parent)
    : QObject(parent)
{
    Bin::fileForSavingNick.setFileName("/root/Freechat/Freechat/Bin/nicks.txt");
    Bin::fileForSavingWANip.setFileName("/root/Freechat/Freechat/Bin/li.txt");
    Bin::fileForSavingLANip.setFileName("/root/Freechat/Freechat/Bin/wi.txt");

    return;
}

Bin::~Bin()
{

    return;
}

void Bin::AddPeerLan()
{
    if(Freechat::lanIpOfPeerBinmanager == "")
        return;

    Bin::WriteElementsInList(Bin::listWithWANIpAddress, Freechat::lanIpOfPeerBinmanager);
    Freechat::lanIpOfPeerBinmanager.QString::clear();

    return;
}

void Bin::AddPeerWan()
{
    if(Freechat::wanIpOfPeerBinmanager == "")
        return;

    Bin::WriteElementsInList(Bin::listWithLANIpAddress, Freechat::wanIpOfPeerBinmanager);
    Freechat::wanIpOfPeerBinmanager.QString::clear();

    return;
}

void Bin::AddPeerNick()
{
    if(Freechat::nickNameOfPeer == "")
        return;

    Bin::WriteElementsInList(Bin::listWithNickName, Freechat::nickNameOfPeer);
    Freechat::nickNameOfPeer.QString::clear();

    for (int i = 0; i < Bin::listWithNickName.size(); ++i)
    {
            #ifndef Q_DEBUG
            qDebug() << "Data from LIST with Nickname: " << Bin::listWithNickName.at(i).toLocal8Bit().constData();
            #endif
    }

    return;
}

void Bin::DeleteAllPeer()
{
    Bin::RemoveElementsFromList(Bin::listWithNickName);
    Bin::RemoveElementsFromList(Bin::listWithWANIpAddress);
    Bin::RemoveElementsFromList(Bin::listWithLANIpAddress);

    for (int i = 0; i < Bin::listWithNickName.size(); ++i)
    {
            #ifndef Q_DEBUG
            qDebug() << "check list: " << Bin::listWithNickName.at(i).toLocal8Bit().constData();
            #endif
    }

    qDeleteAll(Freechat::listWithNickName->QListWidget::selectedItems());
    Freechat::listWithNickName->QListWidget::clear();

    return;
}

void Bin::ReadDataAboutPeer(QFile &pointerOnFile)
{
    if (!pointerOnFile.QFile::open(QFile::ReadOnly))
    {
      #ifndef Q_DEBUG
      qDebug() << "error opening output file";
      #endif
    }
    else
    {
      QTextStream stream(&pointerOnFile);

      #ifndef Q_DEBUG
      qDebug() << "Bin: file is opened";
      #endif

      while(!stream.QTextStream::atEnd())
        Bin::listWithNickName += stream.QTextStream::readLine();
    }

    pointerOnFile.close();
    Freechat::listWithNickName->QListWidget::addItems(Bin::listWithNickName);

    return;
}

void Bin::ReadDataAboutPeer(QStringList &list, QFile &pointerOnFile)
{
      if (!pointerOnFile.QFile::open(QFile::ReadOnly))
      {
        #ifndef Q_DEBUG
        qDebug() << "error opening output file";
        #endif
      }
      else
      {
        QTextStream stream(&pointerOnFile);

        #ifndef Q_DEBUG
        qDebug() << "Bin: file is opened";
        #endif

        while(!stream.QTextStream::atEnd())
          list += stream.QTextStream::readLine();
      }

      pointerOnFile.close();

    return;
}

void Bin::DeleteSelectedPeer()
{
    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        int number = Freechat::listWithNickName->QListWidget::row(item);

        delete Freechat::listWithNickName->QListWidget::takeItem(Freechat::listWithNickName->QListWidget::row(item));
        Bin::listWithNickName.removeAt(number);
        Bin::listWithWANIpAddress.removeAt(number);
        Bin::listWithLANIpAddress.removeAt(number);

        #ifndef Q_DEBUG
        qDebug() << "number from bin for delete selected peer: " << number;
        #endif
    }

    for (int i = 0; i < Bin::listWithNickName.size(); ++i)
    {
        #ifndef Q_DEBUG
        qDebug() << "check list: " << Bin::listWithNickName.at(i).toLocal8Bit().constData();
        #endif
    }

    return;
}

void Bin::SavingPeers()
{
    Bin::SavingDataAboutPeer(Bin::listWithNickName, Bin::fileForSavingNick);
    Bin::SavingDataAboutPeer(Bin::listWithLANIpAddress, Bin::fileForSavingLANip);
    Bin::SavingDataAboutPeer(Bin::listWithWANIpAddress, Bin::fileForSavingWANip);

    return;
}

void Bin::ReadPeers()
{
    Bin::ReadDataAboutPeer(Bin::fileForSavingNick);
    Bin::ReadDataAboutPeer(Bin::listWithLANIpAddress, Bin::fileForSavingLANip);
    Bin::ReadDataAboutPeer(Bin::listWithWANIpAddress, Bin::fileForSavingWANip);

    return;
}

void Bin::SavingDataAboutPeer(QStringList &list, QFile &pointerOnFile)
{
    if (!pointerOnFile.QFile::open(QFile::WriteOnly))
    {
        #ifndef Q_DEBUG
        qDebug() << "error opening output file!";
        #endif
    }
    else
    {
        QTextStream stream(&pointerOnFile);

        #ifndef Q_DEBUG
        qDebug() << "Bin: file is opened";
        #endif

        for (unsigned short row = 0; row < list.QList::size(); ++row)
          stream << list.QList::at(row) << '\n';
    }

    pointerOnFile.QFileDevice::flush();

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

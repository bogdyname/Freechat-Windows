/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

using namespace std;
using namespace Qt;

 QStringList Bin::listWithNickName;
 QStringList Bin::listWithWANIpAddress;
 QStringList Bin::listWithLANIpAddress;

Bin::Bin(QObject *parent)
    : QObject(parent)
{

    return;
}

Bin::~Bin()
{

    return;
}

void Bin::GetSelectedPeer()
{
    Freechat::nickNameOfPeer.QString::clear();
    Freechat::lanIpOfPeer.QString::clear();
    Freechat::wanIpOfPeer.QString::clear();

    if(!(Freechat::writeNickOfPeer->QLineEdit::text() == ""))
    {
        Freechat::writeNickOfPeer->QLineEdit::clear();
        Freechat::writeLanIpOfPeer->QLineEdit::clear();
        Freechat::writeWanIpOfPeer->QLineEdit::clear();
    }

    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        int number = Freechat::listWithNickName->QListWidget::row(item);
        QString nick = "";
        QString lIP = "";
        QString wIP = "";

        nick += Bin::listWithNickName.QList::value(number);
        lIP += Bin::listWithWANIpAddress.QList::value(number);
        wIP += Bin::listWithLANIpAddress.QList::value(number);

        Freechat::writeNickOfPeer->QLineEdit::setText(nick);
        Freechat::writeLanIpOfPeer->QLineEdit::setText(lIP);
        //Freechat::writeWanIpOfPeer->QLineEdit::setText(wIP); //TTS cos network through NAT adn WAN IP not done

        Freechat::nickNameOfPeer += nick;
        Freechat::lanIpOfPeer += lIP;
        Freechat::wanIpOfPeer += wIP;

        #ifndef Q_DEBUG
        qDebug() << "number from bin for auto past code: " << number << ": " << nick << ": " << lIP;
        #endif
    }

    for (unsigned short i = 0; i < Bin::listWithNickName.QList::size(); ++i)
    {
        #ifndef Q_DEBUG
        qDebug() << "check list for auto past code: " << Bin::listWithNickName.QList::at(i).QString::toLocal8Bit().QByteArray::constData();
        #endif
    }

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

    for (unsigned short i = 0; i < Bin::listWithNickName.QList::size(); ++i)
    {
            #ifndef Q_DEBUG
            qDebug() << "Data from LIST with Nickname: " << Bin::listWithNickName.QList::at(i).QString::toLocal8Bit().QByteArray::constData();
            #endif
    }

    return;
}

void Bin::DeleteAllPeer()
{
    Bin::RemoveElementsFromList(Bin::listWithNickName);
    Bin::RemoveElementsFromList(Bin::listWithWANIpAddress);
    Bin::RemoveElementsFromList(Bin::listWithLANIpAddress);

    for (unsigned short i = 0; i < Bin::listWithNickName.QList::size(); ++i)
    {
            #ifndef Q_DEBUG
            qDebug() << "check list: " << Bin::listWithNickName.QList::at(i).QString::toLocal8Bit().QByteArray::constData();
            #endif
    }

    qDeleteAll(Freechat::listWithNickName->QListWidget::selectedItems());
    Freechat::listWithNickName->QListWidget::clear();

    return;
}

void Bin::ReadDataAboutPeer(QFile *pointerOnFile)
{
    if (!pointerOnFile->QFile::open(QFile::ReadOnly))
    {
      #ifndef Q_DEBUG
      qDebug() << "error opening output file";
      #endif
    }
    else
    {
      QTextStream stream(pointerOnFile);

      #ifndef Q_DEBUG
      qDebug() << "Bin: file is opened";
      #endif

      while(!stream.QTextStream::atEnd())
        Bin::listWithNickName += stream.QTextStream::readLine();
    }

    pointerOnFile->close();
    Freechat::listWithNickName->QListWidget::addItems(Bin::listWithNickName);

    return;
}

void Bin::ReadDataAboutPeer(QStringList &list, QFile *pointerOnFile)
{
      if (!pointerOnFile->QFile::open(QFile::ReadOnly))
      {
        #ifndef Q_DEBUG
        qDebug() << "error opening output file";
        #endif
      }
      else
      {
        QTextStream stream(pointerOnFile);

        #ifndef Q_DEBUG
        qDebug() << "Bin: file is opened";
        #endif

        while(!stream.QTextStream::atEnd())
          list += stream.QTextStream::readLine();
      }

      pointerOnFile->QFileDevice::close();

    return;
}

void Bin::DeleteSelectedPeer()
{
    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        int number = Freechat::listWithNickName->QListWidget::row(item);

        delete Freechat::listWithNickName->QListWidget::takeItem(Freechat::listWithNickName->QListWidget::row(item));
        Bin::listWithNickName.QList::removeAt(number);
        Bin::listWithWANIpAddress.QList::removeAt(number);
        Bin::listWithLANIpAddress.QList::removeAt(number);

        #ifndef Q_DEBUG
        qDebug() << "number from bin for delete selected peer: " << number;
        #endif
    }

    for (int i = 0; i < Bin::listWithNickName.QList::size(); ++i)
    {
        #ifndef Q_DEBUG
        qDebug() << "check list: " << Bin::listWithNickName.QList::at(i).QString::toLocal8Bit().QByteArray::constData();
        #endif
    }

    return;
}

void Bin::SavingPeers()
{
    Bin::SavingDataAboutPeer(Bin::listWithNickName, fileForSavingNick);
    Bin::SavingDataAboutPeer(Bin::listWithLANIpAddress, fileForSavingLANip);
    Bin::SavingDataAboutPeer(Bin::listWithWANIpAddress, fileForSavingWANip);

    return;
}

void Bin::ReadPeers()
{
    Bin::ReadDataAboutPeer(fileForSavingNick);
    Bin::ReadDataAboutPeer(Bin::listWithLANIpAddress, fileForSavingLANip);
    Bin::ReadDataAboutPeer(Bin::listWithWANIpAddress, fileForSavingWANip);

    return;
}

void Bin::SavingDataAboutPeer(QStringList &list, QFile *pointerOnFile)
{
    if (!pointerOnFile->QFile::open(QFile::WriteOnly))
    {
        #ifndef Q_DEBUG
        qDebug() << "error opening output file!";
        #endif
    }
    else
    {
        QTextStream stream(pointerOnFile);

        #ifndef Q_DEBUG
        qDebug() << "Bin: file is opened";
        #endif

        for (unsigned short row = 0; row < list.QList::size(); ++row)
          stream << list.QList::at(row) << '\n';
    }

    pointerOnFile->QFileDevice::close();

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

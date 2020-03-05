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

 static Cryptography cryptomanager(Q_UINT64_C(0x0c2ad4a5acb9f012));

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

    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        int number = Freechat::listWithNickName->QListWidget::row(item);

        Freechat::nickNameOfPeer += Bin::listWithNickName.QList::value(number);
        Freechat::lanIpOfPeer += Bin::listWithLANIpAddress.QList::value(number);
        Freechat::wanIpOfPeer += Bin::listWithWANIpAddress.QList::value(number);

        #ifndef Q_DEBUG
        qDebug() << "number from bin for auto past code: " << number << ": " << Freechat::nickNameOfPeer << ": " << Freechat::lanIpOfPeer;
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

    Bin::WriteElementsInList(Bin::listWithLANIpAddress, Freechat::lanIpOfPeerBinmanager);
    Freechat::lanIpOfPeerBinmanager.QString::clear();

    for (unsigned short i = 0; i < Bin::listWithLANIpAddress.QList::size(); ++i)
    {
            #ifndef Q_DEBUG
            qDebug() << "Data from LIST with LAN: " << Bin::listWithLANIpAddress.QList::at(i).QString::toLocal8Bit().QByteArray::constData();
            #endif
    }

    return;
}

void Bin::AddPeerWan()
{
    if(Freechat::wanIpOfPeerBinmanager == "")
        return;

    Bin::WriteElementsInList(Bin::listWithWANIpAddress, Freechat::wanIpOfPeerBinmanager);
    Freechat::wanIpOfPeerBinmanager.QString::clear();

    for (unsigned short i = 0; i < Bin::listWithWANIpAddress.QList::size(); ++i)
    {
            #ifndef Q_DEBUG
            qDebug() << "Data from LIST with WAN: " << Bin::listWithWANIpAddress.QList::at(i).QString::toLocal8Bit().QByteArray::constData();
            #endif
    }

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
    cryptomanager.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    cryptomanager.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

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
      {
        QString cypherText = stream.QTextStream::readLine();
        QString nick = cryptomanager.Cryptography::decryptToString(cypherText);

        #ifndef Q_DEBUG
        qDebug() << "TEXT: " << cypherText;
        qDebug() << "nick: " << nick;
        #endif

        if (!(cryptomanager.Cryptography::lastError() == Cryptography::ErrorNoError))
        {
            #ifndef Q_DEBUG
            qDebug() << "error decrypt nick file";
            #endif

            return;
        }

        Bin::listWithNickName += nick;

        cypherText.QString::clear();
        nick.QString::clear();
      }
    }

    pointerOnFile->close();
    Freechat::listWithNickName->QListWidget::addItems(Bin::listWithNickName);

    return;
}

void Bin::ReadDataAboutPeer(QStringList &list, QFile *pointerOnFile)
{
    cryptomanager.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    cryptomanager.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

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
        {
          QString cypherText = stream.QTextStream::readLine();
          QString ip = cryptomanager.Cryptography::decryptToString(cypherText);

          #ifndef Q_DEBUG
          qDebug() << "TEXT: " << cypherText;
          qDebug() << "ip: " << ip;
          #endif

          if (!(cryptomanager.Cryptography::lastError() == Cryptography::ErrorNoError))
          {
              #ifndef Q_DEBUG
              qDebug() << "error decrypt ip file";
              #endif

              return;
          }

          list += ip;

          cypherText.QString::clear();
          ip.QString::clear();
        }
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
    cryptomanager.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    cryptomanager.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

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
        {
          QString nick = list.QList::at(row);
          QString cypherText = cryptomanager.Cryptography::encryptToString(nick);
          stream << cypherText << '\n';

          cypherText.QString::clear();
          nick.QString::clear();
        }
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

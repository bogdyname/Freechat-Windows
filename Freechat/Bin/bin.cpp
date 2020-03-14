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
    Bin::ReadPeers();

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

    Bin::WriteElementsInList(Bin::listWithLANIpAddress, Freechat::lanIpOfPeerBinmanager);
    Freechat::lanIpOfPeerBinmanager.QString::clear();

    for (unsigned short row = 0; row < Bin::listWithLANIpAddress.QList::size(); ++row)
    {
            #ifndef Q_DEBUG
            qDebug() << "Data from LIST with LAN: " << Bin::listWithLANIpAddress.QList::at(row).QString::toLocal8Bit().QByteArray::constData();
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

    for (unsigned short row = 0; row < Bin::listWithWANIpAddress.QList::size(); ++row)
    {
            #ifndef Q_DEBUG
            qDebug() << "Data from LIST with WAN: " << Bin::listWithWANIpAddress.QList::at(row).QString::toLocal8Bit().QByteArray::constData();
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

    for (unsigned short row = 0; row < Bin::listWithNickName.QList::size(); ++row)
    {
            #ifndef Q_DEBUG
            qDebug() << "Data from LIST with Nickname: " << Bin::listWithNickName.QList::at(row).QString::toLocal8Bit().QByteArray::constData();
            #endif
    }

    return;
}

void Bin::DeleteAllPeer()
{
    Bin::RemoveElementsFromList(Bin::listWithNickName);
    Bin::RemoveElementsFromList(Bin::listWithWANIpAddress);
    Bin::RemoveElementsFromList(Bin::listWithLANIpAddress);

    for (unsigned short row = 0; row < Bin::listWithNickName.QList::size(); ++row)
    {
            #ifndef Q_DEBUG
            qDebug() << "check list: " << Bin::listWithNickName.QList::at(row).QString::toLocal8Bit().QByteArray::constData();
            #endif
    }

    qDeleteAll(Freechat::listWithNickName->QListWidget::selectedItems());
    Freechat::listWithNickName->QListWidget::clear();

    return;
}

void Bin::DeleteSelectedPeer()
{
    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        unsigned short number = Freechat::listWithNickName->QListWidget::row(item);

        delete Freechat::listWithNickName->QListWidget::takeItem(Freechat::listWithNickName->QListWidget::row(item));
        Bin::listWithNickName.QList::removeAt(number);
        Bin::listWithWANIpAddress.QList::removeAt(number);
        Bin::listWithLANIpAddress.QList::removeAt(number);

        #ifndef Q_DEBUG
        qDebug() << "number from bin for delete selected peer: " << number;
        #endif
    }

    for (int row = 0; row < Bin::listWithNickName.QList::size(); ++row)
    {
        #ifndef Q_DEBUG
        qDebug() << "check list: " << Bin::listWithNickName.QList::at(row).QString::toLocal8Bit().QByteArray::constData();
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

void Bin::GetSelectedPeer()
{
    Freechat::nickNameOfPeer.QString::clear();
    Freechat::lanIpOfPeer.QString::clear();
    Freechat::wanIpOfPeer.QString::clear();

    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        unsigned short number = Freechat::listWithNickName->QListWidget::row(item);

        Freechat::nickNameOfPeer += Bin::listWithNickName.QList::value(number);
        Freechat::lanIpOfPeer += Bin::listWithLANIpAddress.QList::value(number);
        Freechat::wanIpOfPeer += Bin::listWithWANIpAddress.QList::value(number);

        #ifndef Q_DEBUG
        qDebug() << "number from bin for auto past code: " << number << ": " << Freechat::nickNameOfPeer << ": " << Freechat::lanIpOfPeer;
        #endif
    }

    for (unsigned short row = 0; row < Bin::listWithNickName.QList::size(); ++row)
    {
        #ifndef Q_DEBUG
        qDebug() << "check list for auto past code: " << Bin::listWithNickName.QList::at(row).QString::toLocal8Bit().QByteArray::constData();
        #endif
    }

    return;
}

void Bin::ReadDataAboutPeer(QFile *pointerOnFile)
{
    cryptomanager.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    cryptomanager.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

    if (!pointerOnFile->QFile::open(QFile::ReadOnly))
    {
      #ifndef Q_DEBUG
      qCritical() << "error opening output file";
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
        const QString cypherText = stream.QTextStream::readLine();
        const QString nick = cryptomanager.Cryptography::decryptToString(cypherText);

        #ifndef Q_DEBUG
        qDebug() << "TEXT: " << cypherText;
        qDebug() << "nick: " << nick;
        #endif

        if (!(cryptomanager.Cryptography::lastError() == Cryptography::ErrorNoError))
        {
            #ifndef Q_DEBUG
            qCritical() << "error decrypt nick file";
            #endif

            return;
        }

        Bin::listWithNickName += nick;
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
        qCritical() << "error opening output file";
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
          const QString cypherText = stream.QTextStream::readLine();
          const QString ip = cryptomanager.Cryptography::decryptToString(cypherText);

          #ifndef Q_DEBUG
          qDebug() << "TEXT: " << cypherText;
          qDebug() << "ip: " << ip;
          #endif

          if (!(cryptomanager.Cryptography::lastError() == Cryptography::ErrorNoError))
          {
              #ifndef Q_DEBUG
              qCritical() << "error decrypt ip file";
              #endif

              return;
          }

          list += ip;
        }
      }

      pointerOnFile->QFileDevice::close();

    return;
}

void Bin::SavingDataAboutPeer(const QStringList &list, QFile *pointerOnFile)
{
    cryptomanager.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    cryptomanager.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

    if (!pointerOnFile->QFile::open(QFile::WriteOnly))
    {
        #ifndef Q_DEBUG
        qCritical() << "error opening output file!";
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
          const QString nick = list.QList::at(row);
          const QString cypherText = cryptomanager.Cryptography::encryptToString(nick);
          stream << cypherText << '\n';
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
Gcontainer Bin::GetElementsFromList(const Gcontainer &list)
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

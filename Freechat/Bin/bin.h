/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef BIN_H
#define BIN_H

#include <QList>
#include <QString>
#include <iostream>
#include <algorithm>
#include <QListWidgetItem>

class Bin : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

private:
    QStringList listWithNickName;
    QStringList listWithWANIpAddress;
    QStringList listWithLANIpAddress;
    QFile fileForSavingNick;
    QFile fileForSavingWANip;
    QFile fileForSavingLANip;

public:
    ~Bin();
    explicit Bin(QObject *parent = nullptr);

public slots:
    void AddPeerLan();//DONE
    void AddPeerWan();//DONE
    void AddPeerNick();//DONE
    void DeleteAllPeer();//DONE
    void ReadDataAboutPeer();//CHECK IT OUT!!!!!
    void DeleteSelectedPeer();//DONE
    void SavingPeers();//CHECK IT OUT!!!!!

private:
    void SavingDataAboutPeer(QStringList &nick);//CHECK IT OUT!!!!!

//ALL DONE
private:
    template <typename Wcontainer>
    Wcontainer WriteElementsInList(Wcontainer &list, const QString &element);

    template <typename Gcontainer>
    Gcontainer GetElementsFromList(Gcontainer &list);

    template <typename Rcontainer>
    Rcontainer RemoveElementsFromList(Rcontainer &list);
};
#endif

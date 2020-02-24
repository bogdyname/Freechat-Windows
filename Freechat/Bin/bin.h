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

private:
    QList<QString> listWithNickName;
    QList<QString> listWithWANIpAddress;
    QList<QString> listWithLANIpAddress;
    QFile fileForSavingIPAndNick;

public:
    ~Bin();
    explicit Bin(QObject *parent = nullptr);

public slots:
    inline void AddPeerLan();
    inline void AddPeerWan();
    inline void AddPeerNick();
    inline void DeleteAllPeer();
    void SavingDataAboutPeers(QList<QString> &list);
    void ReadDataAboutPeers();
    void DeleteSelectedPeer();
    void GetNickname(QList<QString> &nick);

private:
    template <typename Wcontainer>
    Wcontainer WriteElementsInList(Wcontainer &list, const QString &element);

    template <typename Gcontainer>
    Gcontainer GetElementsFromList(Gcontainer &list);

    template <typename Rcontainer>
    Rcontainer RemoveElementsFromList(Rcontainer &list);
};
#endif

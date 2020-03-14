/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef BIN_H
#define BIN_H

#include <QDir>
#include <QList>
#include <QString>
#include <iostream>
#include <algorithm>
#include <QListWidget>
#include <QListWidgetItem>

class Bin : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

public:
    static QStringList listWithNickName;
    static QStringList listWithWANIpAddress;
    static QStringList listWithLANIpAddress;

private:
    QFile *fileForSavingNick = new QFile("nicks.bin");
    QFile *fileForSavingLANip = new QFile("li.bin");
    QFile *fileForSavingWANip = new QFile("wi.bin");

public:
    ~Bin();
    explicit Bin(QObject *parent = nullptr);

public slots:
    void AddPeerLan();
    void AddPeerWan();
    void AddPeerNick();
    void DeleteAllPeer();
    void DeleteSelectedPeer();
    void SavingPeers();
    void ReadPeers();
    void GetSelectedPeer();

private:
    void ReadDataAboutPeer(QFile *pointerOnFile);
    void ReadDataAboutPeer(QStringList &list, QFile *pointerOnFile);
    void SavingDataAboutPeer(const QStringList &list, QFile *pointerOnFile);

//ALL DONE
private:
    template <typename Wcontainer>
    Wcontainer WriteElementsInList(Wcontainer &list, const QString &element);

    template <typename Gcontainer>
    Gcontainer GetElementsFromList(const Gcontainer &list);

    template <typename Rcontainer>
    Rcontainer RemoveElementsFromList(Rcontainer &list);
};
#endif

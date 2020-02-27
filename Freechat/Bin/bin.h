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
    void AddPeerLan();
    void AddPeerWan();
    void AddPeerNick();
    void DeleteAllPeer();
    void ReadDataAboutPeer();
    void DeleteSelectedPeer();
    void GetNickname(QList<QString> &nick);
    void SavingDataAboutPeer(QList<QString> &list);

private:
    inline bool CheckMaxLengthOfString(const QString &string);

private:
    template <typename Wcontainer>
    Wcontainer WriteElementsInList(Wcontainer &list, const QString &element);

    template <typename Gcontainer>
    Gcontainer GetElementsFromList(Gcontainer &list);

    template <typename Rcontainer>
    Rcontainer RemoveElementsFromList(Rcontainer &list);
};
#endif

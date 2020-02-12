/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "Bin/bin.h"
#include "Network/peerin.h"
#include "Network/peerout.h"
#include "Network/connectionf2f.h"
#include "ui_freechat.h"
#include <QTextTableFormat>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QMetaEnum>
#include <QString>
#include <QDialog>

using namespace Qt;

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT

public:
    static QString yourIp;
    static QString yourMAC;
    static QString yourNetmask;
    static QString localHostName;
    static QString command;
    static QString lanIpOfPeer;
    static QString wanIpOfPeer;
    static QString nickNameOfPeer;
    static QString bufferOfMessages;
    static unsigned short int value;
    QStringList commandsList;

    //UI
    static QListWidget *listWithNickName;
    static QTextEdit *viewField;
    static QLineEdit *commandLine;
    static QLineEdit *writeNickOfPeer;
    static QLineEdit *writeLanIpOfPeer;
    static QLineEdit *writeWanIpOfPeer;
    static QLineEdit *lineForTypeText;

private:
    int (*checkNetworkConnection)() = nullptr;
    bool (*checkConnection)() = nullptr;

public:
    explicit Freechat(QWidget *parent = nullptr);
    ~Freechat();

private slots:
    void lineForTypeText_returnPressed();
    void writeWanIpOfPeer_returnPressed();
    void writeLanIpOfPeer_returnPressed();
    void writeNickOfPeer_returnPressed();
    void CommandLineInterface();
    void networkInformation();
    void connectionToPeerIn();

    void ServerStillWorking();// test code

private:
   QString status;
   QString networkdata;

private:
    Ui::Freechat *ui;
};
#endif

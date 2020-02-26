/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "Bin/bin.h"
#include "Data/datasave.h"
#include "Network/peerin.h"
#include "Network/peerout.h"
#include "Network/connectionf2f.h"
#include "ui_freechat.h"
#include <QTextTableFormat>
#include <QFontDatabase>
#include <QListWidget>
#include <QMessageBox>
#include <QTextEdit>
#include <QJSEngine>
#include <QLineEdit>
#include <QMetaEnum>
#include <QPointer>
#include <QString>
#include <QDialog>
#include <QTimer>

using namespace Qt;

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

    //COLORS
    //System out color  | Errors color    | Peerin data       | Peerout data
    //color(255, 153, 0)| color(156, 0, 0)| color(255, 215, 0)| color(0, 255, 255)

    //Command line interface
private:
    QStringList commandsList;

    //COMMANDS
    /* 1) clear
       -- clear all data in view field
       2) ip -l
       -- show message box with LAN ip
       3) ifconfig
       -- Show message box with all data of peer LAN network
       4) shutdown
       -- close programm
       5) con -l
       -- connecting via LAN network
       6) man
       -- data about all commands
       7) con -w
       -- connecting via WAN network
       8) disconnect
       -- disconnect from host
       9) save
       -- saving all data from viewFieldEdit into file
       10) clear -a nick
       -- clear all contacts
    */

    //Global buffer variables
public:
    static QString yourLanIp;
    static QString yourMAC;
    static QString yourNetmask;
    static QString localHostName;
    static QString command;
    static QString lanIpOfPeer;
    static QString wanIpOfPeer;
    static QString nickNameOfPeer;
    static QString bufferOfMessages;
    static unsigned short int value; //for network code (about server)

    //UI
public:
    static QTextEdit *viewField;
    static QLineEdit *commandLine;
    static QLineEdit *lineForTypeText;
    static QLineEdit *writeNickOfPeer;
    static QLineEdit *writeLanIpOfPeer;
    static QLineEdit *writeWanIpOfPeer;
    static QListWidget *listWithNickName;

private:
    int (*checkNetworkConnection)() = nullptr;
    bool (*checkConnection)() = nullptr;

public:
    explicit Freechat(QWidget *parent = nullptr);
    ~Freechat();

private slots:
    void LineForTypeText_returnPressed();
    void WriteWanIpOfPeer_returnPressed();
    void WriteLanIpOfPeer_returnPressed();
    void WriteNickOfPeer_returnPressed();
    void CommandLineInterface();
    void ServerStillWorking();//Debug code

private:
    void NetworkLanIp();
    void NetworkFullInformation();
    void ConnectionToPeerInLan();

private:
    QString status;
    QString networkdata;

private:
    Ui::Freechat *ui;
};
#endif

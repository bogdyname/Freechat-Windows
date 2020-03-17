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
#include <QStatusBar>
#include <QScrollBar>
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
    QStringList commandsList = { "clear",       "ip -l",    "ifconfig",
                                 "shutdown",    "con -l",     "man",
                                 "con -w",    "disconnect",   "save",
                                 "clear -n",   "save -n",    "hide -n",
                                 "show -n",     "hide -a",   "show -a",
                                 "hide -i",     "show -i" };

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
       10) clear -n
       -- clear all contacts
       11) save -n
       -- save all contact into file
       12) hide -n
       -- hide list with Nicks
       13) show -n
       -- show list with Nicks
       14) hide -a
       -- hide all but without main fields
       15) show -a
       -- show all fields
       16) hide -i
       -- hide interface
       17) show -i
       -- show interface
    */

    //Global buffer variables
    //Network
private:
    QString yourLanIp;
    QString yourMAC;
    QString yourNetmask;
    QString localHostName;
    QString statusOfNetwork;
    QString networkdata;

    //Managers
private:
    QPointer<Peerin> server;
    QPointer<Peerout> stpeerout;
    QPointer<ConnectionF2F> netmanager;
    QPointer<Datasave> datamanager;
    QPointer<Bin> binmanager;

public:
    static QString lanIpOfPeer;
    static QString wanIpOfPeer;
    static unsigned short int value; //for network code (about server)

    //CLI
    static QString command;

    //Bin code
    static QString nickNameOfPeer;
    static QString lanIpOfPeerBinmanager;
    static QString wanIpOfPeerBinmanager;

    //Global variable
    static QString bufferOfMessages;

    //UI
public:
    static QTextEdit *viewField;
    static QListWidget *listWithNickName;

private:
    static QLineEdit *commandLine;
    static QLineEdit *lineForTypeText;
    static QLineEdit *writeNickOfPeer;
    static QLineEdit *writeLanIpOfPeer;
    static QLineEdit *writeWanIpOfPeer;

private:
    unsigned short int (*checkNetworkConnection)() = nullptr;
    bool (*checkConnection)() = nullptr;
    bool scrollbarAtBottom;
    int scrollbarPrevValue;

public:
    explicit Freechat(QWidget *parent = nullptr);
    ~Freechat();

private:
    void NetworkLanIp();
    void NetworkFullInformation();
    void ConnectionToPeerInLan();

private slots:
    void ScrollToEnd();
    void ServerStillWorking();
    void LineForTypeText_returnPressed();
    void WriteWanIpOfPeer_returnPressed();
    void WriteLanIpOfPeer_returnPressed();
    void WriteNickOfPeer_returnPressed();
    void CommandLineInterface();

private:
    Ui::Freechat *ui;
};
#endif

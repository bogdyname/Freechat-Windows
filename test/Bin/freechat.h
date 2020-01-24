/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "Bin/bin.h"
#include "ui_freechat.h"
#include "Network/connectionf2f.h"
#include <QTextTableFormat>
#include <QMessageBox>
#include <QtWidgets>
#include <QString>
#include <QDialog>

using namespace Qt;

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT

public:
    static QString yourIp;
    static QString lanIpOfPeer;
    static QString wanIpOfPeer;
    static QString nickNameOfPeer;
    static QString bufferOfMessages;

    //UI
    static QListWidget *listWithNickName;
    static QTextEdit *viewField;
    static QPushButton *showNetworkInfo;
    static QPushButton *connectionToPeer;
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
    void on_lineForTypeText_returnPressed();
    void on_writeWanIpOfPeer_returnPressed();
    void on_writeLanIpOfPeer_returnPressed();
    void on_writeNickOfPeer_returnPressed();
    void on_showNetworkInfo_clicked();
    void on_connectionToPeer_clicked();

    void ServerStillWorking();// test code

private:
    QString status;

private:
    Ui::Freechat *ui;
};
#endif

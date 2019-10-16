/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

 QString Freechat::globalBuffer;
 QString Freechat::viewField;
 QString Freechat::yourIp;
 QString Freechat::lanIpOfPeer;
 QString Freechat::wanIpOfPeer;
 QString Freechat::nickNameOfPeer;
 QString Freechat::bufferOfMessages;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Freechat)
{
    ui->setupUi(this);

    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->bytesAvailable())
    {
        ui->writeNickOfPeer->setReadOnly(true);
        ui->writeWanIpOfPeer->setReadOnly(true);
        ui->writeLanIpOfPeer->setReadOnly(true);
        ui->lineForTypeText->setReadOnly(true);
    }
    else
    {
        /*clear code*/
    }

    //ui->writeWanIpOfPeer->setInputMask("000.000.000.000");
    //ui->writeLanIpOfPeer->setInputMask("000.000.000.000");

    ui->writeNickOfPeer->setPlaceholderText("Write here nickname of peer");
    ui->writeWanIpOfPeer->setPlaceholderText("Write here WAN IP of peer");
    ui->writeLanIpOfPeer->setPlaceholderText("Write here LAN IP of peer");
    ui->lineForTypeText->setPlaceholderText("Type here");

    ui->writeNickOfPeer->setMaxLength(15);
    ui->writeWanIpOfPeer->setMaxLength(15);
    ui->writeLanIpOfPeer->setMaxLength(15);
    ui->lineForTypeText->setMaxLength(200);

    ui->writeNickOfPeer->setFocusPolicy(StrongFocus);
    ui->writeWanIpOfPeer->setFocusPolicy(StrongFocus);
    ui->writeLanIpOfPeer->setFocusPolicy(StrongFocus);
    ui->lineForTypeText->setFocusPolicy(StrongFocus);

    ui->textFieldForViewMessages->setFocusPolicy(NoFocus);
    ui->textFieldForViewMessages->setReadOnly(true);
    ui->listWithNickName->setFocusPolicy(NoFocus);

    //connect(lineForTypeText, SIGNAL(returnPressed()), this, SLOT(clear()));

    return;
}

Freechat::~Freechat()
{
    delete ui;
}

void Freechat::on_showNetworkInfo_clicked(bool checked)
{
    switch(checked)
    {
    case true:
        QMessageBox::information(this, tr("Network Info"),
                                 tr("Your LAN IP address: "), yourIp);
        break;
    case false:
        QMessageBox::information(this, tr("Error"),
                                 tr("Check your network connection."));
        break;
    }

    return;
}

void Freechat::on_connectionToPeer_clicked(bool checked)
{
    switch(checked)
    {
    case true:
    {
        QMessageBox::information(this, tr("Connection"),
                                 tr("Connecting to peer..."));
    }
        break;
    case false:
        QMessageBox::information(this, tr("Disconnected"),
                                 tr("Peer does not want to connect with you"));
        break;
    }

    return;
}

void Freechat::on_lineForTypeText_returnPressed()
{
    bufferOfMessages += ui->lineForTypeText->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << bufferOfMessages;
    #endif

    return;
}

void Freechat::on_writeWanIpOfPeer_returnPressed()
{
    wanIpOfPeer += ui->writeWanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << wanIpOfPeer;
    #endif

    return;
}

void Freechat::on_writeLanIpOfPeer_returnPressed()
{
    lanIpOfPeer += ui->writeLanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << lanIpOfPeer;
    #endif

    return;
}

void Freechat::on_writeNickOfPeer_returnPressed()
{
    nickNameOfPeer += ui->writeNickOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << nickNameOfPeer;
    #endif

    return;
}

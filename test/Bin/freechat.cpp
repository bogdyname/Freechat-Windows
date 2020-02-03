/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"
#include <QTimer>
#include <QPointer>


 QTextEdit *Freechat::viewField;
 QListWidget *Freechat::listWithNickName;
 QPushButton *Freechat::showNetworkInfo;
 QPushButton *Freechat::connectionToPeer;
 QLineEdit *Freechat::writeNickOfPeer;
 QLineEdit *Freechat::writeLanIpOfPeer;
 QLineEdit *Freechat::writeWanIpOfPeer;
 QLineEdit *Freechat::lineForTypeText;

 QString Freechat::yourIp;
 QString Freechat::lanIpOfPeer;
 QString Freechat::wanIpOfPeer;
 QString Freechat::nickNameOfPeer;
 QString Freechat::bufferOfMessages;

 static QPointer<Peerin> server = nullptr;
 static QPointer<Peerout> stpeerout = nullptr;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Freechat)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //delete default status bar
    //this->setAttribute(Qt::WA_TranslucentBackground); //background clear

    //new UI
    try
    {
        Freechat::viewField = new QTextEdit();
        Freechat::listWithNickName = new QListWidget();
        Freechat::showNetworkInfo = new QPushButton();
        Freechat::connectionToPeer = new QPushButton();
        Freechat::writeNickOfPeer = new QLineEdit();
        Freechat::writeLanIpOfPeer = new QLineEdit();
        Freechat::writeWanIpOfPeer = new QLineEdit();
        Freechat::lineForTypeText = new QLineEdit();
    }
    catch(std::bad_alloc& exp)
    {
        #ifndef Q_DEBUG
        qDebug() << "Exception caught: " << exp.what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qDebug() << "Some exception caught";
        #endif
        abort();
    }


    //Bin
    Bin bin;

    //Connecting UI widgets with bin code
    connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerNick()));
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerLan()));
    connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerWan()));

    //Network
    ConnectionF2F netManager;
    netManager.NetworkInfo();

    try
    {
        server = new Peerin();
        stpeerout = new Peerout();
    }
    catch(std::bad_alloc& exp)
    {
        #ifndef Q_DEBUG
        qDebug() << "Exception caught: " << exp.what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qDebug() << "Some exception caught";
        #endif
        abort();
    }

    QTimer *timer = new QTimer;
    timer->setInterval(10000);
    connect(timer, SIGNAL(timeout()), this, SLOT(ServerStillWorking()));
    timer->start();

    //Connecting UI widgets with network object code
    connect(Freechat::showNetworkInfo, SIGNAL(clicked()), this, SLOT(showNetworkInfo_clicked()));
    connect(Freechat::connectionToPeer, SIGNAL(clicked()), this, SLOT(connectionToPeer_clicked()));
    connect(Freechat::connectionToPeer, SIGNAL(clicked()), stpeerout, SLOT(SlotConnecting()));

    //UI connection
    connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), this, SLOT(lineForTypeText_returnPressed()));
    connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(writeWanIpOfPeer_returnPressed()));
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(writeLanIpOfPeer_returnPressed()));
    connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), this, SLOT(writeNickOfPeer_returnPressed()));
    connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), Freechat::lineForTypeText, SLOT(clear()));
    connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeWanIpOfPeer, SLOT(clear()));
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeLanIpOfPeer, SLOT(clear()));
    connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), Freechat::writeNickOfPeer, SLOT(clear()));

    //first layer
    ui->horizontalLayout_1->addWidget(Freechat::writeNickOfPeer);
    ui->horizontalLayout_2->addWidget(Freechat::writeLanIpOfPeer);
    ui->horizontalLayout_3->addWidget(Freechat::writeWanIpOfPeer);

    //second layer
    ui->horizontalLayout_4->addWidget(Freechat::showNetworkInfo);
    ui->horizontalLayout_4->addWidget(Freechat::connectionToPeer);

    //third layer
    ui->horizontalLayout_5->addWidget(Freechat::listWithNickName);
    ui->horizontalLayout_5->addWidget(Freechat::viewField);

    //fourth layer
    ui->horizontalLayout_6->addWidget(Freechat::lineForTypeText);

    //UI style and focus
    Freechat::showNetworkInfo->setText("Info of Network");
    Freechat::connectionToPeer->setText("Connecting to peer");
    Freechat::lineForTypeText->setPlaceholderText("Type here");
    Freechat::writeNickOfPeer->setPlaceholderText("Write here nickname of peer");
    Freechat::writeWanIpOfPeer->setPlaceholderText("Write here WAN IP of peer");
    Freechat::writeLanIpOfPeer->setPlaceholderText("Write here LAN IP of peer");
    Freechat::listWithNickName->addItem("hi boyyyyyy"); // test code

    Freechat::writeNickOfPeer->setMaxLength(15);
    Freechat::writeWanIpOfPeer->setMaxLength(15);
    Freechat::writeLanIpOfPeer->setMaxLength(15);
    Freechat::lineForTypeText->setMaxLength(1500);

    Freechat::listWithNickName->setMaximumHeight(500);
    Freechat::listWithNickName->setMaximumWidth(225);
    Freechat::listWithNickName->setFocusPolicy(ClickFocus);
    Freechat::writeNickOfPeer->setFocusPolicy(WheelFocus);
    Freechat::writeWanIpOfPeer->setFocusPolicy(WheelFocus);
    Freechat::writeLanIpOfPeer->setFocusPolicy(WheelFocus);
    Freechat::lineForTypeText->setFocusPolicy(WheelFocus);
    Freechat::viewField->setFocusPolicy(NoFocus);
    Freechat::viewField->setReadOnly(true);

    //variables for pointer of function from ConnectionF2F
    checkNetworkConnection = ConnectionF2F::CheckConnection;

    //close all QLineEdit if network shutdown
    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            #ifndef Q_DEBUG
            qDebug() << "Network access";
            #endif
        }
        break;
        case 404:
        {
            //block all field without network access
            Freechat::writeNickOfPeer->setReadOnly(true);
            Freechat::writeWanIpOfPeer->setReadOnly(true);
            Freechat::writeLanIpOfPeer->setReadOnly(true);
            Freechat::lineForTypeText->setReadOnly(true);
        }
        break;
    }

    return;
}

Freechat::~Freechat()
{
    if(ui != nullptr)
    {
        delete ui;
        delete server;
        delete stpeerout;
    }
    else
    {
        /*clear code*/
    }

    return;
}

//check server
void Freechat::ServerStillWorking()
{
    if(server != nullptr)
    {
        #ifndef Q_DEBUG
        qDebug() << "Server still working";
        #endif
    }
    else
    {
        #ifndef Q_DEBUG
        qDebug() << "Server stoped!" ;
        #endif
    }

    return;
}

//check this method for scan BUG OF DOUBLE show QMessageBox::info about ip addr
void Freechat::showNetworkInfo_clicked()
{
    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            status = QString("<h1>Your LAN IP address: %1</h1>").arg(Freechat::yourIp);
            QMessageBox::information(Freechat::showNetworkInfo, tr("Network Info"),
                             status, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(Freechat::showNetworkInfo, tr("Error"),
                             tr("<h1>Check your network connection.</h1>"), "ok");
        }
        break;
        default:
        {
            return;
        }
    }

    return;
}

void Freechat::connectionToPeer_clicked()
{
    if(Freechat::lanIpOfPeer != "")
    {
        QMessageBox::information(Freechat::connectionToPeer, tr("Connecting"),
                         tr("<h1>Connecting to peer.</h1>"), "ok");
    }
    else
    {
        QMessageBox::critical(Freechat::connectionToPeer, tr("Connecting error"),
                         tr("<h1>Check IP of peer.</h1>"), "ok");
    }

    return;
}

//check this method for try and catch with SIGNALS and SLOTS of send data (server, stpeerout) WARNING!!!!!!!!!!!!!!
// try to get peerout's IP and make double connecting between peers WARNING!!!!!!!!!!!!!! WARNING!!!!!!!!!!!!!! WARNING!!!!!!!!!!!!!!
void Freechat::lineForTypeText_returnPressed()
{
    QTime time = QTime::currentTime();
    Freechat::bufferOfMessages += Freechat::lineForTypeText->text();
    Freechat::viewField->insertPlainText(time.toString() + ": " + "Me:" + Freechat::bufferOfMessages + "\n");

    if(server->isListening())
    {
        connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), server, SLOT(SendToClientFlush()));

        #ifndef Q_DEBUG
        qDebug() << "Send this data to client: " << Freechat::bufferOfMessages;
        #endif
    }
    else
    {
        connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), stpeerout, SLOT(SlotSendToServer()));

        #ifndef Q_DEBUG
        qDebug() << "Send this data to server: " << Freechat::bufferOfMessages;
        #endif
    }

    return;
}

void Freechat::writeWanIpOfPeer_returnPressed()
{
    Freechat::wanIpOfPeer += Freechat::writeWanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::wanIpOfPeer;
    #endif

    return;
}

void Freechat::writeLanIpOfPeer_returnPressed()
{
    Freechat::lanIpOfPeer += Freechat::writeLanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::lanIpOfPeer;
    #endif

    return;
}

void Freechat::writeNickOfPeer_returnPressed()
{
    Freechat::nickNameOfPeer += Freechat::writeNickOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::nickNameOfPeer;
    #endif

    return;
}

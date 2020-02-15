/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"
#include <QTimer>
#include <QPointer>

 QTextEdit *Freechat::viewField;
 QLineEdit *Freechat::commandLine;
 QLineEdit *Freechat::writeNickOfPeer;
 QLineEdit *Freechat::writeLanIpOfPeer;
 QLineEdit *Freechat::writeWanIpOfPeer;
 QLineEdit *Freechat::lineForTypeText;
 QListWidget *Freechat::listWithNickName;

 QString Freechat::command;
 QString Freechat::yourIp;
 QString Freechat::yourMAC;
 QString Freechat::yourNetmask;
 QString Freechat::localHostName;
 QString Freechat::lanIpOfPeer;
 QString Freechat::wanIpOfPeer;
 QString Freechat::nickNameOfPeer;
 QString Freechat::bufferOfMessages;
 unsigned short int Freechat::value;

 static QPointer<Peerin> server = nullptr;
 static QPointer<Peerout> stpeerout = nullptr;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Freechat)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //delete default status bar

    //new UI
    try
    {
        Freechat::viewField = new QTextEdit();
        Freechat::listWithNickName = new QListWidget();
        Freechat::commandLine = new QLineEdit();
        Freechat::writeNickOfPeer = new QLineEdit();
        Freechat::writeLanIpOfPeer = new QLineEdit();
        Freechat::writeWanIpOfPeer = new QLineEdit();
        Freechat::lineForTypeText = new QLineEdit();
    }
    catch(std::bad_alloc &exp)
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

    Freechat::writeWanIpOfPeer->setReadOnly(true);//TTS cos network through NAT adn WAN IP not done

    //first layer
    ui->horizontalLayout_1->addWidget(Freechat::writeNickOfPeer);
    //ui->horizontalLayout_2->addWidget(Freechat::writeWanIpOfPeer); //TTS cos network through NAT adn WAN IP not done
    ui->horizontalLayout_3->addWidget(Freechat::writeLanIpOfPeer);

    //second layer
    ui->HLForButtons->addWidget(Freechat::commandLine);

    //third layer
    ui->horizontalLayout_5->addWidget(Freechat::listWithNickName);
    ui->horizontalLayout_5->addWidget(Freechat::viewField);

    //fourth layer
    ui->horizontalLayout_6->addWidget(Freechat::lineForTypeText);

    //Bin
    Bin bin;

    //Network data of peer (LAN data)
    ConnectionF2F netManager;
    netManager.NetworkInfo(Freechat::yourIp,
                           Freechat::yourMAC,
                           Freechat::yourNetmask,
                           Freechat::localHostName);

    try
    {
        server = new Peerin();
        stpeerout = new Peerout();
    }
    catch(std::bad_alloc &exp)
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

    //Connecting UI widgets with bin code
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerNick()));
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerLan()));
    //connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerWan())); //TTS cos network through NAT adn WAN IP not done

    //UI connection
    connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), this, SLOT(lineForTypeText_returnPressed()));
    //connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(writeWanIpOfPeer_returnPressed())); //TTS cos network through NAT adn WAN IP not done
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(writeLanIpOfPeer_returnPressed()));
    connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), this, SLOT(writeNickOfPeer_returnPressed()));
    connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), Freechat::lineForTypeText, SLOT(clear()));
    //connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeWanIpOfPeer, SLOT(clear())); //TTS cos network through NAT adn WAN IP not done
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeLanIpOfPeer, SLOT(clear()));
    connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), Freechat::writeNickOfPeer, SLOT(clear()));

    //Command line interface
    commandsList << "clear" << "info" << "whoami" << "shutdown" << "con -l";
    connect(Freechat::commandLine, SIGNAL(returnPressed()), this, SLOT(CommandLineInterface()));
    connect(Freechat::commandLine, SIGNAL(returnPressed()), Freechat::commandLine, SLOT(clear()));

    //UI style and focus
    Freechat::commandLine->setPlaceholderText("Command line");
    Freechat::lineForTypeText->setPlaceholderText("Type here");
    Freechat::writeNickOfPeer->setPlaceholderText("Write here nickname of peer");
    Freechat::writeWanIpOfPeer->setPlaceholderText("Write here WAN IP of peer");
    Freechat::writeLanIpOfPeer->setPlaceholderText("Write here LAN IP of peer");

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
    Freechat::value = 0;

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
            Freechat::commandLine->setReadOnly(true);
        }
        break;
    }

    return;
}

Freechat::~Freechat()
{
    delete ui;
    delete server;
    delete stpeerout;

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

void Freechat::networkLanIp()
{
    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            status = QString("<h1>Your LAN IP address: %1</h1>").arg(Freechat::yourIp);
            QMessageBox::information(Freechat::commandLine, tr("Network Info"),
                             status, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(Freechat::commandLine, tr("Error"),
                             tr("<h1>Check your network connection.</h1>"), "ok");
        }
        break;
    }

    return;
}

void Freechat::networkFullInformation()
{
    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            networkdata = QString("<h1><p>IP = %1</p><p>MAC = %2</p><p>Netmask = %3</p><p>localhost = %4</p></h1>")
            .arg(Freechat::yourIp).arg(Freechat::yourMAC).arg(Freechat::yourNetmask).arg(Freechat::localHostName);

            QMessageBox::information(Freechat::commandLine, tr("Network data"),
                            networkdata, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(Freechat::commandLine, tr("Error"),
                             tr("<h1>Check your network connection.</h1>"), "ok");
        }
        break;
    }

    return;
}

void Freechat::connectionToPeerInLan()
{
    if(Freechat::lanIpOfPeer != "")
    {
        QMessageBox::information(Freechat::commandLine, tr("Connecting"),
                         tr("<h1>Connecting to peer.</h1>"), "ok");
    }
    else
    {
        QMessageBox::critical(Freechat::commandLine, tr("Connecting error"),
                         tr("<h1>Check IP of peer.</h1>"), "ok");
    }

    return;
}

void Freechat::CommandLineInterface()
{
    Freechat::command += Freechat::commandLine->text();

    #ifndef Q_DEBUG
    qDebug() << command;
    #endif

    switch(commandsList.indexOf(command))
    {
        case 0:
        {
                #ifndef Q_DEBUG
                qDebug() << "clear";
                #endif

                Freechat::viewField->clear();
        }
        break;
        case 1:
        {
                #ifndef Q_DEBUG
                qDebug() << "info";
                #endif

                Freechat::networkLanIp();
        }
        break;
        case 2:
        {
                #ifndef Q_DEBUG
                qDebug() << "whoami";
                #endif

                networkFullInformation();
        }
        break;
        case 3:
        {
                #ifndef Q_DEBUG
                qDebug() << "shutdown";
                #endif

                close();
        }
        break;
        case 4:
        {
                 #ifndef Q_DEBUG
                 qDebug() << "con -l";
                 #endif

                 Freechat::connectionToPeerInLan();
                 stpeerout->SlotLanConnecting();
        }
        break;
        default:
        {
                 QMessageBox::critical(Freechat::commandLine, tr("Command error"),
                                tr("<h1>Command not found</h1>"), "ok");
        }
        break;
    }

    Freechat::command.clear();

    return;
}

void Freechat::lineForTypeText_returnPressed()
{
    QTime time = QTime::currentTime();
    Freechat::bufferOfMessages += Freechat::lineForTypeText->text();
    Freechat::viewField->setAlignment(Qt::AlignLeft);
    Freechat::viewField->insertPlainText(time.toString() + "\n" + "Me: " + Freechat::bufferOfMessages + "\n");

    switch(Freechat::value)
    {
        case 1:
        {
            connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), server, SLOT(SendResponseToClient()));

            #ifndef Q_DEBUG
            qDebug() << "Send this data to client: " << Freechat::bufferOfMessages;
            #endif
        }
        break;
        case 0:
        {
            connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), stpeerout, SLOT(SlotSendToServer()));

            #ifndef Q_DEBUG
            qDebug() << "Send this data to server: " << Freechat::bufferOfMessages;
            #endif
        }
        break;
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

/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"

 QTextEdit *Freechat::viewField;
 QLineEdit *Freechat::commandLine;
 QLineEdit *Freechat::writeNickOfPeer;
 QLineEdit *Freechat::writeLanIpOfPeer;
 QLineEdit *Freechat::writeWanIpOfPeer;
 QLineEdit *Freechat::lineForTypeText;
 QListWidget *Freechat::listWithNickName;

 QString Freechat::command;
 QString Freechat::yourLanIp;
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
 static QPointer<ConnectionF2F> netmanager = nullptr;
 static QPointer<Datasave> datamanager = nullptr;
 static QPointer<Bin> binmanager = nullptr;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Freechat)
{
    ui->setupUi(this);

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

    //Network data of peer (LAN data)
    try
    {
        netmanager = new ConnectionF2F();
        server = new Peerin();
        stpeerout = new Peerout();
        datamanager = new Datasave();
        binmanager = new Bin();
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

    netmanager->LanNetwork(Freechat::yourLanIp,
                           Freechat::yourMAC,
                           Freechat::yourNetmask,
                           Freechat::localHostName);

    //Timer for Debug server (check server status)
    QTimer *timerOfServer = new QTimer;
    timerOfServer->setInterval(10000);
    connect(timerOfServer, SIGNAL(timeout()), this, SLOT(ServerStillWorking()));
    timerOfServer->start();

    QTimer *timerOfAutoDataSaving = new QTimer;
    timerOfAutoDataSaving->setInterval(500000);
    connect(timerOfAutoDataSaving, SIGNAL(timeout()), datamanager, SLOT(DataSavingViaTimer()));
    timerOfAutoDataSaving->start();

    //Connecting UI widgets with bin code
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), binmanager, SLOT(AddPeerNick()));
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), binmanager, SLOT(AddPeerLan()));
    //connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerWan())); //TTS cos network through NAT adn WAN IP not done

    //UI connection
    connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), this, SLOT(LineForTypeText_returnPressed()));
    //connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(writeWanIpOfPeer_returnPressed())); //TTS cos network through NAT adn WAN IP not done
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(WriteLanIpOfPeer_returnPressed()));
    connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), this, SLOT(WriteNickOfPeer_returnPressed()));
    connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), Freechat::lineForTypeText, SLOT(clear()));
    //connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeWanIpOfPeer, SLOT(clear())); //TTS cos network through NAT adn WAN IP not done
    connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeLanIpOfPeer, SLOT(clear()));
    connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), Freechat::writeNickOfPeer, SLOT(clear()));

    //Command line interface
    commandsList << "clear" << "ip -l" << "ifconfig" << "shutdown"
                 << "con -l" << "man" << "con -w" << "disconnect"
                 << "save";

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

    datamanager->ReadDataFromFile();// NEED TO TEST IT

    //variables for pointer of function from ConnectionF2F
    checkNetworkConnection = ConnectionF2F::CheckNetworkAccess;
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

void Freechat::NetworkLanIp()
{
    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            status = QString("<h1>Your LAN IP address: %1</h1>").arg(Freechat::yourLanIp);
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

void Freechat::NetworkFullInformation()
{
    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            networkdata = QString("<h1><p>IP = %1</p><p>MAC = %2</p><p>Netmask = %3</p><p>localhost = %4</p></h1>")
            .arg(Freechat::yourLanIp).arg(Freechat::yourMAC).arg(Freechat::yourNetmask).arg(Freechat::localHostName);

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

void Freechat::ConnectionToPeerInLan()
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
    if(Freechat::commandLine->text() == "")
        return;

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
                qDebug() << "ip -l";
                #endif

                Freechat::NetworkLanIp();
        }
        break;
        case 2:
        {
                #ifndef Q_DEBUG
                qDebug() << "ifconfig";
                #endif

                NetworkFullInformation();
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

                 Freechat::ConnectionToPeerInLan();
                 stpeerout->SlotLanConnecting();
        }
        break;
        case 5:
        {
                 #ifndef Q_DEBUG
                 qDebug() << "man";
                 #endif

                 QMessageBox::information(Freechat::commandLine, tr("Connecting"),
                 tr("<h1><p>ifconfig = show all your network data</p>"
                 "<p>clear = clear all data in view field</p>"
                 "<p>con -l = connecting via LAN network</p>"
                 "<p>con -w = connecting via WAN network</p>"
                 "<p>disconnect = disconnect from host</p>"
                 "<p>man = data about all commands</p>"
                 "<p>save = saving all messages</p>"
                 "<p>ip -l = show your LAN ip</p>"
                 "<p>shutdown = close programm</p></h1>"), "ok");
        }
        break;
        case 6:
        {
                #ifndef Q_DEBUG
                qDebug() << "con -w";
                #endif

                /*write hear method for connecting via WAN network*/
        }
        break;
        case 7:
        {
                #ifndef Q_DEBUG
                qDebug() << "disconnect";
                #endif

                stpeerout->disconnectFromHost();
        }
        break;
        case 8:
        {
                #ifndef Q_DEBUG
                qDebug() << "save";
                #endif

                datamanager->DataSavingIntoFile(Datasave::mainFile);
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

void Freechat::LineForTypeText_returnPressed()
{
    if(Freechat::lineForTypeText->text() == "")
        return;

    QTime time = QTime::currentTime();
    QColor color(255, 215, 0);
    Freechat::viewField->setTextColor(color);
    Freechat::viewField->setAlignment(Qt::AlignLeft);
    Freechat::bufferOfMessages += Freechat::lineForTypeText->text();
    Freechat::viewField->insertPlainText(time.toString() + "\n" + "Me:\n" + Freechat::bufferOfMessages + "\n");

    switch(Freechat::value)
    {
        case 1:
        {
            connect(Freechat::lineForTypeText, SIGNAL(editingFinished()), server, SLOT(SendResponseToClient()));

            #ifndef Q_DEBUG
            qDebug() << "Send this data to client: " << Freechat::bufferOfMessages;
            #endif
        }
        break;
        case 0:
        {
            connect(Freechat::lineForTypeText, SIGNAL(editingFinished()), stpeerout, SLOT(SlotSendToServer()));

            #ifndef Q_DEBUG
            qDebug() << "Send this data to server: " << Freechat::bufferOfMessages;
            #endif
        }
        break;
    }

    return;
}

void Freechat::WriteWanIpOfPeer_returnPressed()
{
    if(Freechat::writeWanIpOfPeer->text() == "")
        return;

    Freechat::wanIpOfPeer += Freechat::writeWanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::wanIpOfPeer;
    #endif

    return;
}

void Freechat::WriteLanIpOfPeer_returnPressed()
{
    if(Freechat::writeLanIpOfPeer->text() == "")
        return;

    Freechat::lanIpOfPeer += Freechat::writeLanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::lanIpOfPeer;
    #endif

    return;
}

void Freechat::WriteNickOfPeer_returnPressed()
{
    if(Freechat::writeNickOfPeer->text() == "")
        return;

    Freechat::nickNameOfPeer += Freechat::writeNickOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::nickNameOfPeer;
    #endif

    return;
}

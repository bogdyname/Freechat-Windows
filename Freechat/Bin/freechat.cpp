/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"

 //UI
 QTextEdit *Freechat::viewField;
 QLineEdit *Freechat::commandLine;
 QLineEdit *Freechat::writeNickOfPeer;
 QLineEdit *Freechat::writeLanIpOfPeer;
 QLineEdit *Freechat::writeWanIpOfPeer;
 QLineEdit *Freechat::lineForTypeText;
 QListWidget *Freechat::listWithNickName;

 //Global variable
 QString Freechat::bufferOfMessages;

 //CLI
 QString Freechat::command;

 //Network
 QString Freechat::yourLanIp;
 QString Freechat::yourMAC;
 QString Freechat::yourNetmask;
 QString Freechat::localHostName;
 QString Freechat::lanIpOfPeer;
 QString Freechat::wanIpOfPeer;
 unsigned short int Freechat::value;

 //Bin
 QString Freechat::nickNameOfPeer;
 QString Freechat::lanIpOfPeerBinmanager;
 QString Freechat::wanIpOfPeerBinmanager;

 //Menagers
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
        qDebug() << "Exception caught: " << exp.std::bad_alloc::what();
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

    //first layer
    ui->horizontalLayout_1->QBoxLayout::addWidget(Freechat::writeNickOfPeer);
    //ui->horizontalLayout_2->QBoxLayout::addWidget(Freechat::writeWanIpOfPeer); //TTS cos network through NAT adn WAN IP not done
    ui->horizontalLayout_3->QBoxLayout::addWidget(Freechat::writeLanIpOfPeer);

    //second layer
    ui->HLForButtons->QBoxLayout::addWidget(Freechat::commandLine);

    //third layer
    ui->horizontalLayout_5->QBoxLayout::addWidget(Freechat::listWithNickName);
    ui->horizontalLayout_5->QBoxLayout::addWidget(Freechat::viewField);

    //fourth layer
    ui->horizontalLayout_6->QBoxLayout::addWidget(Freechat::lineForTypeText);

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
        qDebug() << "Exception caught: " << exp.std::bad_alloc::what();
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
    timerOfServer->QTimer::setInterval(10000);
    QObject::connect(timerOfServer, SIGNAL(timeout()), this, SLOT(ServerStillWorking()));
    timerOfServer->QTimer::start();

    //The timer saves all data every 500000 msec (5 min)
    QTimer *timerOfAutoDataSaving = new QTimer;
    timerOfAutoDataSaving->QTimer::setInterval(500000);
    QObject::connect(timerOfAutoDataSaving, SIGNAL(timeout()), datamanager, SLOT(DataSavingViaTimer()));
    timerOfAutoDataSaving->QTimer::start();

    //Connecting UI widgets with bin code
    QTimer *timerOfBin = new QTimer;
    timerOfBin->QTimer::setInterval(500);
    timerOfBin->QTimer::start();

    //UI connection
    QObject::connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), this, SLOT(LineForTypeText_returnPressed()));
    //QObject::connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(writeWanIpOfPeer_returnPressed())); //TTS cos network through NAT adn WAN IP not done
    QObject::connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(WriteLanIpOfPeer_returnPressed()));
    QObject::connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), this, SLOT(WriteNickOfPeer_returnPressed()));

    //Connecting UI widgets with bin code
    QObject::connect(timerOfBin, SIGNAL(timeout()), binmanager, SLOT(ReadDataAboutPeer())); //data showing after 0.5 sec
    QObject::connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), binmanager, SLOT(AddPeerNick()));
    QObject::connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), binmanager, SLOT(AddPeerLan()));
    QObject::connect(Freechat::listWithNickName, SIGNAL(itemDoubleClicked(QListWidgetItem *)), binmanager, SLOT(DeleteSelectedPeer()));
    //QObject::connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerWan())); //TTS cos network through NAT adn WAN IP not done

    //Command line interface
    QObject::connect(Freechat::commandLine, SIGNAL(returnPressed()), this, SLOT(CommandLineInterface()));

    //Clear UI
    QObject::connect(Freechat::commandLine, SIGNAL(returnPressed()), Freechat::commandLine, SLOT(clear()));
    QObject::connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), Freechat::lineForTypeText, SLOT(clear()));
    //QObject::connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeWanIpOfPeer, SLOT(clear())); //TTS cos network through NAT adn WAN IP not done
    QObject::connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), Freechat::writeLanIpOfPeer, SLOT(clear()));
    QObject::connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), Freechat::writeNickOfPeer, SLOT(clear()));

    //UI style and focus
    Freechat::commandLine->QLineEdit::setPlaceholderText("Command line");
    Freechat::lineForTypeText->QLineEdit::setPlaceholderText("Type here");
    Freechat::writeNickOfPeer->QLineEdit::setPlaceholderText("Write here nickname of peer");
    Freechat::writeWanIpOfPeer->QLineEdit::setPlaceholderText("Write here WAN IP of peer");
    Freechat::writeLanIpOfPeer->QLineEdit::setPlaceholderText("Write here LAN IP of peer");

    Freechat::writeNickOfPeer->QLineEdit::setMaxLength(25);
    Freechat::writeWanIpOfPeer->QLineEdit::setMaxLength(15);
    Freechat::writeLanIpOfPeer->QLineEdit::setMaxLength(15);
    Freechat::lineForTypeText->QLineEdit::setMaxLength(1500);

    Freechat::listWithNickName->QListWidget::setMaximumHeight(500);
    Freechat::listWithNickName->QListWidget::setMaximumWidth(150);
    Freechat::listWithNickName->QListWidget::setFocusPolicy(ClickFocus);
    Freechat::writeNickOfPeer->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::writeWanIpOfPeer->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::writeLanIpOfPeer->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::lineForTypeText->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::viewField->QTextEdit::setFocusPolicy(NoFocus);
    Freechat::viewField->QTextEdit::setReadOnly(true);

    datamanager->ReadDataFromFile();// NEED TO TEST IT

    //variables for pointer of function from ConnectionF2F
    Freechat::checkNetworkConnection = ConnectionF2F::CheckNetworkAccess;
    Freechat::value = 0;

    //Global variable
    Freechat::bufferOfMessages = "";
    //CLI
    Freechat::command = "";
    //Network
    Freechat::yourLanIp = "";
    Freechat::yourMAC = "";
    Freechat::yourNetmask = "";
    Freechat::localHostName = "";
    Freechat::lanIpOfPeer = "";
    Freechat::wanIpOfPeer = "";
    //Bin
    Freechat::nickNameOfPeer = "";
    Freechat::lanIpOfPeerBinmanager = "";
    Freechat::wanIpOfPeerBinmanager = "";

    //close all QLineEdit if network shutdown
    switch((*Freechat::checkNetworkConnection)())
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
            QMessageBox::critical(Freechat::commandLine, tr("Network is down"),
                            tr("<h3>Check your network connection.</h3>"), "ok");

            //block all field without network access
            Freechat::writeNickOfPeer->QLineEdit::setReadOnly(true);
            Freechat::writeWanIpOfPeer->QLineEdit::setReadOnly(true);
            Freechat::writeLanIpOfPeer->QLineEdit::setReadOnly(true);
            Freechat::lineForTypeText->QLineEdit::setReadOnly(true);
            Freechat::commandLine->QLineEdit::setReadOnly(true);
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
    switch((*Freechat::checkNetworkConnection)())
    {
        case 101:
        {
            Freechat::status = QString("<h3>Your LAN IP address: %1</h3>").QString::arg(Freechat::yourLanIp);
            QMessageBox::information(Freechat::commandLine, tr("Network Info"),
                             Freechat::status, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(Freechat::commandLine, tr("Error"),
                             tr("<h3>Check your network connection.</h3>"), "ok");
        }
        break;
    }

    return;
}

void Freechat::NetworkFullInformation()
{
    switch((*Freechat::checkNetworkConnection)())
    {
        case 101:
        {
            Freechat::networkdata = QString("<h3><p>IP = %1</p><p>MAC = %2</p><p>Netmask = %3</p><p>localhost = %4</p></h3>")
            .QString::arg(Freechat::yourLanIp).QString::arg(Freechat::yourMAC).QString::arg(Freechat::yourNetmask).QString::arg(Freechat::localHostName);

            QMessageBox::information(Freechat::commandLine, tr("Network data"),
                            Freechat::networkdata, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(Freechat::commandLine, tr("Error"),
                             tr("<h3><p>Check your network connection.</p></h3>"), "ok");
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
                         tr("<h3><p>Connecting to peer.</h3>"), "ok");
    }
    else
    {
        QMessageBox::critical(Freechat::commandLine, tr("Connecting error"),
                         tr("<h3>Check IP of peer.</h3>"), "ok");
    }

    return;
}

void Freechat::CommandLineInterface()
{
    if(Freechat::commandLine->QLineEdit::text() == "")
        return;

    Freechat::command += Freechat::commandLine->QLineEdit::text();

    #ifndef Q_DEBUG
    qDebug() << Freechat::command;
    #endif

    switch(Freechat::commandsList.QStringList::indexOf(Freechat::command))
    {
        case 0:
        {
                #ifndef Q_DEBUG
                qDebug() << "clear";
                #endif

                Freechat::viewField->QTextEdit::clear();
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

                Freechat::NetworkFullInformation();
        }
        break;
        case 3:
        {
                #ifndef Q_DEBUG
                qDebug() << "shutdown";
                #endif

                QWidget::close();
        }
        break;
        case 4:
        {
                 #ifndef Q_DEBUG
                 qDebug() << "con -l";
                 #endif

                 Freechat::ConnectionToPeerInLan();
                 stpeerout->Peerout::SlotLanConnecting();
        }
        break;
        case 5:
        {
                 #ifndef Q_DEBUG
                 qDebug() << "man";
                 #endif

                 QMessageBox::information(Freechat::commandLine, tr("Connecting"),
                 tr("<h6><p>ifconfig = show all your network data</p>"
                 "<p>clear = clear all data in view field</p>"
                 "<p>con -l = connecting via LAN network</p>"
                 "<p>con -w = connecting via WAN network</p>"
                 "<p>disconnect = disconnect from host</p>"
                 "<p>man = data about all commands</p>"
                 "<p>save = saving all messages</p>"
                 "<p>ip -l = show your LAN ip</p>"
                 "<p>shutdown = close programm</p></h6>"), "ok");
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

                stpeerout->QAbstractSocket::disconnectFromHost();
        }
        break;
        case 8:
        {
                #ifndef Q_DEBUG
                qDebug() << "save";
                #endif

                datamanager->Datasave::DataSavingIntoFile(Datasave::mainFile);
        }
        break;
        case 9:
        {
                #ifndef Q_DEBUG
                qDebug() << "clear -n";
                #endif

                binmanager->Bin::DeleteAllPeer();
        }
        break;
        default:
        {
                 QMessageBox::critical(Freechat::commandLine, tr("Command error"),
                                tr("<h3>Command not found</h3>"), "ok");
        }
        break;
    }

    Freechat::command.QString::clear();

    return;
}

void Freechat::LineForTypeText_returnPressed()
{
    if(Freechat::lineForTypeText->QLineEdit::text() == "")
        return;

    QTime time = QTime::currentTime();
    QColor color(255, 215, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignLeft);
    Freechat::bufferOfMessages += Freechat::lineForTypeText->QLineEdit::text();
    Freechat::viewField->QTextEdit::insertPlainText(time.QTime::toString() + "\n" + "Me:\n" + Freechat::bufferOfMessages + "\n");

    switch(Freechat::value)
    {
        case 1:
        {
            QObject::connect(Freechat::lineForTypeText, SIGNAL(editingFinished()), server, SLOT(SendResponseToClient()));

            #ifndef Q_DEBUG
            qDebug() << "Send this data to client: " << Freechat::bufferOfMessages;
            #endif
        }
        break;
        case 0:
        {
            QObject::connect(Freechat::lineForTypeText, SIGNAL(editingFinished()), stpeerout, SLOT(SlotSendToServer()));

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
    if(Freechat::writeWanIpOfPeer->QLineEdit::text() == "")
        return;

    Freechat::wanIpOfPeer += Freechat::writeWanIpOfPeer->QLineEdit::text();
    Freechat::wanIpOfPeerBinmanager += Freechat::writeWanIpOfPeer->QLineEdit::text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::wanIpOfPeer;
    #endif

    return;
}

void Freechat::WriteLanIpOfPeer_returnPressed()
{
    if(Freechat::writeLanIpOfPeer->QLineEdit::text() == "")
        return;

    Freechat::lanIpOfPeer += Freechat::writeLanIpOfPeer->QLineEdit::text();
    Freechat::lanIpOfPeerBinmanager += Freechat::writeLanIpOfPeer->QLineEdit::text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::lanIpOfPeer;
    #endif

    return;
}

void Freechat::WriteNickOfPeer_returnPressed()
{
    if(Freechat::writeNickOfPeer->QLineEdit::text() == "")
        return;

    Freechat::nickNameOfPeer += Freechat::writeNickOfPeer->QLineEdit::text();
    Freechat::listWithNickName->QListWidget::addItem(Freechat::writeNickOfPeer->QLineEdit::text());

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::nickNameOfPeer;
    #endif

    return;
}

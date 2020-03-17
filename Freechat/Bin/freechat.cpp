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
 QString Freechat::lanIpOfPeer;
 QString Freechat::wanIpOfPeer;
 unsigned short int Freechat::value;

 //Bin
 QString Freechat::nickNameOfPeer;
 QString Freechat::lanIpOfPeerBinmanager;
 QString Freechat::wanIpOfPeerBinmanager;

Freechat::Freechat(QWidget *parent)
    : QDialog::QDialog(parent),
      ui(new Ui::Freechat)
{
    Freechat::ui->setupUi(this);

    QWidget::setWindowFlags(Qt::MSWindowsOwnDC);

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
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qCritical() << "Some exception caught";
        #endif
        abort();
    }

    //first layer
    Freechat::ui->verticalLayoutForLineEdit->QBoxLayout::addWidget(Freechat::writeNickOfPeer);
    //ui->verticalLayoutForLineEdit->QBoxLayout::addWidget(Freechat::writeWanIpOfPeer); //TTS cos network through NAT adn WAN IP not done
    Freechat::ui->verticalLayoutForLineEdit->QBoxLayout::addWidget(Freechat::writeLanIpOfPeer);

    //second layer
    Freechat::ui->verticalLayoutForLineEdit->QBoxLayout::addWidget(Freechat::commandLine);

    //third layer
    Freechat::ui->horizontalLayoutForTextEndNicks->QBoxLayout::addWidget(Freechat::listWithNickName);
    Freechat::ui->horizontalLayoutForTextEndNicks->QBoxLayout::addWidget(Freechat::viewField);

    //fourth layer
    Freechat::ui->horizontalLayoutForlbAndLineType->QBoxLayout::addWidget(Freechat::lineForTypeText);

    //Menagers
    Freechat::server = nullptr;
    Freechat::stpeerout = nullptr;
    Freechat::netmanager = nullptr;
    Freechat::datamanager = nullptr;
    Freechat::binmanager = nullptr;

    //Network data of peer (LAN data)
    try
    {
        Freechat::netmanager = new ConnectionF2F();
        Freechat::server = new Peerin();
        Freechat::stpeerout = new Peerout();
        Freechat::datamanager = new Datasave();
        Freechat::binmanager = new Bin();
    }
    catch(std::bad_alloc &exp)
    {
        #ifndef Q_DEBUG
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qCritical() << "Some exception caught";
        #endif
        abort();
    }

    Freechat::netmanager->ConnectionF2F::LanNetwork(
                Freechat::yourLanIp,
                Freechat::yourMAC,
                Freechat::yourNetmask,
                Freechat::localHostName);

    //For scrollbar
    Freechat::scrollbarAtBottom = true;
    Freechat::scrollbarPrevValue = 0;

    //Custom scroll bar for view field
    QScrollBar *bar = Freechat::viewField->QAbstractScrollArea::verticalScrollBar();
    bar->QAbstractSlider::setValue(bar->QScrollBar::maximum());
    scrollbarAtBottom  = (bar->QAbstractSlider::value() >= (bar->QAbstractSlider::maximum() - 4));
    scrollbarPrevValue = bar->QAbstractSlider::value();

    //Custom scroll bar for list field
    QScrollBar *barList = Freechat::listWithNickName->QAbstractScrollArea::horizontalScrollBar();
    barList->QAbstractSlider::setValue(bar->QScrollBar::maximum());
    scrollbarAtBottom  = (barList->QAbstractSlider::value() >= (barList->QAbstractSlider::maximum() - 4));
    scrollbarPrevValue = barList->QAbstractSlider::value();

    //Scroll to end every time then new message is show
    QObject::connect(Freechat::viewField, SIGNAL(textChanged()), this, SLOT(ScrollToEnd()));

    //Timer for Debug server (check server status)
    QTimer *timerOfServer = new QTimer;
    timerOfServer->QTimer::setInterval(10000);
    QObject::connect(timerOfServer, SIGNAL(timeout()), this, SLOT(ServerStillWorking()));
    timerOfServer->QTimer::start();

    //Timer for save peers every 30 seconds
    QTimer *timerOfBinsaving = new QTimer;
    timerOfBinsaving->QTimer::setInterval(30000);
    timerOfBinsaving->QTimer::start();

    //UI connection
    QObject::connect(Freechat::lineForTypeText, SIGNAL(returnPressed()), this, SLOT(LineForTypeText_returnPressed()));
    //QObject::connect(Freechat::writeWanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(writeWanIpOfPeer_returnPressed())); //TTS cos network through NAT adn WAN IP not done
    QObject::connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), this, SLOT(WriteLanIpOfPeer_returnPressed()));
    QObject::connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), this, SLOT(WriteNickOfPeer_returnPressed()));

    //Connecting UI widgets with datasave code
    QObject::connect(Freechat::listWithNickName, SIGNAL(itemClicked(QListWidgetItem *)), datamanager, SLOT(CheckoutFile()));

    //Connecting UI widgets with bin code
    QObject::connect(timerOfBinsaving, SIGNAL(timeout()), binmanager, SLOT(SavingPeers()));
    QObject::connect(Freechat::writeNickOfPeer, SIGNAL(returnPressed()), binmanager, SLOT(AddPeerNick()));
    QObject::connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), binmanager, SLOT(AddPeerLan()));
    //QObject::connect(Freechat::writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerWan())); //TTS cos network through NAT adn WAN IP not done
    QObject::connect(Freechat::listWithNickName, SIGNAL(itemDoubleClicked(QListWidgetItem *)), binmanager, SLOT(DeleteSelectedPeer()));
    QObject::connect(Freechat::listWithNickName, SIGNAL(itemClicked(QListWidgetItem *)), binmanager, SLOT(GetSelectedPeer()));

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

    Freechat::writeNickOfPeer->QLineEdit::setMaxLength(30);
    Freechat::writeWanIpOfPeer->QLineEdit::setMaxLength(15);
    Freechat::writeLanIpOfPeer->QLineEdit::setMaxLength(15);
    Freechat::lineForTypeText->QLineEdit::setMaxLength(1500);

    Freechat::listWithNickName->QListWidget::setMaximumHeight(4028);
    Freechat::listWithNickName->QListWidget::setMaximumWidth(150);
    Freechat::listWithNickName->QListWidget::setFocusPolicy(ClickFocus);
    Freechat::writeNickOfPeer->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::writeWanIpOfPeer->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::writeLanIpOfPeer->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::lineForTypeText->QLineEdit::setFocusPolicy(WheelFocus);
    Freechat::viewField->QTextEdit::setPlaceholderText("Use command 'man'");
    Freechat::viewField->QTextEdit::setAutoFormatting(QTextEdit::AutoAll);
    Freechat::viewField->QTextEdit::setFocusPolicy(NoFocus);
    Freechat::viewField->QTextEdit::setReadOnly(true);

    QTextCursor tc = Freechat::viewField->QTextEdit::textCursor();
    bool visualNavigation = tc.QTextCursor::visualNavigation();
    tc.QTextCursor::setVisualNavigation(true);
    tc.QTextCursor::movePosition(QTextCursor::End);
    tc.QTextCursor::setVisualNavigation(visualNavigation);
    Freechat::viewField->QTextEdit::setTextCursor(tc);

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
            QMessageBox::critical(Freechat::commandLine, Freechat::tr("Network is down"),
                            Freechat::tr("<h3>Check your network connection.</h3>"), "ok");

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
    delete Freechat::ui;
    delete Freechat::netmanager;
    delete Freechat::server;
    delete Freechat::stpeerout;
    delete Freechat::datamanager;
    delete Freechat::binmanager;

    return;
}

void Freechat::NetworkLanIp()
{
    switch((*Freechat::checkNetworkConnection)())
    {
        case 101:
        {
            Freechat::statusOfNetwork = QString("<h3>Your LAN IP address: %1</h3>").QString::arg(Freechat::yourLanIp);
            QMessageBox::information(Freechat::commandLine, Freechat::tr("Network Info"),
                             Freechat::statusOfNetwork, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(Freechat::commandLine, Freechat::tr("Error"),
                             Freechat::tr("<h3>Check your network connection.</h3>"), "ok");
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

            QMessageBox::information(Freechat::commandLine, Freechat::tr("Network data"),
                            Freechat::networkdata, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(Freechat::commandLine, Freechat::tr("Error"),
                             Freechat::tr("<h3><p>Check your network connection.</p></h3>"), "ok");
        }
        break;
    }

    return;
}

void Freechat::ConnectionToPeerInLan()
{
    if(Freechat::lanIpOfPeer != "")
    {
        QMessageBox::information(Freechat::commandLine, Freechat::tr("Connecting"),
                         Freechat::tr("<h3><p>Connecting to peer.</h3>"), "ok");
    }
    else
    {
        QMessageBox::critical(Freechat::commandLine, Freechat::tr("Connecting error"),
                         Freechat::tr("<h3>Check IP of peer.</h3>"), "ok");
    }

    return;
}

void Freechat::ScrollToEnd()
{
    if(Freechat::scrollbarAtBottom)
        Freechat::viewField->QTextEdit::ensureCursorVisible();
    else
        Freechat::viewField->QTextEdit::verticalScrollBar()->QAbstractSlider::setValue(Freechat::scrollbarPrevValue);

    return;
}

void Freechat::ServerStillWorking()
{
    if(Freechat::server != nullptr)
    {
        #ifndef Q_DEBUG
        qDebug() << "Server still working";
        #endif
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "Server stoped!" ;
        #endif
    }

    return;
}

void Freechat::LineForTypeText_returnPressed()
{
    if(Freechat::lineForTypeText->QLineEdit::text() == "")
        return;

    QTextCursor tc = Freechat::viewField->QTextEdit::textCursor();
    bool visualNavigation = tc.QTextCursor::visualNavigation();
    tc.QTextCursor::setVisualNavigation(true);
    tc.QTextCursor::movePosition(QTextCursor::End);
    tc.QTextCursor::setVisualNavigation(visualNavigation);

    if(Freechat::viewField->QTextEdit::textCursor() != tc)
        Freechat::viewField->QTextEdit::setTextCursor(tc);

    const QTime time = QTime::currentTime();
    const QColor color(255, 215, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignLeft);
    Freechat::bufferOfMessages += Freechat::lineForTypeText->QLineEdit::text();
    Freechat::viewField->QTextEdit::insertPlainText(time.QTime::toString() + "\n" + "Me:\n" + Freechat::bufferOfMessages + "\n");

    switch(Freechat::value)
    {
        case 1:
        {
            QObject::connect(Freechat::lineForTypeText, SIGNAL(editingFinished()), server, SLOT(SendMessages()));

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

    Freechat::nickNameOfPeer.QString::clear();
    Freechat::nickNameOfPeer += Freechat::writeNickOfPeer->QLineEdit::text();
    Freechat::listWithNickName->QListWidget::addItem(Freechat::writeNickOfPeer->QLineEdit::text());

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::nickNameOfPeer;
    #endif

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
                 Freechat::stpeerout->Peerout::SlotLanConnecting();
        }
        break;
        case 5:
        {
                 #ifndef Q_DEBUG
                 qDebug() << "man";
                 #endif

                 QMessageBox::information(Freechat::commandLine, Freechat::tr("Connecting"),
                 tr("<h6><p>ifconfig = show all your network data</p>"
                 "<p>clear = clear all data in view field</p>"
                 "<p>con -l = connecting via LAN network</p>"
                 "<p>con -w = connecting via WAN network</p>"
                 "<p>disconnect = disconnect from host</p>"
                 "<p>man = data about all commands</p>"
                 "<p>save = saving all messages</p>"
                 "<p>ip -l = show your LAN ip</p>"
                 "<p>shutdown = close programm</p>"
                 "<p>clear -n = clear all contacts</p>"
                 "<p>save -n = save all contact into file</p>"
                 "<p>hide -n = hide list contacts</p>"
                 "<p>show -n = show list contacts</p>"
                 "<p>hide -a = hide all but without main fields</p>"
                 "<p>show -a = show all fields</p>"
                 "<p>hide -i = hide interface</p>"
                 "<p>show -i = show interface</p></h6>"), "ok");
        }
        break;
        case 6:
        {
                #ifndef Q_DEBUG
                qDebug() << "con -w";
                #endif

                Freechat::stpeerout->SlotWanConnecting();
        }
        break;
        case 7:
        {
                #ifndef Q_DEBUG
                qDebug() << "disconnect";
                #endif

                Freechat::stpeerout->QAbstractSocket::disconnectFromHost();

                switch(Freechat::value)
                {
                    case 1:
                    {
                        server->Peerin::DisconnectPeer();
                    }
                    break;
                    case 0:
                    {
                        Freechat::stpeerout->Peerout::SlotDisconnectPeer();
                    }
                    break;
                }
        }
        break;
        case 8:
        {
                #ifndef Q_DEBUG
                qDebug() << "save";
                #endif

                Freechat::datamanager->Datasave::SavingData();
        }
        break;
        case 9:
        {
                #ifndef Q_DEBUG
                qDebug() << "clear -n";
                #endif

                Freechat::binmanager->Bin::DeleteAllPeer();
        }
        break;
        case 10:
        {
                #ifndef Q_DEBUG
                qDebug() << "save -n";
                #endif

                Freechat::binmanager->Bin::SavingPeers();
        }
        break;
        case 11:
        {
                #ifndef Q_DEBUG
                qDebug() << "hide -n";
                #endif

                Freechat::listWithNickName->QWidget::hide();
        }
        break;
        case 12:
        {
                #ifndef Q_DEBUG
                qDebug() << "show -n";
                #endif

                Freechat::listWithNickName->QWidget::show();
        }
        break;
        case 13:
        {
                #ifndef Q_DEBUG
                qDebug() << "hide -a";
                #endif

                Freechat::listWithNickName->QWidget::hide();
                Freechat::writeNickOfPeer->QWidget::hide();
                Freechat::writeLanIpOfPeer->QWidget::hide();
                //Freechat::writeWanIpOfPeer->QWidget::hide();
        }
        break;
        case 14:
        {
                #ifndef Q_DEBUG
                qDebug() << "show -a";
                #endif

                Freechat::listWithNickName->QWidget::show();
                Freechat::writeNickOfPeer->QWidget::show();
                Freechat::writeLanIpOfPeer->QWidget::show();
                //Freechat::writeWanIpOfPeer->QWidget::show();
        }
        break;
        case 15:
        {
                #ifndef Q_DEBUG
                qDebug() << "hide -i";
                #endif

                Freechat::writeNickOfPeer->QWidget::hide();
                Freechat::writeLanIpOfPeer->QWidget::hide();
                //Freechat::writeWanIpOfPeer->QWidget::hide();
        }
        break;
        case 16:
        {
                #ifndef Q_DEBUG
                qDebug() << "show -i";
                #endif

                Freechat::writeNickOfPeer->QWidget::show();
                Freechat::writeLanIpOfPeer->QWidget::show();
                //Freechat::writeWanIpOfPeer->QWidget::show();
        }
        break;
        default:
        {
                 QMessageBox::critical(Freechat::commandLine, Freechat::tr("Command error"),
                                Freechat::tr("<h3>Command not found</h3>"), "ok");
        }
        break;
    }

    Freechat::command.QString::clear();

    return;
}

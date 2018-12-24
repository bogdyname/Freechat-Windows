#include "dialog.h"

Dialog::Dialog(QWidget *parent) :QDialog(parent),ui(new Ui::Dialog)
{
    _sok = new QTcpSocket(this);
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}

void Dialog::on_pbConnect_clicked()
{
    _sok->connectToHost(ui->leHost->text(), ui->sbPort->value());
}

void Dialog::onSokConnected()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << (quint8)MyClient::comAutchReq << ui->leName->text();
    _name = ui->leName->text();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Dialog::onSokReadyRead()
{
    QDataStream in(_sok);
    if (_blockSize == 0) {
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> _blockSize;
    }
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        _blockSize = 0;
    quint8 command;
    in >> command;

    switch (command)
    {
        case MyClient::comUsersOnline:
        {
            QString users;
            in >> users;
            if (users == "")
                return;
            QStringList l =  users.split(",");
            ui->lwUsers->addItems(l);
        }
        break;
        case MyClient::comPublicServerMessage:
        {
            QString message;
            in >> message;
            AddToLog("[PublicServerMessage]: "+message, Qt::red);
        }
        ...
    }
}

Dialog::Dialog(QWidget *parent) :QDialog(parent), ui(new Ui::Dialog)
{
    _serv = new MyServer(this, this);
    connect(this, SIGNAL(messageFromGui(QString,QStringList)), _serv, SLOT(onMessageFromGui(QString,QStringList)));
    ...
    if (_serv->doStartServer(QHostAddress::LocalHost, 1234))
    {...}
    else
    {...}
}

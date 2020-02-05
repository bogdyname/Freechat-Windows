/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"

Peerin::Peerin(QObject *parent)
    : QTcpServer(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));
    connect(clientSocket1, SIGNAL(disconnected()), this, SLOT(clearValue()));

    if (server->listen(QHostAddress::Any, 6000))
    {
        #ifndef Q_DEBUG
        qDebug() << "Server started!";
        #endif

    }
    else
    {
        #ifndef Q_DEBUG
        qDebug() << "Server not started: " << errorString();
        #endif

        server->close();
    }
}

Peerin::~Peerin()
{
    delete server;
}

void Peerin::clearValue()
{
    #ifndef Q_DEBUG
    qDebug() << "Value was cleared!";
    #endif

    Freechat::value = 0;

    return;
}

void Peerin::SlotNewConnection()
{
    server->setMaxPendingConnections(1);
    clientSocket1 = server->nextPendingConnection();
    Freechat::value = 1;

    #ifndef Q_DEBUG
    qDebug() << "Value already: " << Freechat::value;
    #endif

    connect(clientSocket1, SIGNAL(disconnected()), clientSocket1, SLOT(deleteLater()));
    connect(clientSocket1, SIGNAL(readyRead()), this, SLOT(SlotReadClient()));

    QString connect = "Connected to peerout\n";
    SendResponseToClient(clientSocket1, connect);

    return;
}

void Peerin::SlotReadClient()
{
    clientSocket2 = (QTcpSocket*)sender();
    QDataStream in(clientSocket2);

    in.setVersion(QDataStream::Qt_5_12);

    for(;;)
    {
        if(!nextBlockSize)
        {
            if((clientSocket2->bytesAvailable()) < (sizeof (quint16)))
            {
                break;
            }
            else
            {
                /*clear code*/
            }

            in >> nextBlockSize;
        }
        else
        {
            /*clear code*/
        }

        if((clientSocket2->bytesAvailable()) < nextBlockSize)
        {
            break;
        }
        else
        {
            /*clear code*/
        }

        QTime time = QTime::currentTime();
        QString strOfTimeWithData;
        in >> time >> strOfTimeWithData;

        QString strMessage = "Respons from peer:" + time.toString() + strOfTimeWithData + "\n";

        Freechat::viewField->append(strMessage);
        nextBlockSize = 0;

        QString respons = "Passed to peer\n";//every time then message sent
        SendResponseToClient(clientSocket2, respons);
    }

    return;
}

void Peerin::SendResponseToClient(QTcpSocket *socket, QString &messages)
{
    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << quint16(0) << messages;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof (quint16));

    socket->write(block);

    Freechat::viewField->insertPlainText(messages);
    messages.clear();

    return;
}

void Peerin::SendToClientFlush()
{
    SendResponseToClient(clientSocket2, Freechat::bufferOfMessages);
    Freechat::bufferOfMessages.clear();

    return;
}

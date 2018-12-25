#ifndef DIALOG_H
#define DIALOG_H

#include <QTcpServer>

class myserver
{
public:
    myserver();
};

class MyServer : public QTcpServer
{
public:
    bool doStartServer(QHostAddress addr, qint16 port);
    void doSendToAllUserJoin(QString name);
    void doSendToAllUserLeft(QString name);
    void doSendToAllMessage(QString message, QString fromUsername);
    void doSendToAllServerMessage(QString message);
    void doSendServerMessageToUsers(QString message, const QStringList &users);
    void doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername);
    QStringList getUsersOnline() const;
    bool isNameValid(QString name) const;
    bool isNameUsed(QString name) const;
protected:
    void incomingConnection(int handle);
private:
    QList<MyClient *> _clients; 
    QWidget *_widget;
};

#endif // DIALOG_H

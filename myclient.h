#ifndef MYCLIENT_H
#define MYCLIENT_H
#include <QString>
#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>

class MyClient : public QObject
{
    friend class MyServer;
public:
    static const QString constNameUnknown;
    static const quint8 comAutchReq = 1;
    static const quint8 comUsersOnline = 2;
    ...
    static const quint8 comErrNameUsed = 202;

    void setName(QString name) {_name = name;}
    QString getName() const {return _name;}
    bool getAutched() const {return _isAutched;}
    void doSendCommand(quint8 comm) const;
    void doSendUsersOnline() const;
signals:
    void addUserToGui(QString name);
    void removeUserFromGui(QString name);
    void messageToGui(QString message, QString from, const QStringList &users);
    void removeUser(MyClient *client);
private slots:
    void onConnect();
    void onDisconnect();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError) const;
private:
    QTcpSocket *_sok;
    MyServer *_serv;
    quint16 _blockSize;
    QString _name;
    bool _isAutched;
};

#endif // MYCLIENT_H

#ifndef NETWORKCODE_H
#define NETWORKCODE_H
#include <QDialog>
#include <QTcpSocket>

class networkcode
{
public:
    networkcode();
};

class Dialog : public QDialog
{
private slots:
    void onSokConnected();
    void onSokDisconnected();
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket *_sok;
    quint16 _blockSize;
    QString _name;
};

#endif // NETWORKCODE_H

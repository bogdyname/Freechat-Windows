/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QHostAddress>
#include <QJsonObject>
#include <QIODevice>
#include <QHostInfo>
#include <QSaveFile>
#include <QDateTime>
#include <QString>
#include <QFile>

#ifndef BIN_H
#define BIN_H
class Bin : public QFile
{
    Q_OBJECT

public:
    ~Bin();
    Bin(QWidget *parent = nullptr);

public slots:
    inline void ReadingIpAddress(QFile &fileWithIP);
    inline void ReadingMACAddress(QFile &fileWithMac);

private:
    QString *buffer = nullptr;

protected:
    inline void MakeFileWithIp();
    inline void MakeFileWithMac();
    void GetIpAddressFromWAN(QString &textWithIPAddres);
    inline void GetMacAddress(QString &textWithMacAddresOfUser);
};
#endif

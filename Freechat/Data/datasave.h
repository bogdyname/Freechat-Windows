/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

class Datasave : public QFile
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

public:
    static QFile mainFile;

public:
    Datasave();
    ~Datasave();

public:
    void DataSavingIntoFile(QFile &file);

public slots:
    void CheckoutFile();
    void ReadDataFromFile();
    void DataSavingViaTimer();
    void CreatFileForNewPeer();
};
#endif

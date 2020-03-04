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

private:
    static QString nameOfDatasaveFile;
    static QString nicknameForDatasave;
    QFile *datasave;

public:
    Datasave();
    ~Datasave();

public:
    void SavingData();

private:
    void DataSavingIntoFile(QFile *pointerOnFile);

public slots:
    void CheckoutFile();
    void ReadDataFromFile();
    void DataSavingViaTimer();
};
#endif

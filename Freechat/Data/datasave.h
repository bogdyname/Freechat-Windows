/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include "Data/cryptography.h"
#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

class Datasave : public QFile
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0")

private:
    QString nameOfDatasaveFile;
    QString nicknameForDatasave;
    QFile *datasave;

public:
    Datasave();
    ~Datasave();

public slots:
    void SavingData();
    void CheckoutFile();
    void ReadDataFromFile();

private:
    void DataSavingIntoFile(QFile *pointerOnFile);
};
#endif

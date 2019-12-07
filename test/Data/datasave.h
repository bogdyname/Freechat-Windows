/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include "Bin/freechat.h"
#include "Network/connectionf2f.h"
#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

//CHECK THIS SIDE
//need to refactoring all datasave code
//--- first step: check all methods
//--- second step: refactoring, delete, create methods for this class
//--- third step: connect this code with UI
//P.S - create datasave via timer (QTimer as every 5 min)

class Datasave : public QFile,
private ConnectionF2F, private Freechat
{
    Q_OBJECT

public:
    QString *bufferNickname = nullptr; //check this side, because pointer here it is bad idea

private:
    QByteArray *buffer = nullptr;
    QStorageInfo storage = QStorageInfo::root();

public:
    ~Datasave();
    Datasave(Freechat *parent = nullptr);//refactroing it
    Datasave(QFile &fileWithData, QFile &fileWithDataForBackup);
    //need to thinks about second constructor because it is not need at all

signals:
    void CheckYourMemorySize();
    void ChooseFileWithData(QFile &fileWithData);
    void ReadFileForViewMessages(QFile &file, QString &nickname);

private slots:
    inline void DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup);
    void RunBackupFiles(QFile &fileWithData, QFile &fileWithDataForBackup);
    inline void ReadFile(QFile &fileWithData);
    void OpenFile(QFile &fileWithData);

private:
    void RSAMODULE(QFile &fileWithData);
    inline bool CheckNicknameForSaveFile(QString &nickname);
};
#endif

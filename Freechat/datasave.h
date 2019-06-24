/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "ui_freechat.h"
#include "username.h"
#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

#ifndef DATASAVE_H
#define DATASAVE_H
class Username;
class Freechat;

class Datasave : public Username
{
    Q_OBJECT

private:
    QTimer *runTimer = nullptr;
    QByteArray *buffer = nullptr;

    QStorageInfo storage = QStorageInfo::root();

public:
    ~Datasave();
    Datasave(QObject *parent = nullptr);
    Datasave(Datasave &&MoveSource, QFile &fileWithDataForBackup);
    Datasave(QFile &fileWithData, QFile &fileWithDataForBackup);

signals:
    void SaveDataFileAs();
    void CheckYourMemorySize();
    inline void RunTimeIsOver();
    void ReadFileForViewMessages();
    void CheckUsernameForSaveFile();

public slots:
    inline void DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup);
    void RunBackupFiles(QFile &fileWithData, QFile &fileWithDataForBackup);
    inline void ReadFile(QFile &fileWithData);

private:
    void RSAMODULE();
};

#endif // DATASAVE_H

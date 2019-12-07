/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Data/datasave.h"

Datasave::Datasave(Freechat *parent)
    : QFile(parent)
{
   bufferNickname = new QString;
   bufferNickname = &Freechat::nickNameOfPeer;

   //CAHNGE THIS CODE FOR MAKE ONE OBJECT WHILE CODE IS RUNNING

   QString fname = /*need to past nickname of peer here*/ + ".txt";

   QFile file(fname);

   if(buffer != nullptr)
   {
       buffer = new QByteArray;

       if((file.exists()) && (file.isOpen()))
       {
            if(file.open(WriteOnly))
            {
                QTextStream writeStream(&file);
                writeStream << *bufferNickname;
                writeStream << //Data from text field NOT variables bufferOfMessages
                file.write(*buffer);
                file.close();
            }
            else
            {
                file.flush();
            }
        }
        else
        {
            file.flush();
        }
   }

   QDir().mkdir(QApplication::applicationDirPath()+"/../.savedata");
}

Datasave::Datasave(QFile &fileWithData, QFile &fileWithDataForBackup)
{
    if(buffer != nullptr)
    {
        buffer = new QByteArray;

        if((fileWithData.open(ReadOnly)) && (fileWithDataForBackup.open(WriteOnly)))
        {
            *buffer = fileWithData.readAll();
            fileWithDataForBackup.write(*buffer);
            fileWithData.close();
            fileWithDataForBackup.close();
        }
        else
        {
            fileWithData.flush();
            fileWithDataForBackup.flush();
        }
    }
    else
    {
        fileWithData.flush();
        fileWithDataForBackup.flush();
    }
}

Datasave::~Datasave()
{
    delete buffer;
}

inline bool Datasave::CheckNicknameForSaveFile(QString &nickname)
{
    //need to add more code for connecting UI with data save
    // code as still checking by true code via nickname

    if(*bufferNickname == nickname)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Datasave::CheckYourMemorySize()
{
    #ifndef Q_DEBUG
    qDebug() << storage.rootPath();
    #endif

    if (storage.isReadOnly())
    {
        #ifndef Q_DEBUG
        qDebug() << "isReadOnly:" << storage.isReadOnly();
        #endif
    }
    else
    {
        /*clear code*/
    }

    #ifndef Q_DEBUG
    qDebug() << "name:" << storage.name();
    qDebug() << "fileSystemType:" << storage.fileSystemType();
    qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
    qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";
    #endif

    if (storage.bytesFree() == 1)
    {
        QMessageBox::critical(this, tr("WARNING!"),
                        tr("<h1>Check your memory size!</h1>"), "ok");
    }
    else
    {
        /*clear code*/
    }

    return;
}

inline void Datasave::DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup)
{
    fileWithData.remove();
    fileWithDataForBackup.remove();

    return;
}

void Datasave::ReadFileForViewMessages(QFile &file, QString &nickname)
{
    ReadFile(file);

    //nickname will be useing via Freechat::OBJECT

    switch(CheckNicknameForSaveFile(*bufferNickname))
    {
    case true:
        {
            /*
                need to pass buffer into bufferOfMessages
                for open file line by line in
                field for view messages
            */
        }
        break;
    case false:
        {
            file.flush();
        }
        break;
    }

    return;
}

inline void Datasave::ReadFile(QFile &fileWithData)
{
    if ((fileWithData.exists()) && (fileWithData.open(ReadOnly)))
    {
        fileWithData.readAll();
        fileWithData.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Data/datasave.h"
#include "Bin/freechat.h"

QFile Datasave::mainFile;

Datasave::Datasave()
{


    return;
}

Datasave::~Datasave()
{

    return;
}


void Datasave::DataSavingIntoFile(QFile &file)
{
    QTextStream out(&file);

    if(!file.QFile::exists())
    {
        file.QFile::link(Freechat::nickNameOfPeer + "ßß");
    }
    else if (file.QIODevice::open(QIODevice::WriteOnly))
    {
        while(Freechat::viewField)
        {
            file.QIODevice::write("");
            file.QFileDevice::close();
        }
    }

    return;
}

void Datasave::CheckoutFile()
{

    return;
}

void Datasave::DataSavingViaTimer()
{

    return;
}

void Datasave::CreatFileForNewPeer()
{

    return;
}

void Datasave::ReadDataFromFile()
{
    QFile file("ßß");
    //file.link(Freechat::nickNameOfPeer + "ßß");

    if ((file.QFile::exists())&&(file.QIODevice::open(QIODevice::ReadOnly)))
    {
        QString str = "";

        while(!file.QFileDevice::atEnd())
        {
            str += file.QIODevice::readLine();
            Freechat::viewField->QTextEdit::setText(str);
        }

        file.QFileDevice::close();
    }

    return;
}


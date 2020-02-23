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

    if(!file.exists())
    {
        file.link(Freechat::nickNameOfPeer + "ßß");
    }
    else if (file.open(QIODevice::WriteOnly))
    {
        while(Freechat::viewField)
        {
            file.write("");
            file.close();
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

    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str = "";

        while(!file.atEnd())
        {
            str += file.readLine();
            Freechat::viewField->setText(str);
        }

        file.close();
    }

    return;
}


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
        while()
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

void ReadDataFromFile()
{
    QFile file;
    QTextStream in(&file);

    file.link(Freechat::nickNameOfPeer + "ßß");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
              return;

    while (!in.atEnd())
    {

    }

    return;
}


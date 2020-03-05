/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Data/datasave.h"
#include "Bin/freechat.h"

 QString Datasave::nameOfDatasaveFile;
 QString Datasave::nicknameForDatasave;

Datasave::Datasave()
{
    Datasave::nameOfDatasaveFile = "";
    Datasave::nicknameForDatasave = "";
    Datasave::datasave = nullptr;

    return;
}

Datasave::~Datasave()
{

    return;
}

void Datasave::SavingData()
{
    Datasave::DataSavingIntoFile(Datasave::datasave);
    Datasave::datasave = nullptr;

    #ifndef Q_DEBUG
    qDebug() << "Data had saved!";
    #endif

    return;
}

void Datasave::DataSavingIntoFile(QFile *pointerOnFile)
{
    if((Datasave::nameOfDatasaveFile == "") && (Datasave::nicknameForDatasave == ""))
    {
        #ifndef Q_DEBUG
        qDebug() << "Can not save file";
        #endif

        return;
    }

    QString str = pointerOnFile->QFile::fileName();

    QDateTime correntdate = QDateTime::currentDateTime();

    QColor color(255, 153, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText(correntdate.QDateTime::toString("ddd MMMM d yy") + "\n");

    if(pointerOnFile->QFile::open(QIODevice::WriteOnly | QIODevice::Text))
    {
        #ifndef Q_DEBUG
        qDebug() << "Datasave: file is opened";
        #endif

        QTextStream stream(pointerOnFile);
        stream << Freechat::viewField->toHtml() << '\n';
    }
    else
    {
        #ifndef Q_DEBUG
        qDebug() << "error opening output file!";
        #endif
    }

    Datasave::nameOfDatasaveFile.QString::clear();
    Datasave::nicknameForDatasave.QString::clear();
    pointerOnFile->QFileDevice::close();

    return;
}

void Datasave::CheckoutFile()
{   
    Datasave::nameOfDatasaveFile.QString::clear();
    Datasave::nicknameForDatasave.QString::clear();
    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        int number = Freechat::listWithNickName->QListWidget::row(item);

        Datasave::nicknameForDatasave += Bin::listWithNickName.QList::value(number);
        Datasave::nameOfDatasaveFile += Bin::listWithNickName.QList::value(number) + ".bin";
    }

    Datasave::datasave = new QFile(Datasave::nicknameForDatasave + ".bin");
    Datasave::datasave->QFileDevice::close();

    Datasave::ReadDataFromFile();

    #ifndef Q_DEBUG
    qDebug() << "Data save name: " << Datasave::nameOfDatasaveFile;
    qDebug() << "Nickname for data save name: " << Datasave::nicknameForDatasave;
    #endif

    return;
}

void Datasave::DataSavingViaTimer()
{

    return;
}

void Datasave::ReadDataFromFile()
{
    Freechat::viewField->QTextEdit::clear();

    QFile file(Datasave::nicknameForDatasave + ".bin");

    if (!Datasave::datasave->QFile::open(QFile::ReadOnly))
    {
      #ifndef Q_DEBUG
      qDebug() << "error opening output file";
      #endif
    }
    else
    {
      QString messages = "";
      QTextStream stream(Datasave::datasave);
      messages += stream.readAll();

      #ifndef Q_DEBUG
      qDebug() << "Bin: file is opened";
      #endif

      Freechat::viewField->insertHtml(messages + "\n");
    }

    Datasave::datasave->QFileDevice::close();


    return;
}


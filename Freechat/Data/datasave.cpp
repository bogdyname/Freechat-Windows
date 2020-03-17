/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Data/datasave.h"
#include "Bin/freechat.h"

 static Cryptography cryptomanager(Q_UINT64_C(0x0c2ad4a4acb9f023));

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

    #ifndef Q_DEBUG
    qDebug() << "Data had saved!";
    #endif

    return;
}

void Datasave::CheckoutFile()
{
    Datasave::nameOfDatasaveFile.QString::clear();
    Datasave::nicknameForDatasave.QString::clear();
    QList<QListWidgetItem*> items = Freechat::listWithNickName->QListWidget::selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        unsigned short number = Freechat::listWithNickName->QListWidget::row(item);

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

void Datasave::ReadDataFromFile()
{
    Freechat::viewField->QTextEdit::clear();

    QFile file(Datasave::nicknameForDatasave + ".bin");

    cryptomanager.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    cryptomanager.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

    if (!Datasave::datasave->QFile::open(QFile::ReadOnly))
    {
      #ifndef Q_DEBUG
      qCritical() << "error opening output file";
      #endif
    }
    else
    {
      QTextStream stream(Datasave::datasave);
      QString cryptomessages = "";
      cryptomessages = stream.QTextStream::readAll();
      QString messages = cryptomanager.Cryptography::decryptToString(cryptomessages);

      if (!(cryptomanager.Cryptography::lastError() == Cryptography::ErrorNoError))
      {
          #ifndef Q_DEBUG
          qCritical() << "error decrypt output file";
          #endif

          const QColor color(156, 0, 0);
          Freechat::viewField->QTextEdit::setTextColor(color);
          Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
          Freechat::viewField->QTextEdit::insertPlainText("error decrypt output file \n");

          return;
      }

      #ifndef Q_DEBUG
      qDebug() << "Bin: file is opened";
      #endif

      Freechat::viewField->QTextEdit::insertHtml(messages + "\n");
    }

    Datasave::datasave->QFileDevice::close();

    return;
}

void Datasave::DataSavingIntoFile(QFile *pointerOnFile)
{
    if((Datasave::nameOfDatasaveFile == "") && (Datasave::nicknameForDatasave == ""))
    {
        #ifndef Q_DEBUG
        qCritical() << "Can not save file";
        #endif

        return;
    }

    cryptomanager.Cryptography::setCompressionMode(Cryptography::CompressionAuto);
    cryptomanager.Cryptography::setIntegrityProtectionMode(Cryptography::ProtectionHash);

    QString str = pointerOnFile->QFile::fileName();

    QDateTime correntdate = QDateTime::currentDateTime();

    QTextStream stream(pointerOnFile);

    QTextCursor tc = Freechat::viewField->textCursor();
    bool visualNavigation = tc.visualNavigation();
    tc.setVisualNavigation(true);
    tc.movePosition(QTextCursor::End);
    tc.setVisualNavigation(visualNavigation);

    if(Freechat::viewField->textCursor() != tc)
        Freechat::viewField->setTextCursor(tc);

    const QColor color(255, 153, 0);
    Freechat::viewField->QTextEdit::setTextColor(color);
    Freechat::viewField->QTextEdit::setAlignment(Qt::AlignCenter);
    Freechat::viewField->QTextEdit::insertPlainText(correntdate.QDateTime::toString("ddd MMMM d yy") + "\n");

    if(pointerOnFile->QFile::open(QIODevice::WriteOnly | QIODevice::Text))
    {
        #ifndef Q_DEBUG
        qDebug() << "Datasave: file is opened";
        #endif

        QString messages = Freechat::viewField->QTextEdit::toHtml() + '\n';
        QString cypherText = cryptomanager.Cryptography::encryptToString(messages);

        if (cryptomanager.Cryptography::lastError() == Cryptography::ErrorNoError)
            stream << cypherText;
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "error opening output file!";
        #endif
    }

    pointerOnFile->QFileDevice::close();

    return;
}


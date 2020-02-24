/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile *file = new QFile(":/source/source/style.css");
    file->QIODevice::open(QFile::ReadOnly);
    app.QApplication::setStyleSheet(file->QIODevice::readAll());

    int id = QFontDatabase::addApplicationFont(":/source/source/LetterGothicStd.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace("LetterGothicStd", 12, QFont::Normal);
    app.QApplication::setFont(monospace);

    // ui
    Freechat window;
    window.QWidget::show();

    return app.QApplication::exec();
}

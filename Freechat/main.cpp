/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/source/source/style.css");
    file.QFile::open(QFile::ReadOnly);
    const QString style = QLatin1String(file.QFile::readAll());
    app.QApplication::setStyleSheet(style);

    int id = QFontDatabase::addApplicationFont(":/source/source/LetterGothicStd.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    const QFont monospace("LetterGothicStd", 12, QFont::Normal);
    app.QApplication::setFont(monospace);

    // ui
    Freechat window;
    window.QWidget::show();

    return app.QApplication::exec();
}

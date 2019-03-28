/*
***Copyright (C) 2019 Softwater Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QTextStream>
#include <QDataStream>
#include <QIODevice>
#include <QFile>

class Datasave : public QFile
{
    Q_OBJECT

public:
    Datasave();
};

#endif // DATASAVE_H

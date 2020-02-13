/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

class Datasave : public QFile
{
    Q_OBJECT

public:
    Datasave();
    ~Datasave();
};
#endif

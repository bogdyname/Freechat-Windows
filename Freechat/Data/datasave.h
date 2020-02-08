/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include "Bin/freechat.h"
#include "Network/connectionf2f.h"
#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

class Datasave : public QFile,
private ConnectionF2F, private Freechat
{
    Q_OBJECT

public:
    Datasave();
    ~Datasave();
};
#endif

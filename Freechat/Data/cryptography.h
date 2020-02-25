/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <QFile>

class Cryptography : public QFile
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

public:
    Cryptography();
};
#endif

/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "connection.h"

Connection::Connection(QObject *parent)
    : QSctpSocket(parent), write(this)
{

}

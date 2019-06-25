/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "connectionf2f.h"
#include "Bin/bin.h"

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{

}

ConnectionF2F::~ConnectionF2F()
{

}

Client::Client(QObject *parent)
    : ConnectionF2F(parent)
{

}

Client::~Client()
{

}

Host::Host(QObject *parent)
    :ConnectionF2F(parent)
{

}

Host::~Host()
{

}

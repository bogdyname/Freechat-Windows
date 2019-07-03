/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QtWidgets>
#include "Bin/freechat.h"

using namespace Qt;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineForTypeText->setFocusPolicy(StrongFocus);
    textFieldForViewMessages->setFocusPolicy(NoFocus);
    textFieldForViewMessages->setReadOnly(true);
    listWithNicknameOfUser->setFocusPolicy(NoFocus);
    listViewWithNetworkData->setReadOnly(true);
}

/********************************************************************************
** Form generated from reading UI file 'freechat.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREECHAT_H
#define UI_FREECHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Freechat
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Freechat)
    {
        if (Freechat->objectName().isEmpty())
            Freechat->setObjectName(QString::fromUtf8("Freechat"));
        Freechat->resize(400, 300);
        menuBar = new QMenuBar(Freechat);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Freechat->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Freechat);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Freechat->addToolBar(mainToolBar);
        centralWidget = new QWidget(Freechat);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Freechat->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Freechat);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Freechat->setStatusBar(statusBar);

        retranslateUi(Freechat);

        QMetaObject::connectSlotsByName(Freechat);
    } // setupUi

    void retranslateUi(QMainWindow *Freechat)
    {
        Freechat->setWindowTitle(QApplication::translate("Freechat", "Freechat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Freechat: public Ui_Freechat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREECHAT_H

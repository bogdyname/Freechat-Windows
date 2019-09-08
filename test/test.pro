#-------------------------------------------------
#
# Project created by QtCreator 2019-07-27T18:59:54
#
#-------------------------------------------------

QT       += gui
QT       += svg
QT       += network
QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 5.4): QT += widgets

TARGET = test
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        connectionf2f.cpp \
        peerin.cpp \
        main.cpp \
        freechat.cpp

HEADERS += \
        connectionf2f.h \
        freechat.h \
        peerin.h

FORMS += \
        freechat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

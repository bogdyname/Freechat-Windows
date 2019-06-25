#---------------------------------
#Freechat (decentralized chat)
#Freechat via C++ & Qt
#Debugger(Qt 5.12.0 for UWP 64bit (MSVC 2015)2)
#Copyleft (C) 2019 Softwater, Inc.
#---------------------------------

QT       += gui
QT       += svg
QT       += widgets
QT       += network
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5.4): QT += widgets

TARGET = Freechat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17

SOURCES += \
        connectionf2f.cpp \
        main.cpp \
        freechat.cpp \
        datasave.cpp \
        username.cpp

HEADERS += \
        connectionf2f.h \
        freechat.h \
        datasave.h \
        username.h

FORMS += \
        freechat.ui \
        username.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

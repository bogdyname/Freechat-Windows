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
CONFIG += qt

SOURCES += \
        Bin/bin.cpp \
        Bin/networksettings.cpp \
        Bin/networksettings.cpp \
        Network/connectionf2f.cpp \
        Network/cryptography.cpp \
        Network/cryptography.cpp \
        Network/firewall.cpp \
        Network/firewall.cpp \
        Network/peerin.cpp \
        Network/peerin.cpp \
        Network/peerout.cpp \
        Network/peerout.cpp \
        main.cpp \
        Bin/freechat.cpp \
        Data/datasave.cpp

HEADERS += \
        Bin/bin.h \
        Bin/networksettings.h \
        Bin/networksettings.h \
        Network/connectionf2f.h \
        Bin/freechat.h \
        Data/datasave.h \
        Network/cryptography.h \
        Network/cryptography.h \
        Network/firewall.h \
        Network/firewall.h \
        Network/peerin.h \
        Network/peerin.h \
        Network/peerout.h \
        Network/peerout.h

FORMS += \
        Designer/freechat.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

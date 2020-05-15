QT       += gui
QT       += qml
QT       += network
QT       += widgets
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Freechat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

RC_ICONS = icon.ico

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17

SOURCES += \
        Bin/bin.cpp \
        Bin/freechat.cpp \
        Data/cryptography.cpp \
        Network/connectionf2f.cpp \
        Network/peerin.cpp \
        Network/peerout.cpp \
        Data/datasave.cpp \
        main.cpp

HEADERS += \
        Bin/bin.h \
        Data/cryptography.h \
        Network/connectionf2f.h \
        Bin/freechat.h \
        Network/peerin.h \
        Network/peerout.h \
        Data/datasave.h

FORMS += \
        freechat.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

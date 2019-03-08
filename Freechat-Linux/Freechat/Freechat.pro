#---------------------------------
#Copyright (C) 2019 Freechat Inc
#Contact: bogdyname@gmail.com
#---------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Freechat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        freechat.cpp \
        connection.cpp \
        userserver.cpp \
        userclient.cpp \
        datasave.cpp \
        multimedia.cpp \
        usernametable.cpp \
    sshsocket.cpp

HEADERS += \
        freechat.h \
        connection.h \
        userserver.h \
        userclient.h \
        datasave.h \
        multimedia.h \
        usernametable.h \
    sshsocket.h

FORMS += \
        freechat.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libssh2/bin/ -llibssh2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libssh2/bin/ -llibssh2d
else:unix: LIBS += -L$$PWD/libssh2/bin/ -lllibssh2

INCLUDEPATH += $$PWD/libssh2/include
DEPENDPATH += $$PWD/libsssh2/include

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

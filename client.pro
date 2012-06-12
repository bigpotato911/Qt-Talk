#-------------------------------------------------
#
# Project created by QtCreator 2012-06-11T10:29:49
#
#-------------------------------------------------

QT       += core gui
QT       += network
TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        logindialog.cpp \
    chatdialog.cpp

HEADERS  += logindialog.h \
    chatdialog.h

FORMS    += logindialog.ui \
    chatdialog.ui

RESOURCES += \
    client.qrc

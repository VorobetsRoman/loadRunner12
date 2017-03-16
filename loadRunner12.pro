#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T10:41:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = loadRunner12
TEMPLATE = app


SOURCES += main.cpp\
        loadrunner.cpp \
    mprogram.cpp \
    tablerecord.cpp

HEADERS  += loadrunner.h \
    mprogram.h \
    tablerecord.h

FORMS    += loadrunner.ui

RESOURCES += \
    buttons.qrc

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
    sourcedata.cpp \
    mprogram.cpp

HEADERS  += loadrunner.h \
    global_definitions.h \
    sourcedata.h \
    mprogram.h

FORMS    += loadrunner.ui

#-------------------------------------------------
#
# Project created by QtCreator 2023-04-02T12:00:21
#
#-------------------------------------------------

QT += charts
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MRC_gui
TEMPLATE = app
CONFIG += gnu++17


SOURCES += main.cpp\
        mrc_gui.cpp

HEADERS  += mrc_gui.h\
            ../src/MRC.hpp

#FORMS    += mrc_gui.ui

RESOURCES += \
    textfinder.qrc

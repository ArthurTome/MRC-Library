#-------------------------------------------------
#
# Project created by QtCreator 2023-04-02T12:00:21
#
#-------------------------------------------------

QT += charts
QT += core gui

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

TARGET = mrc_gui
TEMPLATE = app
CONFIG += c++20

LIBS += "/usr/local/lib/libfftw3f.a"

SOURCES += main.cpp\
        mrc_gui.cpp \
        psdtab.cpp \
        rxxtab.cpp \
        soctab.cpp

HEADERS  += mrc_gui.h\
            ../src/MRC.hpp \
            psdtab.h \
            rxxtab.h \
            soctab.h

#FORMS    += mrc_gui.ui

RESOURCES +=

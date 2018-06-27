#-------------------------------------------------
#
# Project created by QtCreator 2018-05-23T18:03:28
#
#-------------------------------------------------

QT       += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        myserver.cpp \
        mythread.cpp \
    inputthread.cpp \
    someotherclass.cpp \
    qcsvdatabase.cpp

HEADERS  += mainwindow.h \
        myserver.h \
        mythread.h \
    inputthread.h \
    someotherclass.h \
    qcsvdatabase.h

FORMS    += mainwindow.ui

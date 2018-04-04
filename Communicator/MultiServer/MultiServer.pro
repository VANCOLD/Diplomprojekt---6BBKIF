QT += core
QT -= gui
QT += network
#QT += testlib

CONFIG += c++11

TARGET = MultiServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp \
    mythread.cpp \
    someotherclass.cpp

HEADERS += \
    myserver.h \
    mythread.h \
    someotherclass.h

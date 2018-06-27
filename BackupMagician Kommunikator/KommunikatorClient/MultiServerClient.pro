QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = MultiServerClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp \
    communicator.cpp \
    inputthread.cpp

HEADERS += \
    myserver.h \
    communicator.h \
    inputthread.h

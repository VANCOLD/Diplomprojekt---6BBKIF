QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = MFWAServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../QtWebApp/QtWebApp/httpserver/httpserver.pri)

SOURCES += \
    src/communicator.cpp \
    src/helloworldcontroller.cpp \
    src/jsoncontroller.cpp \
    src/listdatacontroller.cpp \
    src/main.cpp \
    src/requestmapper.cpp

DISTFILES += \
    etc/webapp1.ini

HEADERS += \
    src/communicator.h \
    src/helloworldcontroller.h \
    src/jsoncontroller.h \
    src/listdatacontroller.h \
    src/requestmapper.h

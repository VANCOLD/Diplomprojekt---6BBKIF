QT += core
QT -= gui
#QT += network

CONFIG += c++11

TARGET = MFWAClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../QtWebApp/QtWebApp/httpserver/httpserver.pri)

SOURCES += \
    src/helloworldcontroller.cpp \
    src/jsoncontroller.cpp \
    src/listdatacontroller.cpp \
    src/main.cpp \
    src/requestmapper.cpp \
    src/communicator.cpp

DISTFILES += \
    etc/webapp1.ini

HEADERS += \
    src/helloworldcontroller.h \
    src/jsoncontroller.h \
    src/listdatacontroller.h \
    src/requestmapper.h \
    src/communicator.h

QT += core
QT -= gui

TARGET = QBackup
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    qdirnode.cpp \
    qbackupmanager.cpp \
    qlogger.cpp \
    qjsonparser.cpp

HEADERS += \
    qdirnode.h \
    qbackupmanager.h \
    qlogger.h \
    qjsonparser.h


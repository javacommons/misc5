QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = app01-$${QMAKE_HOST.arch}

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../lib01
LIBS +=        $$PWD/../lib01/liblib01-$${QMAKE_HOST.arch}.a

SOURCES += \
        main.cpp

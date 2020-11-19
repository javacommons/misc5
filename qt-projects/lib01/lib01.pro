QT -= gui

TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

TARGET = lib01-$${QMAKE_HOST.arch}

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    lib01.cpp

HEADERS += \
    lib01.hpp

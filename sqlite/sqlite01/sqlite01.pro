QT += core gui
QT += widgets

CONFIG += c++17
CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    sqlite01.cpp \
    sqlite01_widget.cpp

HEADERS += \
    sqlite01_common.h \
    sqlite01_widget.h

FORMS += \
    sqlite01_widget.ui

LIBS += -L$$PWD -lsqlite3 -lyaml-cpp

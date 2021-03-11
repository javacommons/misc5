QT -= gui
QT += network

CONFIG += c++11 console

#DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    cons01.cpp

LIBS += -L$$PWD -ldll01.dll

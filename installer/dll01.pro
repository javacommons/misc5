QT -= gui

TEMPLATE = lib
DEFINES += DLL01_LIBRARY

CONFIG += c++11
#CONFIG += staticlib
CONFIG += dll

SOURCES += \
    dll01.cpp

HEADERS += \
    dll01_global.h \
    dll01.h

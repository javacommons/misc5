QT -= gui

CONFIG += c++14 console
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    gc.cpp

LIBS += -lgc -lgccpp

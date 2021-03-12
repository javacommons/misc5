QT += core gui
QT += widgets
QT += network

CONFIG += c++11
CONFIG += console
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    common.h \
    widget.h

FORMS += \
    widget.ui

LIBS += -L$$PWD -ltidy -lpugixml

QT += quick
CONFIG += c++11
TARGET = qml02-$${QMAKE_HOST.arch}

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../common

SOURCES += \
        main.cpp \
        myobject.cpp

HEADERS += \
        myobject.hpp

RESOURCES += qml.qrc

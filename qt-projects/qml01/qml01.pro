QT += quick
CONFIG += c++11
TARGET = qml01-$${QMAKE_HOST.arch}

DEFINES += QT_DEPRECATED_WARNINGS

#CONFIG += qmltypes
#QML_IMPORT_NAME = Mine
#QML_IMPORT_MAJOR_VERSION = 1

INCLUDEPATH += $$PWD/../common

SOURCES += \
        main.cpp \
        myobject.cpp

HEADERS += \
    myobject.hpp

RESOURCES += qml.qrc

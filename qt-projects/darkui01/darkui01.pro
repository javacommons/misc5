QT -= gui
CONFIG += c++17 console
TARGET = cons001-$${QMAKE_HOST.arch}

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../common

SOURCES += \
        main.cpp

LIBS = -larchive -lz -lbz2 -llzma -liconv -lbcrypt -lexpat

QT -= gui

CONFIG += c++17 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ..

SOURCES += \
        main.cpp

QMAKE_LIBS += -lzmq

QT -= gui

CONFIG += c++17 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ..

SOURCES += \
        server.cpp

QMAKE_LIBS += -lzmq

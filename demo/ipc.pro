QT -= gui

CONFIG += c++17 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ..

HEADERS += json-ipc.h zmqipc.hpp httplib.h libarchive.h

SOURCES += \
        json-ipc.cpp \
        server.cpp \
        client.cpp \
        httplib.cc \
        zmqipc.cpp \
        libarchive.cpp

QMAKE_LIBS += -lzmq

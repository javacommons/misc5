QT -= gui

CONFIG += c++20 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ..

HEADERS += json-ipc.h zmqipc.hpp httplib.h

SOURCES += \
        json-ipc.cpp \
        server.cpp \
        client.cpp \
        httplib.cc \
        zmqipc.cpp

QMAKE_LIBS += -lzmq

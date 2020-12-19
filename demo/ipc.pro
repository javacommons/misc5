QT -= gui

CONFIG += c++20 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ..

HEADERS += zmqipc.hpp httplib.h

SOURCES += \
        server.cpp \
        client.cpp \
        httplib.cc \
        zmqipc.cpp

QMAKE_LIBS += -lzmq

QT -= gui

CONFIG += c++17 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ..

HEADERS += zmqipc.hpp

SOURCES += \
        client.cpp \
        zmqipc.cpp

QMAKE_LIBS += -lzmq

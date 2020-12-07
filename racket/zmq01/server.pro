QT -= gui

CONFIG += c++17 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ..

HEADERS += zmqipc.hpp

SOURCES += \
        server.cpp \
        zmqipc.cpp

QMAKE_LIBS += -lzmq

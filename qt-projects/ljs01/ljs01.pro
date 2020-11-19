TEMPLATE = app
CONFIG += console c++17
#CONFIG -= qt

TARGET = ljs01-$${QMAKE_HOST.arch}

DEFINES += LUA_LJS=1

INCLUDEPATH += $$PWD/../lua-binary/lib/ljsjit-$${QMAKE_HOST.arch}
QMAKE_LIBDIR += $$PWD/../lua-binary/lib/ljsjit-$${QMAKE_HOST.arch}
LIBS += -lljsjit

#INCLUDEPATH += $$PWD/../lua-binary/lib/ljs-$${QMAKE_HOST.arch}
#QMAKE_LIBDIR += $$PWD/../lua-binary/lib/ljs-$${QMAKE_HOST.arch}
#LIBS += -lljs

SOURCES += \
        main.cpp

TEMPLATE = app
CONFIG -= qt
CONFIG += console c++11

INCLUDEPATH += $$PWD/../common
INCLUDEPATH += $$PWD/../ChaiScript-5.8.6/include

#message($$QMAKE_QMAKE)
contains(QMAKE_QMAKE, .*\/qt5-static\/.*) {
    message( "[STATIC BUILD]" )
    DEFINES += STATIC_LINK_CHAI_STDLIB
} else {
    message( "[SHARED BUILD]" )
}

SOURCES += \
        main.cpp \
        mychaiscript.cpp

HEADERS += \
    mychaiscript.hpp

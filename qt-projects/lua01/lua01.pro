QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = lua01-$${QMAKE_HOST.arch}

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    sol/sol.hpp

SOURCES += \
    main.cpp

INCLUDEPATH += $$PWD/../lua-binary/lib/luajit-$${QMAKE_HOST.arch}
QMAKE_LIBDIR += $$PWD/../lua-binary/lib/luajit-$${QMAKE_HOST.arch}
LIBS += -lluajit

CONFIG += file_copies
myScripts.files = $$files(scripts/*.lua)
myScripts.path = $$OUT_PWD
COPIES += myScripts

DISTFILES += \
    scripts/hello.lua \
    scripts/json.lua

RESOURCES += \
    scripts.qrc

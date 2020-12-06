QT -= gui

CONFIG += c++17 console

MSYSTEM = $$(MSYSTEM)
TARGET_BIT = $$replace(MSYSTEM, "MINGW", "")
TARGET = app01-$${TARGET_BIT}bit

DEFINES += QT_DEPRECATED_WARNINGS

#INCLUDEPATH += $$PWD/../lib01
#LIBS +=        $$PWD/../lib01/liblib01-$${QMAKE_HOST.arch}.a

SOURCES += \
        main.cpp

QMAKE_LIBS += -larchive -lz -lbz2 -llzma -liconv -lbcrypt -lexpat -llz4 -lzstd

QT -= gui

CONFIG += c++17 console
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    json.cpp \
    json_parser.c

LIBS += -lwaxeye

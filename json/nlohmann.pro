QT -= gui

CONFIG += c++17 console
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    nlohmann.cpp

#LIBS += -lwaxeye

DISTFILES += \
    nlohmann.json

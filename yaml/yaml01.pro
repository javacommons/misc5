QT -= gui

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        yaml01.cpp

LIBS += -L$$PWD libyaml-cpp

yamls.path = $$OUT_PWD
yamls.files += $$PWD/main.yaml
INSTALLS += yamls

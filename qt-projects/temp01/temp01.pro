QT += gui network widgets
CONFIG += c++11 console
DEFINES += QT_DEPRECATED_WARNINGS

TARGET = $$TARGET-$${QMAKE_HOST.arch}

INCLUDEPATH += $$PWD/../common

SOURCES += \
        main.cpp

HEADERS += \
    ../common/qtcommon.hpp

DISTFILES += \
    post.sh

defineReplace(makeBashCommand) {
    CONFIG(debug,debug|release) {
        APP_BUILD_DIR=$${OUT_PWD}/debug
    } else {
        APP_BUILD_DIR=$${OUT_PWD}/release
    }
    return(env SRC_DIR=$${PWD} BLD_DIR=$${APP_BUILD_DIR} bash $$1)
}

post.commands += $$makeBashCommand($${PWD}/post.sh)
QMAKE_EXTRA_TARGETS += post

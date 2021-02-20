QT -= gui

CONFIG += c++17 console
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    generated/Java8Lexer.cpp \
    generated/Java8Parser.cpp \
    generated/Java8ParserBaseListener.cpp \
    generated/Java8ParserBaseVisitor.cpp \
    generated/Java8ParserListener.cpp \
    generated/Java8ParserVisitor.cpp \
    main.cpp

INCLUDEPATH += ./generated

LIBS += -lantlr4-runtime

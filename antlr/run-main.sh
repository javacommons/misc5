#! bash -uvx
antlr-4.9.1.exe -Dlanguage=Cpp -listener -visitor -o generated/ -package antlrcpptest TLexer.g4 TParser.g4
g++ -I generated main.cpp generated/*.cpp -lantlr4-runtime -o main && main

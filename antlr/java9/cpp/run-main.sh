#! bash -uvx
rm -rf generated
#antlr-4.9.1.exe -Dlanguage=Cpp -listener -visitor -o generated -package antlrcpptest ../Java9.g4
antlr-4.9.1.exe -Dlanguage=Cpp -listener -visitor -o generated -package antlrcpptest ../Java8Lexer.g4 ../Java8Parser.g4
g++ -I generated main.cpp generated/*.cpp -lantlr4-runtime -o main && main

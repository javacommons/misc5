#! bash -uvx

if [ ! -e antlr4 ]; then
    unzip ../../antlr-javascript-runtime-4.9.1.zip
fi
#rm -rf generated
#antlr-4.9.1.exe -Dlanguage=JavaScript -listener -visitor -o . -package antlrcpptest ../Java8Lexer.g4 ../Java8Parser.g4
antlr-4.9.1.exe -Dlanguage=JavaScript -listener -visitor -o . ../Java8Lexer.g4 ../Java8Parser.g4
#g++ -I generated main.cpp generated/*.cpp -lantlr4-runtime -o main && main
deno-1.7.5.exe run main.js

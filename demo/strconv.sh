#!bash -uvx
rm -rf obj Makefile
premake4 --file=strconv.premake4 --platform=x${MSYSTEM/MINGW/} gmake
make

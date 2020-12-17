#!bash -uvx
rm -rf obj strconv.make Makefile
premake4 --file=strconv.premake4 --platform=x${MSYSTEM/MINGW/} gmake
make

#! bash -uvx
premake4 --file=arch.premake4 gmake
rm -rf obj
make

#! bash -uvx
premake4 --file=arch.lua gmake
rm -rf obj
make

#! bash -uvx
rm -rf obj Makefile
premake4 --file=foo.premake4 gmake
make
_px32 foo.dll
rustc main.rs -L.&& ./main.exe

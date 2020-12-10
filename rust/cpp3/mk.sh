#! bash -uvx
rm -rf obj Makefile target
premake4 --file=foo.premake4 gmake
make
_px32 foo.dll
cargo run

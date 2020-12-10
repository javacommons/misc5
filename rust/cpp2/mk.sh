#! bash -uvx
premake4 --file=foo.premake4 gmake
make
rustc main.rs -L.&& ./main.exe

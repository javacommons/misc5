#! bash -uvx
g++ -c foo.cpp
ar rcs libfoo.a foo.o
rustc main.rs -L. -lstdc++ && ./main.exe

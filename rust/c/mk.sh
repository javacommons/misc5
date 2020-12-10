#! bash -uvx
gcc -c foo.c
ar rcs libfoo.a foo.o
rustc -L. main.rs && ./main.exe

#! bash -uvx
raco64 exe --gui -o Gauche-mingw-0.9.9-64bit-my-setup.exe Gauche-mingw-0.9.9-64bit-my-setup.rkt
raco64 distribute Gauche-mingw-0.9.9-64bit-my-setup.tmp Gauche-mingw-0.9.9-64bit-my-setup.exe
cp Gauche-mingw-0.9.9-64bit.zip Gauche-mingw-0.9.9-64bit-my-setup.tmp

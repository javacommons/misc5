#! bash -uvx
raco32 exe --gui -o Gauche-mingw-0.9.9-32bit-my-setup.exe Gauche-mingw-0.9.9-32bit-my-setup.rkt
raco32 distribute Gauche-mingw-0.9.9-32bit-my-setup.tmp Gauche-mingw-0.9.9-32bit-my-setup.exe
cp Gauche-mingw-0.9.9-32bit.zip Gauche-mingw-0.9.9-32bit-my-setup.tmp

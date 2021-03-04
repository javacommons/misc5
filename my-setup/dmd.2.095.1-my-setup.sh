#! bash -uvx
rm -rf dmd.2.095.1-my-setup.tmp dmd.2.095.1-my-setup.exe
raco exe --gui -o dmd.2.095.1-my-setup.exe dmd.2.095.1-my-setup.rkt
raco distribute dmd.2.095.1-my-setup.tmp dmd.2.095.1-my-setup.exe
cp dmd.2.095.1.zip dmd.2.095.1-my-setup.tmp

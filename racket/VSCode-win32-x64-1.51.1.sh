#! bash -uvx
raco exe --gui -o VSCode-win32-x64-1.51.1-my-setup.exe VSCode-win32-x64-1.51.1.rkt
raco distribute inst.tmp VSCode-win32-x64-1.51.1-my-setup.exe
cp -p VSCode-win32-x64-1.51.1.zip inst.tmp

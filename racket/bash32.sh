#! bash -uvx
raco32 exe bash32.rkt
cp -p bash32.exe bash64.exe
raco32 distribute bash32.tmp bash32.exe bash64.exe

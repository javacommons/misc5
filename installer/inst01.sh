#! bash -uvx
rm -rf inst01.exe inst01.tmp
raco exe inst01.rkt
raco distribute inst01.tmp inst01.exe
cp -p busybox.exe inst01.tmp/
cp -p curl-7.75.0-win32-mingw/bin/* inst01.tmp/
cp -p msys2-x86_64-latest.tar.xz inst01.tmp/
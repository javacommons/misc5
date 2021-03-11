#! bash -uvx
rm -rf inst01.exe inst01.tmp
raco exe --gui inst01.rkt
raco distribute inst01.tmp inst01.exe
rm -rf main01.exe
nim cpp --nimcache:./nimcache main01.nim
cp -p main01.exe inst01.tmp
cp -p busybox32.exe inst01.tmp/
cp -p curl-7.75.0-win32-mingw/bin/* inst01.tmp/

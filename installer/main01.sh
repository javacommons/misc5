#! bash -uvx
#rm -rf main01.exe ./nimcache
rm -rf main01.exe main01.tmp
#nim cpp -r --nimcache:./nimcache main01.nim
nim cpp --nimcache:./nimcache main01.nim
mkdir -p main01.tmp
cp -p main01.exe main01.tmp/
cp -p busybox32.exe main01.tmp/
cp -p curl-7.75.0-win32-mingw/bin/* main01.tmp/

#! bash -uvx
rm -f test.etag
rm -rf cons01.tmp
mkdir -p cons01.tmp
./mk.sh cons01
./rcedit-x86.exe cons01.exe --set-icon "./wxwidgets.ico"
cp -p cons01.exe cons01.tmp
cp -p busybox32.exe cons01.tmp/
cp -p curl-7.75.0-win32-mingw/bin/* cons01.tmp/

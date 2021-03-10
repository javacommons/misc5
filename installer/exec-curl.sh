#! bash -uvx
dart compile exe exec-curl.dart
rm -rf exec-curl.tmp
mkdir -p exec-curl.tmp
cp -p exec-curl.exe exec-curl.tmp/
cp -p busybox64.exe exec-curl.tmp/
cp -p curl-7.75.0-win64-mingw/bin/* exec-curl.tmp/

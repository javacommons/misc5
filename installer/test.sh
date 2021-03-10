#! bash -uvx
mkdir -p my-msys2.tmp
#./busybox.exe xz -dc msys2-x86_64-latest.tar.xz | ./busybox.exe tar -xf - -C my-msys2.tmp --strip-components 1
./busybox.exe tar -xf msys2-x86_64-latest.tar.xz -C my-msys2.tmp --strip-components 1

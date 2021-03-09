#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
    make \
    unzip \
    wget

cwd=`pwd`

rm -rf build
mkdir build
cd build
cmake -G "MSYS Makefiles" ..
make
cp -p libnative_add.dll ..

cd $cwd
dart --disable-analytics
dart run ffi.dart

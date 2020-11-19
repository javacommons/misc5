#! bash
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
	make

rm -rf build-chai
mkdir build-chai
cd build-chai
cmake -G "MSYS Makefiles" ../ChaiScript-5.8.6
make
cp -p *.dll $MINGW_PREFIX/bin/.

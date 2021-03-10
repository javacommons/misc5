#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
    make \
    subversion \
    unzip \
    wget

cwd=`pwd`

if [ ! -e curlpp ]; then
  svn export https://github.com/jpbarrette/curlpp/trunk curlpp
  rm -rf build-curlpp
  mkdir -p build-curlpp
  cd build-curlpp
  cmake -G "MSYS Makefiles" ../curlpp
  cmake --build . --config Release
  cp -rp ../curlpp/include/* $MINGW_PREFIX/include/
  cp -rp *.a $MINGW_PREFIX/lib/
  cp -rp *.dll $MINGW_PREFIX/bin/
fi

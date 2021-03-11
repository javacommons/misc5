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
  rm -rf build-curlpp.$MSYSTEM_CARCH
fi

if [ ! -e build-curlpp.$MSYSTEM_CARCH ]; then
  mkdir -p build-curlpp.$MSYSTEM_CARCH
  cd build-curlpp.$MSYSTEM_CARCH
  cmake -G "MSYS Makefiles" ../curlpp
  cmake --build . --config Release
  cp -rp ../curlpp/include/* $MINGW_PREFIX/include/
  cp -rp *.a $MINGW_PREFIX/lib/
  cp -rp *.dll $MINGW_PREFIX/bin/
  sed -e "s \prefix=.* prefix=$MINGW_PREFIX g" -e "s#echo lib/libcurlpp.a#echo \$prefix/lib/libcurlpp.a#g" extras/curlpp-config > ./curlpp-config
  cp -rp curlpp-config  $MINGW_PREFIX/bin/
fi

cp -p $MINGW_PREFIX/lib/libbrotlidec-static.a $MINGW_PREFIX/lib/libbrotlidec.a

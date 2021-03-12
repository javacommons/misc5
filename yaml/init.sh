#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-gcc \
	$MINGW_PACKAGE_PREFIX-cmake \
	$MINGW_PACKAGE_PREFIX-boost \
    git \
    make \
	subversion \
    unzip \
    wget

cwd=`pwd`

rm -rf yaml-cpp
svn export https://github.com/jbeder/yaml-cpp/trunk yaml-cpp
rm -rf yaml-cpp-build
mkdir -p yaml-cpp-build
cd yaml-cpp-build
cmake -G "MSYS Makefiles" -DYAML_BUILD_SHARED_LIBS=OFF ../yaml-cpp
cmake --build . --config Release

cd $cwd
cp -rp yaml-cpp/include/yaml-cpp $MINGW_PREFIX/include/
cp -rp yaml-cpp-build/*.a $MINGW_PREFIX/lib/

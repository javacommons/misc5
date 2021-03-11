#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-gcc \
	$MINGW_PACKAGE_PREFIX-cmake \
	$MINGW_PACKAGE_PREFIX-boost \
	$MINGW_PACKAGE_PREFIX-wxWidgets \
	$MINGW_PACKAGE_PREFIX-jbigkit \
    make \
    unzip \
	subversion \
    wget

cwd=`pwd`

rm -rf toml.hpp
svn export https://github.com/marzer/tomlplusplus/trunk/toml.hpp
cp -rp toml.hpp $MINGW_PREFIX/include

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

rm -rf sqlite_orm
svn export https://github.com/fnc12/sqlite_orm/trunk sqlite_orm
rm -rf $MINGW_PREFIX/include/sqlite_orm
cp -rp sqlite_orm/include/sqlite_orm $MINGW_PREFIX/include/
rm -rf tests
cp -rp sqlite_orm/tests .

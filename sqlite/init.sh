#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-gcc \
	$MINGW_PACKAGE_PREFIX-cmake \
	$MINGW_PACKAGE_PREFIX-boost \
	$MINGW_PACKAGE_PREFIX-sqlite3 \
	$MINGW_PACKAGE_PREFIX-tidy \
	$MINGW_PACKAGE_PREFIX-pugixml \
    git \
    make \
	subversion \
    unzip \
    wget

cwd=`pwd`

cd $cwd
rm -rf sqlite_orm
svn export https://github.com/fnc12/sqlite_orm/trunk sqlite_orm
rm -rf $MINGW_PREFIX/include/sqlite_orm
cp -rp sqlite_orm/include/sqlite_orm $MINGW_PREFIX/include/
rm -rf examples
cp -rp sqlite_orm/examples .
rm -rf tests
cp -rp sqlite_orm/tests .

cd $cwd
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

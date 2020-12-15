#! bash -uvx
PACKAGE_PREFIX="${MINGW_PACKAGE_PREFIX:-mingw-w64-x86_64}"
echo $PACKAGE_PREFIX
pacman -S --needed --noconfirm \
    subversion \
	$PACKAGE_PREFIX-boost \
	$PACKAGE_PREFIX-fltk \
	$PACKAGE_PREFIX-libarchive \
	$PACKAGE_PREFIX-postgresql \
	$PACKAGE_PREFIX-sqlite3 \
	$PACKAGE_PREFIX-zeromq
rm -rf fmt
svn export https://github.com/fmtlib/fmt/trunk/include/fmt
rm -rf $MINGW_PREFIX/include/fmt
cp -rp fmt $MINGW_PREFIX/include/
rm -rf nlohmann
svn export https://github.com/nlohmann/json/trunk/include/nlohmann
rm -rf $MINGW_PREFIX/include/nlohmann
cp -rp nlohmann $MINGW_PREFIX/include/
rm -f httplib.h
svn export https://github.com/yhirose/cpp-httplib/trunk/httplib.h
svn export https://github.com/yhirose/cpp-httplib/trunk/split.py
cp -p httplib.h $MINGW_PREFIX/include/
cp -p strconv.h  strconvQt.h  strutil.h  vardecl.h $MINGW_PREFIX/include/

#! bash -uvx
PACKAGE_PREFIX="${MINGW_PACKAGE_PREFIX:-mingw-w64-x86_64}"
echo $PACKAGE_PREFIX
pacman -S --needed --noconfirm \
	$PACKAGE_PREFIX-boost \
	$PACKAGE_PREFIX-fltk \
	$PACKAGE_PREFIX-libarchive \
	$PACKAGE_PREFIX-postgresql \
	$PACKAGE_PREFIX-sqlite3 \
	$PACKAGE_PREFIX-zeromq
rm -rf $MINGW_PREFIX/include/nlohmann
cp -rp nlohmann $MINGW_PREFIX/include/
cp -p strconv.h  strconvQt.h  strutil.h  vardecl.h $MINGW_PREFIX/include/
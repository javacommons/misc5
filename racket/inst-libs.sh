#! bash -uvx
PACKAGE_PREFIX="${MINGW_PACKAGE_PREFIX:-mingw-w64-x86_64}"
echo $PACKAGE_PREFIX
pacman -S --needed --noconfirm \
	$PACKAGE_PREFIX-boost \
	$PACKAGE_PREFIX-fltk \
	$PACKAGE_PREFIX-libarchive \
	$PACKAGE_PREFIX-postgresql \
	$PACKAGE_PREFIX-sqlite3
cp -rp nlohmann /mingw32/include/
cp -rp nlohmann /mingw64/include/

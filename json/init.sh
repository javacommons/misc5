#! bash -uvx
PACKAGE_PREFIX="${MINGW_PACKAGE_PREFIX:-mingw-w64-x86_64}"
echo $PACKAGE_PREFIX
pacman -S --needed --noconfirm \
    subversion \
	$PACKAGE_PREFIX-boost

rm -rf nlohmann
svn export https://github.com/nlohmann/json/trunk/include/nlohmann
rm -rf $MINGW_PREFIX/include/nlohmann
cp -rp nlohmann $MINGW_PREFIX/include/

rm -rf variant_json
svn export https://github.com/ce39906/self-practices/trunk/cppcode/variant_json
rm -rf $MINGW_PREFIX/include/vjson
mkdir -p $MINGW_PREFIX/include/vjson
cp -rp variant_json/*.h* $MINGW_PREFIX/include/vjson

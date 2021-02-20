#! bash -uvx
pacman -S --needed --noconfirm \
    subversion \
    make \
    $MINGW_PACKAGE_PREFIX-toolchain \
    $MINGW_PACKAGE_PREFIX-dlfcn

svn export https://github.com/ftk/quickjspp/trunk/quickjspp.hpp
install -m644 quickjspp.hpp "$MINGW_PREFIX/include"

#exit 0

rm -rf quickjs.tmp
svn export https://github.com/bellard/quickjs/trunk quickjs.tmp
cd quickjs.tmp
make LDEXPORT="-static -s"
install -m755 qjs qjsc "$MINGW_PREFIX/bin"
install -m644 libquickjs.a "$MINGW_PREFIX/lib"
mkdir -p "$MINGW_PREFIX/include/quickjs"
install -m644 quickjs.h quickjs-libc.h "$MINGW_PREFIX/include/quickjs"

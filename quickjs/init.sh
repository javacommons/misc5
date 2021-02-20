#! bash -uvx
pacman -S --needed --noconfirm \
    subversion \
    make \
    $MINGW_PACKAGE_PREFIX-toolchain \
    $MINGW_PACKAGE_PREFIX-dlfcn

rm -rf quickjs.tmp
svn export https://github.com/bellard/quickjs/trunk quickjs.tmp
cd quickjs.tmp
#mv Makefile Makefile.orig
#svn export https://github.com/mengmo/QuickJS-Windows-Build/trunk/Makefile
make LDEXPORT="-static -s"
install -m755 qjs qjsc "$MINGW_PREFIX/bin"
mkdir -p "$MINGW_PREFIX/lib/quickjs"
install -m644 libquickjs.a "$MINGW_PREFIX/lib/quickjs"
mkdir -p "$MINGW_PREFIX/include/quickjs"
install -m644 quickjs.h quickjs-libc.h "$MINGW_PREFIX/include/quickjs"

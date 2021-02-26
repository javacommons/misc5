#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
    unzip \
    wget

wget -nc https://github.com/javacommons/antlr-bin/releases/download/v4.9.1/antlr-4.9.1.exe
cp -p antlr-4.9.1.exe $MINGW_PREFIX/bin/
#wget -nc https://github.com/javacommons/antlr-bin/releases/download/v4.9.1/antlr-gui-4.9.1.exe

wget -nc https://www.antlr.org/download/antlr-javascript-runtime-4.9.1.zip

wget -nc https://www.antlr.org/download/antlr4-cpp-runtime-4.8-source.zip

#if [ ! -e antlr4-cpp-runtime-4.8-source ]; then
#    unzip -d antlr4-cpp-runtime-4.8-source antlr4-cpp-runtime-4.8-source.zip
#    cd antlr4-cpp-runtime-4.8-source
#    mkdir build
#    cd build
#    cmake -G "MSYS Makefiles" -D CMAKE_INSTALL_PREFIX=$MINGW_PREFIX ..
#    make
#    make install
#    cp -p $MINGW_PREFIX/lib/libantlr4-runtime.dll $MINGW_PREFIX/bin/
#    cp -rp $MINGW_PREFIX/include/antlr4-runtime/* $MINGW_PREFIX/include/
#fi

cwd=`pwd`

if [ ! -e antlr4-4.9.1 ]; then
    unzip antlr4-4.9.1.zip
    cd antlr4-4.9.1/runtime/Cpp
    rm -rf build
    mkdir build
    cd build
    cmake -G "MSYS Makefiles" -D CMAKE_INSTALL_PREFIX=$MINGW_PREFIX ..
    make
    make install
    cp -p $MINGW_PREFIX/lib/libantlr4-runtime.dll $MINGW_PREFIX/bin/
    cp -rp $MINGW_PREFIX/include/antlr4-runtime/* $MINGW_PREFIX/include/
fi

#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
    unzip \
    wget

wget -nc https://github.com/jcommons/win-binary/releases/download/dafault/deno-1.7.5.exe
cp -p deno-1.7.5.exe $MINGW_PREFIX/bin/

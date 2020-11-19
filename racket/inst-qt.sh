#! bash -uvx
PACKAGE_PREFIX="${MINGW_PACKAGE_PREFIX:-mingw-w64-x86_64}"
echo $PACKAGE_PREFIX
pacman -S --needed --noconfirm \
	make \
	$PACKAGE_PREFIX-toolchain \
	$PACKAGE_PREFIX-clang \
	$PACKAGE_PREFIX-qt5 \
	$PACKAGE_PREFIX-qt5-static \
	$PACKAGE_PREFIX-qt-creator \
	$PACKAGE_PREFIX-cmake \
	$PACKAGE_PREFIX-premake

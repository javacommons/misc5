#! bash
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-clang \
	$MINGW_PACKAGE_PREFIX-qt5 \
	$MINGW_PACKAGE_PREFIX-qt5-static \
	$MINGW_PACKAGE_PREFIX-qt-creator

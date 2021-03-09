#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
	$MINGW_PACKAGE_PREFIX-nim \
	$MINGW_PACKAGE_PREFIX-nimble \
    make \
    unzip \
    wget

# https://github.com/nimterop/nimterop
nimble install nimterop -y

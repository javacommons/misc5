#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
	$MINGW_PACKAGE_PREFIX-nim \
	$MINGW_PACKAGE_PREFIX-nimble \
    make \
    unzip \
	subversin \
    wget

# https://github.com/sinkingsugar/nimline
nimble install nimline -y

rm -rf NiGui
svn export https://github.com/trustable-code/NiGui/trunk NiGui

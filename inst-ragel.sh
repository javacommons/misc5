#! bash -uvx
echo $MINGW_PACKAGE_PREFIX
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-ragel \
	$MINGW_PACKAGE_PREFIX-graphviz

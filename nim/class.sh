#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-nim \
	$MINGW_PACKAGE_PREFIX-nimble
nim c -d:release -r class.nim

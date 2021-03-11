#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-cmake \
	$MINGW_PACKAGE_PREFIX-nim \
	$MINGW_PACKAGE_PREFIX-nimble \
	$MINGW_PACKAGE_PREFIX-boost \
	$MINGW_PACKAGE_PREFIX-wxWidgets \
    make \
    unzip \
	subversion \
    wget

cwd=`pwd`

# https://github.com/sinkingsugar/nimline
nimble install nimline -y

rm -rf NiGui
svn export https://github.com/trustable-code/NiGui/trunk NiGui

rm -rf boost.ui
#svn export https://github.com/kosenko/ui/trunk boost.ui

#cd boost.ui/build

#export WX_CONFIG=mingw32/bin/wx-config
#export WXWIN=$MINGW_PREFIX
#export BOOST_ROOT=$MINGW_PREFIX
#b2 libs/ui/build/ link=static
#b2 libs/ui/test/ link=static
#b2 libs/ui/example/ link=static
#b2 libs/ui/example/cpp11/ link=static

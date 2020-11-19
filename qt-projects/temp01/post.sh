#! bash -uvx
echo this is post.sh
pwd

pacman -S --needed --noconfirm \
        wget \
        unzip

echo \$SRC_DIR=$SRC_DIR
echo \$BLD_DIR=$BLD_DIR

cd $SRC_DIR
cp -p *.bxproj $BLD_DIR/..
pwd

cd $SRC_DIR/..
wget -nc https://github.com/wixtoolset/wix3/releases/download/wix3112rtm/wix311-binaries.zip
wix=wix311-binaries
[ ! -e $wix ] && unzip -d $wix $wix.zip
cd $wix
cp -p dark.* $BLD_DIR
cp -p *.dll  $BLD_DIR
(cd $BLD_DIR && ls dark.*)
(cd $BLD_DIR && ls *.dll)
(cd $BLD_DIR && ls ../*.bxproj)
pwd
cd $BLD_DIR
ls *.h
ls *.cpp
ls *.moc
ls *.o


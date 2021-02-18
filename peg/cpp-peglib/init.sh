#! bash -uvx
pacman -S --needed --noconfirm \
    wget

rm -f peglib.h
wget https://raw.githubusercontent.com/yhirose/cpp-peglib/master/peglib.h

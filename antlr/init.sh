#! bash -uvx
pacman -S --needed --noconfirm \
    wget

rm -f antlr-4.9.1.exe
wget https://github.com/javacommons/antlr-bin/releases/download/v4.9.1/antlr-4.9.1.exe

rm -f antlr-gui-4.9.1.exe
wget https://github.com/javacommons/antlr-bin/releases/download/v4.9.1/antlr-gui-4.9.1.exe

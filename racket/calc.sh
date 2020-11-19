#! bash -uvx
if [ "${MSYSTEM_CARCH}" = "i686" ]; then
  arch=x32
else
  arch=x64
fi
rm -f Makefile
premake4 --file=calc.premake4 --platform=$arch gmake
rm -rf obj
make
